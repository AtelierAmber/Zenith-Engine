#pragma  once
#include "Rendering/TexturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Zenith {
    class Entity {
    public:
        Entity() {}
        Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale) :
            m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) {}

        void move(glm::vec3 moveVec) { m_position += moveVec; }
        void rotate(glm::vec3 rotVec) { m_rotation += rotVec; }

        const TexturedModel& getModel() const { return m_model; }
        void setModel(TexturedModel val) { m_model = val; }
        const glm::vec3& getPosition() const { return m_position; }
        void setPosition(glm::vec3 val) { m_position = val; }
        const glm::vec3& getRotation() const { return m_rotation; }
        void setRotation(glm::vec3 val) { m_rotation = val; }
        float getScale() const { return m_scale; }
        void setScale(float val) { m_scale = val; }


        glm::mat4 transform(const glm::vec3& translation, float rx, float ry, float rz, float scale) const;
        glm::mat4 transform(const glm::vec3& translation, const glm::vec3& rotation, float scale) const {
            return transform(translation, rotation.x, rotation.y, rotation.z, scale);
        }

    protected:

    private:
        TexturedModel m_model;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        float m_scale;
    };
}