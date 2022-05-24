#version 450 core

#define MAX_LIGHT 8

in vec3 vertex_in;
in vec3 normal_in;
in vec2 uv_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 world_position_out;
out vec3 normal_out;
out vec2 uv_out;

void main() {

  vec4 world_position = modelMatrix * vec4(vertex_in, 1.0f);

  vec4 projection_position = projectionMatrix * viewMatrix * world_position;
  vec4 world_normal = modelMatrix * vec4(normal_in, 0.0f);

  world_position_out = world_position.xyz;
  normal_out = world_normal.xyz;
  uv_out = uv_in;

  gl_Position = projection_position;
}
