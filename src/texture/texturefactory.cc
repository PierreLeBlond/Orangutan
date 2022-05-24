#include "texture/texturefactory.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <gli/gli.hpp>
#include <iostream>
#include <memory>

#include "core/shader/shaderwrapper.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "material/shaderstrategy.h"
#include "mesh/mesh.h"
#include "mesh/meshfactory.h"
#include "nanogui/opengl.h"
#include "object/renderableobject.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "texture/cuberendertarget.h"
#include "texture/rendertarget.h"

#define MAKEFOURCC(_a, _b, _c, _d)                              \
  (((uint32_t)(uint8_t)(_a)) | ((uint32_t)(uint8_t)(_b) << 8) | \
   ((uint32_t)(uint8_t)(_c) << 16) | ((uint32_t)(uint8_t)(_d) << 24))

#define DDS_MAGIC 0x20534444
#define DDS_SIZE 124
#define DDSD_CAPS 0x1
#define DDSD_WIDTH 0x2
#define DDSD_HEIGHT 0x4
#define DDSD_PITCH 0x8
#define DDSD_PIXELFORMAT 0x1000
#define DDSD_MIPMAPCOUNT 0x20000
#define DDPF_ALPHAPIXELS 0x1
#define DDPF_FOURCC 0x4
#define DDPF_RGB 0x40
#define DDSCAPS_COMPLEX 0x8
#define DDSCAPS_MIPMAP 0x400000
#define DDSCAPS_TEXTURE 0x1000
#define DDSCAPS2_CUBEMAP 0x200
#define DDSCAPS2_CUBEMAP_POSITIVEX 0x400
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0x800
#define DDSCAPS2_CUBEMAP_POSITIVEY 0x1000
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x2000
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x4000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x8000
#define DXGI_FORMAT_R32G32B32_FLOAT 6
#define DDS_DIMENSION_TEXTURE2D 3
#define DDS_RESOURCE_MISC_TEXTURECUBE 0x4
#define DDS_ALPHA_MODE_UNKNOWN 0x0

namespace orangutan {

const unsigned int kIrradianceSize = 128;
const unsigned int kRadianceSize = 512;
const unsigned int kBrdfSize = 256;
const unsigned int kRadianceMipMapCount = 10;

const glm::mat4 kProjectionMatrix =
    glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
const glm::mat4 kViewMatrices[] = {
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, -1.0f, 0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, -1.0f, 0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, -1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                glm::vec3(0.0f, -1.0f, 0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                glm::vec3(0.0f, -1.0f, 0.0f))};

std::unique_ptr<Texture> TextureFactory::ImportTexture(
    const std::string& name, const std::string& filename) {
  auto texture = std::make_unique<Texture>(name);

  unsigned int id = texture->getId();

  glBindTexture(GL_TEXTURE_2D, id);
  texture->setPath(filename);

  stbi_set_flip_vertically_on_load(true);

  int width = 0;
  int height = 0;
  int channels = 0;
  unsigned char* data =
      stbi_load(texture->getPath().c_str(), &width, &height, &channels, 0);

  if (data == nullptr) {
    std::cerr << "TextureFactory::ImportTexture : stbi_load error."
              << std::endl;
  }

  texture->set_width(width);
  texture->set_height(height);

  auto format = channels == 3 ? GL_RGB : GL_RGBA;

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);

  return texture;
}

void TextureFactory::ExportTexture(const std::string& filename,
                                   const Texture& texture) {
  stbi_flip_vertically_on_write(true);
  GLubyte data[texture.get_width() * texture.get_height() * 3];

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.getId());

  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, &data);
  stbi_write_png(filename.c_str(), texture.get_width(), texture.get_height(), 3,
                 &data, 3 * texture.get_width());
}

std::unique_ptr<CubeTexture> TextureFactory::ImportCubeTexture(
    const std::string& name, const std::string& filename) {
  auto cube_texture = std::make_unique<CubeTexture>(name);

  std::string suffixes[] = {"posx", "negx", "posy", "negy", "negz", "posz"};
  std::string baseFileName = filename;
  std::string extension = ".png";

  cube_texture->setPath(baseFileName + suffixes[0] + extension);

  unsigned int id = cube_texture->getId();

  glBindTexture(GL_TEXTURE_CUBE_MAP, id);

  GLuint targets[] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
  };

  stbi_set_flip_vertically_on_load(true);

  int width = 0;
  int height = 0;
  int channels = 0;

  for (int i = 0; i < 6; i++) {
    std::string texName = baseFileName + suffixes[i] + extension;

    unsigned char* data =
        stbi_load(texName.c_str(), &width, &height, &channels, 0);

    if (data == nullptr) {
      std::cerr << "TextureFactory::ImportCubeTexture : stbi_load error."
                << std::endl;
    }

    glTexImage2D(targets[i], 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }

  cube_texture->set_size(width);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  return cube_texture;
}

void TextureFactory::ExportCubeTexture(const std::string& filename,
                                       const CubeTexture& cube_texture,
                                       unsigned int face_size,
                                       unsigned int mip_levels) {
  // From https://github.com/dariomanesku/cmft/blob/master/src/cmft/image.cpp
  FILE* fp = fopen(filename.c_str(), "wb");
  if (fp == nullptr) {
    std::cerr << "Could not open file " << filename << std::endl;
    exit(0);
  }

  const unsigned int bits_per_pixel = 96;

  const uint32_t magic = DDS_MAGIC;
  fwrite(&magic, 1, 4, fp);

  const uint32_t size = DDS_SIZE;
  fwrite(&size, 1, 4, fp);

  const uint32_t flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH |
                         DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT | DDSD_PITCH;
  fwrite(&flags, 1, 4, fp);

  const uint32_t width = face_size;
  fwrite(&width, 1, 4, fp);

  const uint32_t height = face_size;
  fwrite(&height, 1, 4, fp);

  const uint32_t pitch_or_linear_size = (face_size * bits_per_pixel + 7) / 8;
  fwrite(&pitch_or_linear_size, 1, 4, fp);

  const uint32_t depth = 0;
  fwrite(&depth, 1, 4, fp);

  const uint32_t mip_map_count = mip_levels;
  fwrite(&mip_map_count, 1, 4, fp);

  const uint32_t reserved_1[11]{0};
  fwrite(&reserved_1, 1, 44, fp);

  const uint32_t pixel_format_size = bits_per_pixel;
  fwrite(&pixel_format_size, 1, 4, fp);

  const uint32_t pixel_format_flags = DDPF_FOURCC;
  fwrite(&pixel_format_flags, 1, 4, fp);

  const uint32_t pixel_format_four_cc = MAKEFOURCC('D', 'X', '1', '0');
  fwrite(&pixel_format_four_cc, 1, 4, fp);

  const uint32_t pixel_format_rgb_bit_count = bits_per_pixel;
  fwrite(&pixel_format_rgb_bit_count, 1, 4, fp);

  const uint32_t pixel_format_r_bit_mask = 0xff0000;
  fwrite(&pixel_format_r_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_g_bit_mask = 0x00ff00;
  fwrite(&pixel_format_g_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_b_bit_mask = 0x0000ff;
  fwrite(&pixel_format_b_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_a_bit_mask = 0x0;
  fwrite(&pixel_format_a_bit_mask, 1, 4, fp);

  const uint32_t caps = DDSCAPS_COMPLEX | DDSCAPS_MIPMAP | DDSCAPS_TEXTURE;
  fwrite(&caps, 1, 4, fp);

  const uint32_t caps_2 =
      DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX |
      DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY |
      DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ |
      DDSCAPS2_CUBEMAP_NEGATIVEZ;
  fwrite(&caps_2, 1, 4, fp);

  const uint32_t caps_3 = 0;
  fwrite(&caps_3, 1, 4, fp);

  const uint32_t caps_4 = 0;
  fwrite(&caps_4, 1, 4, fp);

  const uint32_t reserved_2 = 0;
  fwrite(&reserved_2, 1, 4, fp);

  const uint32_t dxt_10_dxgi_format = DXGI_FORMAT_R32G32B32_FLOAT;
  fwrite(&dxt_10_dxgi_format, 1, 4, fp);

  const uint32_t dxt_10_resource_dimension = DDS_DIMENSION_TEXTURE2D;
  fwrite(&dxt_10_resource_dimension, 1, 4, fp);

  const uint32_t dxt_10_misc_flag = DDS_RESOURCE_MISC_TEXTURECUBE;
  fwrite(&dxt_10_misc_flag, 1, 4, fp);

  const uint32_t dxt_10_array_size = 1;
  fwrite(&dxt_10_array_size, 1, 4, fp);

  const uint32_t dxt_10_misc_flag_2 = DDS_ALPHA_MODE_UNKNOWN;
  fwrite(&dxt_10_misc_flag_2, 1, 4, fp);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId());

  for (unsigned int i = 0; i < 6; i++) {
    for (unsigned int j = 0; j < mip_levels; j++) {
      unsigned int mip_map_size = (face_size / (unsigned int)(pow(2, j)));

      unsigned int data_size = 3 * mip_map_size * mip_map_size;

      GLfloat* data = (GLfloat*)calloc(data_size, sizeof(GLfloat));

      // for (unsigned int k = 0; k < data_size / 3; k++) {
      // data[3 * k] = static_cast<GLfloat>(i < 3 ? 25.7 : 0.0);
      // data[3 * k + 1] = static_cast<GLfloat>(i % 2 == 0 ? 56.8 : 0.0);
      // data[3 * k + 2] = static_cast<GLfloat>(i % 3 == 0 ? 87.3 : 0.0);
      // }

      glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, GL_RGB, GL_FLOAT,
                    data);

      fwrite(data, sizeof(GLfloat), data_size, fp);

      free(data);
    }
  }

  fclose(fp);
}

void TextureFactory::ExportRgbdCubeTexture(const std::string& filename,
                                           const CubeTexture& cube_texture,
                                           unsigned int face_size,
                                           unsigned int mip_levels) {
  // From https://github.com/dariomanesku/cmft/blob/master/src/cmft/image.cpp
  FILE* fp = fopen(filename.c_str(), "wb");
  if (fp == nullptr) {
    std::cerr << "Could not open file " << filename << std::endl;
    exit(0);
  }

  const unsigned int bits_per_pixel = 32;

  const uint32_t magic = DDS_MAGIC;
  fwrite(&magic, 1, 4, fp);

  const uint32_t size = DDS_SIZE;
  fwrite(&size, 1, 4, fp);

  const uint32_t flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH |
                         DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT | DDSD_PITCH;
  fwrite(&flags, 1, 4, fp);

  const uint32_t width = face_size;
  fwrite(&width, 1, 4, fp);

  const uint32_t height = face_size;
  fwrite(&height, 1, 4, fp);

  const uint32_t pitch_or_linear_size = (face_size * bits_per_pixel + 7) / 8;
  fwrite(&pitch_or_linear_size, 1, 4, fp);

  const uint32_t depth = 0;
  fwrite(&depth, 1, 4, fp);

  const uint32_t mip_map_count = mip_levels;
  fwrite(&mip_map_count, 1, 4, fp);

  const uint32_t reserved_1[11]{0};
  fwrite(&reserved_1, 1, 44, fp);

  const uint32_t pixel_format_size = 32;
  fwrite(&pixel_format_size, 1, 4, fp);

  const uint32_t pixel_format_flags = DDPF_ALPHAPIXELS | DDPF_RGB;
  fwrite(&pixel_format_flags, 1, 4, fp);

  const uint32_t pixel_format_four_cc = 0;
  fwrite(&pixel_format_four_cc, 1, 4, fp);

  const uint32_t pixel_format_rgb_bit_count = bits_per_pixel;
  fwrite(&pixel_format_rgb_bit_count, 1, 4, fp);

  const uint32_t pixel_format_r_bit_mask = 0xff0000;
  fwrite(&pixel_format_r_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_g_bit_mask = 0xff00;
  fwrite(&pixel_format_g_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_b_bit_mask = 0xff;
  fwrite(&pixel_format_b_bit_mask, 1, 4, fp);

  const uint32_t pixel_format_a_bit_mask = 0xff000000;
  fwrite(&pixel_format_a_bit_mask, 1, 4, fp);

  const uint32_t caps = DDSCAPS_COMPLEX | DDSCAPS_MIPMAP | DDSCAPS_TEXTURE;
  fwrite(&caps, 1, 4, fp);

  const uint32_t caps_2 =
      DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX |
      DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY |
      DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ |
      DDSCAPS2_CUBEMAP_NEGATIVEZ;
  fwrite(&caps_2, 1, 4, fp);

  const uint32_t caps_3 = 0;
  fwrite(&caps_3, 1, 4, fp);

  const uint32_t caps_4 = 0;
  fwrite(&caps_4, 1, 4, fp);

  const uint32_t reserved_2 = 0;
  fwrite(&reserved_2, 1, 4, fp);

  // const uint32_t dxt_10_dxgi_format = DXGI_FORMAT_R32G32B32_FLOAT;
  // fwrite(&dxt_10_dxgi_format, 1, 4, fp);

  // const uint32_t dxt_10_resource_dimension = DDS_DIMENSION_TEXTURE2D;
  // fwrite(&dxt_10_resource_dimension, 1, 4, fp);

  // const uint32_t dxt_10_misc_flag = DDS_RESOURCE_MISC_TEXTURECUBE;
  // fwrite(&dxt_10_misc_flag, 1, 4, fp);

  // const uint32_t dxt_10_array_size = 1;
  // fwrite(&dxt_10_array_size, 1, 4, fp);

  // const uint32_t dxt_10_misc_flag_2 = DDS_ALPHA_MODE_UNKNOWN;
  // fwrite(&dxt_10_misc_flag_2, 1, 4, fp);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId());

  for (unsigned int i = 0; i < 6; i++) {
    for (unsigned int j = 0; j < mip_levels; j++) {
      unsigned int mip_map_size = (face_size / (unsigned int)(pow(2, j)));

      unsigned int data_size = 3 * mip_map_size * mip_map_size;

      GLfloat* data = (GLfloat*)calloc(data_size, sizeof(GLfloat));

      glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, GL_RGB, GL_FLOAT,
                    data);

      unsigned int rgbd_data_size = 4 * mip_map_size * mip_map_size;
      GLubyte* rgbd_data = (GLubyte*)calloc(rgbd_data_size, sizeof(GLubyte));

      for (unsigned int k = 0; k < rgbd_data_size / 4; k++) {
        const float red = data[3 * k];
        const float green = data[3 * k + 1];
        const float blue = data[3 * k + 2];
        const float highest_component = fmax(red, fmax(green, blue));
        float divider = fmax(255.0 / highest_component, 1.0);
        divider = fmax(fmin(floor(divider) / 255.0, 1.0), 0.0);

        rgbd_data[4 * k] = static_cast<GLubyte>(red * divider * 255.0);
        rgbd_data[4 * k + 1] = static_cast<GLubyte>(green * divider * 255.0);
        rgbd_data[4 * k + 2] = static_cast<GLubyte>(blue * divider * 255.0);
        rgbd_data[4 * k + 3] = static_cast<GLubyte>(divider * 255.0);
      }

      fwrite(rgbd_data, sizeof(GLubyte), rgbd_data_size, fp);

      free(data);
    }
  }

  fclose(fp);
}

void TextureFactory::ExportIrradiance(const std::string& filename,
                                      const CubeTexture& irradiance,
                                      bool convert_to_rgbd) {
  if (convert_to_rgbd) {
    ExportRgbdCubeTexture(filename, irradiance, kIrradianceSize, 1);
  } else {
    ExportCubeTexture(filename, irradiance, kIrradianceSize, 1);
  }
}

void TextureFactory::ExportRadiance(const std::string& filename,
                                    const CubeTexture& radiance,
                                    bool convert_to_rgbd) {
  if (convert_to_rgbd) {
    ExportRgbdCubeTexture(filename, radiance, kRadianceSize,
                          kRadianceMipMapCount);
  } else {
    ExportCubeTexture(filename, radiance, kRadianceSize, kRadianceMipMapCount);
  }
}

unsigned int TextureFactory::ImportEquirectangularHDR(
    const std::string& filename) {
  stbi_set_flip_vertically_on_load(true);
  int width = 0;
  int height = 0;
  int number_of_components = 0;
  float* data =
      stbi_loadf(filename.c_str(), &width, &height, &number_of_components, 0);
  if (!data) {
    std::cerr << "Failed to load HDR image." << std::endl;
  }
  unsigned int hdr_texture_handle;
  glGenTextures(1, &hdr_texture_handle);
  glBindTexture(GL_TEXTURE_2D, hdr_texture_handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT,
               data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_image_free(data);

  return hdr_texture_handle;
}

std::unique_ptr<CubeTexture> TextureFactory::TransformEquirectangularToCube(
    const std::string& name, unsigned int equirectangular_handle) {
  CubeRenderTargetOptions options = {};
  options.min_filter = GL_LINEAR_MIPMAP_LINEAR;
  CubeRenderTarget cube_render_target(name, kRadianceSize, options);

  // shader wrapper
  auto shader_wrapper = std::make_unique<ShaderWrapper>(
      "equirectangular_to_cubemap_shader_wrapper");

  shader_wrapper->build("../resources/shaders/equirectangular_to_cubemap.vert",
                        "../resources/shaders/equirectangular_to_cubemap.frag",
                        "");

  // shader strategy
  auto shader_strategy = std::make_unique<ShaderStrategy>(
      "equirectangular_to_cubemap_shader_strategy");

  shader_strategy->set_shader_wrapper(shader_wrapper.get());
  shader_strategy->InitAttribute();

  // mesh
  auto mesh =
      orangutan::MeshFactory::CreateCube("equirectangular_to_cubemap_mesh");

  // renderable object
  RenderableObject renderable_object(
      "equirectangular_to_cubemap_renderable_object");
  renderable_object.set_shader_strategy(shader_strategy.get());
  renderable_object.set_mesh(mesh.get());
  renderable_object.UpdateVertexArrayObject();

  shader_wrapper->start();

  shader_wrapper->setUniform("equirectangular_map", 0);
  shader_wrapper->setUniform("projection_matrix", kProjectionMatrix);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, equirectangular_handle);

  renderable_object.get_vao().bind();
  renderable_object.get_vao().bindIndexBuffer();

  cube_render_target.get_drawing_signal().Connect([&](unsigned int i) {
    shader_wrapper->setUniform("view_matrix", kViewMatrices[i]);
    renderable_object.get_vao().drawElements();
  });

  cube_render_target.Draw();

  shader_wrapper->stop();

  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_render_target.getId());
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  return std::make_unique<CubeTexture>(std::move(cube_render_target));
}

std::unique_ptr<CubeTexture> TextureFactory::CreateIrradianceMap(
    const CubeTexture& cube_texture) {
  CubeRenderTarget cube_render_target(cube_texture.getName() + "_irradiance",
                                      kIrradianceSize);

  // shader wrapper
  auto shader_wrapper =
      std::make_unique<ShaderWrapper>("irradiance_shader_wrapper");

  shader_wrapper->build("../resources/shaders/irradiance.vert",
                        "../resources/shaders/irradiance.frag", "");

  // shader strategy
  auto shader_strategy =
      std::make_unique<ShaderStrategy>("irradiance_shader_strategy");

  shader_strategy->set_shader_wrapper(shader_wrapper.get());
  shader_strategy->InitAttribute();

  // mesh
  auto mesh = orangutan::MeshFactory::CreateCube("irradiance_mesh");

  // renderable object
  RenderableObject renderable_object("irradiance_renderable_object");
  renderable_object.set_shader_strategy(shader_strategy.get());
  renderable_object.set_mesh(mesh.get());
  renderable_object.UpdateVertexArrayObject();

  shader_wrapper->start();

  shader_wrapper->setUniform("environment_map", 0);
  shader_wrapper->setUniform("projection_matrix", kProjectionMatrix);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId());

  renderable_object.get_vao().bind();
  renderable_object.get_vao().bindIndexBuffer();

  cube_render_target.get_drawing_signal().Connect([&](unsigned int i) {
    shader_wrapper->setUniform("view_matrix", kViewMatrices[i]);
    renderable_object.get_vao().drawElements();
  });

  cube_render_target.Draw();

  shader_wrapper->stop();
  return std::make_unique<CubeTexture>(std::move(cube_render_target));
}

std::unique_ptr<CubeTexture> TextureFactory::CreateRadianceMap(
    const CubeTexture& cube_texture) {
  CubeRenderTargetOptions options = {};
  options.min_filter = GL_LINEAR_MIPMAP_LINEAR;
  options.generate_mip_maps = true;

  CubeRenderTarget cube_render_target(cube_texture.getName() + "_radiance",
                                      kRadianceSize, options);

  // shader wrapper
  auto shader_wrapper =
      std::make_unique<ShaderWrapper>("radiance_shader_wrapper");

  shader_wrapper->build("../resources/shaders/radiance.vert",
                        "../resources/shaders/radiance.frag", "");

  // shader strategy
  auto shader_strategy =
      std::make_unique<ShaderStrategy>("radiance_shader_strategy");

  shader_strategy->set_shader_wrapper(shader_wrapper.get());
  shader_strategy->InitAttribute();

  // mesh
  auto mesh = orangutan::MeshFactory::CreateCube("radiance_mesh");

  // renderable object
  RenderableObject renderable_object("radiance_renderable_object");
  renderable_object.set_shader_strategy(shader_strategy.get());
  renderable_object.set_mesh(mesh.get());
  renderable_object.UpdateVertexArrayObject();

  shader_wrapper->start();

  shader_wrapper->setUniform("size", cube_texture.get_size());
  shader_wrapper->setUniform("environment_map", 0);
  shader_wrapper->setUniform("projection_matrix", kProjectionMatrix);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture.getId());

  renderable_object.get_vao().bind();
  renderable_object.get_vao().bindIndexBuffer();

  cube_render_target.get_drawing_signal().Connect([&](unsigned int i) {
    shader_wrapper->setUniform("view_matrix", kViewMatrices[i]);
    renderable_object.get_vao().drawElements();
  });

  for (unsigned int i = 0; i < kRadianceMipMapCount; i++) {
    float roughness = (float)i / (float)(kRadianceMipMapCount - 1);
    shader_wrapper->setUniform("roughness", roughness);
    cube_render_target.DrawMip(i);
  }

  shader_wrapper->stop();
  return std::make_unique<CubeTexture>(std::move(cube_render_target));
}

std::unique_ptr<Texture> TextureFactory::CreateBrdfMap() {
  RenderTarget render_target("brdf", kBrdfSize, kBrdfSize);

  // shader wrapper
  auto shader_wrapper = std::make_unique<ShaderWrapper>("brdf_shader_wrapper");

  shader_wrapper->build("../resources/shaders/brdf.vert",
                        "../resources/shaders/brdf.frag", "");

  // shader strategy
  auto shader_strategy =
      std::make_unique<ShaderStrategy>("brdf_shader_strategy");

  shader_strategy->set_shader_wrapper(shader_wrapper.get());
  shader_strategy->InitAttribute();

  // mesh
  auto mesh = orangutan::MeshFactory::CreateSquare("brdf_mesh");

  // renderable object
  RenderableObject renderable_object("brdf_renderable_object");
  renderable_object.set_shader_strategy(shader_strategy.get());
  renderable_object.set_mesh(mesh.get());
  renderable_object.UpdateVertexArrayObject();

  shader_wrapper->start();

  renderable_object.get_vao().bind();
  renderable_object.get_vao().bindIndexBuffer();

  render_target.get_drawing_signal().Connect(
      [&]() { renderable_object.get_vao().drawElements(); });

  render_target.Draw();

  shader_wrapper->stop();
  return std::make_unique<Texture>(std::move(render_target));
}

std::unique_ptr<Ibl> TextureFactory::ImportIBLFromHdr(
    const std::string& name, const std::string& filename) {
  unsigned int hdr_texture_handle = ImportEquirectangularHDR(filename);
  auto cube_render_target =
      TransformEquirectangularToCube(name, hdr_texture_handle);
  auto irradiance = CreateIrradianceMap(*cube_render_target.get());
  auto radiance = CreateRadianceMap(*cube_render_target.get());
  return std::make_unique<Ibl>(
      Ibl({name, std::move(irradiance), std::move(radiance)}));
}

std::unique_ptr<CubeTexture> TextureFactory::ImportCubeTextureFromDds(
    const std::string& name, const std::string& filename) {
  // Extracted and adapted from
  // https://github.com/g-truc/gli/blob/master/manual.md#section2_2
  gli::texture gli_texture = gli::load(filename);
  if (gli_texture.empty()) {
    std::cerr << "dds file " << filename << " is empty." << std::endl;
    exit(0);
  }

  gli::gl GL(gli::gl::PROFILE_GL33);
  gli::gl::format const gli_format =
      GL.translate(gli_texture.format(), gli_texture.swizzles());
  GLenum target = GL.translate(gli_texture.target());

  assert(target == GL_TEXTURE_CUBE_MAP && gli_format.Internal == GL_RGB32F &&
         gli_format.External == GL_RGB && gli_format.Type == GL_FLOAT);

  const unsigned int size = gli_texture.extent().x;
  const unsigned int mip_levels = gli_texture.levels();

  GLuint texture_handle = 0;
  glGenTextures(1, &texture_handle);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_handle);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL,
                  static_cast<GLint>(mip_levels - 1));
  glTexStorage2D(GL_TEXTURE_CUBE_MAP, static_cast<GLint>(mip_levels), GL_RGB32F,
                 static_cast<GLsizei>(size), static_cast<GLsizei>(size));

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  for (unsigned int face = 0; face < 6; ++face) {
    for (unsigned int mip_level = 0; mip_level < mip_levels; ++mip_level) {
      unsigned int mip_map_size = (size / (unsigned int)(pow(2, mip_level)));

      unsigned int data_size = 3 * mip_map_size * mip_map_size;

      target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face);

      GLfloat* data = (GLfloat*)gli_texture.data<GLfloat>(0, face, mip_level);

      glTexSubImage2D(target, static_cast<GLint>(mip_level), 0, 0,
                      static_cast<GLsizei>(mip_map_size),
                      static_cast<GLsizei>(mip_map_size), GL_RGB, GL_FLOAT,
                      (GLfloat*)gli_texture.data<GLfloat>(0, face, mip_level));
    }
  }

  auto cube_texture = std::make_unique<CubeTexture>(name);
  cube_texture->getHandle().setId(texture_handle);
  cube_texture->set_size(size);

  return cube_texture;
}

std::unique_ptr<Ibl> TextureFactory::ImportIBLFromDds(
    const std::string& name, const std::string& irradiance_filename,
    const std::string& radiance_filename) {
  auto irradiance =
      ImportCubeTextureFromDds(name + "_irradiance", irradiance_filename);
  auto radiance =
      ImportCubeTextureFromDds(name + "_radiance", radiance_filename);

  return std::make_unique<Ibl>(
      Ibl({name, std::move(irradiance), std::move(radiance)}));
}

void TextureFactory::ExportIbl(const std::string& name,
                               const std::string& irradiance_filename,
                               const std::string& radiance_filename,
                               const Ibl& ibl, bool convert_to_rgbd) {
  ExportIrradiance(irradiance_filename, *ibl.irradiance.get(), convert_to_rgbd);
  ExportRadiance(radiance_filename, *ibl.radiance.get(), convert_to_rgbd);
}

}  // namespace orangutan
