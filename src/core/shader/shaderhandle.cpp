#include "core/shader/shaderhandle.h"

ShaderHandle::ShaderHandle(ShaderType type) :
    _type(type)
{
    _id = glCreateShader((GLenum)type);
}

ShaderHandle::ShaderHandle(const ShaderHandle& handle) :
    _type(handle._type)
{
    _id = glCreateShader((GLenum)_type);

    int bufSize;
    glGetShaderiv(handle._id, GL_SHADER_SOURCE_LENGTH, &bufSize);
    char* source = new char[bufSize];
    int length;
    glGetShaderSource(handle._id, bufSize, &length, source);

    if(length != 0)
    {
        glShaderSource(_id, 1, &source, NULL);

        int isCompiled;
        glGetShaderiv(handle._id, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled)
            glCompileShader(_id);
    }

    delete[] source;
}

ShaderHandle::ShaderHandle(ShaderHandle&& handle) noexcept :
    _type(handle._type)
{
    _id = handle._id;
    handle._id = 0;
}

ShaderHandle::~ShaderHandle() noexcept
{
    glDeleteShader(_id);
}

ShaderHandle& ShaderHandle::operator=(const ShaderHandle& handle)
{
    glDeleteShader(_id);
    ShaderHandle tmp(handle);
    *this = std::move(tmp);
    return *this;
}

ShaderHandle& ShaderHandle::operator=(ShaderHandle&& handle)
{
    glDeleteShader(_id);
    _id = handle.getId();
    handle._id = 0;
    return *this;
}

ShaderType ShaderHandle::getType() const
{
    return _type;
}
