#pragma once
#include <GL/glew.h>
#include "RawModel.h"

namespace Zenith {
    struct ModelTexture {
        ModelTexture() {}
        ModelTexture(int ID) { id = ID; }
        GLuint id = 0;
        unsigned int width = 0;
        unsigned int height = 0;
    };

    class TexturedModel {
    public:
        TexturedModel() {}
        TexturedModel(const RawModel& model, const ModelTexture& texture) :
            m_rawModel(model), m_texture(texture) { }

        const RawModel& getRawModel() const { return m_rawModel; }
        const ModelTexture& getTexture() const { return m_texture; }
    private:
        RawModel m_rawModel;
        ModelTexture m_texture;
    };
}