#include "core/shader/shaderprogramhandle.h"
#include "core/debug.h"

namespace orangutan {

ShaderProgramHandle::ShaderProgramHandle() : Handle() {
  GL_CHECK_ERROR(setId(glCreateProgram()));
}

ShaderProgramHandle::ShaderProgramHandle(const ShaderProgramHandle &handle)
    : Handle() {
  GL_CHECK_ERROR(setId(glCreateProgram()));

  int numberOfAttachedShader = 0;
  unsigned int shaders[MAX_ATTACHED_SHADER];
  GL_CHECK_ERROR(glGetAttachedShaders(handle.getId(), MAX_ATTACHED_SHADER,
                                      &numberOfAttachedShader, shaders));
  for (int i = 0; i < numberOfAttachedShader; ++i)
    GL_CHECK_ERROR(glAttachShader(getId(), shaders[i]));

  int isLinked;
  GL_CHECK_ERROR(glGetProgramiv(handle.getId(), GL_LINK_STATUS, &isLinked));
  if (isLinked)
    GL_CHECK_ERROR(glLinkProgram(getId()));
}

ShaderProgramHandle::ShaderProgramHandle(ShaderProgramHandle &&handle) noexcept
    : Handle() {
  setId(handle.getId());
  handle.setId(0);
}

ShaderProgramHandle::~ShaderProgramHandle() noexcept {
  GL_CHECK_ERROR(glDeleteProgram(getId()));
}

ShaderProgramHandle &
ShaderProgramHandle::operator=(const ShaderProgramHandle &handle) {
  GL_CHECK_ERROR(glDeleteProgram(getId()));
  ShaderProgramHandle tmp(handle);
  *this = std::move(tmp);
  return *this;
}

ShaderProgramHandle &
ShaderProgramHandle::operator=(ShaderProgramHandle &&handle) {
  GL_CHECK_ERROR(glDeleteProgram(getId()));
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

} // namespace orangutan
