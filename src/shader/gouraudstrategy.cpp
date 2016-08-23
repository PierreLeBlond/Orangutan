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

    _shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    _shaderProgram->setUniform("viewMatrix", viewMatrix);
    _shaderProgram->setUniform("modelMatrix", modelMatrix);

    _shaderProgram->setUniform("Ks", material.getKs());
    _shaderProgram->setUniform("Ka", material.getKa()*glm::vec3(((float)material.getColor().red())/255.0, ((float)material.getColor().green())/255.0, ((float)material.getColor().blue())/255.0));
    _shaderProgram->setUniform("Kd", material.getKd()*glm::vec3(((float)material.getColor().red())/255.0, ((float)material.getColor().green())/255.0, ((float)material.getColor().blue())/255.0));
    _shaderProgram->setUniform("Ns", material.getNs());

    int nbAmbiantLights = 0;
    int nbPonctualLights = 0;
    int nbDirectionalLights = 0;
    int nbSpotLights = 0;

    for(unsigned int i = 0;i < lights.size();i++){

        const Light& light = *lights[i];//TODO don't deference pointer
        switch(light.getType())
        {
        case AMBIANT :
            if(nbAmbiantLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("ambiantLights", nbAmbiantLights, "La", light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                nbAmbiantLights++;
            }
            break;
        case DIRECTION :
            if(nbDirectionalLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "direction", glm::mat3(viewMatrix*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0));
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "La", light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "Ld", light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                _shaderProgram->setUniform("directionalLights", nbDirectionalLights, "Ls", light.getLs());
                nbDirectionalLights++;
            }
            break;
        case PONCTUAL :
            if(nbPonctualLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "La", light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "Ld", light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                _shaderProgram->setUniform("ponctualLights", nbPonctualLights, "Ls", light.getLs());
                nbPonctualLights++;
            }
            break;
        case SPOT :
            if(nbSpotLights < MAX_LIGHT && light.getState()) {
                _shaderProgram->setUniform("spotLights", nbSpotLights, "position", viewMatrix*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0));
                _shaderProgram->setUniform("spotLights", nbSpotLights, "direction", glm::normalize(glm::mat3(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0)));
                _shaderProgram->setUniform("spotLights", nbSpotLights, "La", light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
                _shaderProgram->setUniform("spotLights", nbSpotLights, "Ld", light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0));
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


    if(material.getColorMapId() != -1){
        _shaderProgram->bindTexture(O_TEXTURE_2D, "colorMap", material.getColorMapId());
    }

    _shaderProgram->stopUseProgram();
}
