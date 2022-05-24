#include "core/texture/texture.h"

#include <nanogui/opengl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace orangutan {

Texture::Texture(const std::string &name) : Asset(name) {}
Texture::Texture(const std::string &name, TextureHandle handle)
    : Asset(name), _handle(std::move(handle)) {}

unsigned int Texture::getId() const { return _handle.getId(); }

TextureHandle &Texture::getHandle() { return _handle; }

const std::string &Texture::getPath() const { return _path; }
void Texture::setPath(const std::string &path) { _path = path; };

unsigned int Texture::get_width() const { return width_; }
void Texture::set_width(unsigned int width) { width_ = width; }
unsigned int Texture::get_height() const { return height_; }
void Texture::set_height(unsigned int height) { height_ = height; }

}  // namespace orangutan

