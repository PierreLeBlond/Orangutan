#ifndef ORANGUTAN_TEXTURE_TEXTURE_FACTORY_H
#define ORANGUTAN_TEXTURE_TEXTURE_FACTORY_H

#include <memory>

#include "core/texture/cubetexture.h"
#include "core/texture/texture.h"
#include "texture/ibl.h"

namespace orangutan {

class TextureFactory {
 public:
  static std::unique_ptr<Texture> ImportTexture(const std::string& name,
                                                const std::string& filename);
  static std::unique_ptr<Texture> CreateBrdfMap();
  static void ExportTexture(const std::string& filename,
                            const Texture& texture);

  static std::unique_ptr<CubeTexture> ImportCubeTexture(
      const std::string& name, const std::string& filename);
  static void ExportCubeTexture(const std::string& filename,
                                const CubeTexture& cube_texture,
                                unsigned int size, unsigned int mip_map_count);
  static void ExportRgbdCubeTexture(const std::string& filename,
                                    const CubeTexture& cube_texture,
                                    unsigned int size,
                                    unsigned int mip_map_count);
  static void ExportIrradiance(const std::string& filename,
                               const CubeTexture& irradiance,
                               bool convert_to_rgbd = false);
  static void ExportRadiance(const std::string& filename,
                             const CubeTexture& radiance,
                             bool convert_to_rgbd = false);

  static std::unique_ptr<Ibl> ImportIBLFromHdr(const std::string& name,
                                               const std::string& filename);
  static std::unique_ptr<Ibl> ImportIBLFromDds(
      const std::string& name, const std::string& irradiance_filename,
      const std::string& radiance_filename);
  static std::unique_ptr<Ibl> ImportIBLFromRgbdDds(
      const std::string& name, const std::string& irradiance_filename,
      const std::string& radiance_filename);
  static void ExportIbl(const std::string& name,
                        const std::string& irradiance_filename,
                        const std::string& radiance_filename, const Ibl& ibl,
                        bool convert_to_rgbd = false);

 private:
  static unsigned int ImportEquirectangularHDR(const std::string& filename);
  static std::unique_ptr<CubeTexture> TransformEquirectangularToCube(
      const std::string& name, unsigned int equirectangular_handle);
  static std::unique_ptr<CubeTexture> CreateIrradianceMap(
      const CubeTexture& cube_texture);
  static std::unique_ptr<CubeTexture> CreateRadianceMap(
      const CubeTexture& cube_texture);
  static std::unique_ptr<CubeTexture> ImportCubeTextureFromDds(
      const std::string& name, const std::string& filename);
  static std::unique_ptr<CubeTexture> ImportCubeTextureFromRgbdDds(
      const std::string& name, const std::string& filename);
};

}  // namespace orangutan

#endif  // ORANGUTAN_TEXTURE_TEXTURE_FACTORY_H
