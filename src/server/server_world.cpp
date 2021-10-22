#include "../diplomacy.hpp"
#include "../policy.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <set>
#ifndef _MSC_VER
#	include <sys/cdefs.h>
#endif
#include <libintl.h>
#include <locale.h>

#include "../province.hpp"
#include "economy.hpp"
#include "../world.hpp"
#include "../binary_image.hpp"
#include "lua_api.hpp"
#include "../path.hpp"
#include "../print.hpp"
#include "../serializer.hpp"
#include "../io_impl.hpp"
#include "server_network.hpp"

#if (__cplusplus < 201703L)
namespace std {
    template<typename T>
    constexpr inline T clamp(T n, T min, T max) {
        return std::min<T>(max, std::max<T>(n, min));
    }
}
#endif

void ai_do_tick(Nation* nation, World* world);

/**
 * Creates a new world
  */
World::World() {
    g_world = this;

    lua = luaL_newstate();
    luaL_openlibs(lua);

    // Register our API functions
    lua_register(lua, "add_technology", LuaAPI::add_technology);
    lua_register(lua, "get_technology", LuaAPI::get_technology);
    lua_register(lua, "add_req_tech_to_tech", LuaAPI::add_req_tech_to_tech);

    lua_register(lua, "add_invention", LuaAPI::add_invention);
    lua_register(lua, "get_invention", LuaAPI::get_invention);
    lua_register(lua, "set_nation_mod_to_invention", LuaAPI::set_nation_mod_to_invention);

    lua_register(lua, "add_unit_trait", LuaAPI::add_unit_trait);

    lua_register(lua, "add_building_type", LuaAPI::add_building_type);

    lua_register(lua, "add_good", LuaAPI::add_good);
    lua_register(lua, "get_good", LuaAPI::get_good);

    lua_register(lua, "add_input_to_industry_type", LuaAPI::add_input_to_industry_type);
    lua_register(lua, "add_output_to_industry_type", LuaAPI::add_output_to_industry_type);
    lua_register(lua, "add_req_good_to_industry_type", LuaAPI::add_req_good_to_industry_type);

    lua_register(lua, "add_nation", LuaAPI::add_nation);
    lua_register(lua, "get_nation", LuaAPI::get_nation);

    lua_register(lua, "get_friends_of_nation", LuaAPI::get_friends_of_nation);
    lua_register(lua, "get_enemies_of_nation", LuaAPI::get_enemies_of_nation);
    lua_register(lua, "get_allies_of_nation", LuaAPI::get_allies_of_nation);
    lua_register(lua, "get_warenemies_of_nation", LuaAPI::get_warenemies_of_nation);
    lua_register(lua, "get_embargoed_of_nation", LuaAPI::get_embargoed_of_nation);

    lua_register(lua, "get_provinces_owned_by_nation", LuaAPI::get_provinces_owned_by_nation);
    lua_register(lua, "get_provinces_with_nucleus_by_nation", LuaAPI::get_provinces_with_nucleus_by_nation);
    lua_register(lua, "set_nation_primary_culture", LuaAPI::set_nation_primary_culture);
    lua_register(lua, "set_nation_capital", LuaAPI::set_nation_capital);
    lua_register(lua, "add_nation_accepted_culture", LuaAPI::add_accepted_culture);
    lua_register(lua, "add_nation_accepted_religion", LuaAPI::add_accepted_religion);
    lua_register(lua, "add_nation_client_hint", LuaAPI::add_nation_client_hint);
    lua_register(lua, "get_nation_policies", LuaAPI::get_nation_policies);
    lua_register(lua, "set_nation_policies", LuaAPI::set_nation_policies);
    lua_register(lua, "set_nation_ideology", LuaAPI::set_nation_ideology);

    lua_register(lua, "add_nation_mod", LuaAPI::add_nation_mod);
    lua_register(lua, "get_nation_mod", LuaAPI::get_nation_mod);

    lua_register(lua, "add_province", LuaAPI::add_province);
    lua_register(lua, "get_province", LuaAPI::get_province);
    lua_register(lua, "get_province_by_id", LuaAPI::get_province_by_id);
    lua_register(lua, "add_province_industry", LuaAPI::add_province_industry);
    lua_register(lua, "add_province_pop", LuaAPI::add_province_pop);
    lua_register(lua, "give_province_to", LuaAPI::give_province_to);
    lua_register(lua, "get_province_owner", LuaAPI::get_province_owner);
    lua_register(lua, "get_province_controller", LuaAPI::get_province_controller);
    lua_register(lua, "get_province_neighbours", LuaAPI::get_province_neighbours);
    lua_register(lua, "multiply_province_militancy_global", LuaAPI::multiply_province_militancy_global);
    lua_register(lua, "multiply_province_militancy_by_culture", LuaAPI::multiply_province_militancy_by_culture);
    lua_register(lua, "multiply_province_militancy_by_religion", LuaAPI::multiply_province_militancy_by_religion);
    lua_register(lua, "multiply_province_con_global", LuaAPI::multiply_province_con_global);
    lua_register(lua, "multiply_province_con_by_culture", LuaAPI::multiply_province_con_by_culture);
    lua_register(lua, "multiply_province_con_by_religion", LuaAPI::multiply_province_con_by_religion);
    lua_register(lua, "rename_province", LuaAPI::rename_province);
    lua_register(lua, "add_province_nucleus", LuaAPI::add_province_nucleus);
    lua_register(lua, "add_province_owner", LuaAPI::add_province_owner);

    lua_register(lua, "add_company", LuaAPI::add_company);

    lua_register(lua, "add_event", LuaAPI::add_event);
    lua_register(lua, "get_event", LuaAPI::get_event);
    lua_register(lua, "add_event_receivers", LuaAPI::add_event_receivers);

    lua_register(lua, "add_descision", LuaAPI::add_descision);

    lua_register(lua, "add_pop_type", LuaAPI::add_pop_type);
    lua_register(lua, "get_pop_type", LuaAPI::get_pop_type);

    lua_register(lua, "add_culture", LuaAPI::add_culture);
    lua_register(lua, "get_culture", LuaAPI::get_culture);

    lua_register(lua, "add_religion", LuaAPI::add_religion);
    lua_register(lua, "get_religion", LuaAPI::get_religion);

    lua_register(lua, "add_unit_type", LuaAPI::add_unit_type);
    lua_register(lua, "get_unit_type", LuaAPI::get_unit_type);
    lua_register(lua, "add_req_good_unit_type", LuaAPI::add_req_good_unit_type);

    lua_register(lua, "add_ideology", LuaAPI::add_ideology);
    lua_register(lua, "get_ideology", LuaAPI::get_ideology);

    lua_register(lua, "get_hour", [](lua_State* L) {
        lua_pushnumber(L, 1 + (g_world->time % 48));
        return 1;
    });
    lua_register(lua, "get_day", [](lua_State* L) {
        lua_pushnumber(L, 1 + (g_world->time / 48 % 30));
        return 1;
    });
    lua_register(lua, "get_month", [](lua_State* L) {
        lua_pushnumber(L, 1 + (g_world->time / 48 / 30 % 12));
        return 1;
    });
    lua_register(lua, "get_year", [](lua_State* L) {
        lua_pushnumber(L, g_world->time / 48 / 30 / 12);
        return 1;
    });
    lua_register(lua, "set_date", [](lua_State* L) {
        const int year = lua_tonumber(L, 1) * 12 * 30 * 48;
        const int month = lua_tonumber(L, 2) * 30 * 48;
        const int day = lua_tonumber(L, 3) * 48;
        g_world->time = year + month + day;
        return 1;
    });
    lua_register(lua, "_", [](lua_State* L) {
        std::string msgid = luaL_checkstring(L, 1);
        std::string end_msg = gettext(msgid.c_str());
        lua_pushstring(L, end_msg.c_str());
        return 1;
    });

    const struct luaL_Reg ideology_meta[] = {
        { "__gc", [](lua_State* L) {
            print_info("__gc?");
            return 0;
        }},
        { "__index", [](lua_State* L) {
            Ideology** ideology = (Ideology**)luaL_checkudata(L, 1, "Ideology");
            std::string member = luaL_checkstring(L, 2);
            if(member == "ref_name") {
                lua_pushstring(L, (*ideology)->ref_name.c_str());
            } else if(member == "name") {
                lua_pushstring(L, (*ideology)->name.c_str());
            }
            print_info("__index?");
            return 1;
        }},
        { "__newindex", [](lua_State* L) {
            Ideology** ideology = (Ideology**)luaL_checkudata(L, 1, "Ideology");
            std::string member = luaL_checkstring(L, 2);
            if(member == "ref_name") {
                (*ideology)->ref_name = luaL_checkstring(L, 3);
            } else if(member == "name") {
                (*ideology)->name = luaL_checkstring(L, 3);
            }
            print_info("__newindex?");
            return 0;
        }},
        { NULL, NULL }
    };
    const luaL_Reg ideology_methods[] = {
        { "new", [](lua_State* L) {
            Ideology** ideology = (Ideology**)lua_newuserdata(L, sizeof(Ideology*));
            *ideology = new Ideology();
            luaL_setmetatable(L, "Ideology");

            (*ideology)->ref_name = luaL_checkstring(L, 1);
            (*ideology)->name = luaL_optstring(L, 2, (*ideology)->ref_name.c_str());

            print_info("__new?");
            return 1;
        }},
        { "register", [](lua_State* L) {
            Ideology** ideology = (Ideology**)luaL_checkudata(L, 1, "Ideology");
            g_world->insert(*ideology);
            print_info("New ideology %s", (*ideology)->ref_name.c_str());

            print_info("__register?");
            return 0;
        }},
        { "get", [](lua_State* L) {
            const std::string ref_name = lua_tostring(L, 1);
            auto result = std::find_if(g_world->ideologies.begin(), g_world->ideologies.end(),
            [&ref_name](const auto& o) { return (o->ref_name == ref_name); });
            if(result == g_world->ideologies.end())
                throw LuaAPI::Exception("Ideology " + ref_name + " not found");

            Ideology** ideology = (Ideology**)lua_newuserdata(L, sizeof(Ideology*));
            *ideology = *result;
            luaL_setmetatable(L, "Ideology");

            print_info("__get?");
            return 1;
        }},
        { NULL, NULL }
    };
    //LuaAPI::register_new_table(lua, "Ideology", ideology_meta, ideology_methods);

    // Constants for ease of readability
    lua_pushboolean(lua, true);
    lua_setglobal(lua, "EVENT_CONDITIONS_MET");
    lua_pushboolean(lua, false);
    lua_setglobal(lua, "EVENT_CONDITIONS_UNMET");

    lua_pushboolean(lua, true);
    lua_setglobal(lua, "EVENT_DO_MANY_TIMES");
    lua_pushboolean(lua, false);
    lua_setglobal(lua, "EVENT_DO_ONE_TIME");

    // Technology types
    lua_pushnumber(lua, TechnologyType::STRATEGIC);
    lua_setglobal(lua, "TECH_STRATEGIC");
    lua_pushnumber(lua, TechnologyType::MILITARY);
    lua_setglobal(lua, "TECH_MILITARY");
    lua_pushnumber(lua, TechnologyType::NAVY);
    lua_setglobal(lua, "TECH_NAVY");
    lua_pushnumber(lua, TechnologyType::SOCIAL);
    lua_setglobal(lua, "TECH_SOCIAL");
    lua_pushnumber(lua, TechnologyType::ECONOMIC);
    lua_setglobal(lua, "TECH_ECONOMIC");
    lua_pushnumber(lua, TechnologyType::POLITICS);
    lua_setglobal(lua, "TECH_POLITICS");

    // TODO: The. name. is. fucking. long.
    lua_register(lua, "add_op_province_to_company", LuaAPI::add_op_province_to_company);

    // Set path for `require` statements in lua, this will allow us to require
    // without using data/scripts
    lua_getglobal(lua, "package");
    lua_getfield(lua, -1, "path");
    std::string curr_path = lua_tostring(lua, -1);

    // Add all scripts onto the path (with glob operator '?')
    std::vector<std::string> mod_paths = Path::get_paths();
    for(const auto& path : mod_paths) {
        curr_path.append(";" + path + "scripts/?.lua");
    }
    lua_pop(lua, 1);
    lua_pushstring(lua, curr_path.c_str());
    lua_setfield(lua, -2, "path");
    lua_pop(lua, 1);
}

World::~World() {
    lua_close(lua);
    delete[] tiles;

    for(auto& religion : religions) {
        delete religion;
    } for(auto& unit_type : unit_types) {
        delete unit_type;
    } for(auto& event : events) {
        delete event;
    } for(auto& company : companies) {
        delete company;
    } for(auto& pop_type : pop_types) {
        delete pop_type;
    } for(auto& culture : cultures) {
        delete culture;
    } for(auto& good : goods) {
        delete good;
    } for(auto& province : provinces) {
        delete province;
    } for(auto& nation : nations) {
        delete nation;
    } for(auto& building_type : building_types) {
        delete building_type;
    } for(auto& unit_trait : unit_traits) {
        delete unit_trait;
    } for(auto& product : products) {
        delete product;
    } for(auto& unit : units) {
        delete unit;
    } for(auto& ideology : ideologies) {
        delete ideology;
    }
}

static void lua_exec_all_of(World& world, const std::vector<std::string> files) {
    std::string files_buf = "require(\"api\")\n\n";
    for(const auto& file : files) {
        std::vector<std::string> paths = Path::get_all("scripts/" + file + ".lua");
        for(const auto& path : paths) {
            /*luaL_dofile(lua, path.c_str());

            if(luaL_dofile(lua, path.c_str()) != LUA_OK) {
                throw LuaAPI::Exception(lua_tostring(lua, -1));
            }*/
#ifdef windows
            std::string m_path;
            for(auto& c : path) {
                if(c == '\\') {
                    m_path += "\\\\";
                }
                else {
                    m_path += c;
                }
            }
#else
            std::string m_path = path;
#endif
            files_buf += "f = loadfile(\"" + m_path + "\")\n";
            files_buf += "f()\n";
        }
    }
    print_info("files_buf: [%s]\n", files_buf.c_str());

    if(luaL_loadstring(world.lua, files_buf.c_str()) != LUA_OK || lua_pcall(world.lua, 0, 0, 0) != LUA_OK) {
        throw LuaAPI::Exception(lua_tostring(world.lua, -1));
    }
}

void World::load_mod(void) {
    BinaryImage topo(Path::get("map_topo.png"));
    BinaryImage div(Path::get("map_div.png"));
    BinaryImage infra(Path::get("map_infra.png"));

    width = topo.width;
    height = topo.height;

    // Check that size of all maps match
    if(infra.width != width || infra.height != height) {
        throw std::runtime_error("Infrastructure map size mismatch with topographic map");
    }
    else if(div.width != width || div.height != height) {
        throw std::runtime_error("Province map size mismatch with topographic map");
    }

    const size_t total_size = width * height;

    // Sea is	<= sea_level
    // Rivers	== sea_level + 1
    // Land is	> sea_level + 1
    sea_level = 126;
    tiles = new Tile[total_size];
    if(tiles == nullptr) {
        throw std::runtime_error("Out of memory");
    }

    const std::vector<std::string> init_files ={
        "ideologies", "cultures", "nations",  "unit_traits", "building_types",
        "technology", "religions", "pop_types", "good_types", "industry_types",
        "unit_types", "boat_types", "companies", "provinces", "init"
    };
    lua_exec_all_of(*this, init_files);

    // Shrink normally-not-resized vectors to give back memory to the OS
    print_info(gettext("Shrink normally-not-resized vectors to give back memory to the OS"));
    provinces.shrink_to_fit();
    nations.shrink_to_fit();
    goods.shrink_to_fit();
    unit_types.shrink_to_fit();
    cultures.shrink_to_fit();
    religions.shrink_to_fit();
    pop_types.shrink_to_fit();
    ideologies.shrink_to_fit();
    building_types.shrink_to_fit();

    for(auto& province : provinces) {
        province->max_x = std::numeric_limits<uint32_t>::min();
        province->max_y = std::numeric_limits<uint32_t>::min();
        province->min_x = std::numeric_limits<uint32_t>::max();
        province->min_y = std::numeric_limits<uint32_t>::max();
    }

    // Translate all div, pol and topo maps onto this single tile array
    print_info(gettext("Translate all div, pol and topo maps onto this single tile array"));
    for(size_t i = 0; i < total_size; i++) {
        // Set coordinates for the tiles
        tiles[i].owner_id = (Nation::Id)-1;
        tiles[i].province_id = (Province::Id)-1;
        tiles[i].elevation = topo.buffer[i] & 0x000000ff;
        if(topo.buffer[i] == 0xffff0000) {
            tiles[i].elevation = sea_level + 1;
        }

        // Set infrastructure level
        if(infra.buffer[i] == 0xffffffff || infra.buffer[i] == 0xff000000) {
            tiles[i].infra_level = 0;
        }
        else {
            tiles[i].infra_level = 1;
        }
    }

    // Associate tiles with provinces

    // Build a lookup table for super fast speed on finding provinces
    // 16777216 * 4 = c.a 64 MB, that quite a lot but we delete the table after anyways
    print_info(gettext("Building the province lookup table"));

    std::vector<Province::Id> province_color_table(16777216, 0);
    std::fill(province_color_table.begin(), province_color_table.end(), (Province::Id)-1);
    for(const auto& province : provinces) {
        province_color_table[province->color & 0xffffff] = this->get_id(province);
    }

    // Uncomment this and see a bit more below
    //std::set<uint32_t> colors_found;
    print_info(gettext("Associate tiles with provinces"));
    for(size_t i = 0; i < total_size; i++) {
        const uint32_t color = div.buffer[i];

        // This "skip the empty stuff" technique works!
        while(i < total_size && (div.buffer[i] == 0xffffffff || div.buffer[i] == 0xff000000)) {
            ++i;
        }

        if(!(i < total_size))
            break;

        const Province::Id province_id = province_color_table[div.buffer[i] & 0xffffff];
        if(province_id == (Province::Id)-1) {
            // Uncomment this and see below
            //colors_found.insert(color);
            continue;
        }

        const uint32_t rel_color = provinces[province_id]->color;
        while(div.buffer[i] == rel_color) {
            tiles[i].province_id = province_id;
            provinces[province_id]->n_tiles++;
            ++i;
        }
        --i;
    }

    /* Uncomment this for auto-generating lua code for unregistered provinces */
    /*for(const auto& color_raw: colors_found) {
        uint32_t color = color_raw << 8;

        printf("province = Province:create{ ref_name = \"province_%x\", color = 0x%06x }\n", __bswap_32(color), __bswap_32(color));
        printf("province.name = _(\"Province_%x\")\n", __bswap_32(color));
        printf("province:register()\n");
        printf("province:add_pop(artisan, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(farmer, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(soldier, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(craftsmen, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(bureaucrat, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(aristocrat, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(clergymen, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(laborer, arabic, islamic, 1000, 0.5)\n");
        printf("province:add_pop(entrepreneur, arabic, islamic, 1000, 0.5)\n");
    }*/

    // Calculate the edges of the province (min and max x and y coordinates)
    print_info(gettext("Calculate the edges of the province (min and max x and y coordinates)"));
    for(size_t j = 0; j < height; j++) {
        for(size_t i = 0; i < width; i++) {
            Tile& tile = get_tile(i, j);
            if(tile.province_id == (Province::Id)-1)
                continue;

            Province* province = provinces[tile.province_id];
            province->max_x = std::max(province->max_x, i);
            province->max_y = std::max(province->max_y, j);
            province->min_x = std::min(province->min_x, i);
            province->min_y = std::min(province->min_y, j);
        }
    }

    // Correct stuff from provinces
    print_info(gettext("Correcting values for provinces"));
    for(auto& province : provinces) {
        province->max_x = std::min(width, province->max_x);
        province->max_y = std::min(height, province->max_y);

        // Create default stockpile of 0
        province->stockpile.resize(products.size(), 0);
    }

    // Give owners the entire provinces
    print_info(gettext("Give owners the entire provinces"));
    for(auto& nation : nations) {
        for(auto& province : nation->owned_provinces) {
            const Province::Id province_id = get_id(province);
            for(size_t x = province->min_x; x <= province->max_x; x++) {
                for(size_t y = province->min_y; y <= province->max_y; y++) {
                    Tile& tile = get_tile(x, y);

                    if(tile.province_id != province_id)
                        continue;

                    const Nation::Id nation_id = get_id(province->owner);
                    tile.owner_id = nation_id;
                }
            }
        }
    }
    nation_changed_tiles.clear();

    // Neighbours
    print_info(gettext("Creating neighbours for provinces"));
    for(size_t i = 0; i < total_size; i++) {
        const Tile* tile = &this->tiles[i];
        const Tile* other_tile;
        if(tile->owner_id != (Nation::Id)-1) {
            Nation* nation = this->nations[this->tiles[i].owner_id];
            const std::vector<const Tile*> tiles = tile->get_neighbours(*this);

            for(const auto& other_tile: tiles) {
                if(other_tile->owner_id != tile->owner_id && other_tile->owner_id != (Nation::Id)-1) {
                    nation->neighbours.insert(this->nations.at(other_tile->owner_id));
                }
            }
        }

        if(tile->province_id != (Province::Id)-1) {
            Province* province = this->provinces[this->tiles[i].province_id];
            const std::vector<const Tile*> tiles = tile->get_neighbours(*this);

            for(const auto& other_tile: tiles) {
                if(other_tile->province_id != tile->province_id && other_tile->province_id != (Province::Id)-1) {
                    province->neighbours.insert(this->provinces.at(other_tile->province_id));
                }
            }
        }
    }

    // Create diplomatic relations between nations
    print_info(gettext("Creating diplomatic relations"));
    for(const auto& nation : this->nations) {
        // Relations between nations start at 0 (and latter modified by lua scripts)
        nation->relations.resize(this->nations.size(), NationRelation{ 0.f, false, false, false, false, false, false, false, false, true, false });
    }

    const std::vector<std::string> mod_files ={
        "mod", "postinit"
    };
    lua_exec_all_of(*this, mod_files);

    // Default init for policies
    for(auto& nation : this->nations) {
        nation->budget = 10000.f;

        Policies& policy = nation->current_policy;
        policy.import_tax = 0.1f;
        policy.export_tax = 0.1f;
        policy.domestic_export_tax = 0.1f;
        policy.domestic_import_tax = 0.1f;
        policy.med_flat_tax = 0.1f;
        policy.poor_flat_tax = 0.1f;
        policy.rich_flat_tax = 0.1f;
        policy.private_property = true;
        policy.immigration = ALLOW_ALL;
        policy.migration = ALLOW_ALL;
        policy.industry_tax = 0.1f;
        policy.foreign_trade = true;
    }
    print_info(gettext("World fully intiialized"));
}

#include "../actions.hpp"
#include "economy.hpp"
void World::do_tick() {
    std::lock_guard<std::recursive_mutex> lock(world_mutex);
    std::lock_guard<std::recursive_mutex> lock2(tiles_mutex);

    // AI and stuff
    // Just random shit to make the world be like more alive
    for(const auto& nation : nations) {
        ai_do_tick(nation, this);
    }

    // Each tick == 30 minutes
    switch(time % (24 * 2)) {
        // 3:00
    case 6:
        Economy::do_phase_1(*this);
        break;
        // 7:30
        // Busy hour, newspapers come out and people get mad
    case 15:
        Economy::do_phase_2(*this);

        // Calculate prestige for today (newspapers come out!)
        for(auto& nation : this->nations) {
            const float decay_per_cent = 5.f;
            const float max_modifier = 10.f;
            const float min_prestige = std::max<float>(0.5f, ((nation->naval_score + nation->military_score + nation->economy_score) / 2));

            // Prestige cannot go below min prestige
            nation->prestige = std::max<float>(nation->prestige, min_prestige);
            nation->prestige -= (nation->prestige * (decay_per_cent / 100.f)) * fmin(fmax(1, nation->prestige - min_prestige) / min_prestige, max_modifier);
        }
        break;
        // 12:00
    case 24:
        Economy::do_phase_3(*this);
        for(const auto& product : g_world->products) {
            // Broadcast to clients
            Packet packet = Packet();
            Archive ar = Archive();
            ActionType action = ActionType::PRODUCT_UPDATE;
            ::serialize(ar, &action);
            ::serialize(ar, &product); // ProductRef
            ::serialize(ar, product); // ProductObj
            packet.data(ar.get_buffer(), ar.size());
            g_server->broadcast(packet);
        }

        for(auto& nation : this->nations) {
            float economy_score = 0.f;
            for(const auto& province : nation->owned_provinces) {
                // Calculate economy score of nations
                for(const auto& pop : province->pops) {
                    economy_score += pop.budget;
                }

                // Also calculates GDP
                for(const auto& product : g_world->products) {
                    nation->gdp += product->price * province->stockpile[g_world->get_id(product)];
                }
            }
            nation->economy_score = economy_score / 100.f;
        }
        break;
        // 18:00
    case 36:
        Economy::do_phase_4(*this);
        break;
        // 24:00, this is where clients are sent all information **at once**
    case 47:
    {
        for(const auto& nation : g_world->nations) {
            // Broadcast to clients
            Packet packet = Packet();
            Archive ar = Archive();
            ActionType action = ActionType::NATION_UPDATE;
            ::serialize(ar, &action);
            ::serialize(ar, &nation); // NationRef
            ::serialize(ar, nation); // NationObj
            packet.data(ar.get_buffer(), ar.size());
            g_server->broadcast(packet);
        }

        for(const auto& province : g_world->provinces) {
            // Broadcast to clients
            Packet packet = Packet();
            Archive ar = Archive();
            ActionType action = ActionType::PROVINCE_UPDATE;
            ::serialize(ar, &action);
            ::serialize(ar, &province); // ProvinceRef
            ::serialize(ar, province); // ProvinceObj
            packet.data(ar.get_buffer(), ar.size());
            g_server->broadcast(packet);
        }
    }
    break;
    default:
        break;
    }

    // Evaluate units
    for(size_t i = 0; i < units.size(); i++) {
        Unit* unit = units[i];
        if(unit->size <= 0) {
            g_world->remove(unit);
            break;
        }

        // Count friends and foes in range (and find nearest foe)
        size_t n_friends = 0;
        size_t n_foes = 0;
        Unit* nearest_foe = nullptr;
        Unit* nearest_friend = nullptr;
        for(size_t j = 0; j < g_world->units.size(); j++) {
            Unit* other_unit = g_world->units[j];
            if(unit->owner == other_unit->owner) {
                // Only when very close
                if(std::abs(unit->x - other_unit->x) >= 4.f && std::abs(unit->y - other_unit->y) >= 4.f)
                    continue;

                n_friends++;

                if(nearest_friend == nullptr) {
                    nearest_friend = other_unit;
                }

                // Find nearest friend
                if(std::abs(unit->x - other_unit->x) < std::abs(unit->x - nearest_friend->x)
                    && std::abs(unit->y - other_unit->y) < std::abs(unit->y - nearest_friend->y)) {
                    nearest_friend = other_unit;
                }
            }
            else {
                // Foes from many ranges counts
                if(std::abs(unit->x - other_unit->x) >= 1.f && std::abs(unit->y - other_unit->y) >= 1.f)
                    continue;

                n_foes++;

                if(nearest_foe == nullptr) {
                    nearest_foe = other_unit;
                }

                // Find nearest foe
                if(std::abs(unit->x - other_unit->x) < std::abs(unit->x - nearest_foe->x)
                    && std::abs(unit->y - other_unit->y) < std::abs(unit->y - nearest_foe->y)) {
                    nearest_foe = other_unit;
                }
            }
        }

        if((unit->x != unit->tx || unit->y != unit->ty)
            && (std::abs(unit->x - unit->tx) >= 0.2f || std::abs(unit->y - unit->ty) >= 0.2f)) {
            float end_x, end_y;
            const float speed = 0.1f;

            end_x = unit->x;
            end_y = unit->y;

            // Move towards target
            if(unit->x > unit->tx)
                end_x -= speed;
            else if(unit->x < unit->tx)
                end_x += speed;

            if(unit->y > unit->ty)
                end_y -= speed;
            else if(unit->y < unit->ty)
                end_y += speed;

            // This code prevents us from stepping onto water tiles (but allows for rivers)
            if(get_tile(end_x, end_y).elevation <= sea_level) {
                continue;
            }

            unit->x = end_x;
            unit->y = end_y;
        }

        // Make the unit attack automatically
        // and we must be at war with the owner of this unit to be able to attack the unit
        if(nearest_foe != nullptr && unit->owner->is_enemy(*nearest_foe->owner)) {
            unit->attack(*nearest_foe);
        }

        // Unit is on a non-wasteland part of the map
        if(get_tile(unit->x, unit->y).province_id != (Province::Id)-1) {
            Province* province = provinces[get_tile(unit->x, unit->y).province_id];
            const Nation* nation = province->owner;
            bool free_supplies = false;

            // Unit is on domestic soil, so we have to check the domsetic policy for free military supplies
            if(unit->owner == nation) {
                // No-cost supplies
                if(unit->owner->current_policy.free_supplies) {
                    free_supplies = true;
                }
            }
            // Unit is on foreign soil, we check relations to see if we can take free military supplies
            else {
                // No-cost supplies
                if(unit->owner->relations[get_id(nation)].free_supplies) {
                    free_supplies = true;
                }
            }

            if(free_supplies == true) {
                // Take anything you want, it's not needed to fucking pay at all! :)
                for(size_t j = 0; j < province->stockpile.size(); j++) {
                    if(!province->stockpile[j])
                        continue;

                    // We will take your food pleseantly
                    if(products[j]->good->is_edible && unit->supply <= (unit->type->supply_consumption * 10.f)) {
                        float bought = std::min(unit->size, province->stockpile[j]);
                        province->stockpile[j] -= bought;

                        unit->supply += bought / unit->size;
                        unit->morale += bought / unit->size;
                    }
                    // Fuck you, we are also taking your luxury because it's free
                    else {
                        float bought = std::min((rand() + 1) % unit->size, province->stockpile[j]);
                        province->stockpile[j] -= bought;

                        // Yes, we are super happy with your voluntary gifts to the honourable
                        // units of some nation
                        unit->morale += bought / unit->size;
                    }
                }
            }
            else {
                // Buy stuff and what we are able to buy normally
                for(size_t j = 0; j < province->stockpile.size(); j++) {
                    // Must be edible and there must be stock
                    if(!products[j]->good->is_edible || !province->stockpile[j])
                        continue;

                    if(products[j]->price * unit->size <= unit->budget) {
                        size_t bought = std::min(province->stockpile[j], unit->size);
                        
                        province->stockpile[j] -= bought;
                        unit->supply = bought / unit->size;

                        // Pay (including taxes)
                        const float paid = (products[j]->price * unit->size) * province->owner->current_policy.med_flat_tax;
                        province->owner->budget += paid;
                        unit->budget -= paid;
                    }

                    // We will stop buying if we are satisfied
                    if(unit->supply >= (unit->type->supply_consumption * 1.f))
                        break;
                }
            }
        }

        // North and south do not wrap
        unit->y = std::max<float>(0.f, unit->y);
        unit->y = std::min<float>(height, unit->y);

        // West and east do wrap
        if(unit->x <= 0.f) {
            unit->x = width - 1.f;
        }
        else if(unit->x >= width) {
            unit->x = 0.f;
        }

        // Set nearby tiles as owned
        // TODO: Make it conquer multiple tiles
        Tile& tile = get_tile(unit->x, unit->y);
        if(tile.owner_id != get_id(unit->owner)) {
            tile.owner_id = get_id(unit->owner);

            std::lock_guard<std::recursive_mutex> lock(nation_changed_tiles_mutex);
            nation_changed_tiles.push_back(&get_tile(unit->x, unit->y));
            {
                std::pair<size_t, size_t> coord = std::make_pair((size_t)unit->x, (size_t)unit->y);
                // Broadcast to clients
                Packet packet = Packet(0);
                Archive ar = Archive();

                ActionType action = ActionType::TILE_UPDATE;
                ::serialize(ar, &action);
                ::serialize(ar, &coord.first);
                ::serialize(ar, &coord.second);
                ::serialize(ar, &tile);

                packet.data(ar.get_buffer(), ar.size());
                g_server->broadcast(packet);
            }
        }
    }

    for(const auto& unit : units) {
        // Broadcast to clients
        Packet packet = Packet();
        Archive ar = Archive();

        ActionType action = ActionType::UNIT_UPDATE;
        ::serialize(ar, &action);
        ::serialize(ar, &unit);
        ::serialize(ar, unit);

        packet.data(ar.get_buffer(), ar.size());
        g_server->broadcast(packet);
    }

    // Do the treaties clauses
    for(const auto& treaty : treaties) {
        // Check that the treaty is agreed by all parties before enforcing it
        bool on_effect = !(std::find_if(treaty->approval_status.begin(), treaty->approval_status.end(), [](auto& status) { return (status.second != TreatyApproval::ACCEPTED); }) != treaty->approval_status.end());
        if(!on_effect)
            continue;

        // And also check that there is atleast 1 clause that is on effect
        bool is_on_effect = false;
        for(const auto& clause : treaty->clauses) {
            if(clause->type == TreatyClauseType::WAR_REPARATIONS) {
                auto dyn_clause = dynamic_cast<TreatyClause::WarReparations*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }
            else if(clause->type == TreatyClauseType::ANEXX_PROVINCES) {
                auto dyn_clause = dynamic_cast<TreatyClause::AnexxProvince*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }
            else if(clause->type == TreatyClauseType::LIBERATE_NATION) {
                auto dyn_clause = dynamic_cast<TreatyClause::LiberateNation*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }
            else if(clause->type == TreatyClauseType::HUMILIATE) {
                auto dyn_clause = dynamic_cast<TreatyClause::Humiliate*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }
            else if(clause->type == TreatyClauseType::IMPOSE_POLICIES) {
                auto dyn_clause = dynamic_cast<TreatyClause::ImposePolicies*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }
            else if(clause->type == TreatyClauseType::CEASEFIRE) {
                auto dyn_clause = dynamic_cast<TreatyClause::Ceasefire*>(clause);
                is_on_effect = dyn_clause->in_effect();
            }

            if(is_on_effect)
                break;
        }
        if(!is_on_effect)
            continue;

        // Treaties clauses now will be enforced
        print_info("Enforcing treaty %s", treaty->name.c_str());
        for(auto& clause : treaty->clauses) {
            if(clause->type == TreatyClauseType::WAR_REPARATIONS) {
                auto dyn_clause = dynamic_cast<TreatyClause::WarReparations*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }
            else if(clause->type == TreatyClauseType::ANEXX_PROVINCES) {
                auto dyn_clause = dynamic_cast<TreatyClause::AnexxProvince*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }
            else if(clause->type == TreatyClauseType::LIBERATE_NATION) {
                auto dyn_clause = dynamic_cast<TreatyClause::LiberateNation*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }
            else if(clause->type == TreatyClauseType::HUMILIATE) {
                auto dyn_clause = dynamic_cast<TreatyClause::Humiliate*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }
            else if(clause->type == TreatyClauseType::IMPOSE_POLICIES) {
                auto dyn_clause = dynamic_cast<TreatyClause::ImposePolicies*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }
            else if(clause->type == TreatyClauseType::CEASEFIRE) {
                auto dyn_clause = dynamic_cast<TreatyClause::Ceasefire*>(clause);
                if(!dyn_clause->in_effect())
                    goto next_iter;
                dyn_clause->enforce();
            }

        next_iter:
            ;
        }
    }

    LuaAPI::check_events(lua);

    if(time % 48 == 0) {
        print_info("%i/%i/%i", time / 12 / 30 / 48, (time / 30 / 48 % 12) + 1, (time / 48 % 30) + 1);
    }

    //print_info("Tick %i done", time);
    time++;

    // Tell clients that this tick has been done
    Packet packet = Packet(0);
    Archive ar = Archive();
    ActionType action = ActionType::WORLD_TICK;
    ::serialize(ar, &action);
    packet.data(ar.get_buffer(), ar.size());
    g_server->broadcast(packet);
}
