#version 330

in vec3 vertex_in;
in vec3 normal_in;
in vec2 uv_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv_out;
out vec4 position_out;
out vec3 normal_out;

void main()
{
    position_out = viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
    normal_out = normalize( mat3(viewMatrix * modelMatrix) * normal_in);
    uv_out = uv_in;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
}
