#include "client/interface/minimap.hpp"
#include "client/map.hpp"
#include "world.hpp"
#include "unified_render/path.hpp"
#include "unified_render/texture.hpp"
#include <unordered_map>
#include "client/ui/button.hpp"
#include "client/ui/close_button.hpp"
#include "client/ui/image.hpp"
#include "client/ui/tooltip.hpp"

#include <math.h>

using namespace Interface;

std::vector<ProvinceColor> terrain_map_mode(const World& world);
std::vector<ProvinceColor> terrain_color_map_mode(const World& world);
std::vector<ProvinceColor> population_map_mode(const World& world);
std::vector<ProvinceColor> culture_map_mode(const World& world);
std::vector<ProvinceColor> religion_map_mode(const World& world);

Minimap::Minimap(GameState& _gs, int x, int y, UI::Origin origin)
    : UI::Window(x, y, 300, 256),
    gs{ _gs }
{
    this->origin = origin;
    this->is_pinned = true;
    this->is_scroll = false;
    this->text("Minimap");

    auto* flat_btn = new UI::Button(50, -48, 80, 24, this);
    flat_btn->user_data = this;
    flat_btn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;

		state->gs.map->set_view(MapView::PLANE_VIEW);
    });
    flat_btn->text("Flat");

    auto* globe_btn = new UI::Button(130, -48, 80, 24, this);
    globe_btn->user_data = this;
    globe_btn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;

		state->gs.map->set_view(MapView::SPHERE_VIEW);
    });
    globe_btn->text("Globe");
    
    auto* political_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    political_ibtn->user_data = this;
    political_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = political_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    political_ibtn->tooltip = new UI::Tooltip(political_ibtn, 512, 24);
    political_ibtn->tooltip->text("Political");

    auto* terrain_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    terrain_ibtn->right_side_of(*political_ibtn);
    terrain_ibtn->user_data = this;
    terrain_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = terrain_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    terrain_ibtn->tooltip = new UI::Tooltip(terrain_ibtn, 512, 24);
    terrain_ibtn->tooltip->text("Political");

    auto* population_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    population_ibtn->right_side_of(*terrain_ibtn);
    population_ibtn->user_data = this;
    population_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = population_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    population_ibtn->tooltip = new UI::Tooltip(population_ibtn, 512, 24);
    population_ibtn->tooltip->text("Population");

    auto* terrain_color_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    terrain_color_ibtn->right_side_of(*population_ibtn);
    terrain_color_ibtn->user_data = this;
    terrain_color_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = terrain_color_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    terrain_color_ibtn->tooltip = new UI::Tooltip(terrain_color_ibtn, 512, 24);
    terrain_color_ibtn->tooltip->text("Terrain type");

    auto* culture_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    culture_ibtn->right_side_of(*terrain_color_ibtn);
    culture_ibtn->user_data = this;
    culture_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = culture_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    culture_ibtn->tooltip = new UI::Tooltip(culture_ibtn, 512, 24);
    culture_ibtn->tooltip->text("Culture diversity");

    auto* religion_ibtn = new UI::Image(0, 0, 32, 32, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/noicon.png")), this);
    religion_ibtn->right_side_of(*culture_ibtn);
    religion_ibtn->user_data = this;
    religion_ibtn->on_click = ([](UI::Widget& w, void* data) {
        Minimap* state = (Minimap*)data;
        mapmode_generator map_mode = religion_map_mode;
        state->gs.map->set_map_mode(map_mode);
    });
    religion_ibtn->tooltip = new UI::Tooltip(religion_ibtn, 512, 24);
    religion_ibtn->tooltip->text("Religion");

    auto* img = new UI::Image(0, 24, 300, 150, &UnifiedRender::State::get_instance().tex_man->load(Path::get("ui/globe.png")), this);
    img->below_of(*religion_ibtn);
}

std::vector<ProvinceColor> terrain_map_mode(const World& world) {
    std::vector<ProvinceColor> province_color;
    for(unsigned int i = 0; i < world.provinces.size(); i++) {
        province_color.push_back(ProvinceColor(i, UnifiedRender::Color::rgba32(0x00000000)));
    }
    // Water
    province_color.push_back(ProvinceColor((Province::Id)-2, UnifiedRender::Color::rgba32(0x00000000)));
    // Land
    province_color.push_back(ProvinceColor((Province::Id)-1, UnifiedRender::Color::rgba32(0x00000000)));
    return province_color;
}

std::vector<ProvinceColor> terrain_color_map_mode(const World& world) {
    std::vector<ProvinceColor> province_color;
    for(unsigned int i = 0; i < world.provinces.size(); i++) {
        Province* province = world.provinces[i];
        UnifiedRender::Color color = UnifiedRender::Color::rgba32(province->terrain_type->color);
        province_color.push_back(ProvinceColor(i, color));
    }
    // Water
    province_color.push_back(ProvinceColor((Province::Id)-2, UnifiedRender::Color::rgba32(0x00000000)));
    // Land
    province_color.push_back(ProvinceColor((Province::Id)-1, UnifiedRender::Color::rgba32(0x00000000)));
    return province_color;
}

std::vector<ProvinceColor> population_map_mode(const World& world) {
    // Find the maximum amount of pops in one province
    std::vector<std::pair<Province::Id, float>> province_amounts;
    float max_amount = 1;
    for(auto const& province : world.provinces) {
        float amount = 0;
        for(auto const& pop : province->pops) {
            amount += pop.size;
        }
        amount = log2(amount + 1.f);
        max_amount = std::max<float>(amount, max_amount);
        province_amounts.push_back(std::make_pair(world.get_id(province), amount));
    }

    // Mix each color depending of how many live there compared to max_amount
    UnifiedRender::Color min = UnifiedRender::Color::rgb8(255, 229, 217);
    UnifiedRender::Color max = UnifiedRender::Color::rgb8(220, 46, 35);
    std::vector<ProvinceColor> province_color;
    for(auto const& prov_amount : province_amounts) {
        Province::Id prov_id = prov_amount.first;
        uint32_t amount = prov_amount.second;
        float ratio = amount / max_amount;
        UnifiedRender::Color color = UnifiedRender::Color::lerp(min, max, ratio);
        province_color.push_back(ProvinceColor(prov_id, color));
    }
    return province_color;
}

std::vector<ProvinceColor> culture_map_mode(const World& world) {
    std::vector<ProvinceColor> province_color;
    UnifiedRender::Color min = UnifiedRender::Color::rgb8(255, 255, 255);
    for(unsigned int i = 0; i < world.provinces.size(); i++) {
        Province* province = world.provinces[i];
        std::unordered_map<Culture::Id, size_t> culture_amounts;
        size_t total_amount = 0;
        size_t max_amount = 0;
        Culture::Id max_culture_id = 0;
        for(unsigned int j = 0; j < province->pops.size(); j++) {
            const Pop& pop = province->pops[j];
            total_amount += pop.size;

            auto search = culture_amounts.find(pop.culture->cached_id);
            if(search == culture_amounts.end()) {
                culture_amounts[pop.culture->cached_id] = pop.size;
            }
            else {
                culture_amounts[pop.culture->cached_id] += pop.size;
            }
            size_t amount = culture_amounts[pop.culture->cached_id];
            if(amount > max_amount) {
                max_amount = amount;
                max_culture_id = pop.culture->cached_id;
            }
        }
        UnifiedRender::Color max = UnifiedRender::Color::rgba32(world.cultures[max_culture_id]->color);
        UnifiedRender::Color color = UnifiedRender::Color::lerp(min, max, ((float)max_amount) / total_amount);
        province_color.push_back(ProvinceColor(i, color));
    }
    // Water
    province_color.push_back(ProvinceColor((Province::Id)-2, UnifiedRender::Color::rgba32(0x00000000)));
    // Land
    province_color.push_back(ProvinceColor((Province::Id)-1, UnifiedRender::Color::rgba32(0xffdddddd)));
    return province_color;
}

std::vector<ProvinceColor> religion_map_mode(const World& world) {
    std::vector<ProvinceColor> province_color;
    UnifiedRender::Color min = UnifiedRender::Color::rgb8(255, 255, 255);
    for(unsigned int i = 0; i < world.provinces.size(); i++) {
        Province* province = world.provinces[i];
        std::unordered_map<Religion::Id, size_t> religion_amounts;
        size_t total_amount = 0;
        size_t max_amount = 0;
        Religion::Id max_religion_id = 0;
        for(unsigned int j = 0; j < province->pops.size(); j++) {
            const Pop& pop = province->pops[j];
            total_amount += pop.size;

            auto search = religion_amounts.find(pop.religion->cached_id);
            if(search == religion_amounts.end()) {
                religion_amounts[pop.religion->cached_id] = pop.size;
            }
            else {
                religion_amounts[pop.religion->cached_id] += pop.size;
            }
            size_t amount = religion_amounts[pop.religion->cached_id];
            if(amount > max_amount) {
                max_amount = amount;
                max_religion_id = pop.religion->cached_id;
            }
        }
        UnifiedRender::Color max = UnifiedRender::Color::rgba32(world.religions[max_religion_id]->color);
        UnifiedRender::Color color = UnifiedRender::Color::lerp(min, max, ((float)max_amount) / total_amount);
        province_color.push_back(ProvinceColor(i, color));
    }
    // Water
    province_color.push_back(ProvinceColor((Province::Id)-2, UnifiedRender::Color::rgba32(0x00000000)));
    // Land
    province_color.push_back(ProvinceColor((Province::Id)-1, UnifiedRender::Color::rgba32(0xffdddddd)));
    return province_color;
}