#ifndef UTIL_H
#define UTIL_H

#define BUFFER_OFFSET(offset) ((void *)(offset))

enum { Color, DepthStencil, NumRenderBuffers };

enum menu_mode { OBJECT, NODE, CAMERA, LIGHT };

enum mode { PERSPECTIVE, ORTHO };

enum direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

enum shaderProgramType {
  GOURAUD,
  PHONG,
  ENVIRONMENTMAP,
  SKYBOX,
  TOON,
  EDGEFILTER,
  GAUSSIANBLURFILTER
};

#endif  // UTIL_H
