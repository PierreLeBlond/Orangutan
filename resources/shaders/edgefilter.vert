#version 330 core


in vec3 vertex_in;
in vec2 uv_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv_out;

void main()
{
    uv_out = uv_in;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
}

