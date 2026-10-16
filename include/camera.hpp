#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

enum class Dir {
    forward, backward, left, right
};

struct Camera {
    struct Default
    {
        static constexpr float Yaw         = -90.0f;
        static constexpr float Pitch       =  0.0f;
        static constexpr float Speed       =  2.5f;
        static constexpr float Sensitivity =  0.1f;
        static constexpr float Zoom        =  45.0f;
    };

    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_front{0.0f, 0.0f, -1.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_right{1.0f, 0.0f, 0.0f};
    static constexpr glm::vec3 m_worldUp{0.0f, 1.0f, 0.0f};

    float m_yaw = Default::Yaw;
    float m_pitch = Default::Pitch;
    float m_speed = Default::Speed;
    float m_sensitivity = Default::Sensitivity;
    float m_zoom = Default::Zoom;

    Camera() = default;
    Camera(const glm::vec3& position);

    glm::mat4 getViewMatrix();

    void processKeyboard(Dir direction, float dt);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);
private:
    void updateCameraVectors();
};