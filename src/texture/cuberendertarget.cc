#include "texture/cuberendertarget.h"

#include "nanogui/opengl.h"

namespace orangutan {

CubeRenderTarget::CubeRenderTarget(const std::string &name, int size,
                                   const CubeRenderTargetOptions &options)
    : CubeTexture(name) {
  set_size(size);

  glGenFramebuffers(1, &frame_buffer_object_);
  glGenRenderbuffers(1, &render_buffer_object_);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);
  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, get_size(),
                        get_size());
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer_object_);

  glBindTexture(GL_TEXTURE_CUBE_MAP, getId());
  for (unsigned int i = 0; i < 6; ++i) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB32F, get_size(),
                 get_size(), 0, GL_RGB, GL_FLOAT, nullptr);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                  options.min_filter);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (options.generate_mip_maps) {
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  }

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CubeRenderTarget::Draw() {
  glViewport(0, 0, get_size(), get_size());

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);

  for (unsigned int i = 0; i < 6; ++i) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, getId(), 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawing_signal_.Emit("", i);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CubeRenderTarget::DrawMip(unsigned int mip_level) {
  unsigned int mip_size = get_size() * std::pow(0.5, mip_level);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);

  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mip_size,
                        mip_size);

  glViewport(0, 0, mip_size, mip_size);

  for (unsigned int i = 0; i < 6; ++i) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, getId(),
                           mip_level);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawing_signal_.Emit("", i);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Signal<unsigned int> &CubeRenderTarget::get_drawing_signal() {
  return drawing_signal_;
}

}  // namespace orangutan
