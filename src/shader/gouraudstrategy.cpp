#include "shader/gouraudstrategy.h"

GouraudStrategy::GouraudStrategy(const std::string& name) : ShaderStrategy(name)
{
}

GouraudStrategy::~GouraudStrategy()
{
}

void GouraudStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _normalAttribute = _shaderProgram->getAttributeLocation("normal_in");
    _textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void GouraudStrategy::setUniform(const Material &material,
     const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix,
      const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light>> &lights) const
{
    _shaderProgram->startUseProgram();

    setMatrixUniform(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniform(material);

    setLightUniform(lights, viewMatrix);

    if(material.getColorMapId() != -1){
        _shaderProgram->bindTexture(O_TEXTURE_2D, "colorMap", material.getColorMapId());
    }

    _shaderProgram->stopUseProgram();
}
