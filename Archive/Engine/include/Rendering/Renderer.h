#pragma once
#include "TexturedModel.h"

#include "Entities/Entity.h"
#include "Rendering/StaticShader.h"

namespace Zenith {
    class Renderer {
    public:
        void prepare();

        void render(const Entity& entity, StaticShader& shader);
    private:

    };
}