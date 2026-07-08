#include "texture/basisutexturefactory.h"
#include "core/debug.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>

#include "basisu_comp.h"

namespace orangutan {

void BasisUTextureFactory::ExportTexture(const std::string &filename,
                                         const Texture &texture) {
  unsigned int width = texture.get_width();
  unsigned int height = texture.get_height();

  basisu::basis_compressor_params params;
  params.m_hdr = true;
  params.m_uastc_hdr_4x4_options.set_quality_level(3);
  params.m_debug = true;
  // params.m_debug_images = true;
  params.m_status_output = true;
  params.m_compute_stats = true;
  params.m_create_ktx2_file = true;
  params.m_write_output_basis_or_ktx2_files = true;
  params.m_out_filename = filename;
  params.m_perceptual = true;

  // ── Mip maps ──────────────────────────────────────────────────────────
  params.m_mip_gen = false;  // no mips
  params.m_mip_srgb = false; // linear HDR data

  params.m_tex_type = basist::cBASISTexType2D;

  GL_CHECK_ERROR(glActiveTexture(GL_TEXTURE0));
  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, texture.getId()));

  unsigned int data_size = 4 * width * height;

  GLhalf *data = (GLhalf *)calloc(data_size, sizeof(GLhalf));

  GL_CHECK_ERROR(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_HALF_FLOAT, data));

  basisu::imagef img;
  img.resize(width, height);

  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      const uint32_t index = (y * width + x) * 4;
      basisu::vec4F pixel(basist::half_to_float(data[index]),     // R
                          basist::half_to_float(data[index + 1]), // G
                          basist::half_to_float(data[index + 2]), // B
                          basist::half_to_float(data[index + 3])  // A
      );
      img(x, y) = pixel;
    }
  }

  params.m_source_images_hdr.push_back(img);

  free(data);

  const uint32_t NUM_THREADS = 1;
  basisu::job_pool jp(NUM_THREADS);
  params.m_pJob_pool = &jp;
  params.m_multithreading = false;

  // ── Run the compressor ─────────────────────────────────────────────────
  basisu::basis_compressor compressor;
  if (!compressor.init(params)) {
    throw std::runtime_error("basis_compressor::init() failed");
  }

  basisu::basis_compressor::error_code result = compressor.process();
  if (result != basisu::basis_compressor::cECSuccess) {
    throw std::runtime_error("basis_compressor::process() failed, code: " +
                             std::to_string(static_cast<int>(result)));
  }
}

void BasisUTextureFactory::ExportCubeTexture(const std::string &filename,
                                             const CubeTexture &cube_texture,
                                             bool with_mipmaps) {
  unsigned int size = cube_texture.get_size();
  unsigned int mip_levels = with_mipmaps ? log2(size) + 1 : 1;
  std::cout << size << " / " << mip_levels << std::endl;

  basisu::basis_compressor_params params;
  params.m_hdr = true;
  params.m_uastc_hdr_4x4_options.set_quality_level(3);
  params.m_debug = true;
  // params.m_debug_images = true;
  params.m_status_output = true;
  params.m_compute_stats = true;
  params.m_create_ktx2_file = true;
  params.m_write_output_basis_or_ktx2_files = true;
  params.m_out_filename = filename;
  params.m_perceptual = true;

  // ── Mip maps ──────────────────────────────────────────────────────────
  params.m_mip_gen = false;  // we supply our own prefiltered mips
  params.m_mip_srgb = false; // linear HDR data

  params.m_tex_type = basist::cBASISTexTypeCubemapArray;
  params.m_source_images_hdr.resize(6);
  params.m_source_mipmap_images_hdr.resize(6);

  GL_CHECK_ERROR(glActiveTexture(GL_TEXTURE0));
  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId()));

  for (unsigned int i = 0; i < 6; i++) {
    for (unsigned int j = 0; j < mip_levels; j++) {
      unsigned int mip_map_size = size >> j;
      unsigned int data_size = 4 * mip_map_size * mip_map_size;

      GLhalf *data = (GLhalf *)calloc(data_size, sizeof(GLhalf));

      GL_CHECK_ERROR(glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j,
                                   GL_RGBA, GL_HALF_FLOAT, data));

      basisu::imagef img;
      img.resize(mip_map_size, mip_map_size);

      for (uint32_t y = 0; y < mip_map_size; ++y) {
        for (uint32_t x = 0; x < mip_map_size; ++x) {
          const uint32_t index = (y * mip_map_size + x) * 4;
          basisu::vec4F pixel(basist::half_to_float(data[index]),     // R
                              basist::half_to_float(data[index + 1]), // G
                              basist::half_to_float(data[index + 2]), // B
                              basist::half_to_float(data[index + 3])  // A
          );
          img(x, y) = pixel;
        }
      }

      if (j == 0)
        params.m_source_images_hdr[i] = img;
      else
        params.m_source_mipmap_images_hdr[i].push_back(img);

      free(data);
    }
  }

  const uint32_t NUM_THREADS = 1;
  basisu::job_pool jp(NUM_THREADS);
  params.m_pJob_pool = &jp;
  params.m_multithreading = false;

  // ── Run the compressor ─────────────────────────────────────────────────
  basisu::basis_compressor compressor;
  if (!compressor.init(params)) {
    throw std::runtime_error("basis_compressor::init() failed");
  }

  basisu::basis_compressor::error_code result = compressor.process();
  if (result != basisu::basis_compressor::cECSuccess) {
    throw std::runtime_error("basis_compressor::process() failed, code: " +
                             std::to_string(static_cast<int>(result)));
  }
}

void BasisUTextureFactory::ExportIbl(const std::string &irradiance_filename,
                                     const std::string &radiance_filename,
                                     const Ibl &ibl, const Texture &brdf) {
  ExportTexture("./output/brdf_uastc.ktx2", brdf);
  ExportCubeTexture(irradiance_filename, *ibl.irradiance.get());
  ExportCubeTexture(radiance_filename, *ibl.radiance.get(), true);
}
} // namespace orangutan
