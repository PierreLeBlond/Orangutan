#ifndef ORANGUTAN_CORE_TEXTURE_CUBETEXTURE_H
#define ORANGUTAN_CORE_TEXTURE_CUBETEXTURE_H

#include "core/texture/texture.h"

namespace orangutan {

class CubeTexture : public Texture {
 public:
  CubeTexture(const std::string &name);
  CubeTexture(const std::string &name, TextureHandle handle);

  [[nodiscard]] unsigned int get_size() const;
  void set_size(unsigned int size);

 private:
  unsigned int size_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_TEXTURE_CUBETEXTURE_H
