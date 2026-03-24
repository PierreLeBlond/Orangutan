#include "texture/ktxtexturefactory.h"
#include "core/debug.h"
#include "ktx.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>

namespace orangutan {

void KtxTextureFactory::ExportTexture(const std::string &filename,
                                      const Texture &texture) {
  ktxTexture2 *ktx_texture;
  ktxTextureCreateInfo createInfo;
  KTX_error_code result;

  unsigned int width = texture.get_width();
  unsigned int height = texture.get_height();

  createInfo.vkFormat = 97; // VK_FORMAT_R16G16B16_SFLOAT;
  createInfo.baseWidth = width;
  createInfo.baseHeight = height;
  createInfo.baseDepth = 1;
  createInfo.numDimensions = 2;
  createInfo.numLayers = 1;
  createInfo.numFaces = 1;
  createInfo.isArray = KTX_FALSE;
  createInfo.generateMipmaps = KTX_FALSE;

  result = ktxTexture2_Create(&createInfo, KTX_TEXTURE_CREATE_ALLOC_STORAGE,
                              &ktx_texture);

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("ktxTexture2_Create failed: ") +
                             ktxErrorString(result));
  }

  GL_CHECK_ERROR(glActiveTexture(GL_TEXTURE0));
  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, texture.getId()));

  unsigned int data_size = 4 * width * height;

  GLhalf *data = (GLhalf *)calloc(data_size, sizeof(GLhalf));

  GL_CHECK_ERROR(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_HALF_FLOAT, data));

  result = ktxTexture_SetImageFromMemory(
      ktxTexture(ktx_texture), 0, 0, 0,
      reinterpret_cast<const ktx_uint8_t *>(data), data_size);

  if (result != KTX_SUCCESS) {
    ktxTexture_Destroy(ktxTexture(ktx_texture));
    throw std::runtime_error(std::string("SetImageFromMemory failed :") +
                             ktxErrorString(result));
  }

  free(data);

  ktxBasisParams params = {0};
  params.structSize = sizeof(params);
  // params.uastc = KTX_TRUE;
  params.compressionLevel = KTX_ETC1S_DEFAULT_COMPRESSION_LEVEL;
  result = ktxTexture2_CompressBasis(ktx_texture, 0);

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("CompressBasisEx failed: ") +
                             ktxErrorString(result));
  }

  result =
      ktxTexture_WriteToNamedFile(ktxTexture(ktx_texture), filename.c_str());

  ktxTexture_Destroy(ktxTexture(ktx_texture));

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("WriteToNamedFile failed: ") +
                             ktxErrorString(result));
  }
}

void KtxTextureFactory::ExportCubeTexture(const std::string &filename,
                                          const CubeTexture &cube_texture,
                                          bool with_mipmaps) {
  // ktxTexture1 *texture;
  ktxTexture2 *texture;
  ktxTextureCreateInfo createInfo;
  KTX_error_code result;

  unsigned int size = cube_texture.get_size();

  unsigned int mip_levels = with_mipmaps ? log2(size) + 1 : 1;

  std::cout << size << " / " << mip_levels << std::endl;

  // createInfo.glInternalformat = GL_RGBA16F;
  createInfo.vkFormat = 97; // VK_FORMAT_R16G16B16_SFLOAT;
  createInfo.baseWidth = size;
  createInfo.baseHeight = size;
  createInfo.baseDepth = 1;
  createInfo.numDimensions = 2;
  createInfo.numLevels = mip_levels;
  createInfo.numLayers = 1;
  createInfo.numFaces = 6;
  createInfo.isArray = KTX_FALSE;
  createInfo.generateMipmaps = KTX_FALSE;

  // result = ktxTexture1_Create(&createInfo, KTX_TEXTURE_CREATE_ALLOC_STORAGE,
  //                             &texture);
  result = ktxTexture2_Create(&createInfo, KTX_TEXTURE_CREATE_ALLOC_STORAGE,
                              &texture);

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("ktxTexture2_Create failed: ") +
                             ktxErrorString(result));
  }

  GL_CHECK_ERROR(glActiveTexture(GL_TEXTURE0));
  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId()));

  for (unsigned int i = 0; i < 6; i++) {
    for (unsigned int j = 0; j < mip_levels; j++) {
      unsigned int mip_map_size = (size / (unsigned int)(pow(2, j)));

      unsigned int data_size = 4 * mip_map_size * mip_map_size;

      GLhalf *data = (GLhalf *)calloc(data_size, sizeof(GLhalf));

      GL_CHECK_ERROR(glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j,
                                   GL_RGBA, GL_HALF_FLOAT, data));

      result = ktxTexture_SetImageFromMemory(
          ktxTexture(texture), j, 0, i,
          reinterpret_cast<const ktx_uint8_t *>(data), data_size);

      if (result != KTX_SUCCESS) {
        ktxTexture_Destroy(ktxTexture(texture));
        throw std::runtime_error(
            std::string("SetImageFromMemory failed at face=") +
            std::to_string(i) + " mip=" + std::to_string(j) + ": " +
            std::to_string(result) + ": " + ktxErrorString(result));
      }

      free(data);
    }
  }

  ktxBasisParams params = {0};
  params.structSize = sizeof(params);
  // params.uastc = KTX_TRUE;
  params.compressionLevel = KTX_ETC1S_DEFAULT_COMPRESSION_LEVEL;
  result = ktxTexture2_CompressBasis(texture, 0);

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("CompressBasisEx failed: ") +
                             ktxErrorString(result));
  }

  result = ktxTexture_WriteToNamedFile(ktxTexture(texture), filename.c_str());

  ktxTexture_Destroy(ktxTexture(texture));

  if (result != KTX_SUCCESS) {
    throw std::runtime_error(std::string("WriteToNamedFile failed: ") +
                             ktxErrorString(result));
  }
}

void KtxTextureFactory::ExportIbl(const std::string &irradiance_filename,
                                  const std::string &radiance_filename,
                                  const Ibl &ibl, const Texture &brdf) {
  ExportTexture("brdf.ktx2", brdf);
  ExportCubeTexture(irradiance_filename, *ibl.irradiance.get());
  ExportCubeTexture(radiance_filename, *ibl.radiance.get(), true);
}
} // namespace orangutan
