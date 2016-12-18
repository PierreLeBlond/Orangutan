#include "core/rendererable.h"
#include "core/debug.h"

using namespace std;

Rendererable::Rendererable(GLuint width, GLuint height) : _width(width), _height(height), _drawCall([](){})
{
}

void Rendererable::resize(int width, int height)
{
    _width = width;
    _height = height;
}

void Rendererable::setDrawCall(std::function<void()> drawCall)
{
    _drawCall = drawCall;
}
