#version 450 core

in vec3 vertex_in;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

out vec3 world_position_out;

void main() {
  world_position_out = vertex_in;

  vec4 projection_position = projection_matrix * view_matrix * vec4(vertex_in, 1.0f);
  gl_Position = projection_position;
}
