#ifndef ORANGUTAN_MODEL_UNIVERSE_H
#define ORANGUTAN_MODEL_UNIVERSE_H

#include <memory>
#include <vector>

#include "camera/camera.h"
#include "core/texture/cubetexture.h"
#include "core/texture/texture.h"
#include "mesh/mesh.h"
#include "model/library.h"
#include "object/renderableobject.h"
#include "scene/scene.h"
#include "texture/ibl.h"

namespace orangutan {

class Universe {
 public:
  [[nodiscard]] const Library<Light>& get_light_library() const;
  [[nodiscard]] const Library<Camera>& get_camera_library() const;
  [[nodiscard]] const Library<RenderableObject>& get_renderable_object_library()
      const;
  [[nodiscard]] const Library<ObjectNode>& get_object_node_library() const;

  [[nodiscard]] const Library<Mesh>& get_mesh_library() const;
  [[nodiscard]] const Library<Material>& get_material_library() const;
  [[nodiscard]] const Library<Texture>& get_texture_library() const;
  [[nodiscard]] const Library<CubeTexture>& get_cube_texture_library() const;
  [[nodiscard]] const Library<Ibl>& get_ibl_library() const;
  [[nodiscard]] const Library<ShaderWrapper>& get_shader_wrapper_library()
      const;

  [[nodiscard]] const Library<Scene>& get_scene_library() const;

  Light* AddLight(std::unique_ptr<Light> light);
  Camera* AddCamera(std::unique_ptr<Camera> camera);
  RenderableObject* AddRenderableObject(
      std::unique_ptr<RenderableObject> renderable_object);
  ObjectNode* AddObjectNode(std::unique_ptr<ObjectNode> object_node);

  Mesh* AddMesh(std::unique_ptr<Mesh> mesh);
  Material* AddMaterial(std::unique_ptr<Material> material);
  Texture* AddTexture(std::unique_ptr<Texture> texture);
  CubeTexture* AddCubeTexture(std::unique_ptr<CubeTexture> cube_texture);
  Ibl* AddIbl(std::unique_ptr<Ibl> ibl);
  ShaderWrapper* AddShaderWrapper(
      std::unique_ptr<ShaderWrapper> shader_wrapper);

  Scene* AddScene(std::unique_ptr<Scene> scene);

 private:
  Library<Light> light_library_;
  Library<Camera> camera_library_;
  Library<RenderableObject> renderable_object_library_;
  Library<ObjectNode> object_node_library_;

  Library<Mesh> mesh_library_;
  Library<Material> material_library_;
  Library<Texture> texture_library_;
  Library<CubeTexture> cube_texture_library_;
  Library<Ibl> ibl_library_;
  Library<ShaderWrapper> shader_wrapper_library_;

  Library<Scene> _scenes;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MODEL_UNIVERSE_H
