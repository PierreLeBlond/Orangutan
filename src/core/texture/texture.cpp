#include "core/texture/texture.h"

Texture::Texture(const std::string &name) : Asset(name) {
}

Texture::Texture(const std::string &path, const std::string &name) : Asset(name), _path(path) {
}

unsigned int Texture::getId() const {
    return _handle.getId();
}

const std::string &Texture::getPath() const
{
    return _path;
}

