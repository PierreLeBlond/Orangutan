#include "texture.h"

Texture::Texture() : _nbTextures(0) {

}

unsigned int Texture::getNbTextures() const {
    return _nbTextures;
}

std::vector<GLuint> Texture::getIdTextures() const {
    return _idTextures;
}

void Texture::addTexture(GLuint id) {
    _idTextures.push_back(id);
}

void Texture::setTexture(GLuint id, int index){
    if(index < _idTextures.size()){
        _idTextures[index] = id;
    }else{
        addTexture(id);
    }
}

GLuint Texture::createTexture(QImage image) {
    GLuint id;

    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);

    OpenGLFunction::functions().glGenTextures(1, &id);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, id);

    image = image.convertToFormat(QImage::Format_ARGB32);
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

