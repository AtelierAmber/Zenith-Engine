#pragma once

#include "Logger.h"

#include <vector>

namespace Zenith {
    class IShaderProgram;
    class ShaderManager {
    public:
        ShaderManager();
        ~ShaderManager();

        void construct(Logger* logger);
        unsigned int addProgram(IShaderProgram* program, const unsigned int& vbo, const unsigned int& ebo);

        IShaderProgram* getProgram(unsigned int index) { 
            return (index < m_programs.size()) ? m_programs[index] : nullptr; 
        }

        void useProgram(unsigned int index);

        void endProgram(unsigned int index);

        void dispose();

    private:
        std::vector<IShaderProgram*> m_programs;
        Logger* m_logger;
    };
}