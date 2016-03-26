#include "edgefilterstrategy.h"

EdgeFilterStrategy::EdgeFilterStrategy()
{

}

void EdgeFilterStrategy::initAttribute()
{
    _shaderProgram->startUseProgram();

    _vertexAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "vertex_in");
    _textureCoordinateAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "uv_in");

    _shaderProgram->stopUseProgram();
}

void EdgeFilterStrategy::initUniformLocation()
{
    _shaderProgram->startUseProgram();

    _indexOfProjectionMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "projectionMatrix");
    _indexOfViewMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "viewMatrix");
    _indexOfModelMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "modelMatrix");

    _indexOfRenderTex = OpenGLFunction::functions().glGetUniformLocation(_programId, "renderTex");
    _indexOfEdgeThreshold = OpenGLFunction::functions().glGetUniformLocation(_programId, "edgeThreshold");

    _shaderProgram->stopUseProgram();
}

void EdgeFilterStrategy::draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights) const{
    _shaderProgram->startUseProgram();

    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    OpenGLFunction::functions().glUniform1f(_indexOfEdgeThreshold, material.getEdgeFilterThreshold());

    OpenGLFunction::functions().glUniform1i(_indexOfRenderTex, GL_TEXTURE0);
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, material.getRenderMapId());

    OpenGLFunction::functions().glBindVertexArray(vao);

    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idOfIndexArray);

    OpenGLFunction::functions().glDrawElements(GL_TRIANGLES, 3*mesh.getNumberOfTriangles(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    OpenGLFunction::functions().glBindVertexArray(0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);

    _shaderProgram->stopUseProgram();
}
