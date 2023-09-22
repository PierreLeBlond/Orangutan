#define MAX_LIGHT 8

in vec4 position_out;
in vec3 normal_out;
in vec2 uv_out;

struct Lighting {
    vec4 position;
    vec3 direction;
    vec3 Ld;
    vec3 Ls;
    vec3 La;
    float exponent;
    float cutoff;
};

uniform Lighting ponctualLights[MAX_LIGHT];
uniform Lighting ambiantLights[MAX_LIGHT];
uniform Lighting directionalLights[MAX_LIGHT];
uniform Lighting spotLights[MAX_LIGHT];

uniform int nbPonctualLight;
uniform int nbAmbiantLight;
uniform int nbDirectionLight;
uniform int nbSpotLight;

uniform float Ns;
uniform vec3 Ks;
uniform vec3 Kd;
uniform vec3 Ka;

uniform int levels;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform sampler2D colorMap;

uniform int nbDiffuseMap;

layout(location = 0) out vec4 color_out;

vec3 adPhong(Lighting light, vec3 s, vec3 normal)
{
    vec3 ambient = light.La*Ka;
    float sDotN = max(dot(s, normal), 0.0);
    vec3 diffuse = floor(sDotN * levels) * (1.0/levels) * Kd * light.Ld;
    return diffuse + ambient;
}

vec3 adPhongWithSpotLight(Lighting light, vec3 s, vec3 normal)
{
    float scal = dot(-s, light.direction);
    float angle = acos(scal);
    float cutoff = radians(clamp(light.cutoff, 0.0, 90.0));

    vec3 ambient = light.La*Ka;

    if(angle < cutoff) {
        float spotFactor = pow(scal, light.exponent);
        return ambient + spotFactor * light.Ld * Kd * floor(max(dot(s, normal), 0.0) * levels) * (1.0/levels);
    } else {
        return vec3(0.0);
    }
}

void main(void)
{
    vec3 diffuseAndAmbient_all = vec3(0.0);
    vec3 spec_all = vec3(0.0);

    for(int i = 0; i < nbPonctualLight;i++){
        vec3 s = normalize(vec3(ponctualLights[i].position - position_out));
       diffuseAndAmbient_all += adPhong(ponctualLights[i], s, normal_out);
    }

    for(int i = 0;i < nbAmbiantLight;i++){
        diffuseAndAmbient_all += ambiantLights[i].La*Ka;
    }

    for(int i = 0;i < nbDirectionLight;i++){
        vec3 s = normalize(directionalLights[i].direction);
       diffuseAndAmbient_all += adPhong(directionalLights[i], s, normal_out);
    }

    for(int i = 0;i < nbSpotLight;i++){
        vec3 s = normalize(vec3(spotLights[i].position - position_out));
        diffuseAndAmbient_all += adPhongWithSpotLight(spotLights[i], s, normal_out);
    }

    vec4 c = texture(colorMap, uv_out);

    color_out = vec4((diffuseAndAmbient_all + spec_all)*c.rgb, c.a);
}

