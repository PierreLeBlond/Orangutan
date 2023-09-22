in vec2 uv_out;

uniform sampler2D renderTex;

uniform int PixOffset[5] = int[](0, 1, 2, 3, 4);
uniform float Weight[5];

out vec4 color_out;

void main(void)
{
    ivec2 pix = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(renderTex, pix, 0) * Weight[0];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,1) ) * Weight[1];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,-1) ) * Weight[1];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,2) ) * Weight[2];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,-2) ) * Weight[2];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,3) ) * Weight[3];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,-3) ) * Weight[3];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,4) ) * Weight[4];
    sum += texelFetchOffset( renderTex, pix, 0, ivec2(0,-4) ) * Weight[4];
    color_out = sum;
}
