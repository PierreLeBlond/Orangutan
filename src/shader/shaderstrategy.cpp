#include "shader/shaderstrategy.h"
#include "core/debug.h"

ShaderStrategy::ShaderStrategy(const std::string& name) : Asset(name),
    _vertexAttribute(-1),
    _normalAttribute(-1),
    _textureCoordinateAttribute(-1)
{
}

void ShaderStrategy::initAttribute()
{
    _shaderWrapper->start();

    _vertexAttribute = _shaderWrapper->getAttributeLocation("vertex_in");
    _normalAttribute = _shaderWrapper->getAttributeLocation("normal_in");
    _textureCoordinateAttribute = _shaderWrapper->getAttributeLocation("uv_in");

    _shaderWrapper->stop();
}

void ShaderStrategy::setUniforms(const Material &material,
                                 const glm::mat4& modelMatrix,
                                 const glm::mat4& viewMatrix,
                                 const glm::mat4& projectionMatrix,
                                 const std::vector<std::shared_ptr<Light>> &lights) const
{
    _shaderWrapper->start();
    setMatrixUniforms(modelMatrix, viewMatrix, projectionMatrix);
    setMaterialUniforms(material);
    setLightUniforms(lights, viewMatrix);
    _shaderWrapper->stop();
}

void ShaderStrategy::setLightUniforms(const std::vector<std::shared_ptr<Light>> &lights,
                                     const glm::mat4 &viewMatrix) const
{
    int nbAmbiantLights = 0;
    int nbPonctualLights = 0;
    int nbDirectionalLights = 0;
    int nbSpotLights = 0;

    for(unsigned int i = 0;i < lights.size();i++){

        const Light& light = *lights[i];
        switch(light.getType())
        {
          case AMBIANT :
            if(nbAmbiantLights < MAX_LIGHT && light.getState()) {
                _shaderWrapper->setUniform("ambiantLights", nbAmbiantLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                nbAmbiantLights++;
            }
            break;
          case DIRECTION :
            if(nbDirectionalLights < MAX_LIGHT && light.getState()) {
                _shaderWrapper->setUniform("directionalLights", nbDirectionalLights, "direction", glm::mat3(viewMatrix*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0));
                _shaderWrapper->setUniform("directionalLights", nbDirectionalLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("directionalLights", nbDirectionalLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("directionalLights", nbDirectionalLights, "Ls", light.getLs());
                nbDirectionalLights++;
            }
            break;
          case PONCTUAL :
            if(nbPonctualLights < MAX_LIGHT && light.getState()) {
                _shaderWrapper->setUniform("ponctualLights", nbPonctualLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderWrapper->setUniform("ponctualLights", nbPonctualLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("ponctualLights", nbPonctualLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("ponctualLights", nbPonctualLights, "Ls", light.getLs());
                nbPonctualLights++;
            }
            break;
          case SPOT :
            if(nbSpotLights < MAX_LIGHT && light.getState()) {
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "direction", glm::normalize(glm::mat3(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0)));
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "Ls", light.getLs());
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "exponent", light.getExponent());
                _shaderWrapper->setUniform("spotLights", nbSpotLights, "cutoff", light.getCutoffAngle());
                nbSpotLights++;
            }
            break;
          default:
            break;
        }
    }

    _shaderWrapper->setUniform("nbPonctualLight", nbPonctualLights);
    _shaderWrapper->setUniform("nbAmbiantLight", nbAmbiantLights);
    _shaderWrapper->setUniform("nbDirectionLight", nbDirectionalLights);
    _shaderWrapper->setUniform("nbSpotLight", nbSpotLights);
}

void ShaderStrategy::setMatrixUniforms(const glm::mat4& modelMatrix,
                                      const glm::mat4& viewMatrix,
                                      const glm::mat4& projectionMatrix) const
{
    _shaderWrapper->setUniform("projectionMatrix", projectionMatrix);
    _shaderWrapper->setUniform("viewMatrix", viewMatrix);
    _shaderWrapper->setUniform("modelMatrix", modelMatrix);
}

void ShaderStrategy::setMaterialUniforms(const Material &material) const
{
    for(const auto &uniform : material.get1fUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get1iUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get1uiUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get1bUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get3fUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get4fUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get3x3fUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &uniform : material.get4x4fUniforms())
    {
        setUniform(uniform);
    }

    for(const auto &pair : material.getTextures())
    {
        if(pair.second->getId() != -1)
            _shaderWrapper->bindTexture(pair.first, pair.second->getId());
    }

    for(const auto &pair : material.getCubeTextures())
    {
        if(pair.second->getId() != -1)
            _shaderWrapper->bindCubeTexture(pair.first, pair.second->getId());
    }

    for(const auto &subMaterial : material.getMaterials())
    {
        setMaterialUniforms(subMaterial);
    }
}

void ShaderStrategy::setShaderWrapper(std::shared_ptr<ShaderWrapper> shaderWrapper)
{
    _shaderWrapper = shaderWrapper;
    _programId = _shaderWrapper->getProgramId();
}

const std::shared_ptr<ShaderWrapper>& ShaderStrategy::getShaderWrapper() const
{
     return _shaderWrapper;
}

void ShaderStrategy::draw(const Vao &vao) const
{
    _shaderWrapper->start();

    vao.bind();
    vao.bindIndexBuffer();

    vao.drawElements();

    vao.unbindIndexBuffer();
    vao.unbind();

    _shaderWrapper->unbindTexture();

    _shaderWrapper->stop();
}
