#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position) : m_position(position) {}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(Dir direction, float dt)
{
    float velocity = m_speed * dt;

    switch (direction)
    {
    case Dir::forward:
        m_position += m_front * velocity;
        break;
    case Dir::backward:
        m_position -= m_front * velocity;
        break;
    case Dir::right:
        m_position += m_right * velocity;
        break;
    case Dir::left:
        m_position -= m_right * velocity;
        break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
        {
            m_pitch = 89.0f;
        }
        else if (m_pitch < -89.0f)
        {
            m_pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    m_zoom -= (float)yoffset;

    if (m_zoom < 1.0f)
    {
        m_zoom = 1.0f;
    }
    else if (m_zoom > 45.0f)
    {
        m_zoom = 45.0f;
    }
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

