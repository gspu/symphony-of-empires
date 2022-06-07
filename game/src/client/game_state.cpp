// Symphony of Empires
// Copyright (C) 2021, Symphony of Empires contributors
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// ----------------------------------------------------------------------------
// Name:
//      client/game_state.cpp
//
// Abstract:
//      Does some important stuff.
// ----------------------------------------------------------------------------

#include <cstdint>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <filesystem>

#ifdef _MSC_VER
// Required before GL/gl.h
#   ifndef _WINDOWS_
#   	define WIN32_LEAN_AND_MEAN 1
#       ifndef NOMINMAX
#	        define NOMINMAX 1
#       endif
#       include <windows.h>
#       undef WIN32_LEAN_AND_MEAN
#   endif
#endif

#include <GL/glew.h>
// MSVC does not know about glext, mingw does so we just use this ifdef
#ifndef _MSC_VER
#   include <GL/glext.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

#include "eng3d/ui/ui.hpp"
#include "eng3d/ui/input.hpp"
#include "eng3d/ui/image.hpp"
#include "eng3d/ui/progress_bar.hpp"
#include "eng3d/audio.hpp"
#include "eng3d/locale.hpp"
#include "eng3d/event.hpp"
#include "eng3d/path.hpp"
#include "eng3d/serializer.hpp"
#include "eng3d/material.hpp"
#include "eng3d/model.hpp"
#include "eng3d/texture.hpp"
#include "eng3d/log.hpp"
#include "eng3d/camera.hpp"

#include "client/game_state.hpp"
#include "good.hpp"
#include "io_impl.hpp"
#include "product.hpp"
#include "world.hpp"
#include "client/client_network.hpp"
#include "client/interface/decision.hpp"
#include "client/interface/lobby.hpp"
#include "client/interface/top_window.hpp"
#include "client/interface/treaty.hpp"
#include "client/interface/map_dev_view.hpp"
#include "client/interface/army.hpp"
#include "client/interface/building.hpp"
#include "client/interface/minimap.hpp"
#include "client/interface/profiler_view.hpp"
#include "client/map.hpp"
#include "client/map_render.hpp"
#include "server/server_network.hpp"
#include "client/interface/main_menu.hpp"

void GameState::play_nation() {
    current_mode = MapMode::NORMAL;

    const auto& capital = this->world->provinces[this->curr_nation->capital_id];
    map->camera->set_pos(capital.box_area.right, capital.box_area.bottom);
    map->map_render->update_visibility();

    // Make topwindow
    top_win = new Interface::TopWindow(*this);
    minimap = new Interface::Minimap(*this, -400, -200, UI::Origin::LOWER_RIGHT_SCREEN);
    Eng3D::Log::debug("game", "Selecting nation " + this->curr_nation->ref_name);
    g_client->send(Action::SelectNation::form_packet(*this->curr_nation));

    // Set AI to all off
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_do_cmd_troops = false;
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_controlled = false;
    this->curr_nation->ai_controlled = false;
    this->client->send(Action::AiControl::form_packet(*this->curr_nation));
}

std::shared_ptr<Eng3D::Texture> GameState::get_nation_flag(const Nation& nation) {
    Nation::Id id = world->get_id(nation);
    return map->nation_flags[id];
}

void handle_event(Input& input, GameState& gs) {
    std::pair<int, int>& mouse_pos = input.mouse_pos;
    UI::Context* ui_ctx = gs.ui_ctx;

    int& width = gs.width;
    int& height = gs.height;

    // Check window size every update
    //   - needed cause the window sometimes changes size without calling the change window size event
    SDL_GetWindowSize(gs.window, &width, &height);
    gs.ui_ctx->resize(width, height);
    if(gs.map != nullptr)
        gs.map->camera->set_screen(width, height);

    SDL_Event event;
    bool click_on_ui = false;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_CONTROLLERDEVICEADDED:
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(gs.show_ui) {
                click_on_ui = ui_ctx->check_hover(mouse_pos.first, mouse_pos.second);
                if(event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&mouse_pos.first, &mouse_pos.second);
                    ui_ctx->check_drag(mouse_pos.first, mouse_pos.second);
                }
            }
            
            if(event.button.button == SDL_BUTTON_MIDDLE)
                input.middle_mouse_down = true;
            break;
        case SDL_JOYBUTTONDOWN:
            if(gs.show_ui) {
                ui_ctx->check_drag(mouse_pos.first, mouse_pos.second);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            SDL_GetMouseState(&mouse_pos.first, &mouse_pos.second);
            if(event.button.button == SDL_BUTTON_MIDDLE) {
                input.middle_mouse_down = false;
                break;
            }

            if(gs.show_ui) {
                click_on_ui = ui_ctx->check_click(mouse_pos.first, mouse_pos.second);
                if(!click_on_ui && gs.current_mode != MapMode::NO_MAP) {
                    gs.map->handle_click(gs, event);
                }
            }

            if(click_on_ui) {
                std::scoped_lock lock(gs.sound_lock);
                auto entries = gs.package_man->get_multiple_prefix("sfx/click");
                if(!entries.empty())
                    gs.sound_queue.push_back(new Eng3D::Audio(entries[std::rand() % entries.size()]->get_abs_path()));
            }
            break;
        case SDL_JOYBUTTONUP:
            if(gs.show_ui) {
                click_on_ui = ui_ctx->check_click(mouse_pos.first, mouse_pos.second);
                if(!click_on_ui && gs.current_mode != MapMode::NO_MAP) {
                    gs.map->handle_click(gs, event);
                }
            }

            if(click_on_ui) {
                std::scoped_lock lock(gs.sound_lock);
                auto entries = gs.package_man->get_multiple_prefix("sfx/click");
                if(!entries.empty())
                    gs.sound_queue.push_back(new Eng3D::Audio(entries[std::rand() % entries.size()]->get_abs_path()));
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouse_pos.first, &mouse_pos.second);
            if(gs.show_ui) {
                click_on_ui = ui_ctx->check_hover(mouse_pos.first, mouse_pos.second);
            }
            break;
        case SDL_MOUSEWHEEL:
            SDL_GetMouseState(&mouse_pos.first, &mouse_pos.second);
            if(gs.show_ui) {
                ui_ctx->check_hover(mouse_pos.first, mouse_pos.second);
                click_on_ui = ui_ctx->check_wheel(mouse_pos.first, mouse_pos.second, event.wheel.y * 6);
            }
            break;
        case SDL_TEXTINPUT:
            if(gs.show_ui) {
                ui_ctx->check_text_input((const char*)&event.text.text);
            }
            break;
        case SDL_KEYDOWN:
            switch(Eng3D::Keyboard::from_sdlk(event.key.keysym.sym)) {
            case Eng3D::Keyboard::Key::F1:
                gs.show_ui = !gs.show_ui;
                break;
            case Eng3D::Keyboard::Key::F2:
                if(gs.current_mode == MapMode::NORMAL) {
                    if(gs.profiler_view) {
                        delete gs.profiler_view;
                        gs.profiler_view = nullptr;
                    } else {
                        gs.profiler_view = new Interface::ProfilerView(gs);
                    }
                }
                break;
            case Eng3D::Keyboard::Key::F3:
                if(gs.editor)
                    break;

                if(gs.current_mode == MapMode::NORMAL) {
                    if(input.select_pos.first < gs.world->width || input.select_pos.second < gs.world->height) {
                        const Tile& tile = gs.world->get_tile(input.select_pos.first, input.select_pos.second);
                        if(tile.province_id >= gs.world->provinces.size()) {
                            break;
                        }

                        new Interface::BuildingBuildView(gs, input.select_pos.first, input.select_pos.second, true, gs.world->provinces[tile.province_id]);
                    }
                }
                break;
            case Eng3D::Keyboard::Key::F4:
                if(!click_on_ui) {
                    LuaAPI::invoke_registered_callback(gs.world->lua, "ai_settings_window_invoke");
                }
                break;
            case Eng3D::Keyboard::Key::F5:
                if(gs.editor)
                    break;

                if(gs.current_mode == MapMode::NORMAL) {
                    gs.paused = !gs.paused;
                    if(gs.paused) {
                        ui_ctx->prompt("Control", "Unpaused");
                    } else {
                        ui_ctx->prompt("Control", "Paused");
                    }
                }
                break;
            case Eng3D::Keyboard::Key::BACKSPACE:
                ui_ctx->check_text_input(nullptr);
                break;
            default:
                break;
            }
            break;
        case SDL_JOYAXISMOTION:
            ui_ctx->check_hover(gs.input.mouse_pos.first, gs.input.mouse_pos.second);
            break;
        case SDL_QUIT:
            gs.run = false;
            break;
        default:
            break;
        }

        if(gs.current_mode != MapMode::NO_MAP && !click_on_ui) {
            gs.map->update(event, input, ui_ctx, gs);
        }
    }
    ui_ctx->clear_dead();
}

void GameState::send_command(Archive& archive) {
    std::scoped_lock lock(client->pending_packets_mutex);

    Eng3D::Networking::Packet packet = Eng3D::Networking::Packet(g_client->get_fd());
    packet.data(archive.get_buffer(), archive.size());
    client->pending_packets.push_back(packet);
}

#include "eng3d/utils.hpp"
void save(GameState& gs) {
    if(gs.editor) {
        std::filesystem::create_directory("editor");
        std::filesystem::create_directory("editor/lua");
        std::filesystem::create_directory("editor/lua/entities");
        std::filesystem::create_directory("editor/map");
        // Provinces
        auto fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/provinces.lua", "wt"), fclose);
        size_t cnt = 0;
        fprintf(fp.get(), "-- Generated by editor, do not edit manually! :)\n");
        for(const auto& building_type : gs.world->building_types)
            fprintf(fp.get(), "bt_%s=BuildingType:get(\"%s\")\n", building_type.ref_name.c_str(), building_type.ref_name.c_str());
        for(const auto& unit_type : gs.world->unit_types)
            fprintf(fp.get(), "ut_%s=UnitType:get(\"%s\")\n", unit_type.ref_name.c_str(), unit_type.ref_name.c_str());
        for(const auto& terrain_type : gs.world->terrain_types)
            fprintf(fp.get(), "tt_%s=TerrainType:get(\"%s\")\n", terrain_type.ref_name.c_str(), terrain_type.ref_name.c_str());
        for(const auto& pop_type : gs.world->pop_types)
            fprintf(fp.get(), "pt_%s=PopType:get(\"%s\")\n", pop_type.ref_name.c_str(), pop_type.ref_name.c_str());
        for(const auto& culture : gs.world->cultures)
            fprintf(fp.get(), "c_%s=Culture:get(\"%s\")\n", culture.ref_name.c_str(), culture.ref_name.c_str());
        for(const auto& religion : gs.world->religions)
            fprintf(fp.get(), "r_%s=Religion:get(\"%s\")\n", religion.ref_name.c_str(), religion.ref_name.c_str());
        for(const auto& nation : gs.world->nations)
            fprintf(fp.get(), "n_%s=Nation:get(\"%s\")\n", nation.ref_name.c_str(), nation.ref_name.c_str());
        for(auto& province : gs.world->provinces) {
            if(province.neighbours.empty()) continue;

            if(province.terrain_type->is_water_body && (province.controller != nullptr || Nation::is_valid(province.owner_id))) {
                for(auto& terrain : gs.world->terrain_types) {
                    if(terrain.is_water_body) continue;
                    province.terrain_type = &terrain;
                    break;
                }
            }

            // RGO
            const uint32_t color = bswap32((province.color & 0x00ffffff) << 8);
            std::string rgo_size_out = "";
            for(Good::Id id = 0; id < province.rgo_size.size(); id++) {
                const auto& good = gs.world->goods[id];
                auto size = province.rgo_size[id];
                if(size != 0) {
                    rgo_size_out += "{" + good.ref_name + ",";
                    rgo_size_out += std::to_string(size) + "},";
                }
            }
            fprintf(fp.get(), "province=Province:new{ref_name=\"%s\",name=_(\"%s\"),color=0x%x,terrain=tt_%s,rgo_size={%s}}\n",
                province.ref_name.c_str(),
                province.name.c_str(),
                (unsigned int)color,
                province.terrain_type->ref_name.c_str(),
                rgo_size_out.c_str());
            fprintf(fp.get(), "province:register()\n");
            for(const auto& building_type : gs.world->building_types) {
                Building& building = province.buildings[gs.world->get_id(building_type)];
                if(building.level) {
                    building.level = 1;
                    fprintf(fp.get(), "province:update_building(bt_%s,%f)\n", building_type.ref_name.c_str(), building.level);
                }
            }
            // POPs
            for(const auto& pop : province.pops)
                fprintf(fp.get(), "province:add_pop(pt_%s,c_%s,r_%s,%f,%f)\n", pop.type->ref_name.c_str(), pop.culture->ref_name.c_str(), pop.religion->ref_name.c_str(), pop.size, pop.literacy);
            // Nuclei of the provinces
            for(const auto& nucleus_id : province.nuclei)
                fprintf(fp.get(), "province:add_nucleus(n_%s)\n", gs.world->nations[nucleus_id].ref_name.c_str());
            // Give province to owner
            if(Nation::is_valid(province.owner_id)) {
                fprintf(fp.get(), "province:give_to(n_%s)\n", gs.world->nations[province.owner_id].ref_name.c_str());
                if(gs.world->nations[province.owner_id].capital_id == gs.world->get_id(province))
                    fprintf(fp.get(), "n_%s:set_capital(province)\n", gs.world->nations[province.owner_id].ref_name.c_str());
            }
            // Units
            for(const auto unit_id : province.get_units()) {
                auto& unit = g_world->unit_manager.units[unit_id];
                // Units can't exceed max health
                if(unit.size > unit.type->max_health)
                    unit.size = unit.type->max_health;
                fprintf(fp.get(), "province:add_unit(ut_%s,%zu)\n", unit.type->ref_name.c_str(), (size_t)unit.size);
            }
            cnt++;
        }
        if(!cnt)
            fprintf(fp.get(), "-- No provinces? Please add some!\n");
        fp.reset();

        // Terrain types
        fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/terrain_types.lua", "wt"), fclose);
        cnt = 0;
        for(const auto& terrain_type : gs.world->terrain_types) {
            const uint32_t color = bswap32((terrain_type.color & 0x00ffffff) << 8);
            fprintf(fp.get(), "TerrainType:new{ref_name=\"%s\",name=_(\"%s\"),color=0x%x,is_water_body=%s}:register()\n", terrain_type.ref_name.c_str(), terrain_type.name.c_str(), (unsigned int)color, terrain_type.is_water_body ? "true" : "false");
            cnt++;
        }
        if(!cnt)
            fprintf(fp.get(), "-- No terrain types? - add some!\n");
        fp.reset();

        // Religions
        fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/religions.lua", "wt"), fclose);
        cnt = 0;
        for(const auto& religion : gs.world->religions) {
            const uint32_t color = bswap32((religion.color & 0x00ffffff) << 8);
            fprintf(fp.get(), "Religion:new{ref_name=\"%s\",name=_(\"%s\"),color=0x%x}:register()\n", religion.ref_name.c_str(), religion.name.c_str(), (unsigned int)color);
            cnt++;
        }
        if(!cnt)
            fprintf(fp.get(), "-- No religions!, add atleast 1 :)\n");
        fp.reset();

        // Pop types
        fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/pop_types.lua", "wt"), fclose);
        cnt = 0;
        for(const auto& pop_type : gs.world->pop_types) {
            std::string extra_arg = "";
            switch(pop_type.group) {
            case PopGroup::BURGEOISE: extra_arg = ",is_burgeoise=true"; break;
            case PopGroup::FARMER: extra_arg = ",is_farmer=true"; break;
            case PopGroup::LABORER: extra_arg = ",is_laborer=true"; break;
            case PopGroup::SLAVE: extra_arg = ",is_slave=true"; break;
            default: break;
            }
            fprintf(fp.get(), "PopType:new{ ref_name=\"%s\",name=_(\"%s\"),social_value=%f%s}\n", pop_type.ref_name.c_str(), pop_type.name.c_str(), pop_type.social_value, extra_arg.c_str());
            cnt++;
        }
        if(!cnt)
            fprintf(fp.get(), "-- No pop classes (there must be atleast 1!)\n");
        fp.reset();

        // Unit types
        fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/unit_types.lua", "wt"), fclose);
        cnt = 0;
        fprintf(fp.get(), "local v = {}\n");
        for(const auto& unit_type : gs.world->unit_types) {
            if(unit_type.is_ground == true && unit_type.is_naval == false) {
                fprintf(fp.get(), "v=UnitType:new{ref_name=\"%s\",name=_(\"%s\"),defense=%f,attack=%f,health=%f,speed=%f}\n", unit_type.ref_name.c_str(), unit_type.name.c_str(), unit_type.defense, unit_type.attack, unit_type.max_health, unit_type.speed);
            } else if(unit_type.is_ground == false && unit_type.is_naval == true) {
                fprintf(fp.get(), "v=BoatType:new{ref_name=\"%s\",name=_(\"%s\"),defense=%f,attack=%f,health=%f,speed=%f}\n", unit_type.ref_name.c_str(), unit_type.name.c_str(), unit_type.defense, unit_type.attack, unit_type.max_health, unit_type.speed);
            } else if(unit_type.is_ground == true && unit_type.is_naval == true) {
                fprintf(fp.get(), "v=AirplaneType:new{ref_name=\"%s\",name=_(\"%s\"),defense=%f,attack=%f,health=%f,speed=%f}\n", unit_type.ref_name.c_str(), unit_type.name.c_str(), unit_type.defense, unit_type.attack, unit_type.max_health, unit_type.speed);
            }
            fprintf(fp.get(), "v:register()\n");
            for(const auto& good : unit_type.req_goods)
                fprintf(fp.get(), "v:requires_good(Good:get(\"%s\"), %f)\n", good.first->ref_name.c_str(), good.second);
            cnt++;
        }
        if(!cnt)
            fprintf(fp.get(), "-- No unit types - add some!\n");
        fp.reset();

        // Good types
        fp = std::unique_ptr<FILE, int (*)(FILE*)>(fopen("editor/lua/entities/good_types.lua", "wt"), fclose);
        fprintf(fp.get(), "-- Generated by editor :)\n");
        for(const auto& good_type : gs.world->goods)
            fprintf(fp.get(), "GoodType:new{ref_name=\"%s\",name=_(\"%s\")}:register()\n", good_type.ref_name.c_str(), good_type.name.c_str());
        if(!cnt)
            fprintf(fp.get(), "-- Economy.exe has stopped working and the stock market has been /dev/null -ed, add some goods? :)\n");
        fp.reset();

        gs.ui_ctx->prompt("Save", "Editor data saved! (check editor folder)");
    } else {
        Archive ar = Archive();
        ::serialize(ar, gs.world);
        ar.to_file("default.sc4");
        gs.ui_ctx->prompt("Save", "Saved sucessfully!");
    }
}

void handle_popups(std::vector<Event>& displayed_events, std::vector<Treaty*>& displayed_treaties, GameState& gs) {
    // Put popups
    // Event + Decision popups
    for(auto& msg : gs.curr_nation->inbox) {
        // Check that the event is not already displayed to the user
        auto iter = std::find_if(displayed_events.begin(), displayed_events.end(), [&msg](const auto& e) { return e.ref_name == msg.ref_name; });
        if(iter != displayed_events.end()) continue;

        new Interface::DecisionWindow(gs, msg);
        displayed_events.push_back(msg);
    }

    for(auto& treaty : gs.world->treaties) {
        // Check that the treaty is not already displayed
        auto iter = std::find_if(displayed_treaties.begin(), displayed_treaties.end(), [&treaty](const auto& e) { return e == treaty; });
        if(iter != displayed_treaties.end()) continue;
        // Do not mess with treaties we don't partake in, hehe
        if(!treaty->does_participate(*gs.curr_nation)) continue;
        // Must participate in treaty
        new Interface::TreatyChooseWindow(gs, treaty);
        displayed_treaties.push_back(treaty);
    }
}

void GameState::update_on_tick() {
    world->profiler.start("UI_TICK");
    ui_ctx->do_tick();
    world->profiler.stop("UI_TICK");

    /// @todo This is inefficient and we should only update **when** needed
    if(current_mode != MapMode::NO_MAP) {
        map->update_mapmode();
        //map->create_labels();
    }
}

/// @todo Don't run this thread if not needed (i.e non-host-mode)
void GameState::world_thread() {
    while(this->run) {
        // Gamestate thread hasn't acknowledged the updated tick just yet
        while(this->paused) {
            if(!this->run) {
                Eng3D::Log::debug("world_thread", "Unpaused game");
                break;
            }
        }

        // Only run the economy simulation of host mode is ON, otherwise don't :-)
        const auto delta = std::chrono::milliseconds{ ms_delay_speed };
        if(host_mode) {
            const auto start_time = std::chrono::system_clock::now();
            Eng3D::Log::debug("world_thread", "World tick performed!");
            try {
                world->do_tick();
                update_tick = true;
            } catch(const std::exception& e) {
                std::scoped_lock lock(render_lock);
                ui_ctx->prompt("Runtime exception", e.what());
                Eng3D::Log::error("world_thread", e.what());
                paused = true;
            }

            // Wait until time delta is fullfilled
            auto end_time = std::chrono::system_clock::now();
            while(end_time - start_time < delta)
                end_time = std::chrono::system_clock::now();
        }
    }
}

void GameState::music_thread() {
    struct MusicEntry {
        bool has_played;
        std::string path;
    };
    auto path_entries = Eng3D::State::get_instance().package_man->get_multiple_prefix("sfx/music/ambience");
    std::vector<MusicEntry> entries;
    entries.reserve(path_entries.size());
    for(const auto& path : path_entries)
        entries.push_back(MusicEntry{ false, path->get_abs_path() });
    path_entries.clear();
    entries.shrink_to_fit();

    while(this->run) {
        if(this->music_queue.empty()) {
            this->music_fade_value = 0.f;
            // Search through all the music in 'music/ambience' and picks a random
            if(!entries.empty()) {
                const int music_index = std::rand() % entries.size();
                std::scoped_lock lock(this->sound_lock);
                this->music_queue.push_back(new Eng3D::Audio(entries[music_index].path));
                Eng3D::Log::debug("music", "Now playing music file " + entries[music_index].path);
                entries[music_index].has_played = true;
            }
        }
    }
}

void GameState::load_world_thread() {
    this->world = new World();
    this->world->load_initial();
    this->load_progress = 0.0f;
    /// @todo Events can't be properly reloaded right now :/
    this->world->events.clear();
    this->world->load_mod();
    this->load_progress = 0.1f;
    this->loaded_world = true;
}

void start_client(int argc, char** argv) {
    std::vector<std::string> pkg_paths;
    for(int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if(arg == "--mod") {
            i++;
            if(i >= argc)
                CXX_THROW(std::runtime_error, "Expected an absolute path after --mod");
            arg = std::string(argv[i]);
            pkg_paths.push_back(arg);
        }
    }

    GameState gs(pkg_paths);
    // After loading everything initialize the gamestate initial properties
    // Call update_on_tick on start of the gamestate
    gs.update_tick = true;
    gs.in_game = false;
    gs.input = Input();
    gs.run = true;
    gs.paused = true;
    std::thread music_th(&GameState::music_thread, &gs);

#if 0
    {
        std::unique_ptr<FILE, int (*)(FILE*)> fp(fopen(Path::get("locale/es/main.po").c_str(), "rt"), fclose);
        std::unique_ptr<char[]> tmp(new char[1000]);
        while(fgets(tmp.get(), 1000, fp.get()) != nullptr) {
            if(!strncmp(tmp.get(), "msgid", 5)) {
                std::unique_ptr<char[]> msgid(new char[100]);
                sscanf(tmp.get() + 5, " %*c%[^\"]s%*c ", msgid.get());
                fgets(tmp.get(), 1000, fp.get());
                if(!strncmp(tmp.get(), "msgstr", 6)) {
                    std::unique_ptr<char[]> msgstr(new char[100]);
                    sscanf(tmp.get() + 6, " %*c%[^\"]s%*c ", msgstr.get());
                    trans_msg[msgid.get()] = msgstr.get();
                }
            }
        }
        for(const auto& [key, value] : trans_msg)
            Eng3D::Log::debug("trans", key + "=" + value);
    }
#endif

    gs.loaded_world = false;
    gs.loaded_map = false;
    gs.load_progress = 0.f;

    std::thread load_world_th(&GameState::load_world_thread, &gs);

    auto map_layer = new UI::Group(0, 0);

    auto load_screen_tex = gs.tex_man->load(gs.package_man->get_unique("gfx/load_screen/002.png"));
    auto* bg_img = new UI::Image(-(gs.width / 2.f), -(gs.height / 2.f), gs.width, gs.height, load_screen_tex);
    bg_img->origin = UI::Origin::CENTER_SCREEN;

    auto* load_pbar = new UI::ProgressBar(0, -24, gs.width, 24, 0.f, 1.f);
    load_pbar->origin = UI::Origin::LOWER_LEFT_SCREEN;
    load_pbar->text_color = Eng3D::Color(1.f, 1.f, 1.f);

    auto mod_logo_tex = gs.tex_man->load(gs.package_man->get_unique("gfx/mod_logo.png"));
    auto* mod_logo_img = new UI::Image(0, 0, mod_logo_tex->width, mod_logo_tex->height, mod_logo_tex);

    // Pre-cache the textures that the map will use upon construction
    bool init_iterator = true;
    bool load_nation_flags = false;
    std::vector<Nation>::const_iterator load_it_nation;
    bool load_building_type_icons = false;
    std::vector<BuildingType>::const_iterator load_it_building_type;
    bool load_unit_type_icons = false;
    std::vector<UnitType>::const_iterator load_it_unit_type;

    Eng3D::TextureOptions mipmap_options{};
    mipmap_options.wrap_s = GL_REPEAT;
    mipmap_options.wrap_t = GL_REPEAT;
    mipmap_options.min_filter = GL_NEAREST_MIPMAP_LINEAR;
    mipmap_options.mag_filter = GL_LINEAR;
    while(!gs.loaded_map) {
        // Widgets here SHOULD NOT REQUEST UPON WORLD DATA
        // so no world lock is needed beforehand
        handle_event(gs.input, gs);

        /// @todo first create the map and separately load all the assets
        std::scoped_lock lock(gs.render_lock);
        gs.clear();
        if(gs.loaded_world) {
            if(init_iterator) {
                load_it_nation = gs.world->nations.begin();
                load_it_building_type = gs.world->building_types.begin();
                load_it_unit_type = gs.world->unit_types.begin();
                init_iterator = false;
            }

            if(load_nation_flags && load_building_type_icons && load_unit_type_icons) {
                gs.map = new Map(*gs.world, map_layer, gs.width, gs.height);
                gs.current_mode = MapMode::DISPLAY_ONLY;
                gs.map->set_view(MapView::SPHERE_VIEW);
                gs.map->camera->move(0.f, 50.f, 10.f);
                gs.loaded_map = true;
                gs.load_progress = 1.f;
            } else if(!load_nation_flags) {
                const std::string path = "gfx/flags/" + (*load_it_nation).ref_name + "_" + ((*load_it_nation).ideology == nullptr ? "none" : (*load_it_nation).ideology->ref_name.get_string()) + ".png";
                gs.tex_man->load(gs.package_man->get_unique(path), mipmap_options);
                if(!path.empty())
                    load_pbar->text(path);
                gs.load_progress = 0.1f + (0.3f / std::distance(load_it_nation, gs.world->nations.cend()));
                load_it_nation++;
                if(load_it_nation == gs.world->nations.end())
                    load_nation_flags = true;
            } else if(!load_building_type_icons) {
                const std::string model_path = "models/building_types/" + (*load_it_building_type).ref_name + ".obj";
                gs.model_man->load(gs.package_man->get_unique(model_path));
                const std::string tex_path = "gfx/buildingtype/" + (*load_it_building_type).ref_name + ".png";
                gs.tex_man->load(gs.package_man->get_unique(tex_path), mipmap_options);
                if(!model_path.empty())
                    load_pbar->text(model_path);
                gs.load_progress = 0.4f + (0.3f / std::distance(load_it_building_type, gs.world->building_types.cend()));
                load_it_building_type++;
                if(load_it_building_type == gs.world->building_types.end())
                    load_building_type_icons = true;
            } else if(!load_unit_type_icons) {
                const std::string model_path = "models/unit_types/" + (*load_it_unit_type).ref_name + ".obj";
                gs.model_man->load(gs.package_man->get_unique(model_path));
                const std::string tex_path = "gfx/unittype/" + (*load_it_unit_type).ref_name + ".png";
                gs.tex_man->load(gs.package_man->get_unique(tex_path), mipmap_options);
                if(!model_path.empty())
                    load_pbar->text(model_path);
                gs.load_progress = 0.7f + (0.3f / std::distance(load_it_unit_type, gs.world->unit_types.cend()));
                load_it_unit_type++;
                if(load_it_unit_type == gs.world->unit_types.end()) {
                    load_unit_type_icons = true;
                    load_pbar->text("Creating the map");
                }
            }
        }

        load_pbar->set_value(gs.load_progress);
        gs.ui_ctx->render_all(glm::ivec2(gs.input.mouse_pos.first, gs.input.mouse_pos.second));
        gs.swap();
        gs.world->profiler.render_done();
    }
    load_world_th.join();
    bg_img->kill();
    load_pbar->kill();
    mod_logo_img->kill();
    new MapDevView(*gs.map);

    // Connect to server prompt
    new Interface::MainMenu(gs);

    std::vector<Event> displayed_events;
    std::vector<Treaty*> displayed_treaties;
    auto current_frame_time = std::chrono::system_clock::now();
    // Start the world thread
    std::thread world_th(&GameState::world_thread, &gs);
    while(gs.run) {
        // Locking is very expensive, so we condense everything into a big "if"
        if(gs.world->world_mutex.try_lock()) {
            // Required since events may request world data
            handle_event(gs.input, gs);
            if(gs.current_mode == MapMode::NORMAL)
                handle_popups(displayed_events, displayed_treaties, gs);

            if(gs.update_tick) {
                gs.update_on_tick();
                gs.update_tick = false;

                if(gs.current_mode == MapMode::NORMAL) {
                    // Production queue
                    for(unsigned int i = 0; i < gs.production_queue.size(); i++) {
                        const UnitType* unit_type = gs.production_queue[i];

                        /// @todo Make a better queue AI
                        bool is_built = false;
                        for(auto& building_type : gs.world->building_types) {
                            for(const auto province_id : gs.curr_nation->controlled_provinces) {
                                auto& province = gs.world->provinces[province_id];
                                Building& building = province.get_buildings()[gs.world->get_id(building_type)];
                                // Must not be working on something else
                                if(building.working_unit_type != nullptr) continue;
                                is_built = true;
                                g_client->send(Action::BuildingStartProducingUnit::form_packet(province, building_type, *gs.curr_nation, *unit_type));
                                break;
                            }

                            if(!is_built) break;
                        }
                        if(!is_built) break;
                        gs.production_queue.erase(gs.production_queue.begin() + i);
                        i--;
                    }
                }
            }

            if(gs.current_mode == MapMode::DISPLAY_ONLY)
                gs.map->camera->move(0.05f, 0.f, 0.f);
            gs.world->world_mutex.unlock();
        }

        std::scoped_lock lock(gs.render_lock);

        double prev_num = std::chrono::duration<double>(current_frame_time.time_since_epoch()).count();
        double now_num = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
        current_frame_time = std::chrono::system_clock::now();
        gs.delta_time = now_num - prev_num;

        gs.clear();
        if(gs.current_mode != MapMode::NO_MAP) {
            std::scoped_lock lock(gs.world->world_mutex);
            gs.map->camera->update();
            gs.map->draw(gs);
        }
        gs.ui_ctx->clear_dead();
        if(gs.show_ui) {
            gs.ui_ctx->render_all(glm::ivec2(gs.input.mouse_pos.first, gs.input.mouse_pos.second));
        }
        gs.swap();
        gs.world->profiler.render_done();
    }
    world_th.join();
    music_th.join();
    return;
}

GameState::~GameState() {
    // delete world;
    // delete curr_nation;
    // delete map;
    // delete ui_ctx;
};
