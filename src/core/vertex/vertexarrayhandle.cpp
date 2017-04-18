#include "core/vertex/vertexarrayhandle.h"

#include <nanogui/opengl.h>

VertexArrayHandle::VertexArrayHandle()
{
    glGenVertexArrays(1, &_id);
}

VertexArrayHandle::VertexArrayHandle(VertexArrayHandle&& handle) noexcept
{
    _id = handle._id;
    handle._id = 0;
}

VertexArrayHandle::~VertexArrayHandle() noexcept
{
    glDeleteVertexArrays(1, &_id);
}

VertexArrayHandle& VertexArrayHandle::operator=(VertexArrayHandle&& handle)
{
    glDeleteVertexArrays(1, &_id);
    _id = handle._id;
    handle._id = 0;
    return *this;
}

