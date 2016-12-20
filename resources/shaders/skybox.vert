#version 450 core

in vec3 vertex_in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 uv_out;

void main()
{
    vec3 pos = mat3(modelMatrix)*vertex_in;
    vec4 pmp = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
    uv_out = pos;
    gl_Position = pmp.xyzw;
}

