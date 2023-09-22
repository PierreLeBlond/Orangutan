#include "model/universe.h"

namespace orangutan {

const Library<Light>& Universe::get_light_library() const {
  return light_library_;
}

const Library<Camera>& Universe::get_camera_library() const {
  return camera_library_;
}

const Library<RenderableObject>& Universe::get_renderable_object_library()
    const {
  return renderable_object_library_;
}

const Library<ObjectNode>& Universe::get_object_node_library() const {
  return object_node_library_;
}

const Library<Mesh>& Universe::get_mesh_library() const {
  return mesh_library_;
}

const Library<Material>& Universe::get_material_library() const {
  return material_library_;
}

const Library<Texture>& Universe::get_texture_library() const {
  return texture_library_;
}

const Library<CubeTexture>& Universe::get_cube_texture_library() const {
  return cube_texture_library_;
}

const Library<Ibl>& Universe::get_ibl_library() const { return ibl_library_; }

const Library<ShaderWrapper>& Universe::get_shader_wrapper_library() const {
  return shader_wrapper_library_;
}

const Library<Scene>& Universe::get_scene_library() const { return _scenes; }

Light* Universe::AddLight(std::unique_ptr<Light> light) {
  auto name = light->getName();
  return light_library_.AddItem(name, std::move(light));
}

Camera* Universe::AddCamera(std::unique_ptr<Camera> camera) {
  auto name = camera->getName();
  return camera_library_.AddItem(name, std::move(camera));
}

RenderableObject* Universe::AddRenderableObject(
    std::unique_ptr<RenderableObject> renderable_object) {
  auto name = renderable_object->getName();
  return renderable_object_library_.AddItem(name, std::move(renderable_object));
}

ObjectNode* Universe::AddObjectNode(std::unique_ptr<ObjectNode> object_node) {
  auto name = object_node->getName();
  return object_node_library_.AddItem(name, std::move(object_node));
}

Mesh* Universe::AddMesh(std::unique_ptr<Mesh> mesh) {
  auto name = mesh->getName();
  return mesh_library_.AddItem(name, std::move(mesh));
}

Material* Universe::AddMaterial(std::unique_ptr<Material> material) {
  auto name = material->getName();
  return material_library_.AddItem(name, std::move(material));
}

Texture* Universe::AddTexture(std::unique_ptr<Texture> texture) {
  auto name = texture->getName();
  return texture_library_.AddItem(name, std::move(texture));
}

CubeTexture* Universe::AddCubeTexture(
    std::unique_ptr<CubeTexture> cube_texture) {
  auto name = cube_texture->getName();
  return cube_texture_library_.AddItem(name, std::move(cube_texture));
}

Ibl* Universe::AddIbl(std::unique_ptr<Ibl> ibl) {
  auto name = ibl->name;
  return ibl_library_.AddItem(name, std::move(ibl));
}

ShaderWrapper* Universe::AddShaderWrapper(
    std::unique_ptr<ShaderWrapper> shader_wrapper) {
  auto name = shader_wrapper->getName();
  return shader_wrapper_library_.AddItem(name, std::move(shader_wrapper));
}

Scene* Universe::AddScene(std::unique_ptr<Scene> scene) {
  auto name = scene->getName();
  return _scenes.AddItem(name, std::move(scene));
}

}  // namespace orangutan
