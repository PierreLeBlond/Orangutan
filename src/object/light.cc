#include "object/light.h"

Light::Light(const std::string& name) :
    Object(name),
    _color(glm::vec4(255, 255, 255, 255)),
    _Ld(glm::vec3(0.75f, 0.75f, 0.75f)),
    _La(glm::vec3(0.75f, 0.75f, 0.75f)),
    _Ls(glm::vec3(1.0f, 1.0f, 1.0f)),
    _type(PONCTUAL), _cutoffAngle(30), _exponent(10), _state(true)
{
}

const glm::vec4& Light::getColor() const{
    return _color;
}

const glm::vec3& Light::getLd() const{
    return _Ld;
}

const glm::vec3& Light::getLa() const{
    return _La;
}

const glm::vec3& Light::getLs() const{
    return _Ls;
}

int Light::getType() const{
    return _type;
}

float Light::getCutoffAngle() const{
    return (float) _cutoffAngle;
}

float Light::getExponent() const{
    return _exponent;
}

bool Light::getState() const{
    return _state;
}

void Light::setColor(const glm::vec4& color){
    _color = color;
}

void Light::setLd(float Ld){
    _Ld = glm::vec3(Ld);
}

void Light::setLa(float La){
    _La = glm::vec3(La);
}

void Light::setLs(float Ls){
    _Ls = glm::vec3(Ls);
}

void Light::setType(int type){
    _type = type;
}

void Light::setCutoffAngle(float angle){
    _cutoffAngle = angle;
}

void Light::setExponent(float exponent){
    _exponent = exponent;
}

void Light::setState(bool state){
    _state = state;
}
