#include "core/vertex/vertexarrayhandle.h"

#include <nanogui/opengl.h>

namespace orangutan {

VertexArrayHandle::VertexArrayHandle() : Handle() {
  unsigned int id = 0;
  glGenVertexArrays(1, &id);
  setId(id);
}

VertexArrayHandle::VertexArrayHandle(VertexArrayHandle&& handle) noexcept
    : Handle() {
  setId(handle.getId());
  handle.setId(0);
}

VertexArrayHandle::~VertexArrayHandle() noexcept {
  unsigned int id = getId();
  glDeleteVertexArrays(1, &id);
}

VertexArrayHandle& VertexArrayHandle::operator=(VertexArrayHandle&& handle) {
  unsigned int id = getId();
  glDeleteVertexArrays(1, &id);
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

}  // namespace orangutan
