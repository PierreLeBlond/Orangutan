#pragma once

#include "glad/glad.h"

#include "core/texture/cubetexture.h"
#include "texture/ibl.h"

namespace orangutan {

class BasisUTextureFactory {
public:
  static void ExportTexture(const std::string &filename,
                            const Texture &texture);
  static void ExportCubeTexture(const std::string &filename,
                                const CubeTexture &cube_texture,
                                bool with_mipmaps = false);
  static void ExportIbl(const std::string &path, const std::string &base_name,
                        const Ibl &ibl, const Texture &brdf);
};
} // namespace orangutan
