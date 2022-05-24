#ifndef ORANGUTAN_OBJECT_RENDERABLE_OBJECT_H
#define ORANGUTAN_OBJECT_RENDERABLE_OBJECT_H

#include <memory>
#include <vector>

#include "core/vertex/vao.h"
#include "material/material.h"
#include "material/shaderstrategy.h"
#include "mesh/mesh.h"
#include "object/object.h"
#include "util/util.h"

namespace orangutan {

class RenderableObject : public Object {
 public:
  RenderableObject(const std::string& name);

  void UpdateVertexArrayObject();

  void draw(const glm::mat4& viewMatrix, const glm::vec3& camera_position,
            const glm::mat4& projectionMatrix,
            const std::vector<Light*>& lights, const Ibl& ibl,
            const Texture& brdf) override;
  void Draw();

  [[nodiscard]] const Mesh& get_mesh() const;
  void set_mesh(const Mesh* mesh);

  [[nodiscard]] Material& get_material() const;
  void set_material(Material* material);

  [[nodiscard]] const ShaderStrategy& get_shader_strategy() const;
  void set_shader_strategy(const ShaderStrategy* shader_strategy);

  [[nodiscard]] unsigned int get_position_array_id() const;
  [[nodiscard]] unsigned int get_index_array_id() const;
  [[nodiscard]] unsigned int get_normal_array_id() const;
  [[nodiscard]] unsigned int get_uv_array_id() const;

  [[nodiscard]] const Vao& get_vao() const;

  void SetTexture(const std::string& name, const Texture* texture);
  void SetCubeTexture(const std::string& name, const CubeTexture* texture);

  template <class T>
  void SetUniform(const std::string& name, const T& value) {
    material_->SetUniform(name, value);
  }

  template <class T>
  void GetUniform(const std::string& name, T& value) const {
    material_->GetUniform(name, value);
  }

 private:
  const Mesh* mesh_;
  const ShaderStrategy* shader_strategy_;
  Material* material_;

  unsigned int position_array_id_;
  unsigned int index_array_id_;
  unsigned int normal_array_id_;
  unsigned int uv_array_id_;

  Vao vao_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_RENDERABLE_OBJECT_H
