#define MAX_LIGHT 8

in vec4 position_out;
in vec3 normal_out;
in vec3 ReflectDir_out;
in vec3 RefractDir_out;

uniform float reflexionRatio;

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

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform samplerCube cubeMap;

out vec4 color_out;

vec3 adPhong(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    vec3 ambient = light.La*Ka;
    float sDotN = max(dot(s, normal), 0.0);
    vec3 diffuse = sDotN*Kd*light.Ld;
    return diffuse + ambient;
}

vec3 adPhongWithSpotLight(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float scal = dot(-s, light.direction);
    float angle = acos(scal);
    float cutoff = radians(clamp(light.cutoff, 0.0, 90.0));

    vec3 ambient = light.La*Ka;

    if(angle < cutoff) {
        float spotFactor = pow(scal, light.exponent);
        return ambient + spotFactor * light.Ld * Kd * max(dot(s, normal), 0.0);
    } else {
        return vec3(0.0);
    }
}

vec3 sPhong(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float sDotN = max(dot(s, normal), 0.0);
    vec3 spec = vec3(0.0);
    if(sDotN > 0.0)
        spec = light.Ls*Ks*pow(max(dot(r, v), 0.0), Ns);
    return spec;
}

vec3 sPhongWithSpotLight(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float scal = dot(-s, light.direction);
    float angle = acos(scal);
    float cutoff = radians(clamp(light.cutoff, 0.0, 90.0));

    if(angle < cutoff) {
        float spotFactor = pow(scal, light.exponent);
        return spotFactor * light.Ls * Ks * pow(max(dot(r, normal), 0.0), Ns);
    } else {
        return vec3(0.0);
    }
}

void main(void)
{
    vec3 diffuseAndAmbient_all = vec3(0.0);
    vec3 spec_all = vec3(0.0);

    vec3 v = normalize(-position_out.xyz);

    for(int i = 0; i < nbPonctualLight;i++){
        vec3 s = normalize(vec3(ponctualLights[i].position - position_out));
        vec3 r = reflect(-s, normal_out);
       diffuseAndAmbient_all += adPhong(ponctualLights[i], s, v, r, normal_out);
       spec_all += sPhong(ponctualLights[i], s, v, r, normal_out);
    }

    for(int i = 0;i < nbAmbiantLight;i++){
        diffuseAndAmbient_all += ambiantLights[i].La*Ka;
    }

    for(int i = 0;i < nbDirectionLight;i++){
        vec3 s = normalize(directionalLights[i].direction);
        vec3 r = reflect(-s, normal_out);
       diffuseAndAmbient_all += adPhong(directionalLights[i], s, v, r, normal_out);
       spec_all += sPhong(directionalLights[i], s, v, r, normal_out);
    }

    for(int i = 0;i < nbSpotLight;i++){
        vec3 s = normalize(vec3(spotLights[i].position - position_out));
        vec3 r = reflect(-s, normal_out);
        diffuseAndAmbient_all += adPhongWithSpotLight(spotLights[i], s, v, r, normal_out);
        spec_all += sPhongWithSpotLight(spotLights[i], s, v, r, normal_out);
    }

    vec4 reflectColor = texture(cubeMap, ReflectDir_out);
    vec4 refractColor = texture(cubeMap, RefractDir_out);

    color_out = mix(vec4((diffuseAndAmbient_all + spec_all)*refractColor.rgb, refractColor.a),
                    vec4((diffuseAndAmbient_all + spec_all)*reflectColor.rgb, reflectColor.a),
                    reflexionRatio);
}


