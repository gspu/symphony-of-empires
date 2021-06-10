#ifndef IO_IMPL_HPP
#define IO_IMPL_HPP

#include "world.hpp"
#include "province.hpp"
#include "nation.hpp"
#include "economy.hpp"
#include "pop.hpp"
#include "serializer.hpp"

// TODO: Modify the pointer, since we are only passing the pointer as a temporal on the stack
// tl;dr we need a pointer to a pointer instead of a pointer - if decoding problems happens
// this is why

// TODO: We should compile a list of "patches" to apply (since some objects may depend on others
// which are not fully loaded)
template<>
class Serializer<Province *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Province * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Province * obj) {
		ProvinceId id;
		::deserialize(input, id);
		obj = (id != (ProvinceId)-1) ? g_world->provinces[id] : nullptr;
	}
	static inline size_t size(const Province *) {
		return sizeof(ProvinceId);
	}
};

template<>
class Serializer<Nation *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Nation * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Nation * obj) {
		NationId id;
		::deserialize(input, id);
		obj = (id != (NationId)-1) ? g_world->nations[id] : nullptr;
	}
	static inline size_t size(const Nation *) {
		return sizeof(NationId);
	}
};

template<>
class Serializer<Event *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Event * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Event * obj) {
		size_t id;
		::deserialize(input, id);
		obj = (id != (size_t)-1) ? g_world->events[id] : nullptr;
	}
	static inline size_t size(const Event *) {
		return sizeof(size_t);
	}
};

template<>
class Serializer<Product *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Product * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Product * obj) {
		ProductId id;
		::deserialize(input, id);
		obj = (id != (ProductId)-1) ? g_world->products[id] : nullptr;
	}
	static inline size_t size(const Product *) {
		return sizeof(ProductId);
	}
};

template<>
class Serializer<Culture *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Culture * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Culture * obj) {
		CultureId id;
		::deserialize(input, id);
		obj = (id != (CultureId)-1) ? g_world->cultures[id] : nullptr;
	}
	static inline size_t size(const Culture *) {
		return sizeof(CultureId);
	}
};

template<>
class Serializer<Good *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Good * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Good * obj) {
		GoodId id;
		::deserialize(input, id);
		obj = (id != (GoodId)-1) ? g_world->goods[id] : nullptr;
	}
	static inline size_t size(const Good *) {
		return sizeof(GoodId);
	}
};

template<>
class Serializer<Company *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Company * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, Company * obj) {
		CompanyId id;
		::deserialize(input, id);
		obj = (id != (CompanyId)-1) ? g_world->companies[id] : nullptr;
	}
	static inline size_t size(const Company * obj) {
		return sizeof(CompanyId);
	}
};

template<>
class Serializer<IndustryType *> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const IndustryType * obj) {
		::serialize(output, g_world->get_id(obj));
	}
	static inline void deserialize(Archive& input, IndustryType * obj) {
		size_t id;
		::deserialize(input, id);
		obj = (id != (size_t)-1) ? g_world->industry_types[id] : nullptr;
	}
	static inline size_t size(const IndustryType * obj) {
		return sizeof(size_t);
	}
};

template<>
class Serializer<Industry *> : public SerializerMemcpy<Industry *> {};

template<>
class Serializer<NationRelation> : public SerializerMemcpy<NationRelation> {};
template<>
class Serializer<Policies> : public SerializerMemcpy<Policies> {};

template<>
class Serializer<PopType> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const PopType& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		::serialize(output, obj.average_budget);
	}
	static inline void deserialize(Archive& input, PopType& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		::deserialize(input, obj.average_budget);
	}
	static inline size_t size(const PopType& obj) {
		return serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.average_budget)
		;
	}
};

template<>
class Serializer<Culture> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Culture& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
	}
	static inline void deserialize(Archive& input, Culture& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
	}
	static inline size_t size(const Culture& obj) {
		return serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
		;
	}
};

template<>
class Serializer<Religion> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Religion& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
	}
	static inline void deserialize(Archive& input, Religion& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
	}
	static inline size_t size(const Religion& obj) {
		return serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
		;
	}
};

template<>
class Serializer<PartyLoyalty> : public SerializerMemcpy<PartyLoyalty> {};
template<>
class Serializer<IssueInterest> : public SerializerMemcpy<IssueInterest> {};
template<>
class Serializer<Pop> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Pop& obj) {
		::serialize(output, obj.size);
		::serialize(output, obj.unemployed);

		::serialize(output, obj.literacy);
		::serialize(output, obj.militancy);
		::serialize(output, obj.consciousness);
		::serialize(output, obj.budget);

		::serialize(output, obj.life_needs_met);
		::serialize(output, obj.everyday_needs_met);
		::serialize(output, obj.luxury_needs_met);

		::serialize(output, obj.type_id);
		::serialize(output, obj.culture_id);
		::serialize(output, obj.religion_id);

		::serialize(output, obj.party_loyalties);
		::serialize(output, obj.issue_interests);
	}
	static inline void deserialize(Archive& input, Pop& obj) {
		::deserialize(input, obj.size);
		::deserialize(input, obj.unemployed);
		
		::deserialize(input, obj.literacy);
		::deserialize(input, obj.militancy);
		::deserialize(input, obj.consciousness);
		::deserialize(input, obj.budget);

		::deserialize(input, obj.life_needs_met);
		::deserialize(input, obj.everyday_needs_met);
		::deserialize(input, obj.luxury_needs_met);

		::deserialize(input, obj.type_id);
		::deserialize(input, obj.culture_id);
		::deserialize(input, obj.religion_id);
	}
	static inline size_t size(const Pop& obj) {
		return serialized_size(obj.size)
			+ serialized_size(obj.unemployed)
			+ serialized_size(obj.literacy)
			+ serialized_size(obj.militancy)
			+ serialized_size(obj.consciousness)
			+ serialized_size(obj.budget)
			+ serialized_size(obj.life_needs_met)
			+ serialized_size(obj.everyday_needs_met)
			+ serialized_size(obj.luxury_needs_met)
			+ serialized_size(obj.type_id)
			+ serialized_size(obj.culture_id)
			+ serialized_size(obj.religion_id)
		;
	}
};

template<>
class Serializer<Tile> : public SerializerMemcpy<Tile> {};
template<>
class Serializer<OrderGoods> : public SerializerMemcpy<OrderGoods> {};
template<>
class Serializer<DeliverGoods> : public SerializerMemcpy<DeliverGoods> {};

template<>
class Serializer<Nation> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Nation& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		::serialize(output, obj.controlled_by_ai);
		::serialize(output, obj.color);
		::serialize(output, obj.relations);
		::serialize(output, obj.spherer_id);
		::serialize(output, obj.diplomacy_points);
		::serialize(output, obj.prestige);

		::serialize(output, obj.base_literacy);
		::serialize(output, obj.is_civilized);

		::serialize(output, obj.infamy);
		::serialize(output, obj.military_score);
		::serialize(output, obj.naval_score);
		::serialize(output, obj.economy_score);

		::serialize(output, obj.budget);

		::serialize(output, obj.primary_culture);
		::serialize(output, obj.capital);
		::serialize(output, obj.accepted_cultures);
		::serialize(output, obj.owned_provinces);
		::serialize(output, obj.current_policy);
		::serialize(output, obj.diplomatic_timer);
		
		// TODO: Default flag here
	}
	static inline void deserialize(Archive& input, Nation& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		::deserialize(input, obj.controlled_by_ai);
		::deserialize(input, obj.color);
		::deserialize(input, obj.relations);
		::deserialize(input, obj.spherer_id);
		::deserialize(input, obj.diplomacy_points);
		::deserialize(input, obj.prestige);

		::deserialize(input, obj.base_literacy);
		::deserialize(input, obj.is_civilized);

		::deserialize(input, obj.infamy);
		::deserialize(input, obj.military_score);
		::deserialize(input, obj.naval_score);
		::deserialize(input, obj.economy_score);

		::deserialize(input, obj.budget);

		::deserialize(input, obj.primary_culture);
		::deserialize(input, obj.capital);
		::deserialize(input, obj.accepted_cultures);
		::deserialize(input, obj.owned_provinces);
		::deserialize(input, obj.current_policy);
		::deserialize(input, obj.diplomatic_timer);
		
		// TODO: Rest of fields
	}
	static inline size_t size(const Nation& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.controlled_by_ai)
			+ serialized_size(obj.color)
			+ serialized_size(obj.relations)
			+ serialized_size(obj.spherer_id)
			+ serialized_size(obj.diplomacy_points)
			+ serialized_size(obj.prestige)
			+ serialized_size(obj.base_literacy)
			+ serialized_size(obj.is_civilized)
			+ serialized_size(obj.infamy)
			+ serialized_size(obj.military_score)
			+ serialized_size(obj.naval_score)
			+ serialized_size(obj.economy_score)
			+ serialized_size(obj.budget)
			+ serialized_size(obj.primary_culture)
			+ serialized_size(obj.capital)
			+ serialized_size(obj.accepted_cultures)
			+ serialized_size(obj.owned_provinces)
			+ serialized_size(obj.current_policy)
			+ serialized_size(obj.diplomatic_timer)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<UnitType> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const UnitType& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		::serialize(output, obj.supply_consumption);
		::serialize(output, obj.speed);
		::serialize(output, obj.max_health);
		::serialize(output, obj.defense);
		::serialize(output, obj.attack);
		::serialize(output, obj.req_goods);
	}
	static inline void deserialize(Archive& input, UnitType& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		::deserialize(input, obj.supply_consumption);
		::deserialize(input, obj.speed);
		::deserialize(input, obj.max_health);
		::deserialize(input, obj.defense);
		::deserialize(input, obj.attack);
		::deserialize(input, obj.req_goods);
	}
	static inline size_t size(const UnitType& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.supply_consumption)
			+ serialized_size(obj.speed)
			+ serialized_size(obj.max_health)
			+ serialized_size(obj.defense)
			+ serialized_size(obj.attack)
			+ serialized_size(obj.req_goods)
		;
	}
};

template<>
class Serializer<Province> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Province& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		
		::serialize(output, obj.color);
		::serialize(output, obj.budget);
		::serialize(output, obj.n_tiles);
		
		::serialize(output, obj.max_x);
		::serialize(output, obj.max_y);
		::serialize(output, obj.min_x);
		::serialize(output, obj.min_y);
		
		::serialize(output, obj.supply_limit);
		::serialize(output, obj.supply_rem);
		::serialize(output, obj.worker_pool);
		
		::serialize(output, obj.owner);
		
		::serialize(output, obj.nucleuses);
		::serialize(output, obj.neighbours);
		::serialize(output, obj.stockpile);
		::serialize(output, obj.industries);
		::serialize(output, obj.products);
		::serialize(output, obj.pops);
	}
	static inline void deserialize(Archive& input, Province& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		
		::deserialize(input, obj.color);
		::deserialize(input, obj.budget);
		::deserialize(input, obj.n_tiles);
		
		::deserialize(input, obj.max_x);
		::deserialize(input, obj.max_y);
		::deserialize(input, obj.min_x);
		::deserialize(input, obj.min_y);
		
		::deserialize(input, obj.supply_limit);
		::deserialize(input, obj.supply_rem);
		::deserialize(input, obj.worker_pool);
		
		::deserialize(input, obj.owner);
		
		::deserialize(input, obj.nucleuses);
		::deserialize(input, obj.neighbours);
		::deserialize(input, obj.stockpile);
		::deserialize(input, obj.industries);
		::deserialize(input, obj.products);
		::deserialize(input, obj.pops);
	}
	static inline size_t size(const Province& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.color)
			+ serialized_size(obj.budget)
			+ serialized_size(obj.n_tiles)
			+ serialized_size(obj.max_x)
			+ serialized_size(obj.max_y)
			+ serialized_size(obj.min_x)
			+ serialized_size(obj.min_y)
			+ serialized_size(obj.supply_limit)
			+ serialized_size(obj.supply_rem)
			+ serialized_size(obj.worker_pool)
			+ serialized_size(obj.owner)
			+ serialized_size(obj.nucleuses)
			+ serialized_size(obj.neighbours)
			+ serialized_size(obj.stockpile)
			+ serialized_size(obj.industries)
			+ serialized_size(obj.products)
			+ serialized_size(obj.pops)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<Company> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Company& obj) {
		::serialize(output, obj.name);
		
		::serialize(output, obj.money);
		::serialize(output, obj.is_transport);
		::serialize(output, obj.is_retailer);
		::serialize(output, obj.is_industry);
		
		::serialize(output, obj.operating_provinces);
	}
	static inline void deserialize(Archive& input, Company& obj) {
		::deserialize(input, obj.name);
		
		::deserialize(input, obj.money);
		::deserialize(input, obj.is_transport);
		::deserialize(input, obj.is_retailer);
		::deserialize(input, obj.is_industry);
		
		::deserialize(input, obj.operating_provinces);
		
		// TODO: Rest of fields
	}
	static inline size_t size(const Company& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.money)
			+ serialized_size(obj.is_transport)
			+ serialized_size(obj.is_retailer)
			+ serialized_size(obj.is_industry)
			+ serialized_size(obj.operating_provinces)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<Industry> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Industry& obj) {
		::serialize(output, obj.owner);
		::serialize(output, obj.type);
		
		::serialize(output, obj.days_unoperational);
		::serialize(output, obj.production_cost);
		
		::serialize(output, obj.stockpile);
		::serialize(output, obj.output_products);
		
		::serialize(output, obj.min_quality);
		::serialize(output, obj.willing_payment);
	}
	static inline void deserialize(Archive& input, Industry& obj) {
		::deserialize(input, obj.owner);
		::deserialize(input, obj.type);
		
		::deserialize(input, obj.days_unoperational);
		::deserialize(input, obj.production_cost);
		
		::deserialize(input, obj.stockpile);
		::deserialize(input, obj.output_products);
		
		::deserialize(input, obj.min_quality);
		::deserialize(input, obj.willing_payment);
	}
	static inline size_t size(const Industry& obj) {
		return
			serialized_size(obj.owner)
			+ serialized_size(obj.type)
			+ serialized_size(obj.days_unoperational)
			+ serialized_size(obj.production_cost)
			+ serialized_size(obj.stockpile)
			+ serialized_size(obj.output_products)
			+ serialized_size(obj.min_quality)
			+ serialized_size(obj.willing_payment)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<Product> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Product& obj) {
		::serialize(output, obj.owner);
		::serialize(output, obj.origin);
		::serialize(output, obj.industry);
		::serialize(output, obj.good);
		
		::serialize(output, obj.price);
		::serialize(output, obj.price_vel);
		::serialize(output, obj.quality);
		::serialize(output, obj.supply);
		::serialize(output, obj.demand);
	}
	static inline void deserialize(Archive& input, Product& obj) {
		::deserialize(input, obj.owner);
		::deserialize(input, obj.origin);
		::deserialize(input, obj.industry);
		::deserialize(input, obj.good);
		
		::deserialize(input, obj.price);
		::deserialize(input, obj.price_vel);
		::deserialize(input, obj.quality);
		::deserialize(input, obj.supply);
		::deserialize(input, obj.demand);
	}
	static inline size_t size(const Product& obj) {
		return
			serialized_size(obj.owner)
			+ serialized_size(obj.origin)
			+ serialized_size(obj.industry)
			+ serialized_size(obj.good)
			+ serialized_size(obj.price)
			+ serialized_size(obj.price_vel)
			+ serialized_size(obj.quality)
			+ serialized_size(obj.supply)
			+ serialized_size(obj.demand)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<IndustryType> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const IndustryType& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		
		::serialize(output, obj.inputs);
		::serialize(output, obj.outputs);
		
		// TODO: Image texture serialized here
	}
	static inline void deserialize(Archive& input, IndustryType& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		
		::deserialize(input, obj.inputs);
		::deserialize(input, obj.outputs);
	}
	static inline size_t size(const IndustryType& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.inputs)
			+ serialized_size(obj.outputs)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<Good> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Good& obj) {
		::serialize(output, obj.name);
		::serialize(output, obj.ref_name);
		::serialize(output, obj.is_edible);
	}
	static inline void deserialize(Archive& input, Good& obj) {
		::deserialize(input, obj.name);
		::deserialize(input, obj.ref_name);
		::deserialize(input, obj.is_edible);
	}
	static inline size_t size(const Good& obj) {
		return
			serialized_size(obj.name)
			+ serialized_size(obj.ref_name)
			+ serialized_size(obj.is_edible)
		;
	}
};

template<>
class Serializer<Event> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, const Event& obj) {
		::serialize(output, obj.ref_name);
		::serialize(output, obj.conditions_function);
		::serialize(output, obj.do_event_function);
		::serialize(output, obj.receivers);
		
		// TODO: Descicions should not be pointers
	}
	static inline void deserialize(Archive& input, Event& obj) {
		::deserialize(input, obj.ref_name);
		::deserialize(input, obj.conditions_function);
		::deserialize(input, obj.do_event_function);
		::deserialize(input, obj.receivers);
		
		// TODO: Rest of fields
	}
	static inline size_t size(const Event& obj) {
		return
			serialized_size(obj.ref_name)
			+ serialized_size(obj.conditions_function)
			+ serialized_size(obj.do_event_function)
			+ serialized_size(obj.receivers)
		;
		// TODO: Rest of fields
	}
};

template<>
class Serializer<World> {
public:
	static constexpr bool is_const_size = false;
	static inline void serialize(Archive& output, World const& obj) {
		::serialize(output, obj.width);
		::serialize(output, obj.height);
		::serialize(output, obj.sea_level);
		::serialize(output, obj.time);

		for(size_t i = 0; i < obj.width * obj.height; i++) {
			::serialize(output, obj.tiles[i]);
		}
		
		::serialize(output, obj.delivers);
		::serialize(output, obj.orders);
		
		const uint32_t n_goods = obj.goods.size();
		::serialize(output, n_goods);
		for(const auto& good: obj.goods) {
			::serialize(output, *good);
		}
		
		const uint32_t n_industry_types = obj.industry_types.size();
		::serialize(output, n_industry_types);
		for(const auto& industry_type: obj.industry_types) {
			::serialize(output, *industry_type);
		}
		
		const uint32_t n_unit_types = obj.unit_types.size();
		::serialize(output, n_unit_types);
		for(const auto& unit_type: obj.unit_types) {
			::serialize(output, *unit_type);
		}
		
		const uint32_t n_religions = obj.religions.size();
		::serialize(output, n_religions);
		for(const auto& religion: obj.religions) {
			::serialize(output, *religion);
		}
		
		const uint32_t n_cultures = obj.cultures.size();
		::serialize(output, n_cultures);
		for(const auto& culture: obj.cultures) {
			::serialize(output, *culture);
		}
		
		const uint32_t n_pop_types = obj.pop_types.size();
		::serialize(output, n_pop_types);
		for(const auto& pop_type: obj.pop_types) {
			::serialize(output, *pop_type);
		}
		
		const uint32_t n_nations = obj.nations.size();
		::serialize(output, n_nations);
		for(const auto& nation: obj.nations) {
			::serialize(output, *nation);
		}
		
		const uint32_t n_provinces = obj.provinces.size();
		::serialize(output, n_provinces);
		for(const auto& province: obj.provinces) {
			::serialize(output, *province);
		}
		
		const uint32_t n_companies = obj.companies.size();
		::serialize(output, n_companies);
		for(const auto& company: obj.companies) {
			::serialize(output, *company);
		}
		
		const uint32_t n_products = obj.products.size();
		::serialize(output, n_products);
		for(const auto& product: obj.products) {
			::serialize(output, *product);
		}
		
		const uint32_t n_events = obj.events.size();
		::serialize(output, n_events);
		for(const auto& event: obj.events) {
			::serialize(output, *event);
		}
	}
	static inline void deserialize(Archive& input, World& obj) {
		::deserialize(input, obj.width);
		::deserialize(input, obj.height);
		::deserialize(input, obj.sea_level);
		::deserialize(input, obj.time);

		obj.tiles = new Tile[obj.width * obj.height];
		for(size_t i = 0; i < obj.width * obj.height; i++) {
			::deserialize(input, obj.tiles[i]);
		}

		::deserialize(input, obj.delivers);
		::deserialize(input, obj.orders);
		
		uint32_t n_goods;
		::deserialize(input, n_goods);
		for(size_t i = 0; i < n_goods; i++) {
			Good * sub_obj = new Good();
			::deserialize(input, *sub_obj);
			obj.goods.push_back(sub_obj);
		}
		
		uint32_t n_industry_types;
		::deserialize(input, n_industry_types);
		for(size_t i = 0; i < n_industry_types; i++) {
			IndustryType * sub_obj = new IndustryType();
			::deserialize(input, *sub_obj);
			obj.industry_types.push_back(sub_obj);
		}
		
		uint32_t n_unit_types;
		::deserialize(input, n_unit_types);
		for(size_t i = 0; i < n_unit_types; i++) {
			UnitType * sub_obj = new UnitType();
			::deserialize(input, *sub_obj);
			obj.unit_types.push_back(sub_obj);
		}
		
		uint32_t n_religions;
		::deserialize(input, n_religions);
		for(size_t i = 0; i < n_religions; i++) {
			Religion * sub_obj = new Religion();
			::deserialize(input, *sub_obj);
			obj.religions.push_back(sub_obj);
		}
		
		uint32_t n_cultures;
		::deserialize(input, n_cultures);
		for(size_t i = 0; i < n_cultures; i++) {
			Culture * sub_obj = new Culture();
			::deserialize(input, *sub_obj);
			obj.cultures.push_back(sub_obj);
		}
		
		uint32_t n_pop_types;
		::deserialize(input, n_pop_types);
		for(size_t i = 0; i < n_pop_types; i++) {
			PopType * sub_obj = new PopType();
			::deserialize(input, *sub_obj);
			obj.pop_types.push_back(sub_obj);
		}
		
		uint32_t n_nations;
		::deserialize(input, n_nations);
		for(size_t i = 0; i < n_nations; i++) {
			Nation * sub_obj = new Nation();
			::deserialize(input, *sub_obj);
			obj.nations.push_back(sub_obj);
		}
		
		uint32_t n_provinces;
		::deserialize(input, n_provinces);
		for(size_t i = 0; i < n_provinces; i++) {
			Province * sub_obj = new Province();
			::deserialize(input, *sub_obj);
			obj.provinces.push_back(sub_obj);
		}
		
		uint32_t n_companies;
		::deserialize(input, n_companies);
		for(size_t i = 0; i < n_companies; i++) {
			Company * sub_obj = new Company();
			::deserialize(input, *sub_obj);
			obj.companies.push_back(sub_obj);
		}
		
		uint32_t n_products;
		::deserialize(input, n_products);
		for(size_t i = 0; i < n_products; i++) {
			Product * sub_obj = new Product();
			::deserialize(input, *sub_obj);
			obj.products.push_back(sub_obj);
		}
		
		uint32_t n_events;
		::deserialize(input, n_events);
		for(size_t i = 0; i < n_events; i++) {
			Event * sub_obj = new Event();
			::deserialize(input, *sub_obj);
			obj.events.push_back(sub_obj);
		}
	}
	static inline size_t size(World const& obj) {
		return
			serialized_size(obj.width)
			+ serialized_size(obj.height)
			+ serialized_size(obj.sea_level)
			+ serialized_size(obj.time)
			+ serialized_size(obj.delivers)
			+ serialized_size(obj.orders)
			+ (sizeof(Tile) * (obj.width * obj.height))
			+ (obj.goods.size() * sizeof(Good))
			+ (obj.industry_types.size() * sizeof(IndustryType))
			+ (obj.unit_types.size() * sizeof(UnitType))
			+ (obj.religions.size() * sizeof(Religion))
			+ (obj.cultures.size() * sizeof(Culture))
			+ (obj.pop_types.size() * sizeof(PopType))
			+ (obj.nations.size() * sizeof(Nation))
			+ (obj.provinces.size() * sizeof(Province))
			+ (obj.companies.size() * sizeof(Company))
			+ (obj.products.size() * sizeof(Product))
			+ (obj.events.size() * sizeof(Event))
		;
	}
};

#endif
