#pragma once
#include "Vertex.h"

#include <glm/glm.hpp>

namespace Zenith{
    class Model {
    public:
        Model(){}
        Model(std::vector<unsigned short> indicies, std::vector<Vertex> verticies,
            unsigned int textureID = 0) :
            m_indicies(indicies), m_vertices(verticies), m_textureID(textureID) {}

        void init(std::vector<unsigned short> indicies, std::vector<Vertex> verticies, 
            unsigned int textureID = 0) {
            m_indicies = indicies;
            m_vertices = verticies;
            m_textureID = textureID;
        }

        unsigned short* getIndicieRef() { return &m_indicies[0]; }
        Vertex* getVerticieRef() { return &m_vertices[0]; }
        unsigned int getNumIndicies() { return (unsigned int)m_indicies.size(); }

        const unsigned int& getTexture() { return m_textureID; }
        const std::vector<unsigned short>& getIndicies() { return m_indicies; }
        const std::vector<Vertex>& getVertices() { return m_vertices; }
    private:
        unsigned int m_textureID;
        std::vector<unsigned short> m_indicies;
        std::vector<Vertex> m_vertices;
    };
}