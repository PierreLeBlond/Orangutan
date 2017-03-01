#include "object/object.h"

#include <iostream>

using namespace std;

Object::Object(const string &name) : Asset(name)
{
}

const Transform& Object::getTransform() const
{
    return _transform;
}

void Object::setTransform(const Transform& transform)
{
    _transform = transform;
}

void Object::draw(const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix,
        const std::vector<std::shared_ptr<Light>> &lights)
{
    //By default, nothing to draw
}

void Object::setGlobalMatrix(const glm::mat4 &sceneMatrix)
{
    _transform.setGlobalMatrix(sceneMatrix);
}

void Object::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void Object::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void Object::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void Object::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void Object::setXScale(float scale){
    _transform.setXScale(scale);
}

void Object::setYScale(float scale){
    _transform.setYScale(scale);
}

void Object::setZScale(float scale){
    _transform.setZScale(scale);
}

void Object::setXPos(int x){
    _transform.setXPos(x);
}

void Object::setXPos(float x){
    _transform.setXPos(x);
}

void Object::setYPos(int y){
    _transform.setYPos(y);
}

void Object::setYPos(float y){
    _transform.setYPos(y);
}

void Object::setZPos(int z){
    _transform.setZPos(z);
}

void Object::setZPos(float z){
    _transform.setZPos(z);
}

void Object::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void Object::move(int direction){
    _transform.move(direction);
}

void Object::animate(){
    _transform.animate();
}

void Object::update(){
    _transform.update();
}

void Object::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void Object::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void Object::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void Object::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void Object::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void Object::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void Object::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void Object::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void Object::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void Object::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void Object::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void Object::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
