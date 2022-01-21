#include "core/buffer/bufferhandle.h"

#include <nanogui/opengl.h>

BufferHandle::BufferHandle() : Handle() {
  unsigned int id = 0;
  glGenBuffers(1, &id);
  setId(id);
}

BufferHandle::BufferHandle(BufferHandle&& handle) noexcept : Handle() {
  setId(handle.getId());
  handle.setId(0);
}

BufferHandle::~BufferHandle() noexcept {
  unsigned int id = getId();
  glDeleteBuffers(1, &id);
}

BufferHandle& BufferHandle::operator=(BufferHandle&& handle) {
  unsigned int id = getId();
  glDeleteBuffers(1, &id);
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

