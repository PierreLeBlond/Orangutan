#include "object/renderableobject.h"

#include "core/debug.h"

namespace orangutan {

RenderableObject::RenderableObject(const std::string& name)
    : Object(name),
      mesh_(nullptr),
      shader_strategy_(nullptr),
      material_(nullptr) {}

void RenderableObject::UpdateVertexArrayObject() {
  position_array_id_ = vao_.addBuffer();
  normal_array_id_ = vao_.addBuffer();
  uv_array_id_ = vao_.addBuffer();

  if (shader_strategy_->get_vertex_attribute() > -1)
    vao_.fillBuffer(position_array_id_,
                    mesh_->getNumberOfPositions() * sizeof(float),
                    mesh_->getPositions().data());
  if (shader_strategy_->get_normal_attribute() > -1)
    vao_.fillBuffer(normal_array_id_,
                    mesh_->getNumberOfNormals() * sizeof(float),
                    mesh_->getNormals().data());
  if (shader_strategy_->get_texture_coordinate_attribute() > -1)
    vao_.fillBuffer(uv_array_id_, mesh_->getNumberOfUvs() * sizeof(float),
                    mesh_->getUvs().data());
  vao_.fillIndexBuffer(mesh_->getNumberOfFaces() * sizeof(int),
                       mesh_->getFaces().data());
  vao_.setNumberOfElements(3 * mesh_->getNumberOfFaces());
  if (shader_strategy_->get_vertex_attribute() > -1)
    vao_.attribBuffer(position_array_id_,
                      shader_strategy_->get_vertex_attribute(), 3, O_FLOAT);
  if (shader_strategy_->get_normal_attribute() > -1)
    vao_.attribBuffer(normal_array_id_,
                      shader_strategy_->get_normal_attribute(), 3, O_FLOAT);
  if (shader_strategy_->get_texture_coordinate_attribute() > -1)
    vao_.attribBuffer(uv_array_id_,
                      shader_strategy_->get_texture_coordinate_attribute(), 2,
                      O_FLOAT);
}

void RenderableObject::draw(const glm::mat4& viewMatrix,
                            const glm::vec3& camera_position,
                            const glm::mat4& projectionMatrix,
                            const std::vector<Light*>& lights, const Ibl& ibl,
                            const Texture& brdf) {
  shader_strategy_->SetUniforms(*material_, getTransform().get_world_matrix(),
                                viewMatrix, camera_position, projectionMatrix,
                                lights, ibl, brdf);
  Draw();
}

void RenderableObject::Draw() { shader_strategy_->Draw(vao_); }

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

const ShaderStrategy& RenderableObject::get_shader_strategy() const {
  return *shader_strategy_;
}
void RenderableObject::set_shader_strategy(
    const ShaderStrategy* shader_strategy) {
  shader_strategy_ = shader_strategy;
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
