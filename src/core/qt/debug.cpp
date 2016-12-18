#include "core/debug.h"
#include <iostream>

#include "core/qt/context.h"

void Debug::getError(std::string str)
{
    for(GLenum err; (err = Context::functions().glGetError()) != GL_NO_ERROR;)
        std::cout << "error : " << err  << " at " << str << std::endl;
}

