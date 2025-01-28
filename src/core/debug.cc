#include "core/debug.h"

#include <nanogui/opengl.h>

#include <iostream>
#include <map>
#include <sstream>

namespace orangutan {

std::map<std::string, int> errors;

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
    std::ostringstream ost;
    ost << error << " | " << cmd << " | " << file << " (" << line << ")";

    std::string error_msg = ost.str();

    if (errors.find(error_msg) == errors.end()) {
      errors[error_msg] = 0;
    }

    errors[error_msg] += 1;

    if (errors[error_msg] == 5) {
      std::cerr << "Too many errors, last time you'll see this one :"
                << std::endl;
    }

    if (errors[error_msg] <= 5) {
      std::cerr << error_msg << std::endl;
    }
  }
  return errorCode;
}

} // namespace orangutan