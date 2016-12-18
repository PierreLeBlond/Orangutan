#include "core/qt/context.h"

Context Context::_instance=Context();

Context::Context()
{
}

Context::~Context()
{
}

Context& Context::instance(){
    return _instance;
}

QOpenGLFunctions_4_5_Core& Context::functions(){
    return _instance.getFunctionsPointer();
}

QOpenGLFunctions_4_5_Core& Context::getFunctionsPointer(){
    return *_functionPointer;
}

void Context::setFunctionsPointer(QOpenGLFunctions_4_5_Core *functionPointer){
    _functionPointer = functionPointer;
    _functionPointer->initializeOpenGLFunctions();
}
