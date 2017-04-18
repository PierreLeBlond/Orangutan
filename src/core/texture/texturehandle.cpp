#include "core/texture/texturehandle.h"

#include <nanogui/opengl.h>

TextureHandle::TextureHandle()
{
    glGenTextures(1, &_id);
}

TextureHandle::TextureHandle(TextureHandle&& handle) noexcept
{
    _id = handle._id;
    handle._id = 0;
}

TextureHandle::~TextureHandle() noexcept
{
    glDeleteTextures(1, &_id);
}

TextureHandle& TextureHandle::operator=(TextureHandle&& handle)
{
    glDeleteTextures(1, &_id);
    _id = handle._id;
    handle._id = 0;
    return *this;
}

