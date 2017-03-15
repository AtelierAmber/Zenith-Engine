#include "DataLoader.h"
#include "loadpng.h"
#include <fstream>

#include <GL/glew.h>

namespace Zenith{

    const Texture* TextureCache::add(const char* name, unsigned int id, 
        unsigned int width, unsigned int height) {
        if (!exists(name)) {
            m_cache[name] = Texture(id, width, height);
        }
        return get(name);
    }

    void TextureCache::remove(const char* name) {
        if (exists(name)) {
            m_cache.erase(name);
        }
    }

    const Texture* TextureCache::get(const char* name){
        if (exists(name)) {
            return &m_cache[name];
        }
        return nullptr;
    }

    bool TextureCache::exists(const char* name) const {
        return (m_cache.find(name) != m_cache.end());
    }

    /**************************************************************************/

    DataLoader::DataLoader(){
        m_logger.construct("data.log", "LOAD");
    }

    DataLoader::~DataLoader(){

    }

    const Texture* DataLoader::loadImage(const char* fileName, ImageFlag flags /*= DataFlag::NO_FLAGS*/) {
        std::vector<unsigned char> image;
        unsigned int width, height;

        unsigned int err = lodepng::decode(image, width, height, fileName);
        if (err) {
            m_logger.log("LOAD", LogType::ERROR, "Could not load image " + std::string(fileName) + "!!", err);
            return nullptr;
        }
        else {
            /* Flip the image to comply with opengl coordinate system */
            std::vector<unsigned char> correctedImage;
            for (int i = (int)image.size(); i > 0; i -= (width*4)) {
                for (unsigned int j = 0; j < width * 4; ++j) {
                    correctedImage.push_back(image[(i-(width*4))+j]);
                }
            }
            /* Setup the texture */
            unsigned int id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            if (flags & TEX_REPEAT) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            else if (flags & TEX_MIRROR) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            }
            else if (flags & TEX_CLAMP) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            else {
                m_logger.log("LOAD", LogType::WARNING, "Loaded image " + std::string(fileName) + " without specifying texture edge!");
            }

            if (flags & TEX_FILTER_LINEAR) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else if (flags & TEX_FILTER_NEAREST) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            else if(!(flags & TEX_FILTER_MIPMAP)){
                m_logger.log("LOAD", LogType::WARNING, "Loaded image " + std::string(fileName) + " without mipmap!");
            } 
            if (flags & TEX_FILTER_MIPMAP) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else {
                m_logger.log("LOAD", LogType::WARNING, "Loaded image " + std::string(fileName) + " without mipmap!");
            }

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &correctedImage[0]);
            if (flags & TEX_FILTER_MIPMAP) {
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            return (m_texCache.add(fileName, id, width, height));
        }
    }

    Zenith::Model DataLoader::loadOBJ(const char* fileName, ImageFlag flags /*= NO_FLAGS*/) {
        Model newModel;
        std::fstream fin;
        fin.open(fileName, std::ios::in | std::ios::binary);
        if (fin.fail()) {
            std::printf("Failed to open%s", fileName);
        }
        /* Materials */
        unsigned int numMats = 0;
        fin.read((char*)&numMats, sizeof(unsigned int));
        newModel.m_materials.resize(numMats);
        for (unsigned int i = 0; i < numMats; ++i) {
            std::string matName = "";
            std::getline(fin, matName);
            newModel.m_materialIndices[matName] = i;
            newModel.m_materials[i].name = matName;
            fin.read((char*)&newModel.m_materials[i].specularExponent, sizeof(float)); /* 4 being the size of float */
            fin.read((char*)&newModel.m_materials[i].refractionValue, sizeof(float));
            fin.read((char*)&newModel.m_materials[i].illumValue, sizeof(unsigned int)); /* 4U being the size of unsigned int */
            fin.read((char*)&newModel.m_materials[i].ambientColor, sizeof(unsigned char)*4);/* 4U being the size of unsigned char * 4 -> the size of ColorRGB8 */
            fin.read((char*)&newModel.m_materials[i].diffuseColor, sizeof(unsigned char)*4);
            fin.read((char*)&newModel.m_materials[i].specularColor, sizeof(unsigned char)*4);
        }
        /* Object Data */
        unsigned int numObj = 0;
        fin.read((char*)&numObj, sizeof(unsigned int));
        newModel.m_objects.resize(numObj);
        for (unsigned int i = 0; i < numObj; ++i) {
            auto& object = newModel.m_objects[i];
            std::getline(fin, object.name);
            /* Vertices */
            unsigned int numVert = 0;
            fin.read((char*)&numVert, sizeof(unsigned int));
            newModel.m_objects[i].vertices.resize(numVert);
            for (unsigned int v = 0; v < numVert; ++v) {
                fin.read((char*)&object.vertices[v].position.x, sizeof(float)); /* 4 being the size of float */
                fin.read((char*)&object.vertices[v].position.y, sizeof(float));
                fin.read((char*)&object.vertices[v].position.z, sizeof(float));
                fin.read((char*)&object.vertices[v].uv.u, sizeof(float));
                fin.read((char*)&object.vertices[v].uv.v, sizeof(float));
                fin.read((char*)&object.vertices[v].normal.nx, sizeof(float));
                fin.read((char*)&object.vertices[v].normal.ny, sizeof(float));
                fin.read((char*)&object.vertices[v].normal.nz, sizeof(float));
            }
            /* Face data */
            unsigned int numFace = 0;
            fin.read((char*)&numFace, sizeof(unsigned int));
            newModel.m_objects[i].faces.resize(numFace);
            for (unsigned int f = 0; f < numFace; ++f) {
                auto& object = newModel.m_objects[i];
                fin.read((char*)&object.faces[f].mat, sizeof(unsigned int));
                fin.read((char*)&object.faces[f].vi_A, sizeof(unsigned short));
                fin.read((char*)&object.faces[f].vi_B, sizeof(unsigned short));
                fin.read((char*)&object.faces[f].vi_C, sizeof(unsigned short));
                /* Set vertex diffuse colors */
                ColorRGBA8& vertColor = newModel.m_materials[object.faces[f].mat].diffuseColor;
                object.vertices[object.faces[f].vi_A].color = vertColor;
                object.vertices[object.faces[f].vi_B].color = vertColor;
                object.vertices[object.faces[f].vi_C].color = vertColor;
            }
        }
        fin.close();
        return newModel;
    }
}