#include "object/shadermaterial.h"

ShaderMaterial::ShaderMaterial(const std::string &name) : Material(name)
{}

std::shared_ptr<const ShaderStrategy> ShaderMaterial::getShaderStrategy() const{
    return _shaderStrategy;
}

void ShaderMaterial::setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _shaderStrategy = shaderStrategy;
}

