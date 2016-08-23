#include "shader/shaderstrategy.h"

ShaderStrategy::ShaderStrategy(const std::string& name) : Asset(name)
{

}

ShaderStrategy::~ShaderStrategy()
{
}

void ShaderStrategy::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
    _shaderProgram = shaderProgram;
    _programId = _shaderProgram->getProgramId();
}

std::shared_ptr<ShaderProgram> ShaderStrategy::getShaderProgram() const
{
     return _shaderProgram;
}

void ShaderStrategy::draw(const Vao &vao) const
{
    _shaderProgram->startUseProgram();

    vao.bind();
    vao.bindIndexBuffer();

    vao.drawElements();

    vao.unbindIndexBuffer();
    vao.unbind();

    _shaderProgram->unbindTexture();

    _shaderProgram->stopUseProgram();
}
