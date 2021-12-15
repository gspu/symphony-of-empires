#include "province.hpp"
#include "world.hpp"
#include "product.hpp"
#include "good.hpp"
#include "company.hpp"

// Obtains the country that currently has a larger number of
// tiles controlled from this province
Nation& Province::get_occupation_controller(void) const {
    const World& world = World::get_instance();

#if defined TILE_GRANULARITY
    std::vector<Nation::Id> nations_cnt;
    for(size_t x = min_x; x < max_x; x++) {
        for(size_t y = min_y; y < max_y; y++) {
            nations_cnt.push_back(world.get_tile(x, y).owner_id);
        }
    }

    // We are going to obtain all nations who have a foothold on this province
    // then we are going to obtain the one with the highest tile count
    std::set<Nation::Id> unique_nations(nations_cnt.begin(), nations_cnt.end());
    Nation::Id nation_id = world.get_id(owner);
    size_t max_tiles_cnt = 0;
    for(const auto& curr_nation_id : unique_nations) {
        // This will count the tiles for this nation
        const size_t tiles_cnt = std::count(nations_cnt.begin(), nations_cnt.end(), curr_nation_id);
        if(tiles_cnt > max_tiles_cnt) {
            max_tiles_cnt = tiles_cnt;
            nation_id = curr_nation_id;
        }
    }
    return (*world.nations[nation_id]);
#else
    return (*controller);
#endif
}

// Calculates the total number of POPs in this province (total population)
size_t Province::total_pops(void) const {
    size_t total = 0;
    for(const auto& pop : pops) {
        total += pop.size;
    }
    return total;
}

// Create a vector containing a list of all products available on this province
std::vector<Product*> Province::get_products(void) const {
    return products;
}

float Province::get_attractiveness(const Pop& pop) const {
    float attractive = this->base_attractive;
    
    if(!this->owner->is_accepted_culture(pop) && !this->owner->is_accepted_religion(pop)) {
        // Linearized version, instead of using if-else trees we just
        // multiply the attractive by the scale; EXTERMINATE = 3, so 3 - 3 is 0 which nullifies the attractivenes
        // and the more open the borders are the more lenient the "scale" becomes
        const int scale = 3 - this->owner->current_policy.treatment;
        attractive *= scale;
    }

    // Account for literacy difference
    attractive -= this->owner->base_literacy;

    // Account for GDP difference
    attractive -= this->owner->gdp * 0.0001f;

    // A social value between 0 and 1 is for poor people, the value for medium class
    // is between 1 and 2, for the rich is above 2

    // For the lower class, lower taxes is good, and so on for other POPs
    if(pop.type->social_value >= 0.f && pop.type->social_value <= 1.f) {
        attractive += -(this->owner->current_policy.poor_flat_tax);
    }
    // For the medium class
    else if(pop.type->social_value >= 1.f && pop.type->social_value <= 2.f) {
        attractive += -(this->owner->current_policy.med_flat_tax);
    }
    // For the high class
    else if(pop.type->social_value >= 2.f) {
        attractive += -(this->owner->current_policy.rich_flat_tax);
    }
    return attractive;
}