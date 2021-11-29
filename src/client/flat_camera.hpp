#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

class FlatCamera: public Camera {
public:
    glm::vec3 velocity;

    FlatCamera(int width, int height): Camera(width, height) {
        position = glm::vec3(400, 200, -400.f);
        velocity = glm::vec3(0);
    }

    void move(float x_dir, float y_dir, float z_dir) override {
        velocity.x += x_dir;
        velocity.y += y_dir;
        velocity.z += z_dir;
    }

    void update(void) override {
        velocity.x = std::min(16.f, velocity.x);
        velocity.y = std::min(16.f, velocity.y);
        velocity.z = std::min(16.f, velocity.z);

        if(velocity.x >= 0.9f)
            velocity.x -= 0.8f;
        else if(velocity.x <= -0.9f)
            velocity.x += 0.8f;
        else
            velocity.x = 0.f;

        if(velocity.y >= 0.9f)
            velocity.y -= 0.8f;
        else if(velocity.y <= -0.9f)
            velocity.y += 0.8f;
        else
            velocity.y = 0.f;

        if(velocity.z >= 0.9f)
            velocity.z -= 0.8f;
        else if(velocity.z <= -0.9f)
            velocity.z += 0.8f;
        else
            velocity.z = 0.f;

        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;

        position.x = std::max(0.f, std::min((float)g_world->width, position.x));
        position.y = std::max(0.f, std::min((float)g_world->height, position.y));
        position.z = -std::max(10.f, std::min((float)g_world->width / 2.f, -position.z));
    };

    void set_pos(float x, float y) override {
        position.x = x;
        position.y = y;
    }

    glm::mat4 get_projection() override {
        float aspect_ratio = screen_size.x / screen_size.y;
        return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
    };

    glm::mat4 get_view() override {
        glm::vec3 look_at = position;
        look_at.z = 0;
        look_at.y -= position.z > -200 ? 0.06f * (200 + position.z) : 0;
        glm::vec3 up_vector = glm::vec3(0.f, -1.f, 0.f);
        return glm::lookAt(position, look_at, up_vector);
    };

    std::pair<float, float> get_map_pos(std::pair<int, int> mouse_pos) override {
        float mouse_x = mouse_pos.first;
        float mouse_y = screen_size.y - 1.f - mouse_pos.second;

        glm::mat4 view = get_view();
        glm::mat4 projection = get_projection();

        glm::vec3 world_space_near = glm::unProject(
            glm::vec3(mouse_x, mouse_y, 0.f),
            view, projection,
            glm::vec4(0.f, 0.f, screen_size));

        glm::vec3 world_space_far = glm::unProject(
            glm::vec3(mouse_x, mouse_y, 1.f),
            view, projection,
            glm::vec4(0.f, 0.f, screen_size)
        );

        glm::vec3 ray_direction = world_space_far - world_space_near;

        float distance = 0.f;
        glm::intersectRayPlane(world_space_near, ray_direction, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), distance);

        glm::vec3 intersection_point = world_space_near + ray_direction * distance;
        return std::pair<float, float>(intersection_point.x, intersection_point.y);
    };
};