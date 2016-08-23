#ifndef GAUSSIANBLURFILTERSTRATEGY_H
#define GAUSSIANBLURFILTERSTRATEGY_H

#include "shader/shaderstrategy.h"

#include <math.h>

class GaussianBlurFilterStrategy : public ShaderStrategy
{
public:
                                    GaussianBlurFilterStrategy(const std::string& name = "unknown");
                                    ~GaussianBlurFilterStrategy();
    virtual void                    setUniform(const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>>& lights) const;
    virtual void                    initAttribute();

private:

    float*                          weights;

    float                           gauss(int i, float sigma);
};

#endif // GAUSSIANBLURFILTERSTRATEGY_H
