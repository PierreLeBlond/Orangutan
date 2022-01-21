#include "core/texture/ddtexture.h"

#include <nanogui/opengl.h>
#include <util/image.h>

#include "core/debug.h"

//#include <SOIL.h>

#include <iostream>
#include <memory>

// using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;

DDTexture::DDTexture(const std::string &name) : Texture(name) {}

DDTexture::DDTexture(const std::string &path, const std::string &name)
    : Texture(path, name) {
  // glActiveTexture(GL_TEXTURE0 + 0);
  load(getPath());
}

bool DDTexture::load(const std::string &path) {
  unsigned int id = getId();

  glBindTexture(GL_TEXTURE_2D, id);
  setPath(path);

  int w = 0, h = 0;

  unsigned char *data = Image::loadPNG(getPath().c_str(), &w, &h);

  if (data == nullptr) {
    return false;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  delete[] data;

  return true;
  /*_id = SOIL_load_OGL_texture
    (
    path.c_str(),
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
    SOIL_FLAG_COMPRESS_TO_DXT
    );*/

  /*
     int force_channels = 0;
     int w = 0, h = 0, n;
  //handleType image(stbi_load(fileName.c_str(), &w, &h, &n, force_channels),
  stbi_image_free);
  //if (!textureData)
  //throw std::invalid_argument("Could not load texture data from file " +
  fileName);*/
}
