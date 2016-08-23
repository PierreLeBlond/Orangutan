#include "shader/skyboxstrategy.h"

SkyboxStrategy::SkyboxStrategy(const std::string& name) : ShaderStrategy(name)
{

}

SkyboxStrategy::~SkyboxStrategy()
{

}

void SkyboxStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _normalAttribute = _shaderProgram->getAttributeLocation("normal_in");
    _textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void SkyboxStrategy::setUniform(const Material& material,
     const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix,
      const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light>>& lights) const
{
    _shaderProgram->startUseProgram();

    _shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    _shaderProgram->setUniform("viewMatrix", viewMatrix);
    _shaderProgram->setUniform("modelMatrix", modelMatrix);

    glm::vec3 La;
    for(unsigned int i = 0; i < lights.size();i++){
        if(lights[i]->getState()){
            La += lights[i]->getLa();
        }
    }
    _shaderProgram->setUniform("La", La);

    _shaderProgram->bindTexture(O_TEXTURE_CUBE_MAP, "cubeMap", material.getColorMapId());

    _shaderProgram->stopUseProgram();
}
