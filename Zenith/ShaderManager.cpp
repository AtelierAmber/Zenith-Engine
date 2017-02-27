#include "ShaderManager.h"

#include "IShaderProgram.h"

#include <iostream>

namespace Zenith {
    ShaderManager::ShaderManager() { }

    ShaderManager::~ShaderManager() {}

    void ShaderManager::construct(Logger* logger) {
        logger->construct("render.log", "SHDR");
        m_logger = logger;
    }

    unsigned int ShaderManager::addProgram(IShaderProgram* program, const unsigned int& vbo, const unsigned int& ebo) {
        program->m_shaderLog = m_logger;
        program->construct();
        program->setupVAO(vbo, ebo);
        program->bindAttributes();
        program->link();
        m_programs.push_back(program);
        return (int)m_programs.size()-1;
    }

    void ShaderManager::useProgram(unsigned int index) {

        if (index < m_programs.size()) {
            m_programs[index]->use();
            m_programs[index]->loadUniforms();
        }
        else std::cerr << "Trying to use shader index " << index << " that has not been added!";
    }

    void ShaderManager::endProgram(unsigned int index) {
        if (index < m_programs.size()) {
            m_programs[index]->end();
        }
        else std::cerr << "Trying to end shader index " << index << " that has not been added!";
    }

    void ShaderManager::dispose() {
        if (m_programs.size() > 0) {
            for (auto& program : m_programs) {
                program->dispose();
                delete program;
            }
            m_programs.resize(0);
        }
    }
}