const float PI = 3.14159265359;

in vec3 world_position_out;

uniform samplerCube environment_map;

out vec4 color_out;

void main() {
  vec3 normal = normalize(world_position_out);

  vec3 irradiance = vec3(0.0);

  vec3 up = vec3(0.0, 1.0, 0.0);
  vec3 right = normalize(cross(up, normal));
  up = normalize(cross(normal, right));

  float sample_delta = 0.025;
  float number_of_samples = 0.0; 
  for(float phi = 0.0; phi < 2.0 * PI; phi += sample_delta) {
    for(float theta = 0.0; theta < 0.5 * PI; theta += sample_delta) {
      // spherical to cartesian (in tangent space)
      vec3 tangent = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
      vec3 tangent_world = tangent.x * right + tangent.y * up + tangent.z * normal;

      irradiance += texture(environment_map, tangent_world).rgb * cos(theta) * sin(theta);
      number_of_samples++;
    }
  }
  irradiance = PI * irradiance * (1.0 / float(number_of_samples));

  color_out = vec4(irradiance, 1.0);
}
