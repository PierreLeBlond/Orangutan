#include "core/texture.h"

#include "core/debug.h"

#include <nanogui/opengl.h>

#include <util/image.h>

#include <SOIL.h>

#include <iostream>
#include <memory>

using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;

Texture::Texture() : _id(-1) {
}

Texture::Texture(std::string path, std::string name) : Asset(name), _id(-1), _path(path), _type(O_TEXTURE_2D) {
    load(path);
}

unsigned int Texture::getId() const {
    return _id;
}

bool Texture::load(std::string path) {

    _type = O_TEXTURE_2D;

    _path = path;

    int w = 0, h = 0;

    void* data = Image::loadPNG(path.c_str(), &w, &h);

    if(data != NULL)
    {
        glActiveTexture(GL_TEXTURE0 + 0);

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        std::cout << "Bind texture to id " << _id << std::endl;

        return true;
    }

    return false;


        /*_id = SOIL_load_OGL_texture
            (
                path.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );*/


    /*
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

    glBindTexture(GL_TEXTURE_2D, 0);*/
}

void Texture::loadCubeMap(std::string path_prefix)
{
    _type = O_TEXTURE_CUBE_MAP;

    const char* suffixes[] = { "posx", "negx", "posy", "negy", "negz", "posz"};
    std::string baseFileName = path_prefix;
    std::string extension = ".png";

    /*_id = SOIL_load_OGL_cubemap
        (
            (path_prefix + suffixes[0] + extension).c_str(),
            (path_prefix + suffixes[1] + extension).c_str(),
            (path_prefix + suffixes[2] + extension).c_str(),
            (path_prefix + suffixes[3] + extension).c_str(),
            (path_prefix + suffixes[4] + extension).c_str(),
            (path_prefix + suffixes[5] + extension).c_str(),
            SOIL_LOAD_RGB,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
        );
*/
    glActiveTexture(GL_TEXTURE0 + 0);
    //glEnable(GL_TEXTURE_CUBE_MAP);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

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
        std::string texName = baseFileName + suffixes[i] + extension;
        int w = 0, h = 0;
        void* data = Image::loadPNG(texName.c_str(), &w, &h);
        if(data != NULL)
            glTexImage2D(targets[i], 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
