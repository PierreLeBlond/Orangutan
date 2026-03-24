#ifndef ORANGUTAN_TEXTURE_IBL_H
#define ORANGUTAN_TEXTURE_IBL_H

#include <memory>

#include "core/texture/cubetexture.h"

namespace orangutan {

struct Ibl {
  std::string name;
  std::unique_ptr<CubeTexture> irradiance;
  std::unique_ptr<CubeTexture> radiance;
};

} // namespace orangutan

#endif // ORANGUTAN_TEXTURE_IBL_H
