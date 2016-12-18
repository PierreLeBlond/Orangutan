#ifndef ENVIRONMENTSTRATEGY_H
#define ENVIRONMENTSTRATEGY_H

#include "shader/shaderstrategy.h"

class EnvironmentStrategy: public ShaderStrategy
{
public:
                                                EnvironmentStrategy(const std::string& name = "unknown");
                                                ~EnvironmentStrategy();
    virtual void                                setUniform(const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,const std::vector<std::shared_ptr<Light>>& lights) const;
    virtual void                                initAttribute();
};

#endif // ENVIRONMENTSTRATEGY_H
