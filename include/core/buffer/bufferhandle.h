#ifndef ORANGUTAN_CORE_BUFFER_BUFFER_HANDLE_H
#define ORANGUTAN_CORE_BUFFER_BUFFER_HANDLE_H

#include <nanogui/opengl.h>

#include "core/handle.h"

namespace orangutan {

class BufferHandle : public Handle {
 public:
  BufferHandle();

  BufferHandle(const BufferHandle& handle) = delete;
  BufferHandle(BufferHandle&& handle) noexcept;

  ~BufferHandle() noexcept;

  BufferHandle& operator=(const BufferHandle& handle) = delete;
  BufferHandle& operator=(BufferHandle&& handle);
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_BUFFER_BUFFER_HANDLE_H
