#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include "core/texture/texture.h"

class CubeTexture : public Texture {
 public:
  CubeTexture(const std::string &name = "CubeTexture X");
  CubeTexture(const std::string &path, const std::string &name);

  bool load(const std::string &path) override;
};

#endif  // CUBETEXTURE_H
