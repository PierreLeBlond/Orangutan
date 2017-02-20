#pragma once

#include "object/asset.h"
#include "shader/shaderstrategy.h"
#include "object/material.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <memory>

class ShaderStrategy;

class ShaderMaterialable
{
  public:
    virtual std::shared_ptr<const ShaderStrategy>   getShaderStrategy() const = 0;
    virtual void                                    setShaderStrategy(
        std::shared_ptr<const ShaderStrategy> shaderStrategy) = 0;
};

class ShaderMaterial : public ShaderMaterialable, public Material
{
public:
                                                    ShaderMaterial(const std::string &name = "ShaderMaterial X");

    virtual std::shared_ptr<const ShaderStrategy>   getShaderStrategy() const;
    virtual void                                    setShaderStrategy(
        std::shared_ptr<const ShaderStrategy> shaderStrategy);

private:
    std::shared_ptr<const ShaderStrategy>           _shaderStrategy;
};
