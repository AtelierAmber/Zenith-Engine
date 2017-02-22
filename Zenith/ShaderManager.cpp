#include "ShaderManager.h"

#include "IShaderProgram.h"

namespace Zenith {
    ShaderManager::ShaderManager() {
        m_logger.construct("render.log", "SHDR");
    }

    ShaderManager::~ShaderManager() {}

    unsigned int ShaderManager::addProgram(IShaderProgram* program) {
        program->construct();
        program->compile();
        m_programs.push_back(program);
        return m_programs.size()-1;
    }

    void ShaderManager::construct() {
        for () {

        }
    }

    void ShaderManager::useProgram(unsigned int index) {

    }

    void ShaderManager::endProgram(unsigned int index) {

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