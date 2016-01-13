#include "light.h"

Light::Light() : _Ld(glm::vec3(0.75f, 0.75f, 0.75f)), _La(glm::vec3(0.75f, 0.75f, 0.75f)), _Ls(glm::vec3(1.0f, 1.0f, 1.0f)),
  _type(PONCTUAL), _state(true), _color(QColor::fromRgb(255, 255, 255)),
  _cutoffAngle(30), _exponent(10)
{
}

Light::~Light()
{
}

const Transform& Light::getTransform() const{
    return _transform;
}

const QColor& Light::getColor() const{
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

void Light::setColor(const QColor& color){
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

//inherit from Transformable
void Light::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void Light::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void Light::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void Light::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void Light::setXScale(float scale){
    _transform.setXScale(scale);
}

void Light::setYScale(float scale){
    _transform.setYScale(scale);
}

void Light::setZScale(float scale){
    _transform.setZScale(scale);
}

void Light::setXPos(int x){
    _transform.setXPos(x);
}

void Light::setXPos(float x){
    _transform.setXPos(x);
}

void Light::setYPos(int y){
    _transform.setYPos(y);
}

void Light::setYPos(float y){
    _transform.setYPos(y);
}

void Light::setZPos(int z){
    _transform.setZPos(z);
}

void Light::setZPos(float z){
    _transform.setZPos(z);
}

void Light::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void Light::move(int direction){
    _transform.move(direction);
}

void Light::animate(){
    _transform.animate();
}

void Light::update(){
    _transform.update();
}

void Light::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void Light::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void Light::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void Light::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void Light::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void Light::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void Light::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void Light::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void Light::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void Light::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void Light::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void Light::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
