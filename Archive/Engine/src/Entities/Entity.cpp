#include "Entities/Entity.h"

namespace Zenith {
    glm::mat4 Entity::transform(const glm::vec3& translation, float rx, float ry, float rz, float scale) const {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix *= glm::translate(translation);
        matrix *= glm::rotate(rx, glm::vec3(1.0f, 0.0f, 0.0f));
        matrix *= glm::rotate(ry, glm::vec3(0.0f, 1.0f, 0.0f));
        matrix *= glm::rotate(rz, glm::vec3(0.0f, 0.0f, 1.0f));
        matrix *= scale;
        return matrix;
    }
}