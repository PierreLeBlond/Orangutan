#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "object/asset.h"
#include "object/material.h"
#include "shader/shaderstrategy.h"

class ShaderStrategy;

class ShaderMaterialable {
 public:
  [[nodiscard]] virtual std::shared_ptr<const ShaderStrategy>
  getShaderStrategy() const = 0;
  virtual void setShaderStrategy(
      std::shared_ptr<const ShaderStrategy> shaderStrategy) = 0;
};

class ShaderMaterial : public ShaderMaterialable, public Material {
 public:
  ShaderMaterial(const std::string &name = "ShaderMaterial X");

  [[nodiscard]] std::shared_ptr<const ShaderStrategy> getShaderStrategy()
      const override;
  void setShaderStrategy(
      std::shared_ptr<const ShaderStrategy> shaderStrategy) override;

 private:
  std::shared_ptr<const ShaderStrategy> _shaderStrategy;
};
