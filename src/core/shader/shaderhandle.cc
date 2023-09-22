#include "core/shader/shaderhandle.h"

namespace orangutan {

ShaderHandle::ShaderHandle(ShaderType type) : type_(type) {
  setId(glCreateShader((GLenum)type));
}

ShaderHandle::ShaderHandle(const ShaderHandle& handle) : type_(handle.type_) {
  setId(glCreateShader((GLenum)type_));

  int bufSize = 0;
  glGetShaderiv(handle.getId(), GL_SHADER_SOURCE_LENGTH, &bufSize);
  char* source = new char[bufSize];
  int length = 0;
  glGetShaderSource(handle.getId(), bufSize, &length, source);

  if (length != 0) {
    glShaderSource(getId(), 1, &source, nullptr);

    int isCompiled = false;
    glGetShaderiv(handle.getId(), GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled) glCompileShader(getId());
  }

  delete[] source;
}

ShaderHandle::ShaderHandle(ShaderHandle&& handle) noexcept
    : type_(handle.type_) {
  setId(handle.getId());
  handle.setId(0);
}

ShaderHandle::~ShaderHandle() noexcept { glDeleteShader(getId()); }

ShaderHandle& ShaderHandle::operator=(const ShaderHandle& handle) {
  glDeleteShader(getId());
  ShaderHandle tmp(handle);
  *this = std::move(tmp);
  return *this;
}

ShaderHandle& ShaderHandle::operator=(ShaderHandle&& handle) {
  glDeleteShader(getId());
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

ShaderType ShaderHandle::GetType() const { return type_; }

}  // namespace orangutan
