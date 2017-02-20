#ifndef VERTEX_ARRAY_HANDLE_H
#define VERTEX_ARRAY_HANDLE_H

#include "core/handle.h"

#include <nanogui/opengl.h>

class VertexArrayHandle : public Handle
{
  public:
                                    VertexArrayHandle();

                                    VertexArrayHandle(const VertexArrayHandle& handle) = delete;
                                    VertexArrayHandle(VertexArrayHandle&& handle) noexcept;

                                    ~VertexArrayHandle() noexcept;

    VertexArrayHandle&              operator=(const VertexArrayHandle& handle) = delete;
    VertexArrayHandle&              operator=(VertexArrayHandle&& handle);
};

#endif //VERTEX_ARRAY_HANDLE_H
