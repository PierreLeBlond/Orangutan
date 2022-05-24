#ifndef ORANGUTAN_CORE_VERTEX_VERTEX_ARRAY_HANDLE_H
#define ORANGUTAN_CORE_VERTEX_VERTEX_ARRAY_HANDLE_H

#include <nanogui/opengl.h>

#include "core/handle.h"

namespace orangutan {

class VertexArrayHandle : public Handle {
 public:
  VertexArrayHandle();

  VertexArrayHandle(const VertexArrayHandle& handle) = delete;
  VertexArrayHandle(VertexArrayHandle&& handle) noexcept;

  ~VertexArrayHandle() noexcept;

  VertexArrayHandle& operator=(const VertexArrayHandle& handle) = delete;
  VertexArrayHandle& operator=(VertexArrayHandle&& handle);
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_VERTEX_VERTEX_ARRAY_HANDLE_H
