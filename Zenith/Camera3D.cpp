#include "Camera3D.h"

#include <glm/gtx/transform.hpp>

namespace Zenith {
    Camera3D::Camera3D() : 
        m_perspectiveMatrix(glm::mat4(1.0f)), m_viewMatrix(glm::mat4(1.0f)) , m_screenWidth(1080), m_screenHeight(720),
        m_position(glm::vec3(0.0f)), m_rotation(glm::vec3(0.0f)), m_fov(90.0f), m_near(0.1f), m_far(100.0f) { }

    Camera3D::~Camera3D(){

    }

    void Camera3D::init(unsigned int width, unsigned int height) {
        m_screenWidth = width;
        m_screenHeight = height;
        m_perspectiveMatrix = glm::perspective(m_fov, (float)width / (float)height, m_near, m_far);
        update();
    }

    void Camera3D::update() {
        /* Update only when needed */
        if (m_needsUpdate) {
            //m_perspectiveMatrix = glm::perspective(m_fov, (float)m_screenWidth / (float)m_screenHeight, m_near, m_far);
            m_viewMatrix = glm::mat4(1.0f);
            m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            m_viewMatrix = glm::translate(m_viewMatrix, -m_position);
            m_viewMatrix *= m_perspectiveMatrix;
            m_needsUpdate = false;
        }
    }

}