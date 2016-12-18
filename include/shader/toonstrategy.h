#ifndef TOONSTRATEGY_H
#define TOONSTRATEGY_H

#include "shader/shaderstrategy.h"

class ToonStrategy : public ShaderStrategy
{
public:
                                                ToonStrategy(const std::string& name = "unknown");
                                                ~ToonStrategy();
    virtual void                                setUniform(const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<Light>>& lights) const;
    virtual void                                initAttribute();
};

#endif // TOONSTRATEGY_H
