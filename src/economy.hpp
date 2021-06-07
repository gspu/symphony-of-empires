#ifndef ECONOMY_H
#define ECONOMY_H

#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <cstdint>
#include <cstddef>

#include "texture.hpp"
#include "array_ops.hpp"
#include "province.hpp"

// Functions that do a economy simulation in various steps, divided to reduce
// overhead, they are distributed accross 48 ticks
namespace Economy {
	void do_phase_1(World& world);
	void do_phase_2(World& world);
	void do_phase_3(World& world);
	void do_phase_4(World& world);
}

/**
 * A company that operates one or more factories and is able to build even more factories
 */
class Company {
public:
	// Name of this company
	std::string name;
	
	// How many money this company has
	float money;

	bool is_transport;
	bool is_retailer;
	bool is_industry;

	// List of province IDs where this company operates (mostly used for transport companies)
	std::vector<Province *> operating_provinces;

	inline bool in_range(Province * province) {
		return (std::find(operating_provinces.begin(), operating_provinces.end(), province)
			!= operating_provinces.end());
	}

	void name_gen() {
		size_t r = (rand() % 12) + 1;
		for(size_t i = 0; i < r; i++) {
			name += 'a' + (rand() % 25);
		}
	}
};

typedef uint8_t GoodId;
/**
 * A good, mostly serves as a "product type"
 */
class Good {
public:
	~Good() {
		delete icon;
	}

	std::string name;
	std::string ref_name;

	// Determines if the good can be "eaten", this makes the product fullfill a life need
	bool is_edible;

	Texture * icon = nullptr;
};

class IndustryType {
public:
	~IndustryType() {
		delete image;
	}

	std::string name;
	std::string ref_name;

	Texture * image = nullptr;

	// List of good required to create output
	std::vector<Good *> inputs;

	// List of good that this factory type creates
	std::vector<Good *> outputs;
};

#include "nation.hpp"
class World;

typedef uint16_t IndustryId;
class Industry {
public:
	IndustryId get_id(const World& world, ProvinceId province_id);
	bool can_do_output(const World& world);
	void add_to_stock(const World& world, const Good * good, size_t add);

	// Owner nation of this factory
	Company * owner;

	// Type of factory
	IndustryType * type;

	// Days that the factory has not been operational
	size_t days_unoperational;

	// Money needed to produce - helps determine the price of the output products
	float production_cost;

	// Stockpile of inputs in the factory
	std::vector<size_t> stockpile;
	
	// Used for faster lookups
	std::vector<Product *> output_products;

	// The desired quality of a product (otherwise it's not accepted)
	size_t min_quality;

	// The pay we are willing to give
	size_t willing_payment;
};

typedef uint16_t ProductId;
/**
 * A product (based off a Good) which can be bought by POPs, converted by factories and transported
 * accross the world
 */
class Product {
public:
	// Onwer (companyId) of this product
	Company * owner;
	
	// Origin province (where this product was made)
	Province * origin;
	
	// Industry in province that made this product
	Industry * industry;
	
	// Good that this product is based on
	Good * good;
	
	// Price of the product
	float price;
	
	// Velocity of change of price of the product
	float price_vel;
	
	// Quality of the product
	size_t quality;
	
	// Total supply (worldwide) of the product
	size_t supply;
	
	// Total demand (worldwide) of the product
	size_t demand;

	// History of price, supply and demand for the past 30 days
	std::deque<float> price_history;
	std::deque<size_t> supply_history;
	std::deque<size_t> demand_history;
};

#endif
