#ifndef SKYBOXSTRATEGY_H
#define SKYBOXSTRATEGY_H

#include "shader/shaderstrategy.h"

class SkyboxStrategy : public ShaderStrategy
{
public:
                                                SkyboxStrategy(const std::string& name = "unknown");
                                                ~SkyboxStrategy();
    virtual void                                setUniform(const Material &material, const glm::core::type::mat4& modelMatrix, const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>> &lights) const;
    virtual void                                initAttribute();
};

#endif // SKYBOXSTRATEGY_H
