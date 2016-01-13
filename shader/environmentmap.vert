#version 330


in vec3 vertex_in;
in vec3 normal_in;
in vec2 uv_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform float refractionRatio;


out vec3 ReflectDir_out;
out vec3 RefractDir_out;
out vec4 position_out;
out vec3 normal_out;

void main()
{
    position_out = viewMatrix * modelMatrix * vec4(vertex_in, 1.0);

    normal_out = normalize( mat3(viewMatrix * modelMatrix) * normal_in);

    vec3 worldPos = vec3(modelMatrix * vec4(vertex_in, 1.0));
    vec3 worldNorm = vec3(modelMatrix * vec4(normal_in, 0.0));
    vec3 worldView = normalize(vec3(inverse(viewMatrix)[3]) - worldPos);

    ReflectDir_out = reflect(-worldView, worldNorm);
    RefractDir_out = refract(-worldView, worldNorm, 1/(refractionRatio/100.0));

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
}

