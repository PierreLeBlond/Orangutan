#version 450 core

in vec2 uv_out;

uniform sampler2D renderTex;

uniform int PixOffset[5] = int[](0, 1, 2, 3, 4);
uniform float Weight[5];

out vec4 color_out;

void main(void)
{
    ivec2 pix = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(renderTex, pix, 0) * Weight[0];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(1,0) ) * Weight[1];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(-1,0) ) * Weight[1];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(2,0) ) * Weight[2];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(-2,0) ) * Weight[2];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(3,0) ) * Weight[3];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(-3,0) ) * Weight[3];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(4,0) ) * Weight[4];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(-4,0) ) * Weight[4];
    color_out = sum;
}
