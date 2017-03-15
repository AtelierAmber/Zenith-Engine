#pragma once
#include "Vertex.h"

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Zenith{

    struct Transform {
        Transform() { transformMatrix = glm::mat4(1.0f); }
        Transform(glm::vec3 pos, glm::vec3 rot, float Scale) :
            position(pos), rotation(rot), scale(Scale) {
            generate(); 
        }

        void generate() {
            transformMatrix = glm::mat4(1.0f);
            transformMatrix = glm::translate(transformMatrix, position);
            transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            transformMatrix *= scale;
        }

        glm::vec3 position;
        glm::vec3 rotation;
        float scale;
        glm::mat4 transformMatrix;
    };

    struct Mesh {
        Mesh(unsigned int offset, unsigned int NumIndicies, unsigned int texture, glm::mat4 Transform) :
            indexOffset(offset), numIndicies(NumIndicies), textureID(texture), transform(Transform) {}
        glm::mat4 transform;
        unsigned int indexOffset;
        unsigned int numIndicies;
        unsigned int textureID;
    };

    struct Material {
        Material() {}
        std::string name;

        void setTransparency(float Alpha) {
            if (Alpha > 1.0f || Alpha < 0.0f) {
                std::printf("UNDEFINED ALPHA VALUE %f", Alpha);
                return;
            }
            ambientColor.a = (GLubyte)(Alpha * 255);
            diffuseColor.a = (GLubyte)(Alpha * 255);
            specularColor.a = (GLubyte)(Alpha * 255);
        }

        float specularExponent = 0.0f;
        float refractionValue = 0.0f;
        unsigned int illumValue = 0;
        ColorRGBA8 ambientColor = ColorRGBA8();
        ColorRGBA8 diffuseColor = ColorRGBA8();
        ColorRGBA8 specularColor = ColorRGBA8();
    };

    struct Face {
        Face() {}
        Face(unsigned short A, unsigned short B, unsigned short C, unsigned int M) :
            vi_A(A), vi_B(B), vi_C(C), mat(M) {}

        unsigned short vi_A, vi_B, vi_C;
        unsigned int mat;
    };

    struct Object {
        Object() {}
        Object(std::string Name) : name(Name) {}

        unsigned int getNumFaces() const { return (unsigned int)faces.size(); }
        unsigned int getNumVerts() const { return (unsigned int)vertices.size(); }

        std::string name;

        std::vector<Vertex> vertices;
        std::vector<Face> faces;
    };

    class Model {
    public:
        friend class DataLoader;
        Model(){}
        Model(std::vector<Object> objects, std::vector<Material> materials, unsigned int textureID = 0) :
            m_objects(objects), m_materials(materials), m_textureID(textureID) {
            for (unsigned int i = 0; i < materials.size(); ++i) {
                m_materialIndices[materials[i].name] = i;
            }
        }

        void init(std::vector<Object> objects, std::vector<Material> materials, 
            unsigned int textureID = 0) {
            m_materials = materials;
            m_objects = objects;
            m_textureID = textureID;
        }

        const unsigned int& getTexture() { return m_textureID; }
        const std::vector<Object>& getObjects() { return m_objects; }
        const Material& getMaterial(std::string name) { return m_materials[m_materialIndices[name]]; }
        const Material& getMaterial(unsigned int index) { return m_materials[index]; }
    private:

        unsigned int m_textureID = 0;
        std::vector<Object> m_objects;

        std::vector<Material> m_materials;
        std::unordered_map<std::string, unsigned int> m_materialIndices;
    };

    struct TransformedModel {
        TransformedModel() {}
        TransformedModel(Transform transform, Model* modelPointer, std::vector<Transform> objectTransforms = {}) :
            m_transform(transform), ptr_model(modelPointer), m_objectTransforms(objectTransforms){}
        Transform m_transform;

        Model* ptr_model;
        /* Object transforms are set up in:
         * Position = position offset from the models position
         * Rotation = rotation from default rotation around -Position-
         * Scale    = scale of the object 
         */
        std::vector<Transform> m_objectTransforms;
    };
}