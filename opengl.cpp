#include "opengl.h"

OpenGLFunction OpenGLFunction::_instance=OpenGLFunction();

OpenGLFunction::OpenGLFunction()
{
}

OpenGLFunction::~OpenGLFunction()
{
}

OpenGLFunction& OpenGLFunction::Instance(){
    return _instance;
}

QOpenGLFunctions_3_3_Core& OpenGLFunction::functions(){
    return _instance.getFunctionsPointer();
}

QOpenGLFunctions_3_3_Core& OpenGLFunction::getFunctionsPointer(){
    return *_functionPointer;
}

void OpenGLFunction::setFunctionsPointer(QOpenGLFunctions_3_3_Core *functionPointer){
    _functionPointer = functionPointer;
    _functionPointer->initializeOpenGLFunctions();
}

