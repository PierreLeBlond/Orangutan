#define MAX_LIGHT 8

in vec3 vertex_in;
in vec3 normal_in;
in vec3 tangent_in;
in vec2 uv_in;
#if defined(OCCLUSION_TEXTURE)
  in vec2 uv_2_in;
#endif

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 world_position_out;
out vec2 uv_out;
#if defined(OCCLUSION_TEXTURE)
  out vec2 uv_2_out;
#endif
#if defined(NORMAL_TEXTURE)
  out mat3 tbn_out;
#else
  out vec3 normal_out;
#endif

void main() {

  vec4 world_position = modelMatrix * vec4(vertex_in, 1.0f);

  vec4 projection_position = projectionMatrix * viewMatrix * world_position;
  vec4 world_normal = modelMatrix * vec4(normal_in, 0.0f);

  world_position_out = world_position.xyz;
  uv_out = uv_in;
  #if defined(OCCLUSION_TEXTURE)
    uv_2_out = uv_2_in;
  #endif

  #if defined(NORMAL_TEXTURE)
    vec3 t = normalize(vec3(modelMatrix * vec4(tangent_in, 0.0)));
    vec3 n = normalize(vec3(modelMatrix * vec4(normal_in, 0.0)));
    // re-orthogonalize T with respect to N
    t = normalize(t - dot(t, n) * n);
    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 b = cross(n, t);

    tbn_out = mat3(t, b, n);
  #else
    normal_out = world_normal.xyz;
  #endif

  gl_Position = projection_position;
}
