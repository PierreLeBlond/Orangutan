#include "core/texture/texturehandle.h"
#include "core/debug.h"

namespace orangutan {

TextureHandle::TextureHandle() : Handle() {
  unsigned int id = 0;
  GL_CHECK_ERROR(glGenTextures(1, &id));
  setId(id);
}

TextureHandle::TextureHandle(TextureHandle &&handle) noexcept : Handle() {
  setId(handle.getId());
  handle.setId(0);
}

TextureHandle::~TextureHandle() noexcept {
  unsigned int id = getId();
  GL_CHECK_ERROR(glDeleteTextures(1, &id));
}

TextureHandle &TextureHandle::operator=(TextureHandle &&handle) {
  unsigned int id = getId();
  GL_CHECK_ERROR(glDeleteTextures(1, &id));
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

} // namespace orangutan
