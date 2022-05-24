#ifndef ORANGUTAN_TEXTURE_CUBE_RENDER_TARGET_H
#define ORANGUTAN_TEXTURE_CUBE_RENDER_TARGET_H

#include <memory>
#include <optional>

#include "core/texture/cubetexture.h"
#include "nanogui/opengl.h"
#include "patterns/observer/signal.h"

namespace orangutan {

struct CubeRenderTargetOptions {
  int min_filter = GL_LINEAR;
  bool generate_mip_maps = false;
};

class CubeRenderTarget : public CubeTexture {
 public:
  CubeRenderTarget(
      const std::string &name, int size,
      const CubeRenderTargetOptions &options = CubeRenderTargetOptions());
  void Draw();
  void DrawMip(unsigned int mip_level);

  [[nodiscard]] Signal<unsigned int> &get_drawing_signal();

 private:
  unsigned int frame_buffer_object_;
  unsigned int render_buffer_object_;
  Signal<unsigned int> drawing_signal_;
};
}  // namespace orangutan

#endif  // ORANGUTAN_TEXTURE_CUBE_RENDER_TARGET_H
