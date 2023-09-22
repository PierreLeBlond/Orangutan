in vec3 uv_out;

struct Ibl {
  samplerCube irradiance;
  samplerCube radiance;
};

uniform Ibl ibl;

out vec4 color_out;

void main(void) {
  vec3 color = textureLod(ibl.radiance, uv_out, 1.0).rgb;

  color = color / (color + vec3(1.0));
  color = pow(color, vec3(1.0/2.2));

  color_out = vec4(color, 1.0f);
}

