#include "core/rendererable.h"
#include "core/debug.h"

using namespace std;

Rendererable::Rendererable() : _drawCall([](){})
{
}

Rendererable::~Rendererable()
{
}

void Rendererable::setDrawCall(std::function<void()> drawCall)
{
    _drawCall = drawCall;
}
