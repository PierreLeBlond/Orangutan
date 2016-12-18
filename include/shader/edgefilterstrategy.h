#ifndef EDGEFILTERSTRATEGY_H
#define EDGEFILTERSTRATEGY_H

#include "shader/shaderstrategy.h"


class EdgeFilterStrategy : public ShaderStrategy
{
public:
                                    EdgeFilterStrategy(const std::string& name = "unknown");
    virtual void                    setUniform(const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>>& lights) const;
    virtual void                    initAttribute();
};

#endif // EDGEFILTERSTRATEGY_H
