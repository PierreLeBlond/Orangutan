const float kPi = 3.14159265359;

in vec3 world_position_out;

uniform samplerCube environment_map;
uniform float roughness;
uniform uint size;

out vec4 color_out;

float RadicalInverseVanDerCorput(uint bits) {
  bits = (bits << 16u) | (bits >> 16u);
  bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
  bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
  bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
  bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
  return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint sample_id, uint sample_count) {
  return vec2(float(sample_id)/float(sample_count), RadicalInverseVanDerCorput(sample_id));
}

vec3 ImportanceSampleGGX(vec2 hammersley_sample, vec3 normal, float roughness) {
  float a = roughness*roughness;

  float phi = 2.0 * kPi * hammersley_sample.x;
  float cos_theta = sqrt((1.0 - hammersley_sample.y) / (1.0 + (a*a - 1.0) * hammersley_sample.y));
  float sin_theta = sqrt(1.0 - cos_theta*cos_theta);

  // from spherical coordinates to cartesian coordinates
  vec3 sample_tangent;
  sample_tangent.x = cos(phi) * sin_theta;
  sample_tangent.y = sin(phi) * sin_theta;
  sample_tangent.z = cos_theta;

  // from tangent-space vector to world-space sample vector
  vec3 up        = abs(normal.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tangent   = normalize(cross(up, normal));
  vec3 bitangent = cross(normal, tangent);

  vec3 sample_world = tangent * sample_tangent.x + bitangent * sample_tangent.y + normal * sample_tangent.z;
  return normalize(sample_world);
}

float DistributionGGX(float n_dot_h, float roughness) {
  float a      = roughness*roughness;
  float a2     = a*a;
  float NdotH2 = n_dot_h*n_dot_h;

  float num   = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = kPi * denom * denom;

  return num / denom;
}

void main() {
  vec3 normal = normalize(world_position_out);
  vec3 view_vector = normal;

  const uint sample_count = 4096u;

  vec3 prefiltered_color = vec3(0.0);
  float total_weigth = 0.0;

  for(uint i = 0u; i < sample_count; i++) {
    vec2 hammersley_sample = Hammersley(i, sample_count);
    vec3 importance_sample = ImportanceSampleGGX(hammersley_sample, normal, roughness);
    vec3 light_vector = normalize(2.0*dot(view_vector, importance_sample)*importance_sample - view_vector); // Reflection formula
    vec3 half_vector = normalize(view_vector + light_vector);

    float n_dot_l = max(dot(normal, light_vector), 0.0);
    float n_dot_h = max(dot(normal, half_vector), 0.0);
    float h_dot_v = max(dot(half_vector, view_vector), 0.0);

    if (n_dot_l > 0.0) {

      float distribution_term = DistributionGGX(n_dot_h, roughness);
      float pdf = (distribution_term * n_dot_h / (4.0 * h_dot_v)) + 0.0001;

      float sa_texel  = 4.0 * kPi / (6.0 * float(size) * float(size));
      float sa_sample = 1.0 / (float(sample_count) * pdf + 0.00001);

      float mip_level = roughness == 0.0 ? 0.0 : 0.5 * log2(sa_sample / sa_texel);

      prefiltered_color += textureLod(environment_map, light_vector, mip_level).rgb * n_dot_l;
      total_weigth += n_dot_l;
    }
  }

  prefiltered_color /= max(total_weigth, 0.001);

  color_out = vec4(prefiltered_color, 1.0);
}
