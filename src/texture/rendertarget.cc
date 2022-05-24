#include "texture/rendertarget.h"

#include "nanogui/opengl.h"

namespace orangutan {

RenderTarget::RenderTarget(const std::string &name, int width, int height)
    : Texture(name) {
  set_width(width);
  set_height(height);

  unsigned int render_buffer_object;
  glGenFramebuffers(1, &frame_buffer_object_);
  glGenRenderbuffers(1, &render_buffer_object);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);
  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, get_width(),
                        get_height());
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer_object);

  glBindTexture(GL_TEXTURE_2D, getId());
  for (unsigned int i = 0; i < 6; ++i) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB,
                 GL_FLOAT, nullptr);
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::Draw() {
  glViewport(0, 0, get_width(), get_height());

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         getId(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawing_signal_.Emit("");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Signal<> &RenderTarget::get_drawing_signal() { return drawing_signal_; }

}  // namespace orangutan
