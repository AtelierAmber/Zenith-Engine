#include "Camera3D.h"

#include <glm/gtx/transform.hpp>

namespace Zenith {
    Camera3D::Camera3D() : 
        m_perspectiveMatrix(glm::mat4(1.0f)), m_viewMatrix(glm::mat4(1.0f)) , m_screenWidth(1080), m_screenHeight(720),
        m_position(glm::vec3(0.0f)), m_rotation(glm::vec3(0.0f, -90.0f, 0.0f)), m_fov(45.0f), m_near(0.1f), m_far(250.0f) { }

    Camera3D::~Camera3D() { }

    void Camera3D::init(unsigned int width, unsigned int height) {
        m_screenWidth = width;
        m_screenHeight = height;
        m_direction.x = glm::cos(glm::radians(m_rotation.x)) * glm::cos(glm::radians(m_rotation.y));
        m_direction.y = glm::sin(glm::radians(m_rotation.x));
        m_direction.z = glm::cos(glm::radians(m_rotation.x)) * glm::sin(glm::radians(m_rotation.y));
        m_direction = glm::normalize(m_direction);
        m_right = glm::normalize(glm::cross(m_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_up = glm::normalize(glm::cross(m_right, m_direction));
        update();
    }

    void Camera3D::update() {
        /* Update only when needed */
        if (m_needsUpdate) {
            m_perspectiveMatrix = glm::perspective(m_fov, (float)m_screenWidth / (float)m_screenHeight, m_near, m_far);
            m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
            m_viewMatrix = m_perspectiveMatrix * m_viewMatrix;
            m_needsUpdate = false;
        }
    }

}