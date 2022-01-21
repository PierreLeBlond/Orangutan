#ifndef RENDERERABLE_H
#define RENDERERABLE_H

#include <functional>
#include <iostream>

class Rendererable {
 public:
  Rendererable();

  virtual void init() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;

  virtual void resize(int width, int height) = 0;

  void setDrawCall(std::function<void()> drawCall);

  virtual void createFrameBuffer(unsigned int *fboHandle,
                                 unsigned int *depthBuf,
                                 unsigned int *renderTex1,
                                 unsigned int *renderTex2, int width,
                                 int height) = 0;

 private:
  std::function<void()> _drawCall;
};

#endif  // RENDERERABLE_H
