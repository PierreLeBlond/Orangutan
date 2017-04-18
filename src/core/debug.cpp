#include "core/debug.h"
#include <iostream>

#include <nanogui/opengl.h>

void Debug::getError(std::string str)
{
    for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
        std::cout << "error : " << err  << " at " << str << std::endl;
}

