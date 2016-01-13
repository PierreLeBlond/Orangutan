#include "shaderstrategy.h"

ShaderStrategy::ShaderStrategy()
{

}

ShaderStrategy::~ShaderStrategy()
{
}

void ShaderStrategy::setShaderProgram(const ShaderProgram *shaderProgram)
{
    _shaderProgram = shaderProgram;
    _programId = _shaderProgram->getProgramId();
}



