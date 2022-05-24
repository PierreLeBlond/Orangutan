#include "core/texture/cubetexture.h"

#include <nanogui/opengl.h>

#include <iostream>
#include <memory>

#include "core/debug.h"
#include "stb_image.h"

namespace orangutan {

CubeTexture::CubeTexture(const std::string &name) : Texture(name) {}

CubeTexture::CubeTexture(const std::string &name, TextureHandle handle)
    : Texture(name, std::move(handle)) {}

unsigned int CubeTexture::get_size() const { return size_; }
void CubeTexture::set_size(unsigned int size) { size_ = size; }

}  // namespace orangutan

