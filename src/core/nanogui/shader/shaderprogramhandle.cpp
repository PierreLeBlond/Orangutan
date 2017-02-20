#include "core/shader/shaderprogramhandle.h"

#include <nanogui/opengl.h>

ShaderProgramHandle::ShaderProgramHandle()
{
    _id = glCreateProgram();
}

ShaderProgramHandle::ShaderProgramHandle(const ShaderProgramHandle& handle)
{
    _id = glCreateProgram();

    int numberOfAttachedShader;
    unsigned int shaders[MAX_ATTACHED_SHADER];
    glGetAttachedShaders(handle._id, MAX_ATTACHED_SHADER, &numberOfAttachedShader, shaders);
    for(int i = 0; i < numberOfAttachedShader; ++i)
        glAttachShader(_id, shaders[i]);

    int isLinked;
    glGetProgramiv(handle._id, GL_LINK_STATUS, &isLinked);
    if(isLinked)
        glLinkProgram(_id);
}

ShaderProgramHandle::ShaderProgramHandle(ShaderProgramHandle&& handle) noexcept
{
    _id = handle._id;
    handle._id = 0;
}

ShaderProgramHandle::~ShaderProgramHandle() noexcept
{
    glDeleteProgram(_id);
}

ShaderProgramHandle& ShaderProgramHandle::operator=(const ShaderProgramHandle& handle)
{
    glDeleteProgram(_id);
    ShaderProgramHandle tmp(handle);
    *this = std::move(tmp);
    return *this;
}

ShaderProgramHandle& ShaderProgramHandle::operator=(ShaderProgramHandle&& handle)
{
    glDeleteProgram(_id);
    _id = handle._id;
    handle._id = 0;
    return *this;
}

