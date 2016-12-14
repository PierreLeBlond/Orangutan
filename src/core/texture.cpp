#include "core/texture.h"
#include "core/debug.h"

#include <iostream>

Texture::Texture() : _id(-1) {
}

Texture::Texture(std::string path, std::string name) : Asset(name), _id(-1), _path(path), _type(GL_TEXTURE_2D), _image(QString::fromStdString(_path)) {
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);


    OpenGLFunction::functions().glGenTextures(1, &_id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, _id);
    std::cout << "Bind texture to id " << _id << std::endl;

    _image = _image.convertToFormat(QImage::Format_ARGB32);
    _image = _image.rgbSwapped();
    _image = _image.mirrored();
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getId() const {
    return _id;
}

void Texture::load(std::string path) {

    _path = path;

    _image.load(QString::fromStdString(_path));

    _type = GL_TEXTURE_2D;

    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);

    OpenGLFunction::functions().glGenTextures(1, &_id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, _id);

    //_image = _image.convertToFormat(QImage::Format_ARGB32);
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadCubeMap(std::string path_prefix)
{
    _type = GL_TEXTURE_CUBE_MAP;

    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //OpenGLFunction::functions().glEnable(GL_TEXTURE_CUBE_MAP);

    OpenGLFunction::functions().glGenTextures(1, &_id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

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
        QImage img(texName.c_str());
        img = img.rgbSwapped();
        OpenGLFunction::functions().glTexImage2D(targets[i], 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }

    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
