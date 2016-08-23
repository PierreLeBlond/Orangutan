#include "shader/gaussianblurfilterstrategy.h"

GaussianBlurFilterStrategy::GaussianBlurFilterStrategy(const std::string& name) : ShaderStrategy(name)
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
        weights[i] /= sum;
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

    _vertexAttribute = _shaderProgram->getAttributeLocation("vertex_in");
    _textureCoordinateAttribute = _shaderProgram->getAttributeLocation("uv_in");

    _shaderProgram->stopUseProgram();
}

void GaussianBlurFilterStrategy::setUniform(const Material &material, const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light> > &lights) const{
    _shaderProgram->startUseProgram();

    _shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    _shaderProgram->setUniform("viewMatrix", viewMatrix);
    _shaderProgram->setUniform("modelMatrix", modelMatrix);

    _shaderProgram->bindTexture(O_TEXTURE_2D, "renderTex", material.getRenderMapId());

    for(unsigned int i = 0; i < 5; i++){
        _shaderProgram->setUniform("Weight", i, weights[i]);
    }

    _shaderProgram->stopUseProgram();
}
