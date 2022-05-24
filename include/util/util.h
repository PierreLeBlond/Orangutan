#ifndef ORANGUTAN_UTIL_UTIL_H
#define ORANGUTAN_UTIL_UTIL_H

#define BUFFER_OFFSET(offset) ((void *)(offset))

namespace orangutan {

enum { Color, DepthStencil, NumRenderBuffers };

enum shaderProgramType {
  GOURAUD,
  PHONG,
  ENVIRONMENTMAP,
  SKYBOX,
  TOON,
  EDGEFILTER,
  GAUSSIANBLURFILTER
};

}  // namespace orangutan

#endif  // ORANGUTAN_UTIL_UTIL_H
