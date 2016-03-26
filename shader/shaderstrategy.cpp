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

std::string ShaderStrategy::getName() const{
    return _name;
}

void ShaderStrategy::setName(std::string name){
    _name = name;
}



