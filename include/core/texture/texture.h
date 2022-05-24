#ifndef ORANGUTAN_CORE_TEXTURE_TEXTURE_H
#define ORANGUTAN_CORE_TEXTURE_TEXTURE_H

#include <vector>

#include "core/texture/texturehandle.h"
#include "object/asset.h"

namespace orangutan {

class Texture : public Asset {
 public:
  Texture(const std::string &name);
  Texture(const std::string &name, TextureHandle handle);

  [[nodiscard]] unsigned int getId() const;

  [[nodiscard]] TextureHandle &getHandle();

  [[nodiscard]] const std::string &getPath() const;
  void setPath(const std::string &path);

  [[nodiscard]] unsigned int get_width() const;
  void set_width(unsigned int width);
  [[nodiscard]] unsigned int get_height() const;
  void set_height(unsigned int height);

 private:
  unsigned int width_;
  unsigned int height_;
  TextureHandle _handle;
  std::string _path;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_TEXTURE_TEXTURE_H
