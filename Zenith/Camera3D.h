#pragma once

#include <glm/glm.hpp>

namespace Zenith {
    class Camera3D
    {
    public:
        Camera3D();
        ~Camera3D();

        void init(unsigned int width, unsigned int height);

        void update();

        void move(const glm::vec3& pos) { 
            m_position += m_direction * pos.z;
            m_position += m_right * pos.x;
            m_position += m_up * pos.y;
            m_needsUpdate = true;
        }
        void rotate(const glm::vec3& rotation) {
            m_rotation += rotation;
            if (m_rotation.x > 89.0f) {
                m_rotation.x = 89.0f;
            }
            if (m_rotation.x < -89.0f) {
                m_rotation.x = -89.0f;
            }
            m_direction.x = glm::cos(glm::radians(m_rotation.x)) * glm::cos(glm::radians(m_rotation.y));
            m_direction.y = glm::sin(glm::radians(m_rotation.x));
            m_direction.z = glm::cos(glm::radians(m_rotation.x)) * glm::sin(glm::radians(m_rotation.y));
            m_direction = glm::normalize(m_direction);
            m_right = glm::normalize(glm::cross(m_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
            m_up = glm::normalize(glm::cross(m_right, m_direction));
            m_needsUpdate = true;
        }
        void setPosition(const glm::vec3& pos) {
            m_position = pos;
            m_needsUpdate = true;
        }
        void setRotation(const glm::vec3& rotation) {
            m_rotation = rotation;
            m_direction.x = glm::cos(glm::radians(m_rotation.x)) * glm::cos(glm::radians(m_rotation.y));
            m_direction.y = glm::sin(glm::radians(m_rotation.x));
            m_direction.z = glm::cos(glm::radians(m_rotation.x)) * glm::sin(glm::radians(m_rotation.y));
            m_direction = glm::normalize(m_direction);
            m_right = glm::normalize(glm::cross(m_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
            m_up = glm::normalize(glm::cross(m_right, m_direction));
            m_needsUpdate = true;
        }
        glm::mat4* getMatrix() { return &m_viewMatrix; }
        void setNear(float near) { 
            m_near = near;
            m_needsUpdate = true;
        }
        void setFar(float far) {
            m_far = far;
            m_needsUpdate = true;
        }
        void setFOV(float fov) {
            m_fov = fov; 
            m_needsUpdate = true;
        }
    private:
        glm::mat4 m_perspectiveMatrix;
        glm::mat4 m_viewMatrix;
        unsigned int m_screenWidth, m_screenHeight;
        float m_near, m_far, m_fov;
        glm::vec3 m_position;
        /* Rotation:
         * Pitch = x
         * Yaw = y
         * Roll = z 
         */
        glm::vec3 m_rotation;
        glm::vec3 m_direction;
        glm::vec3 m_right;
        glm::vec3 m_up;
        bool m_needsUpdate = true;
    };
}