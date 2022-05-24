#include "material/shaderstrategy.h"

#include "core/debug.h"

namespace orangutan {

ShaderStrategy::ShaderStrategy(const std::string &name)
    : Asset(name), shader_wrapper_(nullptr) {}

void ShaderStrategy::InitAttribute() {
  shader_wrapper_->start();

  vertex_attribute_ = shader_wrapper_->getAttributeLocation("vertex_in");
  normal_attribute_ = shader_wrapper_->getAttributeLocation("normal_in");
  texture_coordinate_attribute_ =
      shader_wrapper_->getAttributeLocation("uv_in");

  shader_wrapper_->stop();
}

void ShaderStrategy::SetUniforms(const Material &material,
                                 const glm::mat4 &modelMatrix,
                                 const glm::mat4 &viewMatrix,
                                 const glm::vec3 &camera_position,
                                 const glm::mat4 &projectionMatrix,
                                 const std::vector<Light *> &lights,
                                 const Ibl &ibl, const Texture &brdf) const {
  shader_wrapper_->start();
  SetSceneUniforms(modelMatrix, viewMatrix, camera_position, projectionMatrix);
  SetMaterialUniforms(material);
  SetLightUniforms(lights, viewMatrix, ibl, brdf);
  shader_wrapper_->stop();
}

void ShaderStrategy::SetLightUniforms(const std::vector<Light *> &lights,
                                      const glm::mat4 &viewMatrix,
                                      const Ibl &ibl,
                                      const Texture &brdf) const {
  unsigned int number_of_lights = lights.size();

  for (unsigned int i = 0; i < number_of_lights; i++) {
    const Light &light = *lights[i];
    shader_wrapper_->setUniform("lights", i, "position",
                                light.getTransform().GetGlobalPos());
    shader_wrapper_->setUniform("lights", i, "color", light.get_color());
    shader_wrapper_->setUniform("lights", i, "intensity",
                                light.get_intensity());
    shader_wrapper_->setUniform("lights", i, "falloffRadius",
                                light.get_falloff_radius());
  }

  shader_wrapper_->setUniform("numberOfLights", number_of_lights);

  shader_wrapper_->bindCubeTexture("ibl.radiance", ibl.radiance->getId());
  shader_wrapper_->bindCubeTexture("ibl.irradiance", ibl.irradiance->getId());
  shader_wrapper_->bindTexture("brdf", brdf.getId());
}

void ShaderStrategy::SetSceneUniforms(const glm::mat4 &modelMatrix,
                                      const glm::mat4 &viewMatrix,
                                      const glm::vec3 &camera_position,
                                      const glm::mat4 &projectionMatrix) const {
  shader_wrapper_->setUniform("projectionMatrix", projectionMatrix);
  shader_wrapper_->setUniform("viewMatrix", viewMatrix);
  shader_wrapper_->setUniform("modelMatrix", modelMatrix);
  shader_wrapper_->setUniform("cameraPosition", camera_position);
}

void ShaderStrategy::SetMaterialUniforms(const Material &material) const {
  for (const auto &uniform : material.get_uniforms_1f()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_1i()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_1ui()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_1b()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_3f()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_4f()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_3x3()) {
    SetUniform(uniform.second);
  }

  for (const auto &uniform : material.get_uniforms_4x4()) {
    SetUniform(uniform.second);
  }

  for (const auto &pair : material.get_textures()) {
    shader_wrapper_->bindTexture(pair.first, pair.second->getId());
  }

  for (const auto &pair : material.get_cube_textures()) {
    shader_wrapper_->bindCubeTexture(pair.first, pair.second->getId());
  }
}

void ShaderStrategy::set_shader_wrapper(ShaderWrapper *shaderWrapper) {
  shader_wrapper_ = shaderWrapper;
  program_id_ = shader_wrapper_->getProgramId();
}

ShaderWrapper &ShaderStrategy::get_shader_wrapper() const {
  return *shader_wrapper_;
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

}  // namespace orangutan
