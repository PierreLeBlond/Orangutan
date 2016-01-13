#include "skyboxstrategy.h"

SkyboxStrategy::SkyboxStrategy()
{

}

SkyboxStrategy::~SkyboxStrategy()
{

}

void SkyboxStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "vertex_in");
    _normalAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "normal_in");
    _textureCoordinateAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "uv_in");

    _shaderProgram->stopUseProgram();
}



void SkyboxStrategy::initUniformLocation()
{
    _shaderProgram->startUseProgram();

    _indexOfProjectionMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "projectionMatrix");
    _indexOfViewMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "viewMatrix");
    _indexOfDiffuseMap = OpenGLFunction::functions().glGetUniformLocation(_programId, "diffuseMap");
    _indexOfModelMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "modelMatrix");
    _indexOfLa = OpenGLFunction::functions().glGetUniformLocation(_programId, "La");

    _shaderProgram->stopUseProgram();
}



void SkyboxStrategy::draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material& material, const glm::core::type::mat4 modelMatrix, const glm::core::type::mat4 viewMatrix, const glm::core::type::mat4 projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) const
{
    _shaderProgram->startUseProgram();

    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));//Maybe we want only the rotation matrix
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::vec3 La;
    for(int i = 0; i < lights.size();i++){
        if(/*lights[i]->getLight().getType() == AMBIANT && */lights[i]->getLight().getState()){
            La += lights[i]->getLight().getLa();
        }
    }
    OpenGLFunction::functions().glUniform3fv(_indexOfLa, 1, glm::value_ptr(La));

    OpenGLFunction::functions().glUniform1i(_indexOfDiffuseMap, 0);

    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, material.getCubeMapId());

    OpenGLFunction::functions().glBindVertexArray(vao);
    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idOfIndexArray);

    OpenGLFunction::functions().glDrawElements(GL_TRIANGLES, 3 * mesh.getNumberOfTriangles(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    OpenGLFunction::functions().glBindVertexArray(0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    _shaderProgram->stopUseProgram();
}


