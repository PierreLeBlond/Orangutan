#ifndef ORANGUTAN_TEXTURE_RENDER_TARGET_H
#define ORANGUTAN_TEXTURE_RENDER_TARGET_H

#include <memory>

#include "core/texture/texture.h"
#include "patterns/observer/signal.h"

namespace orangutan {

class RenderTarget : public Texture {
 public:
  RenderTarget(const std::string &name, int width, int height);
  void Draw();

  [[nodiscard]] Signal<> &get_drawing_signal();

 private:
  unsigned int frame_buffer_object_;
  Signal<> drawing_signal_;
};
}  // namespace orangutan

#endif  // ORANGUTAN_TEXTURE_RENDER_TARGET_H
