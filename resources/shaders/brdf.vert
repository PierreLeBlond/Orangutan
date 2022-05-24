#version 450 core

#define MAX_LIGHT 8

in vec3 vertex_in;

out vec2 uv_out;

void main() {
  uv_out = vertex_in.xy;

  gl_Position = vec4(uv_out, 0.0f, 1.0f);
}
