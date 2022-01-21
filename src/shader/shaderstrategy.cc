#include "shader/shaderstrategy.h"

#include "core/debug.h"

ShaderStrategy::ShaderStrategy(const std::string &name)
    : Asset(name),
      program_id_(-1),
      vertex_attribute_(-1),
      normal_attribute_(-1),
      texture_coordinate_attribute_(-1) {}

void ShaderStrategy::InitAttribute() {
  shader_wrapper_->start();

  vertex_attribute_ = shader_wrapper_->getAttributeLocation("vertex_in");
  normal_attribute_ = shader_wrapper_->getAttributeLocation("normal_in");
  texture_coordinate_attribute_ =
      shader_wrapper_->getAttributeLocation("uv_in");

  shader_wrapper_->stop();
}

void ShaderStrategy::SetUniforms(
    const Material &material, const glm::mat4 &modelMatrix,
    const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix,
    const std::vector<std::shared_ptr<Light>> &lights) const {
  shader_wrapper_->start();
  SetMatrixUniforms(modelMatrix, viewMatrix, projectionMatrix);
  SetMaterialUniforms(material);
  SetLightUniforms(lights, viewMatrix);
  shader_wrapper_->stop();
}

void ShaderStrategy::SetLightUniforms(
    const std::vector<std::shared_ptr<Light>> &lights,
    const glm::mat4 &viewMatrix) const {
  int nbAmbiantLights = 0;
  int nbPonctualLights = 0;
  int nbDirectionalLights = 0;
  int nbSpotLights = 0;

  for (unsigned int i = 0; i < lights.size(); i++) {
    const Light &light = *lights[i];
    switch (light.getType()) {
      case AMBIANT:
        if (nbAmbiantLights < MAX_LIGHT && light.getState()) {
          shader_wrapper_->setUniform(
              "ambiantLights", nbAmbiantLights, "La",
              light.getLa() * glm::vec3(light.getColor()) / 255.0f);
          nbAmbiantLights++;
        }
        break;
      case DIRECTION:
        if (nbDirectionalLights < MAX_LIGHT && light.getState()) {
          shader_wrapper_->setUniform(
              "directionalLights", nbDirectionalLights, "direction",
              glm::mat3(viewMatrix * light.getTransform().get_model_matrix()) *
                  glm::vec3(1.0, 0.0, 0.0));
          shader_wrapper_->setUniform(
              "directionalLights", nbDirectionalLights, "La",
              light.getLa() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform(
              "directionalLights", nbDirectionalLights, "Ld",
              light.getLd() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform("directionalLights", nbDirectionalLights,
                                      "Ls", light.getLs());
          nbDirectionalLights++;
        }
        break;
      case PONCTUAL:
        if (nbPonctualLights < MAX_LIGHT && light.getState()) {
          shader_wrapper_->setUniform(
              "ponctualLights", nbPonctualLights, "position",
              viewMatrix * light.getTransform().get_model_matrix() *
                  glm::vec4(0.0, 0.0, 0.0, 1.0));
          shader_wrapper_->setUniform(
              "ponctualLights", nbPonctualLights, "La",
              light.getLa() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform(
              "ponctualLights", nbPonctualLights, "Ld",
              light.getLd() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform("ponctualLights", nbPonctualLights, "Ls",
                                      light.getLs());
          nbPonctualLights++;
        }
        break;
      case SPOT:
        if (nbSpotLights < MAX_LIGHT && light.getState()) {
          shader_wrapper_->setUniform(
              "spotLights", nbSpotLights, "position",
              viewMatrix * light.getTransform().get_model_matrix() *
                  glm::vec4(0.0, 0.0, 0.0, 1.0));
          shader_wrapper_->setUniform(
              "spotLights", nbSpotLights, "direction",
              glm::normalize(
                  glm::mat3(viewMatrix *
                            lights[i]->getTransform().get_model_matrix() *
                            light.getTransform().get_model_matrix()) *
                  glm::vec3(1.0, 0.0, 0.0)));
          shader_wrapper_->setUniform(
              "spotLights", nbSpotLights, "La",
              light.getLa() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform(
              "spotLights", nbSpotLights, "Ld",
              light.getLd() * glm::vec3(light.getColor()) / 255.0f);
          shader_wrapper_->setUniform("spotLights", nbSpotLights, "Ls",
                                      light.getLs());
          shader_wrapper_->setUniform("spotLights", nbSpotLights, "exponent",
                                      light.getExponent());
          shader_wrapper_->setUniform("spotLights", nbSpotLights, "cutoff",
                                      light.getCutoffAngle());
          nbSpotLights++;
        }
        break;
      default:
        break;
    }
  }

  shader_wrapper_->setUniform("nbPonctualLight", nbPonctualLights);
  shader_wrapper_->setUniform("nbAmbiantLight", nbAmbiantLights);
  shader_wrapper_->setUniform("nbDirectionLight", nbDirectionalLights);
  shader_wrapper_->setUniform("nbSpotLight", nbSpotLights);
}

void ShaderStrategy::SetMatrixUniforms(
    const glm::mat4 &modelMatrix, const glm::mat4 &viewMatrix,
    const glm::mat4 &projectionMatrix) const {
  shader_wrapper_->setUniform("projectionMatrix", projectionMatrix);
  shader_wrapper_->setUniform("viewMatrix", viewMatrix);
  shader_wrapper_->setUniform("modelMatrix", modelMatrix);
}

void ShaderStrategy::SetMaterialUniforms(const Material &material) const {
  for (const auto &uniform : material.get1fUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get1iUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get1uiUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get1bUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get3fUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get4fUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get3x3fUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &uniform : material.get4x4fUniforms()) {
    SetUniform(uniform);
  }

  for (const auto &pair : material.getTextures()) {
    shader_wrapper_->bindTexture(pair.first, pair.second->getId());
  }

  for (const auto &pair : material.getCubeTextures()) {
    shader_wrapper_->bindCubeTexture(pair.first, pair.second->getId());
  }

  for (const auto &subMaterial : material.getMaterials()) {
    SetMaterialUniforms(subMaterial);
  }
}

void ShaderStrategy::set_shader_wrapper(
    std::shared_ptr<ShaderWrapper> shaderWrapper) {
  shader_wrapper_ = shaderWrapper;
  program_id_ = shader_wrapper_->getProgramId();
}

const std::shared_ptr<ShaderWrapper> &ShaderStrategy::get_shader_wrapper()
    const {
  return shader_wrapper_;
}

void ShaderStrategy::Draw(const Vao &vao) const {
  shader_wrapper_->start();

  vao.bind();
  vao.bindIndexBuffer();

  vao.drawElements();

  vao.unbindIndexBuffer();
  vao.unbind();

  shader_wrapper_->unbindTexture();

  shader_wrapper_->stop();
}
