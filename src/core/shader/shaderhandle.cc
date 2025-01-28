#include "core/shader/shaderhandle.h"
#include "core/debug.h"

namespace orangutan {

ShaderHandle::ShaderHandle(ShaderType type) : type_(type) {
  GL_CHECK_ERROR(setId(glCreateShader((GLenum)type)));
}

ShaderHandle::ShaderHandle(const ShaderHandle &handle) : type_(handle.type_) {
  GL_CHECK_ERROR(setId(glCreateShader((GLenum)type_)));

  int bufSize = 0;
  GL_CHECK_ERROR(
      glGetShaderiv(handle.getId(), GL_SHADER_SOURCE_LENGTH, &bufSize));
  char *source = new char[bufSize];
  int length = 0;
  GL_CHECK_ERROR(glGetShaderSource(handle.getId(), bufSize, &length, source));

  if (length != 0) {
    GL_CHECK_ERROR(glShaderSource(getId(), 1, &source, nullptr));

    int isCompiled = false;
    GL_CHECK_ERROR(
        glGetShaderiv(handle.getId(), GL_COMPILE_STATUS, &isCompiled));
    if (isCompiled)
      GL_CHECK_ERROR(glCompileShader(getId()));
  }

  delete[] source;
}

ShaderHandle::ShaderHandle(ShaderHandle &&handle) noexcept
    : type_(handle.type_) {
  setId(handle.getId());
  handle.setId(0);
}

ShaderHandle::~ShaderHandle() noexcept {
  GL_CHECK_ERROR(glDeleteShader(getId()));
}

ShaderHandle &ShaderHandle::operator=(const ShaderHandle &handle) {
  GL_CHECK_ERROR(glDeleteShader(getId()));
  ShaderHandle tmp(handle);
  *this = std::move(tmp);
  return *this;
}

ShaderHandle &ShaderHandle::operator=(ShaderHandle &&handle) {
  GL_CHECK_ERROR(glDeleteShader(getId()));
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

ShaderType ShaderHandle::GetType() const { return type_; }

} // namespace orangutan
