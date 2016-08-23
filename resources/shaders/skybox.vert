#version 330

in vec3 vertex_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 uv_out;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
    uv_out = vertex_in;
}

