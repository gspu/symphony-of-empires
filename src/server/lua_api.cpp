// NOTE: Use .at() instead of the [] operator since it will
// throw exceptions when an invalid element is accessed so
// the lua exceptions

#ifdef windows
extern "C" {
#	include <lua.h>
}
#else
#  ifdef LUA54
#    include <lua5.4/lua.hpp>
#  else
#    include <lua5.3/lua.hpp>
#  endif
#endif
#include <cstring>
#include <cstdlib>
#ifdef windows
#	define bswap_32(x) _byteswap_ulong(x)
#	define bswap_64(x) _byteswap_uint64(x)
#else
#	include <byteswap.h>
#endif
#include <libintl.h>
#include <locale.h>

#include "lua_api.hpp"
#include "../world.hpp"
#include "../nation.hpp"
#include "economy.hpp"
#include "../print.hpp"
#include "../path.hpp"
#include "../event.hpp"
#include "../building.hpp"

template<typename T>
const T* find_or_throw(const std::string& ref_name) {
    const T* invention = nullptr;

    const auto& list = World::get_instance().get_list(invention);
    const auto result = std::find_if(list.begin(), list.end(),
        [&ref_name](const auto& o) { return (o->ref_name == ref_name); });

    if(result == list.end()) {
        throw LuaAPI::Exception(ref_name + " not found");
    }
    return (*result);
}

int LuaAPI::register_new_table(lua_State* L, const std::string& name, const luaL_Reg meta[], const luaL_Reg methods[]) {
    return 0;
}

int LuaAPI::add_invention(lua_State* L) {
    Invention* invention = new Invention();

    invention->ref_name = luaL_checkstring(L, 1);
    invention->name = luaL_checkstring(L, 2);
    invention->description = lua_tostring(L, 3);

    g_world->insert(invention);
    lua_pushnumber(L, g_world->inventions.size() - 1);
    return 1;
}

int LuaAPI::get_invention(lua_State* L) {
    const auto* invention = find_or_throw<Invention>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(invention));
    lua_pushstring(L, invention->name.c_str());
    lua_pushstring(L, invention->description.c_str());
    return 3;
}

int LuaAPI::set_nation_mod_to_invention(lua_State* L) {
    Invention* invention = g_world->inventions.at(lua_tonumber(L, 1));
    invention->mod = g_world->nation_modifiers.at(lua_tonumber(L, 2));
    return 0;
}

int LuaAPI::add_technology(lua_State* L) {
    Technology* technology = new Technology();

    technology->ref_name = luaL_checkstring(L, 1);
    technology->name = luaL_checkstring(L, 2);
    technology->description = lua_tostring(L, 3);
    technology->cost = lua_tonumber(L, 4);
    technology->type = (TechnologyType)((int)lua_tonumber(L, 5));

    g_world->insert(technology);
    lua_pushnumber(L, g_world->technologies.size() - 1);
    return 1;
}

int LuaAPI::get_technology(lua_State* L) {
    const auto* technology = find_or_throw<Technology>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(technology));
    lua_pushstring(L, technology->name.c_str());
    lua_pushstring(L, technology->description.c_str());
    lua_pushnumber(L, technology->cost);
    lua_pushnumber(L, technology->type);
    return 5;
}

int LuaAPI::add_req_tech_to_tech(lua_State* L) {
    Technology* technology = g_world->technologies.at(lua_tonumber(L, 1));
    technology->req_technologies.push_back(g_world->technologies.at(lua_tonumber(L, 2)));
    return 0;
}

int LuaAPI::add_unit_trait(lua_State* L) {
    UnitTrait* unit_trait = new UnitTrait();

    unit_trait->ref_name = luaL_checkstring(L, 1);
    unit_trait->supply_consumption_mod = lua_tonumber(L, 2);
    unit_trait->speed_mod = lua_tonumber(L, 3);
    unit_trait->max_health_mod = lua_tonumber(L, 4);
    unit_trait->defense_mod = lua_tonumber(L, 5);
    unit_trait->attack_mod = lua_tonumber(L, 6);

    g_world->insert(unit_trait);
    lua_pushnumber(L, g_world->unit_traits.size() - 1);
    return 1;
}

int LuaAPI::add_building_type(lua_State* L) {
    BuildingType* building_type = new BuildingType();

    building_type->ref_name = luaL_checkstring(L, 1);
    building_type->name = luaL_checkstring(L, 2);
    building_type->is_plot_on_sea = lua_toboolean(L, 3);
    building_type->is_build_land_units = lua_toboolean(L, 4);
    building_type->is_build_naval_units = lua_toboolean(L, 5);
    building_type->defense_bonus = lua_tonumber(L, 6);
    building_type->is_factory = lua_toboolean(L, 7);

    g_world->insert(building_type);
    lua_pushnumber(L, g_world->building_types.size() - 1);
    return 1;
}

int LuaAPI::add_good(lua_State* L) {
    Good* good = new Good();

    good->ref_name = luaL_checkstring(L, 1);
    good->name = luaL_checkstring(L, 2);
    good->is_edible = lua_toboolean(L, 3);

    g_world->insert(good);
    lua_pushnumber(L, g_world->goods.size() - 1);
    return 1;
}

int LuaAPI::get_good(lua_State* L) {
    const auto* good = find_or_throw<Good>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(good));
    lua_pushstring(L, good->name.c_str());
    return 2;
}

int LuaAPI::add_input_to_industry_type(lua_State* L) {
    BuildingType* industry_type = g_world->building_types.at(lua_tonumber(L, 1));
    Good* good = g_world->goods.at(lua_tonumber(L, 2));
    industry_type->inputs.push_back(good);
    return 0;
}

int LuaAPI::add_output_to_industry_type(lua_State* L) {
    BuildingType* industry_type = g_world->building_types.at(lua_tonumber(L, 1));
    Good* good = g_world->goods.at(lua_tonumber(L, 2));
    industry_type->outputs.push_back(good);
    return 0;
}

int LuaAPI::add_req_good_to_industry_type(lua_State* L) {
    BuildingType* industry_type = g_world->building_types.at(lua_tonumber(L, 1));
    Good* good = g_world->goods.at(lua_tonumber(L, 2));
    industry_type->req_goods.push_back(std::make_pair(good, lua_tonumber(L, 3)));
    return 0;
}

int LuaAPI::add_nation(lua_State* L) {
    Nation* nation = new Nation();

    nation->ref_name = luaL_checkstring(L, 1);
    nation->name = luaL_checkstring(L, 2);

    // Check for duplicates
    for(size_t i = 0; i < g_world->nations.size(); i++) {
        if(nation->ref_name == g_world->nations[i]->ref_name) {
            throw LuaAPI::Exception("Duplicate ref_name " + nation->ref_name);
        }
    }

    g_world->insert(nation);
    lua_pushnumber(L, g_world->get_id(nation));
    return 1;
}

int LuaAPI::get_nation(lua_State* L) {
    const auto* nation = find_or_throw<Nation>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(nation));
    lua_pushstring(L, nation->name.c_str());
    return 2;
}

int LuaAPI::get_provinces_owned_by_nation(lua_State* L) {
    const auto* nation = g_world->nations.at(lua_tonumber(L, 1));
    lua_newtable(L);

    size_t i = 0;
    for(const auto& province : nation->owned_provinces) {
        lua_pushnumber(L, g_world->get_id(province));
        lua_rawseti(L, -2, i + 1);
        ++i;
    }
    return 1;
}

int LuaAPI::get_provinces_with_nucleus_by_nation(lua_State* L) {
    const auto* nation = g_world->nations.at(lua_tonumber(L, 1));
    lua_newtable(L);

    size_t i = 0;
    for(const auto& province : g_world->provinces) {
        bool is_nuclei = false;
        for(const auto& nuclei : province->nucleuses) {
            if(nuclei == nation) {
                is_nuclei = true;
                break;
            }
        }
        if(is_nuclei == false) {
            continue;
        }

        lua_pushnumber(L, g_world->get_id(province));
        lua_rawseti(L, -2, i + 1);
        ++i;
    }
    return 1;
}

int LuaAPI::set_nation_primary_culture(lua_State* L) {
    return 0;
}

int LuaAPI::set_nation_capital(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));
    nation->capital = g_world->provinces.at(lua_tonumber(L, 2));
    return 0;
}

int LuaAPI::add_accepted_culture(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));
    nation->accepted_cultures.insert(g_world->cultures.at(lua_tonumber(L, 2)));
    return 0;
}

int LuaAPI::add_accepted_religion(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));
    nation->accepted_religions.insert(g_world->religions.at(lua_tonumber(L, 2)));
    return 0;
}

int LuaAPI::add_nation_client_hint(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));

    NationClientHint hint;
    hint.ideology = g_world->ideologies.at(lua_tonumber(L, 2));
    hint.alt_name = luaL_checkstring(L, 3);
    hint.colour = bswap_32(lua_tonumber(L, 4));
    hint.colour >>= 8;
    hint.colour |= 0xff000000;

    nation->client_hints.push_back(hint);
    return 0;
}

int LuaAPI::get_nation_policies(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));

    // We are going to push everything in the policies structure
    // this is horrible - reflection may help in this case
    const Policies& policy = nation->current_policy;
    lua_pushnumber(L, policy.treatment);
    lua_pushnumber(L, policy.migration);
    lua_pushnumber(L, policy.immigration);
    lua_pushnumber(L, policy.censorship);
    lua_pushnumber(L, policy.build_infrastructure);
    lua_pushnumber(L, policy.build_factories);
    lua_pushboolean(L, policy.national_id);
    lua_pushboolean(L, policy.men_suffrage);
    lua_pushboolean(L, policy.men_labour);
    lua_pushboolean(L, policy.women_suffrage);
    lua_pushboolean(L, policy.women_labour);
    lua_pushboolean(L, policy.private_property);
    lua_pushboolean(L, policy.companies_allowed);
    lua_pushboolean(L, policy.public_education);
    lua_pushboolean(L, policy.secular_education);
    lua_pushboolean(L, policy.public_healthcare);
    lua_pushboolean(L, policy.social_security);
    lua_pushboolean(L, policy.slavery);
    lua_pushboolean(L, policy.legislative_parliament);
    lua_pushboolean(L, policy.executive_parliament);
    lua_pushboolean(L, policy.constitutional);
    lua_pushboolean(L, policy.foreign_trade);
    lua_pushnumber(L, policy.import_tax);
    lua_pushnumber(L, policy.export_tax);
    lua_pushnumber(L, policy.domestic_import_tax);
    lua_pushnumber(L, policy.domestic_export_tax);
    lua_pushnumber(L, policy.poor_flat_tax);
    lua_pushnumber(L, policy.med_flat_tax);
    lua_pushnumber(L, policy.rich_flat_tax);
    lua_pushnumber(L, policy.industry_tax);
    lua_pushnumber(L, policy.military_spending);
    lua_pushboolean(L, policy.free_supplies);
    lua_pushnumber(L, policy.minimum_wage);
    return 33;
}

int LuaAPI::set_nation_policies(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));

    // We are going to push everything in the policies structure
    // this is horrible - reflection may help in this case
    Policies& policy = nation->current_policy;
    policy.treatment = static_cast<TreatmentPolicy>(lua_tonumber(L, 1));
    policy.migration = static_cast<AllowancePolicy>(lua_tonumber(L, 2));
    policy.immigration = static_cast<AllowancePolicy>(lua_tonumber(L, 3));
    policy.censorship = static_cast<CensorshipPolicy>(lua_tonumber(L, 4));
    policy.build_infrastructure = static_cast<AutoBuildPolicy>(lua_tonumber(L, 5));
    policy.build_factories = static_cast<AutoBuildPolicy>(lua_tonumber(L, 6));
    policy.national_id = lua_toboolean(L, 7);
    policy.men_suffrage = lua_toboolean(L, 8);
    policy.men_labour = lua_toboolean(L, 9);
    policy.women_suffrage = lua_toboolean(L, 10);
    policy.women_labour = lua_toboolean(L, 11);
    policy.private_property = lua_toboolean(L, 12);
    policy.companies_allowed = lua_toboolean(L, 13);
    policy.public_education = lua_toboolean(L, 14);
    policy.secular_education = lua_toboolean(L, 15);
    policy.public_healthcare = lua_toboolean(L, 16);
    policy.social_security = lua_toboolean(L, 17);
    policy.slavery = lua_toboolean(L, 18);
    policy.legislative_parliament = lua_toboolean(L, 19);
    policy.executive_parliament = lua_toboolean(L, 20);
    policy.constitutional = lua_toboolean(L, 21);
    policy.foreign_trade = lua_toboolean(L, 22);
    policy.import_tax = lua_tonumber(L, 23);
    policy.export_tax = lua_tonumber(L, 24);
    policy.domestic_import_tax = lua_tonumber(L, 25);
    policy.domestic_export_tax = lua_tonumber(L, 26);
    policy.poor_flat_tax = lua_tonumber(L, 27);
    policy.med_flat_tax = lua_tonumber(L, 28);
    policy.rich_flat_tax = lua_tonumber(L, 29);
    policy.industry_tax = lua_tonumber(L, 30);
    policy.military_spending = lua_tonumber(L, 31);
    policy.free_supplies = lua_toboolean(L, 32);
    policy.minimum_wage = lua_tonumber(L, 33);
    return 0;
}

int LuaAPI::set_nation_ideology(lua_State* L) {
    Nation* nation = g_world->nations.at(lua_tonumber(L, 1));
    nation->ideology = g_world->ideologies.at(lua_tonumber(L, 2));
    return 0;
}

int LuaAPI::add_nation_mod(lua_State* L) {
    NationModifier* mod = new NationModifier();

    mod->ref_name = luaL_checkstring(L, 1);
    mod->name = luaL_checkstring(L, 2);

    mod->industry_output_mod = lua_tonumber(L, 3);
    mod->industry_input_mod = lua_tonumber(L, 4);
    mod->workers_needed_mod = lua_tonumber(L, 5);
    mod->salary_paid_mod = lua_tonumber(L, 6);
    mod->delivery_cost_mod = lua_tonumber(L, 7);
    mod->literacy_learn_mod = lua_tonumber(L, 8);
    mod->reproduction_mod = lua_tonumber(L, 9);
    mod->death_mod = lua_tonumber(L, 10);
    mod->militancy_mod = lua_tonumber(L, 11);
    mod->consciousness_mod = lua_tonumber(L, 12);
    mod->life_needs_met_mod = lua_tonumber(L, 13);
    mod->everyday_needs_met_mod = lua_tonumber(L, 14);
    mod->luxury_needs_met_mod = lua_tonumber(L, 15);

    g_world->insert(mod);
    lua_pushnumber(L, g_world->get_id(mod));
    return 1;
}

int LuaAPI::get_nation_mod(lua_State* L) {
    const auto* mod = find_or_throw<NationModifier>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(mod));
    lua_pushstring(L, mod->name.c_str());

    lua_pushnumber(L, mod->industry_output_mod);
    lua_pushnumber(L, mod->industry_input_mod);
    lua_pushnumber(L, mod->workers_needed_mod);
    lua_pushnumber(L, mod->salary_paid_mod);
    lua_pushnumber(L, mod->delivery_cost_mod);
    lua_pushnumber(L, mod->literacy_learn_mod);
    lua_pushnumber(L, mod->reproduction_mod);
    lua_pushnumber(L, mod->death_mod);
    lua_pushnumber(L, mod->militancy_mod);
    lua_pushnumber(L, mod->consciousness_mod);
    lua_pushnumber(L, mod->life_needs_met_mod);
    lua_pushnumber(L, mod->everyday_needs_met_mod);
    lua_pushnumber(L, mod->luxury_needs_met_mod);
    return 1;
}

int LuaAPI::add_province(lua_State* L) {
    Province* province = new Province();

    province->ref_name = luaL_checkstring(L, 1);
    province->color = bswap_32(lua_tonumber(L, 2));
    province->color >>= 8;
    province->color |= 0xff000000;

    province->name = luaL_checkstring(L, 3);
    province->budget = 500.f;

    // Check for duplicates
    for(size_t i = 0; i < g_world->provinces.size(); i++) {
        if(province->color == g_world->provinces[i]->color) {
            throw LuaAPI::Exception(province->name + " province has same colour as " + g_world->provinces[i]->name);
        }
        else if(province->ref_name == g_world->provinces[i]->ref_name) {
            throw LuaAPI::Exception("Duplicate ref_name " + province->ref_name);
        }
    }

    g_world->insert(province);
    lua_pushnumber(L, g_world->get_id(province));
    return 1;
}

int LuaAPI::get_province(lua_State* L) {
    const auto* province = find_or_throw<Province>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(province));
    lua_pushstring(L, province->name.c_str());
    lua_pushnumber(L, province->color);
    return 3;
}

int LuaAPI::get_province_by_id(lua_State* L) {
    const Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    lua_pushstring(L, province->ref_name.c_str());
    lua_pushstring(L, province->name.c_str());
    lua_pushnumber(L, province->color);
    return 3;
}

int LuaAPI::add_province_industry(lua_State* L) {
    Province*& province = g_world->provinces.at(lua_tonumber(L, 1));

    Building* building = new Building();

    building->corporate_owner = g_world->companies.at(lua_tonumber(L, 2));
    building->type = g_world->building_types.at(lua_tonumber(L, 3));
    building->owner = g_world->nations.at(lua_tonumber(L, 4));

    // Randomly place in any part of the province
    // TODO: This will create some funny situations where coal factories will appear on
    // the fucking pacific ocean - we need to fix that
    building->x = province->min_x + (rand() % (province->max_x - province->min_x));
    building->y = province->min_y + (rand() % (province->max_y - province->min_y));
    building->x = std::min(building->x, g_world->width - 1);
    building->y = std::min(building->y, g_world->height - 1);
    building->province = province;

    building->working_unit_type = nullptr;
    building->req_goods_for_unit = std::vector<std::pair<Good*, size_t>>();
    building->req_goods = std::vector<std::pair<Good*, size_t>>();
    if(building->type->is_factory == true) {
        building->budget = 100.f;
        building->create_factory(*g_world);
        building->corporate_owner->operating_provinces.insert(building->get_province(*g_world));
    }
    g_world->insert(building);
    return 0;
}

int LuaAPI::give_province_to(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    g_world->nations.at(lua_tonumber(L, 2))->give_province(*g_world, *province);
    return 0;
}

/** Obtains the owner of a province (ref_name) */
int LuaAPI::get_province_owner(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    lua_pushstring(L, province->owner->ref_name.c_str());
    return 1;
}

/** Get the country who owms a larger chunk of the province - this is not the same as owner */
int LuaAPI::get_province_controller(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    Nation& nation = province->get_occupation_controller(*g_world);
    lua_pushnumber(L, g_world->get_id(&nation));
    return 1;
}

/** Obtains the neighbours of a province (by ID) */
int LuaAPI::get_province_neighbours(lua_State* L) {
    const Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    lua_newtable(L);

    size_t i = 0;
    for(const auto& neighbour : province->neighbours) {
        lua_pushnumber(L, g_world->get_id(neighbour));
        lua_rawseti(L, -2, i + 1);
        ++i;
    }
    return 1;
}

/** Mulitplies the province militancy by a factor globally */
int LuaAPI::multiply_province_militancy_global(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));

    double factor = lua_tonumber(L, 2);
    for(auto& pop : province->pops) {
        pop.militancy *= factor;
    }
    return 0;
}

int LuaAPI::multiply_province_militancy_by_culture(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    Culture* culture = g_world->cultures.at(lua_tonumber(L, 2));

    double factor = lua_tonumber(L, 3);
    for(auto& pop : province->pops) {
        if(pop.culture != g_world->cultures.at(lua_tonumber(L, 2))) {
            continue;
        }
        pop.militancy *= factor;
    }
    return 0;
}

int LuaAPI::multiply_province_militancy_by_religion(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    const Religion* religion = g_world->religions.at(lua_tonumber(L, 2));

    double factor = lua_tonumber(L, 3);
    for(auto& pop : province->pops) {
        if(pop.religion != g_world->religions.at(lua_tonumber(L, 2))) {
            continue;
        }
        pop.militancy *= factor;
    }
    return 0;
}

int LuaAPI::multiply_province_con_global(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));

    double factor = lua_tonumber(L, 2);
    for(auto& pop : province->pops) {
        pop.consciousness *= factor;
    }
    return 0;
}

int LuaAPI::multiply_province_con_by_culture(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    const Culture* culture = g_world->cultures.at(lua_tonumber(L, 2));

    double factor = lua_tonumber(L, 3);
    for(auto& pop : province->pops) {
        if(pop.culture != g_world->cultures.at(lua_tonumber(L, 2))) {
            continue;
        }
        pop.consciousness *= factor;
    }
    return 0;
}

int LuaAPI::multiply_province_con_by_religion(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    const Religion* religion = g_world->religions.at(lua_tonumber(L, 2));

    double factor = lua_tonumber(L, 3);
    for(auto& pop : province->pops) {
        if(pop.religion != g_world->religions.at(lua_tonumber(L, 2))) {
            continue;
        }
        pop.consciousness *= factor;
    }
    return 0;
}

int LuaAPI::add_province_pop(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));

    Pop pop;
    pop.type = g_world->pop_types.at(lua_tonumber(L, 2));
    pop.culture = g_world->cultures.at(lua_tonumber(L, 3));
    pop.religion = g_world->religions.at(lua_tonumber(L, 4));
    pop.size = lua_tonumber(L, 5);
    pop.literacy = lua_tonumber(L, 6);

    if(pop.size == 0) {
        throw LuaAPI::Exception("Can't create pops with 0 size");
    }
    province->pops.push_back(pop);
    return 0;
}

int LuaAPI::rename_province(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    province->name = luaL_checkstring(L, 2);
    return 0;
}

int LuaAPI::add_province_nucleus(lua_State* L) {
    g_world->provinces.at(lua_tonumber(L, 1))->nucleuses.insert(g_world->nations.at(lua_tonumber(L, 2)));
    return 0;
}

int LuaAPI::add_province_owner(lua_State* L) {
    Province* province = g_world->provinces.at(lua_tonumber(L, 1));
    Nation* nation = g_world->nations.at(lua_tonumber(L, 2));

    // TODO: Remove province from old nation (of owned provinces)
    if(province->owner != nullptr) {

    }

    province->owner = nation;
    nation->owned_provinces.insert(province);
    return 0;
}

int LuaAPI::add_company(lua_State* L) {
    Company* company = new Company();

    company->name = luaL_checkstring(L, 1);
    company->money = lua_tonumber(L, 2);
    company->is_transport = lua_toboolean(L, 3);
    company->is_retailer = lua_toboolean(L, 4);
    company->is_industry = lua_toboolean(L, 5);

    company->operating_provinces.clear();

    // Add onto vector
    g_world->insert(company);
    lua_pushnumber(L, g_world->get_id(company));
    return 1;
}

int LuaAPI::add_op_province_to_company(lua_State* L) {
    Company* company = g_world->companies.at(lua_tonumber(L, 1));
    //std::string ref_name = luaL_checkstring(L, 2);
    //company->operating_provinces.insert(province);
    return 0;
}

int LuaAPI::add_event(lua_State* L) {
    Event* event = new Event();

    event->ref_name = luaL_checkstring(L, 1);
    event->conditions_function = luaL_checkstring(L, 2);
    event->do_event_function = luaL_checkstring(L, 3);
    event->title = luaL_checkstring(L, 4);
    event->text = luaL_checkstring(L, 5);

    // Add onto vector
    g_world->insert(event);
    lua_pushnumber(L, g_world->events.size() - 1);
    return 1;
}

int LuaAPI::get_event(lua_State* L) {
    const auto* event = find_or_throw<Event>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(event));
    lua_pushstring(L, event->conditions_function.c_str());
    lua_pushstring(L, event->do_event_function.c_str());
    return 3;
}

int LuaAPI::add_event_receivers(lua_State* L) {
    // Add receivers of the event by id
    Event* event = g_world->events.at(lua_tonumber(L, 1));
    for(size_t i = 0; i < lua_tonumber(L, 2); i++) {
        event->receivers.push_back(g_world->nations.at(lua_tonumber(L, 3 + i)));
    }
    return 0;
}

int LuaAPI::add_descision(lua_State* L) {
    Event* event = g_world->events.at(lua_tonumber(L, 1));

    Descision descision = Descision();

    descision.ref_name = luaL_checkstring(L, 2);
    descision.name = luaL_checkstring(L, 3);
    descision.do_descision_function = luaL_checkstring(L, 4);
    descision.effects = luaL_checkstring(L, 5);

    // Add onto vector
    event->descisions.push_back(descision);
    return 0;
}

int LuaAPI::add_pop_type(lua_State* L) {
    PopType* pop = new PopType();

    pop->ref_name = luaL_checkstring(L, 1);
    pop->name = luaL_checkstring(L, 2);
    pop->social_value = lua_tonumber(L, 3);
    pop->is_entrepreneur = lua_toboolean(L, 4);
    pop->is_slave = lua_toboolean(L, 5);
    pop->is_farmer = lua_toboolean(L, 6);
    pop->is_laborer = lua_toboolean(L, 7);

    // Add onto vector
    g_world->insert(pop);
    lua_pushnumber(L, g_world->pop_types.size() - 1);
    return 1;
}

int LuaAPI::get_pop_type(lua_State* L) {
    const auto* pop_type = find_or_throw<PopType>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(pop_type));
    lua_pushstring(L, pop_type->name.c_str());
    lua_pushnumber(L, pop_type->social_value);
    lua_pushboolean(L, pop_type->is_entrepreneur);
    lua_pushboolean(L, pop_type->is_slave);
    lua_pushboolean(L, pop_type->is_farmer);
    lua_pushboolean(L, pop_type->is_laborer);
    return 7;
}

int LuaAPI::add_culture(lua_State* L) {
    Culture* culture = new Culture();

    culture->ref_name = luaL_checkstring(L, 1);
    culture->name = luaL_checkstring(L, 2);

    g_world->insert(culture);
    lua_pushnumber(L, g_world->cultures.size() - 1);
    return 1;
}

int LuaAPI::get_culture(lua_State* L) {
    const auto* culture = find_or_throw<Culture>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(culture));
    lua_pushstring(L, culture->name.c_str());
    return 2;
}

int LuaAPI::add_religion(lua_State* L) {
    Religion* religion = new Religion();

    religion->ref_name = luaL_checkstring(L, 1);
    religion->name = luaL_checkstring(L, 2);

    g_world->insert(religion);
    lua_pushnumber(L, g_world->religions.size() - 1);
    return 1;
}

int LuaAPI::get_religion(lua_State* L) {
    const auto* religion = find_or_throw<Religion>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(religion));
    lua_pushstring(L, religion->name.c_str());
    return 2;
}

int LuaAPI::add_unit_type(lua_State* L) {
    UnitType* unit_type = new UnitType();

    unit_type->ref_name = luaL_checkstring(L, 1);
    unit_type->name = luaL_checkstring(L, 2);
    unit_type->attack = lua_tonumber(L, 3);
    unit_type->defense = lua_tonumber(L, 4);
    unit_type->max_health = lua_tonumber(L, 5);

    unit_type->max_defensive_ticks = lua_tonumber(L, 6);
    unit_type->position_defense = lua_tonumber(L, 7);

    unit_type->is_ground = lua_toboolean(L, 8);
    unit_type->is_naval = lua_toboolean(L, 9);

    g_world->insert(unit_type);
    lua_pushnumber(L, g_world->unit_types.size() - 1);
    return 1;
}

int LuaAPI::get_unit_type(lua_State* L) {
    const auto* unit_type = find_or_throw<UnitType>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(unit_type));
    lua_pushstring(L, unit_type->name.c_str());
    lua_pushnumber(L, unit_type->attack);
    lua_pushnumber(L, unit_type->defense);
    lua_pushnumber(L, unit_type->max_health);
    lua_pushnumber(L, unit_type->max_defensive_ticks);
    lua_pushnumber(L, unit_type->position_defense);
    lua_pushboolean(L, unit_type->is_ground);
    lua_pushboolean(L, unit_type->is_naval);
    return 9;
}

int LuaAPI::add_req_good_unit_type(lua_State* L) {
    UnitType* unit_type = g_world->unit_types.at(lua_tonumber(L, 1));

    Good* good = g_world->goods.at(lua_tonumber(L, 2));
    size_t amount = lua_tonumber(L, 3);
    unit_type->req_goods.push_back(std::make_pair(good, amount));
    return 0;
}

int LuaAPI::add_ideology(lua_State* L) {
    Ideology* ideology = new Ideology();

    ideology->ref_name = luaL_checkstring(L, 1);
    ideology->name = luaL_checkstring(L, 2);
    ideology->check_policies_fn = lua_tostring(L, 3);

    g_world->insert(ideology);
    lua_pushnumber(L, g_world->ideologies.size() - 1);
    return 1;
}

int LuaAPI::get_ideology(lua_State* L) {
    const auto* ideology = find_or_throw<Ideology>(luaL_checkstring(L, 1));

    lua_pushnumber(L, g_world->get_id(ideology));
    lua_pushstring(L, ideology->name.c_str());
    return 2;
}

int LuaAPI::get_hour(lua_State* L) {
    lua_pushnumber(L, 1 + (g_world->time % 48));
    return 1;
}

int LuaAPI::get_day(lua_State* L) {
    lua_pushnumber(L, 1 + (g_world->time / 48 % 30));
    return 1;
}

int LuaAPI::get_month(lua_State* L) {
    lua_pushnumber(L, 1 + (g_world->time / 48 / 30 % 12));
    return 1;
}

int LuaAPI::get_year(lua_State* L) {
    lua_pushnumber(L, g_world->time / 48 / 30 / 12);
    return 1;
}

int LuaAPI::set_date(lua_State* L) {
    const int year = lua_tonumber(L, 1) * 12 * 30 * 48;
    const int month = lua_tonumber(L, 2) * 30 * 48;
    const int day = lua_tonumber(L, 3) * 48;
    g_world->time = year + month + day;
    return 1;
}

// Checks all events and their condition functions
void LuaAPI::check_events(lua_State* L) {
    // Because of the logic of this loop, only 1 event can happen in the world per tick
    // This is on purpouse ;)
    for(size_t i = 0; i < g_world->events.size(); i++) {
        Event* event = g_world->events[i];
        if(event->checked == true)
            continue;

        lua_getglobal(L, event->conditions_function.c_str());
        lua_call(L, 0, 1);
        bool r = lua_toboolean(L, -1);
        lua_pop(L, 1);

        // Conditions met
        if(r) {
            // Call the "do event" function
            lua_getglobal(L, event->do_event_function.c_str());
            lua_call(L, 0, 1);
            bool multi = lua_tointeger(L, -1);
            lua_pop(L, 1);

            print_info("Event triggered! %s (with %zu descisions)", event->ref_name.c_str(), (size_t)event->descisions.size());

            // Place event into inbox
            for(auto& nation : event->receivers) {
                nation->inbox.push_back(event);
            }

            // Event is marked as checked if it's not of multiple occurences
            if(!multi) {
                g_world->events[i]->checked = true;
                break;
            }
        }
        // Conditions not met, continue to next event...
    }

    // Do descisions taken effects in the queue, then clear it awaiting
    // other taken descisions :)
    for(auto& descision : g_world->taken_descisions) {
        lua_getglobal(L, descision->do_descision_function.c_str());
        lua_call(L, 0, 1);
    }
    g_world->taken_descisions.clear();
}

int LuaAPI::get_text(lua_State* L) {
    std::string msgid = luaL_checkstring(L, 1);
    std::string end_msg = gettext(msgid.c_str());
    lua_pushstring(L, end_msg.c_str());
    return 1;
}
