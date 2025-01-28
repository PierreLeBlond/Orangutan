#version 450

in vec3 uv_out;

uniform samplerCube radiance;

out vec4 color_out;

void main() {
  vec3 color = textureLod(radiance, uv_out, 1.0).rgb;

  /*color = color / (color + vec3(1.0));
  color = pow(color, vec3(1.0/2.2));*/

  color_out = vec4(color, 1.0f);
}

