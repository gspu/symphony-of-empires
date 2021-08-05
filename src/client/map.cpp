#include <algorithm>
#include <functional>
#include <execution>
#include <mutex>
#include <cstdlib>
#include <cstring>
#include <GL/glu.h>

#include "map.hpp"
#include "path.hpp"
#include "print.hpp"

extern TextureManager* g_texture_manager;
Map::Map(const World& _world) : world(_world) {
    std::lock_guard<std::recursive_mutex> lock(world.provinces_mutex);

    print_info("Creating province meshes");
    for(const auto& province: world.provinces) {
        ProvinceShape pr_shape = ProvinceShape(*this, *province);
        province_shapes.push_back(pr_shape);
    }

    overlay_tex = &g_texture_manager->load_texture(Path::get("ui/map_overlay.png"));
    
    print_info("Creating topo map");
    // Generate the underlying topo map texture, since the topo map
    // dosen't changes too much we can just do a texture
    topo_tex = new Texture(world.width, world.height);
    for(size_t i = 0; i < world.width * world.height; i++) {
        uint8_t r, g, b;
        const Tile& tile = world.get_tile(i);
        
        if(tile.elevation <= world.sea_level) {
            r = 8;
            g = 8;
            b = 128;
        } else {
            r = 8;
            g = tile.elevation;
            b = 8;
        }
        topo_tex->buffer[i] = (0xff << 24) | (b << 16) | (g << 8) | (r);
    }
    topo_tex->to_opengl();
}

void Map::draw_flag(const Texture* flag, int x, int y) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINE_STRIP);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(x, y, 0.f);
        glVertex3f(x, y, -2.f);
    glEnd();

    // Draw a flag that "waves" with some cheap wind effects it
    // looks nice and it's super cheap to make - only using sine
    const float n_steps = 8.f; // Resolution of flag in one side (in vertices)
    const float step = 90.f; // Steps per vertice
    glBindTexture(GL_TEXTURE_2D, flag->gl_tex_num);

    // sin_r - Sin'ed iterator along with the wind oscillator
    glBegin(GL_TRIANGLE_STRIP);
    for(float r = 0.f; r <= (n_steps * step); r += step) {
        float sin_r;

        sin_r = sin(r + wind_osc) / 24.f;
        glColor3f((sin_r * 18.f) + 0.5f, (sin_r * 18.f) + 0.5f, (sin_r * 18.f) + 0.5f);
        glTexCoord2f((r / step) / n_steps, 1.f);
        glVertex3f(x + (((r / step) / n_steps) * 1.5f), y + sin_r, -2.f);

        sin_r = sin(r + wind_osc + 245.f) / 24.f;
        glColor3f((sin_r * 18.f) + 0.5f, (sin_r * 18.f) + 0.5f, (sin_r * 18.f) + 0.5f);
        glTexCoord2f((r / step) / n_steps, 0.f);
        glVertex3f(x + (((r / step) / n_steps) * 1.5f), y + sin_r, -1.f);
    }
    glEnd();
}

extern TextureManager* g_texture_manager;
void Map::draw(Camera& cam, const int width, const int height) {
    // Topo map texture
    glBindTexture(GL_TEXTURE_2D, topo_tex->gl_tex_num);
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex2f(0.f + world.width, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex2f(0.f + world.width, 0.f + world.height);
    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, 0.f + world.height);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    for(size_t i = 0; i < world.provinces.size(); i++) {
        if(world.provinces[i]->owner != nullptr) {
            uint32_t& color = world.provinces[i]->owner->color;
            glColor4ub(color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff, 0xc0);
        } else {
            glColor4ub(0x80, 0x80, 0x80, 0xc0);
        }

        glCallList(province_shapes[i].shape_gl_list);

        //glColor4f(0.f, 0.f, 0.f, 0.5f);
        //glCallList(province_shapes[i].outline_gl_list);
    }
    glCallList(coastline_gl_list);

    /*glBindTexture(GL_TEXTURE_2D, overlay_tex->gl_tex_num);
    glBegin(GL_QUADS);
    glColor4f(1.f, 1.f, 1.f, 0.8f);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex2f(0.f + world.width, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex2f(0.f + world.width, 0.f + world.height);
    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, 0.f + world.height);
    glEnd();*/
    glBindTexture(GL_TEXTURE_2D, 0);
}

ProvinceShape::ProvinceShape(const Map& map, const Province& base) {
    Province::Id province_id = map.world.get_id(&base);

    shape_gl_list = glGenLists(1);
    glNewList(shape_gl_list, GL_COMPILE);

    const size_t min_x = std::min(base.min_x, map.world.width - 1);
    const size_t min_y = std::min(base.min_y, map.world.height - 1);
    const size_t max_x = std::min(base.max_x, map.world.width - 1);
    const size_t max_y = std::min(base.max_y + 1, map.world.height - 1);
    for(size_t y = min_y; y < max_y; y++) {
        for(size_t x = min_x; x < max_x; x++) {
            Tile& tile = map.world.get_tile(x, y);
            if(tile.province_id != province_id)
                continue;
            
            std::pair<size_t, size_t> start = std::make_pair(x, y);
            size_t len = 1;
            while(x < max_x) {
                if(tile.province_id != province_id) {
                    len--;
                    x--;
                    break;
                }
                len++;
                x++;
                tile = map.world.get_tile(x, y);
            }

            glBegin(GL_QUADS);
            glVertex2f(start.first, start.second);
            glVertex2f(start.first, start.second + 1.f);
            glVertex2f(start.first + len, start.second + 1.f);
            glVertex2f(start.first + len, start.second);
            glEnd();
        }
    }
    glEndList();

    outline_gl_list = glGenLists(1);
    glNewList(outline_gl_list, GL_COMPILE);
    for(size_t y = min_y; y < max_y; y++) {
        if(y == 0) {
            continue;
        }
        for(size_t x = min_x; x < max_x; x++) {
            if(x == 0) {
                continue;
            }

            const Tile& left_tile = map.world.get_tile(x - 1, y);
            const Tile& top_tile = map.world.get_tile(x, y - 1);
            const Tile& tile = map.world.get_tile(x, y);
                
            if(left_tile.province_id != tile.province_id) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(x, y);
                glVertex2f(x, y + 1.f);
                glEnd();
            }
                
            if(top_tile.province_id != tile.province_id) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(x, y);
                glVertex2f(x + 1.f, y);
                glEnd();
            }
        }
    }
    glEndList();
}
