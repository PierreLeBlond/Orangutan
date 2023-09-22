#include "object/renderableobject.h"

#include <iostream>

#include "core/debug.h"

namespace orangutan {

RenderableObject::RenderableObject(const std::string& name)
    : Object(name), mesh_(nullptr), material_(nullptr) {}

void RenderableObject::UpdateVertexArrayObject() {
  position_array_id_ = vao_.addBuffer();
  normal_array_id_ = vao_.addBuffer();
  tangent_array_id_ = vao_.addBuffer();
  uv_array_id_ = vao_.addBuffer();
  uv_2_array_id_ = vao_.addBuffer();

  auto shader_wrapper = material_->get_shader_wrapper();

  shader_wrapper.Start();

  int vertex_attribute = shader_wrapper.GetAttributeLocation("vertex_in");
  int normal_attribute = shader_wrapper.GetAttributeLocation("normal_in");
  int tangent_attribute = shader_wrapper.GetAttributeLocation("tangent_in");
  int texture_coordinate_attribute =
      shader_wrapper.GetAttributeLocation("uv_in");
  int texture_coordinate_2_attribute =
      shader_wrapper.GetAttributeLocation("uv_2_in");

  shader_wrapper.Stop();

  if (vertex_attribute > -1) {
    vao_.fillBuffer(position_array_id_,
                    mesh_->GetNumberOfPositions() * sizeof(float),
                    mesh_->GetPositions().data());
  }

  if (normal_attribute > -1) {
    vao_.fillBuffer(normal_array_id_,
                    mesh_->GetNumberOfNormals() * sizeof(float),
                    mesh_->GetNormals().data());
  }

  if (tangent_attribute > -1) {
    vao_.fillBuffer(tangent_array_id_,
                    mesh_->GetNumberOfTangents() * sizeof(float),
                    mesh_->GetTangents().data());
  }

  if (texture_coordinate_attribute > -1) {
    vao_.fillBuffer(uv_array_id_, mesh_->GetNumberOfUvs() * sizeof(float),
                    mesh_->GetUvs().data());
  }

  if (texture_coordinate_2_attribute > -1) {
    vao_.fillBuffer(uv_2_array_id_, mesh_->GetNumberOfUvs2() * sizeof(float),
                    mesh_->GetUvs2().data());
  }

  vao_.fillIndexBuffer(mesh_->GetNumberOfFaces() * sizeof(int),
                       mesh_->GetFaces().data());
  vao_.setNumberOfElements(3 * mesh_->GetNumberOfFaces());
  if (vertex_attribute > -1) {
    vao_.attribBuffer(position_array_id_, vertex_attribute, 3, O_FLOAT);
  }
  if (normal_attribute > -1) {
    vao_.attribBuffer(normal_array_id_, normal_attribute, 3, O_FLOAT);
  }
  if (tangent_attribute > -1) {
    vao_.attribBuffer(tangent_array_id_, tangent_attribute, 3, O_FLOAT);
  }
  if (texture_coordinate_attribute > -1) {
    vao_.attribBuffer(uv_array_id_, texture_coordinate_attribute, 2, O_FLOAT);
  }
  if (texture_coordinate_2_attribute > -1) {
    vao_.attribBuffer(uv_2_array_id_, texture_coordinate_2_attribute, 2,
                      O_FLOAT);
  }
}

void RenderableObject::Draw(const glm::mat4& viewMatrix,
                            const glm::vec3& camera_position,
                            const glm::mat4& projectionMatrix,
                            const std::vector<Light*>& lights, const Ibl& ibl,
                            const Texture& brdf) {
  material_->BindUniforms(*material_, getTransform().get_world_matrix(),
                          viewMatrix, camera_position, projectionMatrix, lights,
                          ibl, brdf);
  Draw();
}

void RenderableObject::Draw() {
  material_->get_shader_wrapper().Start();

  vao_.bind();
  vao_.bindIndexBuffer();

  vao_.drawElements();

  vao_.unbindIndexBuffer();
  vao_.unbind();

  material_->get_shader_wrapper().UnbindTexture();

  material_->get_shader_wrapper().Stop();
}

const Mesh& RenderableObject::get_mesh() const { return *mesh_; }
void RenderableObject::set_mesh(const Mesh* mesh) {
  if (mesh_ != nullptr) {
    std::cerr << "Renderable object already has a attached mesh" << std::endl;
  }
  mesh_ = mesh;
}

Material& RenderableObject::get_material() const { return *material_; }
void RenderableObject::set_material(Material* material) {
  material_ = material;
}

unsigned int RenderableObject::get_position_array_id() const {
  return position_array_id_;
}

unsigned int RenderableObject::get_index_array_id() const {
  return index_array_id_;
}

unsigned int RenderableObject::get_normal_array_id() const {
  return normal_array_id_;
}

unsigned int RenderableObject::get_uv_array_id() const { return uv_array_id_; }

const Vao& RenderableObject::get_vao() const { return vao_; }

void RenderableObject::SetTexture(const std::string& name,
                                  const Texture* texture) {
  material_->SetTexture(name, texture);
}

void RenderableObject::SetCubeTexture(const std::string& name,
                                      const CubeTexture* texture) {
  material_->SetCubeTexture(name, texture);
}

}  // namespace orangutan
