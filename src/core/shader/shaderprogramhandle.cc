#include "core/shader/shaderprogramhandle.h"

#include <nanogui/opengl.h>

ShaderProgramHandle::ShaderProgramHandle() : Handle() {
  setId(glCreateProgram());
}

ShaderProgramHandle::ShaderProgramHandle(const ShaderProgramHandle& handle)
    : Handle() {
  setId(glCreateProgram());

  int numberOfAttachedShader = 0;
  unsigned int shaders[MAX_ATTACHED_SHADER];
  glGetAttachedShaders(handle.getId(), MAX_ATTACHED_SHADER,
                       &numberOfAttachedShader, shaders);
  for (int i = 0; i < numberOfAttachedShader; ++i)
    glAttachShader(getId(), shaders[i]);

  int isLinked;
  glGetProgramiv(handle.getId(), GL_LINK_STATUS, &isLinked);
  if (isLinked) glLinkProgram(getId());
}

ShaderProgramHandle::ShaderProgramHandle(ShaderProgramHandle&& handle) noexcept
    : Handle() {
  setId(handle.getId());
  handle.setId(0);
}

ShaderProgramHandle::~ShaderProgramHandle() noexcept {
  glDeleteProgram(getId());
}

ShaderProgramHandle& ShaderProgramHandle::operator=(
    const ShaderProgramHandle& handle) {
  glDeleteProgram(getId());
  ShaderProgramHandle tmp(handle);
  *this = std::move(tmp);
  return *this;
}

ShaderProgramHandle& ShaderProgramHandle::operator=(
    ShaderProgramHandle&& handle) {
  glDeleteProgram(getId());
  setId(handle.getId());
  handle.setId(0);
  return *this;
}

