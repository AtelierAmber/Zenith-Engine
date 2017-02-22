#include "ShaderManager.h"

#include "IShaderProgram.h"

#include <iostream>

namespace Zenith {
    ShaderManager::ShaderManager() {
        m_logger.construct("render.log", "SHDR");
    }

    ShaderManager::~ShaderManager() {}

    unsigned int ShaderManager::addProgram(IShaderProgram* program) {
        program->construct();
        program->link();
        m_programs.push_back(program);
        return m_programs.size()-1;
    }

    void ShaderManager::useProgram(unsigned int index) {
        if (index < m_programs.size()) {
            m_programs[index]->use();
        }
        else std::cerr << "Trying to use shader index " << index << " that has not been added!";
    }

    void ShaderManager::endProgram(unsigned int index) {
        if (index < m_programs.size()) {
            m_programs[index]->end();
        }
        else std::cerr << "Trying to use shader index " << index << " that has not been added!";
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