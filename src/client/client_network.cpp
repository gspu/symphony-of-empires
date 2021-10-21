#ifdef unix
#	define _XOPEN_SOURCE_EXTENDED 1
#	include <netdb.h>
#	include <arpa/inet.h>
#endif
#include <sys/types.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <mutex>
/* Visual Studio does not know about UNISTD.H, Mingw does through */
#ifndef _MSC_VER
#	include <unistd.h>
#endif

#ifdef unix
#	include <poll.h>
#elif defined windows
/* Allow us to use deprecated functions like inet_addr */
#	define _WINSOCK_DEPRECATED_NO_WARNINGS
#	include <winsock2.h>
#	include <ws2def.h>
#	include <ws2tcpip.h>
/* MingW does not behave well with pollfd structures, however MSVC does */
#	ifndef _MSC_VER
typedef struct pollfd {
    SOCKET fd;
    SHORT events;
    SHORT revents;
} WSAPOLLFD, *PWSAPOLLFD, FAR *LPWSAPOLLFD;
WINSOCK_API_LINKAGE int WSAAPI WSAPoll(LPWSAPOLLFD fdArray, ULONG fds, INT timeout);
#	endif
#endif

#ifdef windows
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

#include "client_network.hpp"
#include "../actions.hpp"
#include "../unit.hpp"
#include "../diplomacy.hpp"
#include "../world.hpp"
#include "../io_impl.hpp"
#include "game_state.hpp"

#include <chrono>
#include <thread>

Client* g_client = nullptr;
Client::Client(std::string host, const unsigned port) {
    g_client = this;

    // Initialize WSA
#ifdef windows
    WSADATA data;
    if(WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        print_error("WSA code: %u", WSAGetLastError());
        throw std::runtime_error("Cannot start WSA");
    }
#endif
    
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host.c_str());
    addr.sin_port = htons(port);
    
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd == INVALID_SOCKET) {
#ifdef windows
        print_error("WSA Code: %u", WSAGetLastError());
        WSACleanup();
#endif
        throw SocketException("Cannot create client socket");
    }
    
    if(connect(fd, (sockaddr*)&addr, sizeof(addr)) != 0) {
#ifdef unix
        close(fd);
#elif defined windows
        print_error("WSA Code: %u", WSAGetLastError());
        closesocket(fd);
#endif
        throw SocketException("Cannot connect to server");
    }
    
    // Launch the receive and send thread
    net_thread = std::thread(&Client::net_loop, this);
    has_snapshot = false;
}

// The server assumes all clients are able to handle all events regardless of anything
// if the client runs out of memory it needs to disconnect and then reconnect in order
// to establish a new connection; since the server won't hand out snapshots - wait...
// if you need snapshots for any reason (like desyncs) you can request with ActionType::SNAPSHOT
void Client::net_loop(void) {
    // Receive the first snapshot of the world
    {
        g_world->world_mutex.lock();
        Packet packet = Packet(fd);
        packet.recv();
        Archive ar = Archive();
        ar.set_buffer(packet.data(), packet.size());
        ::deserialize(ar, g_world);
        g_world->world_mutex.unlock();
    }

    {
        Archive ar = Archive();

        ActionType action = ActionType::CONNECT;
        ::serialize(ar, &action);
        ::serialize(ar, &username);

        Packet packet = Packet(fd);
        packet.data(ar.get_buffer(), ar.size());
        packet.send();
    }
    
    has_snapshot = true;
    
    try {
        ActionType action;
        
#ifdef unix
        struct pollfd pfd;
        pfd.fd = fd;
        pfd.events = POLLIN;
#endif
        while(1) {
            // Check if we need to read packets
#ifdef unix
            int has_pending = poll(&pfd, 1, 10);
#elif defined windows
            u_long has_pending = 0;
            ioctlsocket(fd, FIONREAD, &has_pending);
#endif

            // Conditional of above statements
#ifdef unix
            if(pfd.revents & POLLIN || has_pending) {
#elif defined windows
            if(has_pending) {
#endif
                Packet packet = Packet(fd);
                Archive ar = Archive();

                // Obtain the action from the server
                packet.recv();
                ar.set_buffer(packet.data(), packet.size());
                ar.rewind();
                ::deserialize(ar, &action);

                // Ping from server, we should answer with a pong!
                std::lock_guard<std::recursive_mutex> lock(g_world->world_mutex);
                switch(action) {
                case ActionType::PONG: {
                    packet.send(&action);
                    print_info("Received ping, responding with pong!");
                } break;
                // Update/Remove/Add Actions
                // These actions all follow the same format they give a specialized ID for the index
                // where the operated object is or should be; this allows for extreme-level fuckery
                // like ref-name changes in the middle of a game in the case of updates.
                //
                // After the ID the object in question is given in a serialized form, in which the
                // deserializer will deserialize onto the final object; after this the operation
                // desired is done.
                case ActionType::NATION_UPDATE: {
                    Nation* nation;
                    ::deserialize(ar, &nation);
                    if(nation == nullptr)
                        throw ClientException("Unknown nation");
                    ::deserialize(ar, nation);
                } break;
                case ActionType::NATION_ENACT_POLICY: {
                    Nation* nation;
                    ::deserialize(ar, &nation);
                    if(nation == nullptr)
                        throw ClientException("Unknown nation");
                    Policies policy;
                    ::deserialize(ar, &policy);
                    nation->current_policy = policy;
                } break;
                // TODO: There is a problem with this
                // TODO: It throws serializer errors but idk where, maybe the server?
                case ActionType::PROVINCE_UPDATE: {
                    Province* province;
                    ::deserialize(ar, &province);
                    if(province == nullptr)
                        throw ClientException("Unknown province");
                    ::deserialize(ar, province);
                } break;
                case ActionType::PRODUCT_ADD: {
                    Product* product = new Product();
                    ::deserialize(ar, product);
                    g_world->insert(product);

                    // NOTE: The stockpile will later be synchronized on a PROVINCE_UPDATE
                    // to the actual value by the server
                    for(auto& province: g_world->provinces) {
                        province->stockpile.push_back(0);
                    }
                    print_info("New product of good type %s", product->good->name.c_str());
                } break;
                case ActionType::PRODUCT_UPDATE: {
                    Product* product;
                    ::deserialize(ar, &product);
                    if(product == nullptr)
                        throw ClientException("Unknown product");
                    ::deserialize(ar, product);
                } break;
                case ActionType::PRODUCT_REMOVE: {
                    Product* product;
                    ::deserialize(ar, &product);
                    g_world->remove(product);
                } break;
                case ActionType::UNIT_UPDATE: {
                    Unit* unit;
                    ::deserialize(ar, &unit);
                    if(unit == nullptr)
                        throw ClientException("Unknown unit");
                    ::deserialize(ar, unit);
                } break;
                case ActionType::UNIT_ADD: {
                    Unit* unit = new Unit();
                    ::deserialize(ar, unit);
                    g_world->insert(unit);
                    print_info("New unit of %s", unit->owner->name.c_str());
                } break;
                case ActionType::BUILDING_UPDATE: {
                    Building* building;
                    ::deserialize(ar, &building);
                    if(building == nullptr)
                        throw ClientException("Unknown building");
                    ::deserialize(ar, building);
                } break;
                case ActionType::BUILDING_ADD: {
                    Building* building = new Building();
                    ::deserialize(ar, building);
                    g_world->insert(building);

                    if(building->get_owner(*g_world) != nullptr) {
                        print_info("New building property of %s", building->get_owner(*g_world)->name.c_str());
                    }
                } break;
                case ActionType::BUILDING_REMOVE: {
                    Building* building;
                    ::deserialize(ar, &building);

                    if(building->get_owner(*g_world) != nullptr) {
                        print_info("Remove building property of %s", building->get_owner(*g_world)->name.c_str());
                    }

                    if(building->type->is_factory == true) {
                        building->delete_factory(*g_world);
                    }
                    
                    g_world->remove(building);
                    delete building;
                } break;
                case ActionType::TREATY_ADD: {
                    Treaty* treaty = new Treaty();
                    ::deserialize(ar, treaty);
                    g_world->treaties.push_back(treaty);
                    print_info("%s: Drafted new treaty", treaty->sender->name.c_str());
                    for(const auto& status: treaty->approval_status) {
                        print_info("- %s", status.first->name.c_str());
                    }
                } break;
                case ActionType::WORLD_TICK: {
                    extern void client_update_on_tick(void);
                    client_update_on_tick();
                    g_world->time++;
                } break;
                case ActionType::TILE_UPDATE: {
                    // get_tile is already mutexed
                    std::pair<size_t, size_t> coord;
                    ::deserialize(ar, &coord.first);
                    ::deserialize(ar, &coord.second);
                    ::deserialize(ar, &g_world->get_tile(coord.first, coord.second));

                    std::lock_guard<std::recursive_mutex> lock(g_world->changed_tiles_coords_mutex);
                    g_world->nation_changed_tiles.push_back(&g_world->get_tile(coord.first, coord.second));
                } break;
                case ActionType::PROVINCE_COLONIZE: {
                    Province* province;
                    ::deserialize(ar, &province);
                    if(province == nullptr)
                        throw ClientException("Unknown province");
                    ::deserialize(ar, province);
                } break;
                default:
                    break;
                }
            }

            // Client will also flush it's queue to the server
            std::lock_guard<std::mutex> lock(packet_mutex);
            while(!packet_queue.empty()) {
                print_info("Network: sending packet");
                Packet elem = packet_queue.front();
                packet_queue.pop_front();

                elem.stream = SocketStream(fd);
                elem.send();
            }
            packet_queue.clear();
        }
    } catch(ClientException& e) {
        print_error("Except: %s", e.what());
    }
}

// Waits to receive the server initial world snapshot
void Client::wait_for_snapshot(void) {
    while(!has_snapshot) {
        // Just wait...
    }
}

Client::~Client() {
#ifdef windows
    closesocket(fd);
    WSACleanup();
#else
    close(fd);
#endif
    net_thread.join();
}
