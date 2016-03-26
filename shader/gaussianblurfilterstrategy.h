#ifndef GAUSSIANBLURFILTERSTRATEGY_H
#define GAUSSIANBLURFILTERSTRATEGY_H

#include "shaderstrategy.h"

#include <math.h>

class GaussianBlurFilterStrategy : public ShaderStrategy
{
public:
                                    GaussianBlurFilterStrategy();
                                    ~GaussianBlurFilterStrategy();
    virtual void                    draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) const;
    virtual void                    initAttribute();
    virtual void                    initUniformLocation();

private:
    GLuint                          _indexOfProjectionMatrix;
    GLuint                          _indexOfViewMatrix;
    GLuint                          _indexOfModelMatrix;

    GLuint                          _indexOfRenderTex;
    std::vector<GLuint>             _indexOfWeights;
    std::vector<GLuint>             _indexOfPixelOffsets;

    float*                          weights;

    float                           gauss(int i, float sigma);
};

#endif // GAUSSIANBLURFILTERSTRATEGY_H
