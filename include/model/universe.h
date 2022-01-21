#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <memory>
#include <vector>

#include "camera/camera.h"
#include "core/texture/cubetexture.h"
#include "core/texture/ddtexture.h"
#include "model/library.h"
#include "object/mesh.h"
#include "object/renderableobject.h"
#include "scene/scene.h"
#include "shader/shaderstrategy.h"

class Universe {
 public:
  [[nodiscard]] const Library<Light>& get_light_library() const;
  [[nodiscard]] const Library<Camera>& get_camera_library() const;
  [[nodiscard]] const Library<RenderableObject>& get_renderable_object_library()
      const;
  [[nodiscard]] const Library<ObjectNode>& get_object_node_library() const;

  [[nodiscard]] const Library<Mesh>& get_mesh_library() const;
  [[nodiscard]] const Library<DDTexture>& get_texture_library() const;
  [[nodiscard]] const Library<CubeTexture>& get_cube_texture_library() const;
  [[nodiscard]] const Library<ShaderWrapper>& get_shader_wrapper_library()
      const;
  [[nodiscard]] const Library<ShaderStrategy>& get_shader_strategy_library()
      const;

  [[nodiscard]] const Library<Scene>& get_scene_library() const;

  void AddLight(std::shared_ptr<Light> light);
  void AddCamera(std::shared_ptr<Camera> camera);
  void AddRenderableObject(std::shared_ptr<RenderableObject> renderable_object);
  void AddObjectNode(std::shared_ptr<ObjectNode> object_node);

  void AddMesh(std::shared_ptr<Mesh> mesh);
  void AddTexture(std::shared_ptr<DDTexture> texture);
  void AddCubeTexture(std::shared_ptr<CubeTexture> cube_texture);
  void AddShaderWrapper(std::shared_ptr<ShaderWrapper> shader_wrapper);
  void AddShaderStrategy(std::shared_ptr<ShaderStrategy> shader_strategy);

  void AddScene(std::shared_ptr<Scene> scene);

  void SetCurrentLight(std::shared_ptr<Light> light);
  void SetCurrentCamera(std::shared_ptr<Camera> camera);
  void SetCurrentRenderableObject(
      std::shared_ptr<RenderableObject> renderable_object);
  void SetCurrentObjectNode(std::shared_ptr<ObjectNode> object_node);

  void SetCurrentScene(std::shared_ptr<Scene> scene);

 private:
  Library<Light> light_library_;
  Library<Camera> camera_library_;
  Library<RenderableObject> renderable_object_library_;
  Library<ObjectNode> object_node_library_;

  Library<Mesh> mesh_library_;
  Library<DDTexture> texture_library_;
  Library<CubeTexture> cube_texture_library_;
  Library<ShaderWrapper> shader_wrapper_library_;
  Library<ShaderStrategy> shader_strategy_library_;

  Library<Scene> _scenes;
};

#endif  // UNIVERSE_H
