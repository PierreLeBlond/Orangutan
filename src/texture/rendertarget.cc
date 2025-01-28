#include "texture/rendertarget.h"
#include "core/debug.h"

#include "nanogui/opengl.h"

namespace orangutan {

RenderTarget::RenderTarget(const std::string &name, int width, int height)
    : Texture(name) {
  set_width(width);
  set_height(height);

  unsigned int render_buffer_object;
  GL_CHECK_ERROR(glGenFramebuffers(1, &frame_buffer_object_));
  GL_CHECK_ERROR(glGenRenderbuffers(1, &render_buffer_object));

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_));
  GL_CHECK_ERROR(glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object));
  GL_CHECK_ERROR(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                                       get_width(), get_height()));
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer_object);

  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, getId()));
  for (unsigned int i = 0; i < 6; ++i) {
    GL_CHECK_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0,
                                GL_RGB, GL_HALF_FLOAT, nullptr));
  }
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CHECK_ERROR(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  GL_CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, 0));
  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void RenderTarget::Draw() {
  GL_CHECK_ERROR(glViewport(0, 0, get_width(), get_height()));

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_));

  GL_CHECK_ERROR(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                        GL_TEXTURE_2D, getId(), 0));
  GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  drawing_signal_.Emit("");

  GL_CHECK_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

Signal<> &RenderTarget::get_drawing_signal() { return drawing_signal_; }

} // namespace orangutan
