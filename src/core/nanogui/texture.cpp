#include "core/texture.h"

#include "core/debug.h"

#include <nanogui/opengl.h>

#include <iostream>
#include <memory>

using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;

Texture::Texture() : _id(-1) {
}

Texture::Texture(std::string path, std::string name) : Asset(name), _id(-1), _path(path), _type(O_TEXTURE_2D) {
    glActiveTexture(GL_TEXTURE0 + 0);
    //glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    std::cout << "Bind texture to id " << _id << std::endl;

    int force_channels = 0;
    int w = 0, h = 0, n;
    //handleType image(stbi_load(fileName.c_str(), &w, &h, &n, force_channels), stbi_image_free);
    //if (!textureData)
        //throw std::invalid_argument("Could not load texture data from file " + fileName);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getId() const {
    return _id;
}

void Texture::load(std::string path) {

    _path = path;

    _type = O_TEXTURE_2D;

    int force_channels = 0;
    int w = 0, h = 0, n;
    //handleType image(stbi_load(fileName.c_str(), &w, &h, &n, force_channels), stbi_image_free);
    //if (!textureData)
        //throw std::invalid_argument("Could not load texture data from file " + fileName);


    glActiveTexture(GL_TEXTURE0 + 0);
    //glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    //_image = _image.convertToFormat(QImage::Format_ARGB32);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadCubeMap(std::string path_prefix)
{
    _type = O_TEXTURE_CUBE_MAP;

    glActiveTexture(GL_TEXTURE0 + 0);
    //glEnable(GL_TEXTURE_CUBE_MAP);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

    const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz"};
    std::string baseFileName = path_prefix;

    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    for(int i = 0;i < 6;i++)
    {
        std::string texName = baseFileName + suffixes[i];
        //load img here
        int w = 0, h = 0;
        glTexImage2D(targets[i], 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
