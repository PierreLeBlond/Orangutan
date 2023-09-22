#ifndef ORANGUTAN_DEBUG_DEBUG_H
#define ORANGUTAN_DEBUG_DEBUG_H

#include <memory>

#include "core/texture/texture.h"
#include "object/renderableobject.h"

namespace orangutan {

class VisualDebugger {
 public:
  void DisplayTexture(const Texture& texture);
  void DisplayCubeTexture(const CubeTexture& cube_texture, int width,
                          int height);

 private:
  std::unique_ptr<ShaderWrapper> texture_displayer_shader_wrapper_;
  std::unique_ptr<Material> texture_displayer_material_;
  std::unique_ptr<Mesh> texture_displayer_mesh_;
  std::unique_ptr<RenderableObject> texture_displayer_;
  std::unique_ptr<ShaderWrapper> cube_texture_displayer_shader_wrapper_;
  std::unique_ptr<Material> cube_texture_displayer_material_;
  std::unique_ptr<Mesh> cube_texture_displayer_mesh_;
  std::unique_ptr<RenderableObject> cube_texture_displayer_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_DEBUG_DEBUG_H
