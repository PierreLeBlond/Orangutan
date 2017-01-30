#include "shader/edgefilterstrategy.h"

EdgeFilterStrategy::EdgeFilterStrategy(const std::string& name) : ShaderStrategy(name)
{

}

void EdgeFilterStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void EdgeFilterStrategy::setUniform(const Material &material,
    const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix,
    const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light> > &lights) const
{
    _shaderProgram->startUseProgram();

    _shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    _shaderProgram->setUniform("viewMatrix", viewMatrix);
    _shaderProgram->setUniform("modelMatrix", modelMatrix);

    _shaderProgram->setUniform("edgeThreshold", material.getEdgeFilterThreshold());

    _shaderProgram->bindTexture(O_TEXTURE_2D, "renderTex", material.getRenderMapId());

    _shaderProgram->stopUseProgram();
}
