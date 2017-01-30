#include "shader/environmentstrategy.h"

EnvironmentStrategy::EnvironmentStrategy(const std::string& name) : ShaderStrategy(name)
{

}

EnvironmentStrategy::~EnvironmentStrategy()
{

}

void EnvironmentStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _normalAttribute = _shaderProgram->getAttributeLocation("normal_in");
    //_textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void EnvironmentStrategy::setUniform(const Material &material,
     const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix,
      const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light>> &lights) const
{
    _shaderProgram->startUseProgram();

    setMatrixUniform(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniform(material);

    setLightUniform(lights, viewMatrix);

    _shaderProgram->setUniform("refractionRatio", material.getRefractionRatio()/100.0f);
    _shaderProgram->setUniform("reflexionPercentage", material.getReflexionPercentage()/100.0f);

    if(material.getCubeMapId() != -1){
        _shaderProgram->bindTexture(O_TEXTURE_CUBE_MAP, "cubeMap", material.getCubeMapId());
    }

    _shaderProgram->stopUseProgram();
}
