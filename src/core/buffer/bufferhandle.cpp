#include "core/buffer/bufferhandle.h"

#include <nanogui/opengl.h>

BufferHandle::BufferHandle()
{
    glGenBuffers(1, &_id);
}

BufferHandle::BufferHandle(BufferHandle&& handle) noexcept
{
    _id = handle._id;
    handle._id = 0;
}

BufferHandle::~BufferHandle() noexcept
{
    glDeleteBuffers(1, &_id);
}

BufferHandle& BufferHandle::operator=(BufferHandle&& handle)
{
    glDeleteBuffers(1, &_id);
    _id = handle._id;
    handle._id = 0;
    return *this;
}

