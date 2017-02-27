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
            m_position += pos;
            m_needsUpdate = true;
        }
        void setPosition(const glm::vec3& pos) {
            m_position = pos;
            m_needsUpdate = true;
        }
        void setCenterPosition(const glm::vec3& pos) { 
            m_position = glm::vec3(pos.x + m_screenWidth / 2, pos.y + m_screenHeight / 2, pos.z);
            m_needsUpdate = true;
        }
        void setRotation(const glm::vec3& rot) { 
            m_rotation = rot;
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
        glm::vec3 m_rotation;
        bool m_needsUpdate = true;
    };
}