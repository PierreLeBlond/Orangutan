#include "toonstrategy.h"

ToonStrategy::ToonStrategy()
{

}

ToonStrategy::~ToonStrategy()
{

}

void ToonStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "vertex_in");
    _normalAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "normal_in");
    _textureCoordinateAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "uv_in");

    _shaderProgram->stopUseProgram();
}

void ToonStrategy::initUniformLocation()
{
    _shaderProgram->startUseProgram();

    _indexOfKs = OpenGLFunction::functions().glGetUniformLocation(_programId, "Ks");
    _indexOfKa = OpenGLFunction::functions().glGetUniformLocation(_programId, "Ka");
    _indexOfNs = OpenGLFunction::functions().glGetUniformLocation(_programId, "Ns");
    _indexOfKd = OpenGLFunction::functions().glGetUniformLocation(_programId, "Kd");

    _indexOfProjectionMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "projectionMatrix");
    _indexOfViewMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "viewMatrix");
    _indexOfModelMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "modelMatrix");

    _indexOfDiffuseMap.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, "firstDiffuseMap"));
    _indexOfDiffuseMap.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, "secondDiffuseMap"));
    _indexOfDiffuseMap.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, "ThirdDiffuseMap"));

    _indexOfNbDiffuseMap = OpenGLFunction::functions().glGetUniformLocation(_programId, "nbDiffuseMap");

    _indexOfNbPonctualLight = OpenGLFunction::functions().glGetUniformLocation(_programId, "nbPonctualLight");
    _indexOfNbAmbiantLight = OpenGLFunction::functions().glGetUniformLocation(_programId, "nbAmbiantLight");
    _indexOfNbDirectionLight = OpenGLFunction::functions().glGetUniformLocation(_programId, "nbDirectionLight");
    _indexOfNbSpotLight = OpenGLFunction::functions().glGetUniformLocation(_programId, "nbSpotLight");

    for(int i = 0; i < MAX_LIGHT;i++) {
        std::ostringstream ost;
        ost << "ambiantLights[" << i << "].La";
        _indexOfAmbientLightLaLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
    }
    for(int i = 0; i < MAX_LIGHT;i++) {
        std::ostringstream ost;
        ost << "ponctualLights[" << i << "].position";
        _indexOfPonctualLightPositionLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "ponctualLights[" << i << "].La";
        _indexOfPonctualLightLaLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "ponctualLights[" << i << "].Ld";
        _indexOfPonctualLightLdLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "ponctualLights[" << i << "].Ls";
        _indexOfPonctualLightLsLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
    }

    for(int i = 0; i < MAX_LIGHT;i++) {
        std::ostringstream ost;
        ost << "directionalLights[" << i << "].direction";
        _indexOfDirectionalLightDirectionLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "directionalLights[" << i << "].La";
        _indexOfDirectionalLightLaLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "directionalLights[" << i << "].Ld";
        _indexOfDirectionalLightLdLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "directionalLights[" << i << "].Ls";
        _indexOfDirectionalLightLsLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
    }

    for(int i = 0; i < MAX_LIGHT;i++) {
        std::ostringstream ost;
        ost << "spotLights[" << i << "].position";
        _indexOfSpotLightPositionLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].direction";
        _indexOfSpotLightDirectionLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].La";
        _indexOfSpotLightLaLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].Ld";
        _indexOfSpotLightLdLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].Ls";
        _indexOfSpotLightLsLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].exponent";
        _indexOfSpotLightExponentLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "spotLights[" << i << "].cutoff";
        _indexOfSpotLightCutoffLocation.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
    }
    _shaderProgram->stopUseProgram();
}

void ToonStrategy::draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights) const
{
    _shaderProgram->startUseProgram();

    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    OpenGLFunction::functions().glUniform3fv(_indexOfKs, 1, glm::value_ptr(material.getKs()));
    OpenGLFunction::functions().glUniform3fv(_indexOfKa, 1, glm::value_ptr(material.getKa()*glm::vec3(((float)material.getColor().red())/255.0, ((float)material.getColor().green())/255.0, ((float)material.getColor().blue())/255.0)));
    OpenGLFunction::functions().glUniform3fv(_indexOfKd, 1, glm::value_ptr(material.getKd()*glm::vec3(((float)material.getColor().red())/255.0, ((float)material.getColor().green())/255.0, ((float)material.getColor().blue())/255.0)));
    OpenGLFunction::functions().glUniform1f(_indexOfNs, material.getNs());

    int nbAmbiantLights = 0;
    int nbPonctualLights = 0;
    int nbDirectionalLights = 0;
    int nbSpotLights = 0;

    for(int i = 0;i < lights.size();i++){

        const Light& light = lights[i]->getLight();
        switch(light.getType())
        {
        case AMBIANT :
            if(nbAmbiantLights < MAX_LIGHT && light.getState()) {
                OpenGLFunction::functions().glUniform3fv(_indexOfAmbientLightLaLocation[nbAmbiantLights], 1, glm::value_ptr(light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                nbAmbiantLights++;
            }
            break;
        case DIRECTION :
            if(nbDirectionalLights < MAX_LIGHT && light.getState()) {
                OpenGLFunction::functions().glUniform3fv(_indexOfDirectionalLightDirectionLocation[nbDirectionalLights], 1, glm::value_ptr(glm::normalize(glm::mat3(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0))));
                OpenGLFunction::functions().glUniform3fv(_indexOfDirectionalLightLaLocation[nbDirectionalLights], 1, glm::value_ptr(light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfDirectionalLightLdLocation[nbDirectionalLights], 1, glm::value_ptr(light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfDirectionalLightLsLocation[nbDirectionalLights], 1, glm::value_ptr(light.getLs()));
                nbDirectionalLights++;
            }
            break;
        case PONCTUAL :
            if(nbPonctualLights < MAX_LIGHT && light.getState()) {
                OpenGLFunction::functions().glUniform4fv(_indexOfPonctualLightPositionLocation[nbPonctualLights], 1, glm::value_ptr(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfPonctualLightLaLocation[nbPonctualLights], 1, glm::value_ptr(light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfPonctualLightLdLocation[nbPonctualLights], 1, glm::value_ptr(light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfPonctualLightLsLocation[nbPonctualLights], 1, glm::value_ptr(light.getLs()));
                nbPonctualLights++;
            }
            break;
        case SPOT :
            if(nbSpotLights < MAX_LIGHT && light.getState()) {
                OpenGLFunction::functions().glUniform4fv(_indexOfSpotLightPositionLocation[nbSpotLights], 1, glm::value_ptr(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix()*glm::vec4(0.0, 0.0, 0.0, 1.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfSpotLightDirectionLocation[nbSpotLights], 1, glm::value_ptr(glm::normalize(glm::mat3(viewMatrix*lights[i]->getTransform().getModelMatrix()*light.getTransform().getModelMatrix())*glm::vec3(1.0, 0.0, 0.0))));
                OpenGLFunction::functions().glUniform3fv(_indexOfSpotLightLaLocation[nbSpotLights], 1, glm::value_ptr(light.getLa()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfSpotLightLdLocation[nbSpotLights], 1, glm::value_ptr(light.getLd()*glm::vec3(((float)light.getColor().red())/255.0, ((float)light.getColor().green())/255.0, ((float)light.getColor().blue())/255.0)));
                OpenGLFunction::functions().glUniform3fv(_indexOfSpotLightLsLocation[nbSpotLights], 1, glm::value_ptr(light.getLs()));
                OpenGLFunction::functions().glUniform1f(_indexOfSpotLightExponentLocation[nbSpotLights], light.getExponent());
                OpenGLFunction::functions().glUniform1f(_indexOfSpotLightCutoffLocation[nbSpotLights], light.getCutoffAngle());
                nbSpotLights++;
            }
            break;
        default:
            break;
        }
    }

    OpenGLFunction::functions().glUniform1i(_indexOfNbPonctualLight, nbPonctualLights);
    OpenGLFunction::functions().glUniform1i(_indexOfNbAmbiantLight, nbAmbiantLights);
    OpenGLFunction::functions().glUniform1i(_indexOfNbDirectionLight, nbDirectionalLights);
    OpenGLFunction::functions().glUniform1i(_indexOfNbSpotLight, nbSpotLights);


    int nbDiffuseMap = 0;

    for(int i = 0; i < material.getDiffuseMapId()->getIdTextures().size();i++){
            if(material.getDiffuseMapId()->getIdTextures()[i] != -1){
                OpenGLFunction::functions().glUniform1i(_indexOfDiffuseMap[i], nbDiffuseMap);
                OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + nbDiffuseMap);
                OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, material.getDiffuseMapId()->getIdTextures()[i]);
                nbDiffuseMap++;
            }
    }

    OpenGLFunction::functions().glUniform1i(_indexOfNbDiffuseMap, nbDiffuseMap);

    OpenGLFunction::functions().glBindVertexArray(vao);
    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idOfIndexArray);


    OpenGLFunction::functions().glDrawElements(GL_TRIANGLES, 3 * mesh.getNumberOfTriangles(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));


    //OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    OpenGLFunction::functions().glBindVertexArray(0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    _shaderProgram->stopUseProgram();

}


