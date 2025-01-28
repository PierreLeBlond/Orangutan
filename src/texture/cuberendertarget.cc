#include "texture/cuberendertarget.h"
#include "core/debug.h"

#include "nanogui/opengl.h"

namespace orangutan {

CubeRenderTarget::CubeRenderTarget(const std::string &name, int size,
                                   const CubeRenderTargetOptions &options)
    : CubeTexture(name) {
  set_size(size);

  GL_CHECK_ERROR(glGenFramebuffers(1, &frame_buffer_object_));
  GL_CHECK_ERROR(glGenRenderbuffers(1, &render_buffer_object_));

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_));
  GL_CHECK_ERROR(glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object_));
  GL_CHECK_ERROR(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                                       get_size(), get_size()));
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer_object_);

  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, getId()));
  for (unsigned int i = 0; i < 6; ++i) {
    GL_CHECK_ERROR(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                                GL_RGB32F, get_size(), get_size(), 0, GL_RGB,
                                GL_FLOAT, nullptr));
  }
  GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
                                 GL_CLAMP_TO_EDGE));
  GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
                                 GL_CLAMP_TO_EDGE));
  GL_CHECK_ERROR(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
                                 GL_CLAMP_TO_EDGE));
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                  options.min_filter);
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  if (options.generate_mip_maps) {
    GL_CHECK_ERROR(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
  }

  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void CubeRenderTarget::Draw() {
  GL_CHECK_ERROR(glViewport(0, 0, get_size(), get_size()));

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_));

  for (unsigned int i = 0; i < 6; ++i) {
    GL_CHECK_ERROR(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                          getId(), 0));
    GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    drawing_signal_.Emit("", i);
  }

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void CubeRenderTarget::DrawMip(unsigned int mip_level) {
  unsigned int mip_size = get_size() * std::pow(0.5, mip_level);

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_));

  GL_CHECK_ERROR(glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object_));
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mip_size,
                        mip_size);

  GL_CHECK_ERROR(glViewport(0, 0, mip_size, mip_size));

  for (unsigned int i = 0; i < 6; ++i) {
    GL_CHECK_ERROR(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                          getId(), mip_level));
    GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    drawing_signal_.Emit("", i);
  }

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

Signal<unsigned int> &CubeRenderTarget::get_drawing_signal() {
  return drawing_signal_;
}

} // namespace orangutan
