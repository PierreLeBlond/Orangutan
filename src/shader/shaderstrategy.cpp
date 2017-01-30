#include "shader/shaderstrategy.h"
#include "core/debug.h"

ShaderStrategy::ShaderStrategy(const std::string& name) : Asset(name),
    _vertexAttribute(-1),
    _normalAttribute(-1),
    _textureCoordinateAttribute(-1)
{
}

ShaderStrategy::~ShaderStrategy()
{
}

void ShaderStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _normalAttribute = _shaderProgram->getAttributeLocation("normal_in");
    _textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void ShaderStrategy::setUniforms(const Material &material,
                                 const glm::mat4& modelMatrix,
                                 const glm::mat4& viewMatrix,
                                 const glm::mat4& projectionMatrix,
                                 const std::vector<std::shared_ptr<Light>> &lights) const
{
    _shaderProgram->startUseProgram();
    setMatrixUniforms(modelMatrix, viewMatrix, projectionMatrix);
    setMaterialUniforms(material);
    setLightUniforms(lights, viewMatrix);
    _shaderProgram->stopUseProgram();
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
                _shaderProgram->setUniform("ambiantLights", nbAmbiantLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                nbAmbiantLights++;
            }
            break;
          case DIRECTION :
            if(nbDirectionalLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "direction", glm::mat3(viewMatrix*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0));
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "Ls", light.getLs());
                nbDirectionalLights++;
            }
            break;
          case PONCTUAL :
            if(nbPonctualLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "Ls", light.getLs());
                nbPonctualLights++;
            }
            break;
          case SPOT :
            if(nbSpotLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("spotLights", nbSpotLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderProgram->setUniform("spotLights", nbSpotLights, "direction", glm::normalize(glm::mat3(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0)));
                _shaderProgram->setUniform("spotLights", nbSpotLights, "La", light.getLa()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("spotLights", nbSpotLights, "Ld", light.getLd()*glm::vec3(light.getColor())/255.0f);
                _shaderProgram->setUniform("spotLights", nbSpotLights, "Ls", light.getLs());
                _shaderProgram->setUniform("spotLights", nbSpotLights, "exponent", light.getExponent());
                _shaderProgram->setUniform("spotLights", nbSpotLights, "cutoff", light.getCutoffAngle());
                nbSpotLights++;
            }
            break;
          default:
            break;
        }
    }

    _shaderProgram->setUniform("nbPonctualLight", nbPonctualLights);
    _shaderProgram->setUniform("nbAmbiantLight", nbAmbiantLights);
    _shaderProgram->setUniform("nbDirectionLight", nbDirectionalLights);
    _shaderProgram->setUniform("nbSpotLight", nbSpotLights);
}

void ShaderStrategy::setMatrixUniforms(const glm::mat4& modelMatrix,
                                      const glm::mat4& viewMatrix,
                                      const glm::mat4& projectionMatrix) const
{
    _shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    _shaderProgram->setUniform("viewMatrix", viewMatrix);
    _shaderProgram->setUniform("modelMatrix", modelMatrix);
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
            _shaderProgram->bindTexture(pair.second->getType(), pair.first, pair.second->getId());
    }

    for(const auto &subMaterial : material.getMaterials())
    {
        setMaterialUniforms(subMaterial);
    }
}

void ShaderStrategy::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
    _shaderProgram = shaderProgram;
    _programId = _shaderProgram->getProgramId();
}

const std::shared_ptr<ShaderProgram>& ShaderStrategy::getShaderProgram() const
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
