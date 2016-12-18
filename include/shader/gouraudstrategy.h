#ifndef GOURAUDSTRATEGY_H
#define GOURAUDSTRATEGY_H

#include "shader/shaderstrategy.h"

class GouraudStrategy : public ShaderStrategy
{
public:
                                                GouraudStrategy(const std::string& name = "unknown");
                                                ~GouraudStrategy();

    virtual void                                setUniform(const Material& material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>>& lights) const;
    virtual void                                initAttribute();
};

#endif // GOURAUDSTRATEGY_H
