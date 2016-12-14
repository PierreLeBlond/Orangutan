#include "core/debug.h"
#include <iostream>

void Debug::getError(std::string str)
{
    for(GLenum err; (err = OpenGLFunction::functions().glGetError()) != GL_NO_ERROR;)
        std::cout << "error : " << err  << " at " << str << std::endl;
}
