#include "core/debug.h"

#include <nanogui/opengl.h>

#include <iostream>

void Debug::getError(std::string str) {
  for (GLenum err = 0; (err = glGetError()) != GL_NO_ERROR;)
    std::cerr << err << " at " << str << std::endl;
}

