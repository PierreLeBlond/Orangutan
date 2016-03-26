#include "gaussianblurfilterstrategy.h"

GaussianBlurFilterStrategy::GaussianBlurFilterStrategy()
{
    weights = new float[5];

    float sum = 0.0f, sigma2 = 4.0f;

    weights[0] = gauss(0.0f, sigma2);
    sum = weights[0];
    for(int i = 1; i < 5; i++){
        weights[i] = gauss(i, sigma2);
        sum += 2.0f*weights[i];
    }

    for(int i = 0; i < 5; i++){
        weights[i] / sum;
    }
}

float GaussianBlurFilterStrategy::gauss(int i, float sigma){
    return (1/(sqrt(2.0f*3.14f*sigma*sigma)))*exp(-(i*i)/(2.0f*sigma*sigma));
}

GaussianBlurFilterStrategy::~GaussianBlurFilterStrategy()
{
    delete weights;
}

void GaussianBlurFilterStrategy::initAttribute(){
    _shaderProgram->startUseProgram();

    _vertexAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "vertex_in");
    _textureCoordinateAttribute = OpenGLFunction::functions().glGetAttribLocation(_programId, "uv_in");

    _shaderProgram->stopUseProgram();
}

void GaussianBlurFilterStrategy::initUniformLocation(){
    _shaderProgram->startUseProgram();

    _indexOfProjectionMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "projectionMatrix");
    _indexOfViewMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "viewMatrix");
    _indexOfModelMatrix = OpenGLFunction::functions().glGetUniformLocation(_programId, "modelMatrix");

    _indexOfRenderTex = OpenGLFunction::functions().glGetUniformLocation(_programId, "renderTex");

    for(int i = 0; i < 5; i++){
        std::ostringstream ost;
        ost << "Weight[" << i << "]";
        _indexOfWeights.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
        ost.str("");
        ost.clear();
        ost << "PixOffset[" << i << "]";
        _indexOfPixelOffsets.push_back(OpenGLFunction::functions().glGetUniformLocation(_programId, ost.str().c_str()));
    }

    _shaderProgram->stopUseProgram();
}

void GaussianBlurFilterStrategy::draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights) const{
    _shaderProgram->startUseProgram();

    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    OpenGLFunction::functions().glUniformMatrix4fv(_indexOfModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    OpenGLFunction::functions().glUniform1i(_indexOfRenderTex, GL_TEXTURE0);
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, material.getRenderMapId());

    for(int i = 0; i < 5;i++){
        OpenGLFunction::functions().glUniform1f(_indexOfWeights[i], weights[i]);
    }

    OpenGLFunction::functions().glBindVertexArray(vao);

    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idOfIndexArray);

    OpenGLFunction::functions().glDrawElements(GL_TRIANGLES, 3*mesh.getNumberOfTriangles(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    OpenGLFunction::functions().glBindVertexArray(0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);

    _shaderProgram->stopUseProgram();
}
