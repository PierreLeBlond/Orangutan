#version 450

in vec3 uv_out;

uniform samplerCube radiance;

out vec4 color_out;

void main() {
  vec4 texture_sample = textureLod(radiance, uv_out, 0.0);

  vec3 color = texture_sample.rgb / texture_sample.a;

  color = color / (color + vec3(1.0));
  color = pow(color, vec3(1.0/2.2));

  color_out = vec4(color, 1.0f);
}

