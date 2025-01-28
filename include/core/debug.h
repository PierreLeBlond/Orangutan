#ifndef ORANGUTAN_CORE_DEBUG_H
#define ORANGUTAN_CORE_DEBUG_H

#include <nanogui/opengl.h>

#include <iostream>

namespace orangutan {

GLenum glCheckError_(const char *cmd, const char *file, int line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (errorCode) {
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    case GL_STACK_OVERFLOW:
      error = "STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      error = "STACK_UNDERFLOW";
      break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    }
    std::cout << error << " | " << cmd << " | " << file << " (" << line << ")"
              << std::endl;
  }
  return errorCode;
}

#define GL_CHECK_ERROR(cmd)                                                    \
  cmd;                                                                         \
  (void)glCheckError_(#cmd, __FILE__, __LINE__);

} // namespace orangutan

#endif // ORANGUTAN_CORE_DEBUG_H
