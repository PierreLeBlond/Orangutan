#include "model/universe.h"

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

const Library<DDTexture>& Universe::get_texture_library() const {
  return texture_library_;
}

const Library<CubeTexture>& Universe::get_cube_texture_library() const {
  return cube_texture_library_;
}

const Library<ShaderWrapper>& Universe::get_shader_wrapper_library() const {
  return shader_wrapper_library_;
}

const Library<ShaderStrategy>& Universe::get_shader_strategy_library() const {
  return shader_strategy_library_;
}

const Library<Scene>& Universe::get_scene_library() const { return _scenes; }

void Universe::AddLight(std::shared_ptr<Light> light) {
  light_library_.AddItem(light);
}

void Universe::AddCamera(std::shared_ptr<Camera> camera) {
  camera_library_.AddItem(camera);
}

void Universe::AddRenderableObject(
    std::shared_ptr<RenderableObject> renderable_object) {
  renderable_object_library_.AddItem(renderable_object);
}

void Universe::AddObjectNode(std::shared_ptr<ObjectNode> object_node) {
  object_node_library_.AddItem(object_node);
}

void Universe::AddMesh(std::shared_ptr<Mesh> mesh) {
  mesh_library_.AddItem(mesh);
}

void Universe::AddTexture(std::shared_ptr<DDTexture> texture) {
  texture_library_.AddItem(texture);
}

void Universe::AddCubeTexture(std::shared_ptr<CubeTexture> cube_texture) {
  cube_texture_library_.AddItem(cube_texture);
}

void Universe::AddShaderWrapper(std::shared_ptr<ShaderWrapper> shader_wrapper) {
  shader_wrapper_library_.AddItem(shader_wrapper);
}

void Universe::AddShaderStrategy(
    std::shared_ptr<ShaderStrategy> shader_strategy) {
  shader_strategy_library_.AddItem(shader_strategy);
}

void Universe::AddScene(std::shared_ptr<Scene> scene) {
  _scenes.AddItem(scene);
}

void Universe::SetCurrentLight(std::shared_ptr<Light> light) {
  light_library_.SetCurrentItemByValue(light);
}

void Universe::SetCurrentCamera(std::shared_ptr<Camera> camera) {
  camera_library_.SetCurrentItemByValue(camera);
}

void Universe::SetCurrentRenderableObject(
    std::shared_ptr<RenderableObject> renderable_object) {
  renderable_object_library_.SetCurrentItemByValue(renderable_object);
}

void Universe::SetCurrentObjectNode(std::shared_ptr<ObjectNode> object_node) {
  object_node_library_.SetCurrentItemByValue(object_node);
}

void Universe::SetCurrentScene(std::shared_ptr<Scene> scene) {
  _scenes.SetCurrentItemByValue(scene);
}
