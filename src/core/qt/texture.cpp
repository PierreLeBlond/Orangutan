#include "core/texture.h"

#include "core/debug.h"
#include "core/qt/context.h"
#include <iostream>
#include <QImage>

Texture::Texture() : _id(-1) {
}

Texture::Texture(std::string path, std::string name) : Asset(name), _id(-1), _path(path), _type(GL_TEXTURE_2D) {
    Context::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //Context::functions().glEnable(GL_TEXTURE_2D);

    Context::functions().glGenTextures(1, &_id);
    Context::functions().glBindTexture(GL_TEXTURE_2D, _id);
    std::cout << "Bind texture to id " << _id << std::endl;

    QImage image(QString::fromStdString(_path));
    image = image.convertToFormat(QImage::Format_ARGB32);
    image = image.rgbSwapped();
    image = image.mirrored();

    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getId() const {
    return _id;
}

void Texture::load(std::string path) {

    _path = path;

    QImage image(QString::fromStdString(_path));

    image = image.convertToFormat(QImage::Format_ARGB32);
    image = image.rgbSwapped();
    image = image.mirrored();

    _type = GL_TEXTURE_2D;

    Context::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //Context::functions().glEnable(GL_TEXTURE_2D);

    Context::functions().glGenTextures(1, &_id);
    Context::functions().glBindTexture(GL_TEXTURE_2D, _id);

    //_image = _image.convertToFormat(QImage::Format_ARGB32);
    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadCubeMap(std::string path_prefix)
{
    _type = GL_TEXTURE_CUBE_MAP;

    Context::functions().glActiveTexture(GL_TEXTURE0 + 0);
    //Context::functions().glEnable(GL_TEXTURE_CUBE_MAP);

    Context::functions().glGenTextures(1, &_id);
    Context::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

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
        Context::functions().glTexImage2D(targets[i], 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }

    Context::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    Context::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    Context::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Context::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
