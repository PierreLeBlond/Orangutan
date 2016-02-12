#include "texture.h"

Texture::Texture() : _id(-1) {
}

Texture::Texture(std::string path) : _id(-1), _path(path), _image(QString::fromStdString(_path)) {
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);

    OpenGLFunction::functions().glGenTextures(1, &_id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, _id);

    _image = _image.convertToFormat(QImage::Format_ARGB32);
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

    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);

    OpenGLFunction::functions().glGenTextures(1, &_id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, _id);

    _image = _image.convertToFormat(QImage::Format_ARGB32);
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
}

