#define MAX_LIGHT 8

const float kPi = 3.14159265359;
const float kMaxRadianceLod = 9.0;

in vec3 world_position_out;
in vec2 uv_out;
#if defined(NORMAL_TEXTURE)
  in mat3 tbn_out;
#else
  in vec3 normal_out;
#endif
#if defined(OCCLUSION_TEXTURE)
  in vec2 uv_2_out;
#endif

struct Lighting {
  vec3 position;
  vec3 color;
  float intensity;
  float falloffRadius;
};

uniform Lighting lights[MAX_LIGHT];

uniform uint numberOfLights;

struct Ibl {
  samplerCube irradiance;
  samplerCube radiance;
};

uniform Ibl ibl;
uniform sampler2D brdf;

uniform vec3 cameraPosition;

uniform vec3 albedo;
#if defined(ALBEDO_TEXTURE)
  uniform sampler2D albedo_texture;
#endif

#if defined(NORMAL_TEXTURE)
  uniform sampler2D normal_texture;
#endif

uniform float roughness;
uniform float metalness;
#if defined(PBR_TEXTURE)
  uniform sampler2D pbr_texture;
#endif

#if defined(OCCLUSION_TEXTURE)
  uniform sampler2D occlusion_texture;
#endif

out vec4 color_out;

float GetSquareFalloffAttenuation(vec3 position_to_light, float light_inverse_radius) {
  float squared_distance = dot(position_to_light, position_to_light);
  float factor = squared_distance * light_inverse_radius * light_inverse_radius;
  float smooth_factor = max(1.0 - factor * factor, 0.0);
  return (smooth_factor * smooth_factor) / max(squared_distance, 1e-4);
}

vec3 FresnelSchlick(float cos_theta, vec3 f_0) {
  return f_0 + (1.0 - f_0) * pow(clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
}

vec3 FresnelSchlickRoughness(float cos_theta, vec3 f_0, float roughness) {
  return f_0 + (max(vec3(1.0 - roughness), f_0) - f_0) * pow(clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
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

float GeometrySchlickGGX(float n_dot_v, float roughness) {
  float r = (roughness + 1.0);
  float k = (r*r) / 8.0;

  float num   = n_dot_v;
  float denom = n_dot_v * (1.0 - k) + k;

  return num / denom;
}

float GeometrySmith(float n_dot_v, float n_dot_l, float roughness) {
  float ggx2  = GeometrySchlickGGX(n_dot_v, roughness);
  float ggx1  = GeometrySchlickGGX(n_dot_l, roughness);

  return ggx1 * ggx2;
}

vec3 GetConductorMultipleScattering(float n_dot_v, float roughness, vec3 color, vec3 irradiance, vec3 radiance) {
  vec3 f_0 = color;

  // Correction at low roughness for dielectrics, from Fdez-Aguera
  vec3 k_s = FresnelSchlickRoughness(n_dot_v, f_0, roughness);

  vec2 F_ab = textureLod(brdf, vec2(n_dot_v, roughness), 0).rg;
  vec3 FssEss = k_s * F_ab.x + F_ab.y;


  // Adding multiple scattering, from Fdez-Aguera
  float Ess = F_ab.x + F_ab.y;
  float Ems = 1.0 - Ess;
  vec3 Favg = f_0 + (1.0 - f_0) / 21.0;
  vec3 Fms = FssEss * Favg / (1.0 - (1.0 - Ess) * Favg);

  return FssEss * radiance + (Fms * Ems) * irradiance;
}

vec3 GetDielectricMultipleScattering(float n_dot_v, float roughness, vec3 color, vec3 irradiance, vec3 radiance) {
  vec3 f_0 = vec3(0.04);

  // Correction at low roughness for dielectrics, from Fdez-Aguera
  vec3 k_s = FresnelSchlickRoughness(n_dot_v, f_0, roughness);

  vec2 F_ab  = textureLod(brdf, vec2(n_dot_v, roughness), 0).rg;
  vec3 FssEss = k_s * F_ab.x + F_ab.y;


  // Adding multiple scattering, from Fdez-Aguera
  float Ess = F_ab.x + F_ab.y;
  float Ems = 1.0 - Ess;
  vec3 Favg = f_0 + (1.0 - f_0) / 21.0;
  vec3 Fms = FssEss * Favg / (1.0 - (1.0 - Ess) * Favg);

  vec3 Edss = 1.0 - (FssEss + Fms * Ems);
  vec3 k_d = color * Edss;

  return FssEss * radiance + (Fms * Ems + k_d) * irradiance;

}

void main() {
  #if defined(NORMAL_TEXTURE)
    vec3 normal = texture(normal_texture, uv_out).xyz;
    normal = normal*2.0 - 1.0;
    normal = normalize(tbn_out * normal);
  #else
    vec3 normal = normalize(normal_out);
  #endif

  vec3 view_vector = normalize(cameraPosition - world_position_out);

  float n_dot_v = max(dot(normal, view_vector), 0.0f);

  vec3 color = pow(albedo, vec3(2.2));

  #if defined(ALBEDO_TEXTURE)
    vec4 albedo_sample = texture(albedo_texture, uv_out);
    color *= pow(albedo_sample.rgb, vec3(2.2));
  #endif

  float metalness_factor = metalness;
  float roughness_factor = roughness;
  #if defined(PBR_TEXTURE)
    vec4 pbr_sample = texture(pbr_texture, uv_out);
    metalness_factor *= pbr_sample.b;
    roughness_factor *= pbr_sample.g;
  #endif

  vec4 irradiance_sample = texture(ibl.irradiance, normal);
  vec3 irradiance = texture(ibl.irradiance, normal).rgb;

  vec3 reflection_vector = reflect(-view_vector, normal);
  float lod_level = roughness_factor * kMaxRadianceLod;

  vec3 radiance = textureLod(ibl.radiance, reflection_vector, lod_level).rgb;

  vec3 ambient = mix(GetDielectricMultipleScattering(n_dot_v, roughness_factor, color, irradiance, radiance),
                     GetConductorMultipleScattering(n_dot_v, roughness_factor, color, irradiance, radiance),
                     metalness_factor);
  #if defined(OCCLUSION_TEXTURE)
    vec3 occlusion = texture(occlusion_texture, uv_2_out).rgb;
    ambient *= occlusion;
  #endif

  vec3 l_o = vec3(0.0);

  // Gives point light a minimum size
  float analytical_roughness = max(roughness_factor, 0.01f);

  vec3 f_0 = vec3(0.04);
  f_0 = mix(f_0, color, metalness_factor);

  for(int i = 0; i < numberOfLights; i++) {
    vec3 light_vector = normalize(lights[i].position - world_position_out);
    vec3 half_vector = normalize(view_vector + light_vector);

    float n_dot_l = max(dot(normal, light_vector), 0.0);
    float n_dot_h = max(dot(normal, half_vector), 0.0);
    float h_dot_v = max(dot(half_vector, view_vector), 0.0);

    float attenuation = GetSquareFalloffAttenuation(light_vector, 1.0/lights[i].falloffRadius);
    vec3 radiance = lights[i].color * lights[i].intensity * attenuation;

    vec3 fresnel_term = FresnelSchlick(h_dot_v, f_0);
    float distribution_term = DistributionGGX(n_dot_h, analytical_roughness);
    float geometry_term   = GeometrySmith(n_dot_v, n_dot_l, analytical_roughness);

    vec3 numerator    = distribution_term * geometry_term * fresnel_term;
    float denominator = 4.0 * n_dot_v * n_dot_l  + 0.0001;
    vec3 specular     = numerator / denominator;

    vec3 k_s = fresnel_term;
    vec3 k_d = 1.0f - k_s;

    k_d *= 1.0 - metalness_factor;

    l_o += (k_d * color / kPi + specular) * radiance * n_dot_l;
  }

  vec3 final_color = ambient + l_o;

  final_color = final_color / (final_color + vec3(1.0));
  final_color = pow(final_color, vec3(1.0/2.2));
  color_out = vec4(final_color, 1.0);
}
