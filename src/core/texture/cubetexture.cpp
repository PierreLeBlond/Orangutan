#include "core/texture/cubetexture.h"
#include "core/debug.h"

#include <nanogui/opengl.h>

#include <util/image.h>

//#include <SOIL.h>

#include <iostream>
#include <memory>

//using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;

CubeTexture::CubeTexture(const std::string &name) : Texture(name)
{
}

CubeTexture::CubeTexture(const std::string &path, const std::string &name) :
    Texture(path, name)
{
    load(_path);
}

bool CubeTexture::load(const std::string &path)
{

    bool success = true;

    std::string suffixes[] = { "posx", "negx", "posy", "negy", "negz", "posz"};
    std::string baseFileName = path;
    std::string extension = ".png";

    _path = path + suffixes[0] + extension;

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
    //glActiveTexture(GL_TEXTURE0 + 0);

    unsigned int id = getId();

    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    for(int i = 0;i < 6 && success;i++)
    {
        std::string texName = baseFileName + suffixes[i] + extension;
        int w = 0, h = 0;
        unsigned char* data = Image::loadPNG(texName.c_str(), &w, &h);
        if(success = (success && data != nullptr))
        {
            glTexImage2D(targets[i], 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            delete[] data;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return success;
}

