#version 450 core

in vec3 uv_out;

uniform vec3 Ka;

uniform samplerCube cubeMap;

out vec4 color;

void main(void) {
  vec3 ray = uv_out;
  color = texture(cubeMap, ray)*vec4(Ka, 1.0);
}

