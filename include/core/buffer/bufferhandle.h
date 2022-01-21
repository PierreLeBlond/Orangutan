#ifndef BUFFER_HANDLE_H
#define BUFFER_HANDLE_H

#include <nanogui/opengl.h>

#include "core/handle.h"

class BufferHandle : public Handle {
 public:
  BufferHandle();

  BufferHandle(const BufferHandle& handle) = delete;
  BufferHandle(BufferHandle&& handle) noexcept;

  ~BufferHandle() noexcept;

  BufferHandle& operator=(const BufferHandle& handle) = delete;
  BufferHandle& operator=(BufferHandle&& handle);
};

#endif  // BUFFER_HANDLE_H
