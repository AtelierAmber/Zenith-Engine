#pragma once
#include <unordered_map>
#include "Logger.h"

namespace Zenith {
    struct Texture {
        Texture() {}
        Texture(unsigned int ID, unsigned int Width, unsigned int Height) : 
            id(ID), width(Width), height(Height){}
        unsigned int id = 0;
        unsigned int width = 0, height = 0;
    };

    class TextureCache {
    public:
        /* Returns the texture of the added texture */
        const Texture* add(const char* name, unsigned int id, 
            unsigned int width, unsigned int height);
        void remove(const char* name);
        const Texture* get(const char* name);
        /* Checks if it exists already */
        bool exists(const char* name) const;
    private:
        /* Maps file names to texture id's to prevent duplicating data */
        std::unordered_map<const char*, Texture> m_cache;
    };

    enum DataFlag {
        NO_FLAGS = 0,
        TEX_REPEAT = 0b1,
        TEX_MIRROR = 0b10,
        TEX_CLAMP = 0b100,
        TEX_FILTER_LINEAR = 0b1000,
        TEX_FILTER_NEAREST = 0b10000,
        TEX_FILTER_MIPMAP = 0b100000
    };

    typedef unsigned int ImageFlag;

    class DataLoader
    {
    public:
        DataLoader();
        ~DataLoader();

        const Texture* loadImage(const char* fileName, ImageFlag flags = DataFlag::NO_FLAGS);
        ///unsigned int loadVolume();
    private:
        Logger m_logger;
        TextureCache m_texCache;
    };
}