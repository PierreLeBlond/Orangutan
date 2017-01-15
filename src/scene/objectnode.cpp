
#include "scene/objectnode.h"

#include <iostream>

ObjectNode::ObjectNode()
{
}

void ObjectNode::setObject(std::shared_ptr<Object> object)
{
    _object = object;
}

void ObjectNode::addChild(std::shared_ptr<ObjectNode> node)
{
    _childs.push_back(node);
}

void ObjectNode::removeChild(std::shared_ptr<ObjectNode> node)
{
	unsigned int i = 0;
    while (i < _childs.size() && _childs[i] != node)
	{
		i++;
	}
    if (i < _childs.size())
	{
        _childs.erase(_childs.begin() + i);
	}
}

void ObjectNode::removeNode(std::shared_ptr<ObjectNode> node)
{
	unsigned int i = 0;
    while (i < _childs.size() && _childs[i] != node)
	{
		i++;
	}
    if (i < _childs.size())
	{
        _childs.erase(_childs.begin() + i);
	}
	else
	{
        for (unsigned int j = 0; j < _childs.size(); j++)
		{
            _childs[j]->removeNode(node);
		}
	}
}

void ObjectNode::displayScene(const glm::mat4&  viewMatrix,
                            const glm::mat4& projectionMatrix,
                            const std::vector<std::shared_ptr<Light>>& lights)
{
    if(_object)
        _object->draw(viewMatrix, projectionMatrix, lights);
    for (unsigned int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->displayScene(viewMatrix, projectionMatrix, lights);
    }
}

void ObjectNode::animateScene()
{
     _transform.animate();
    if(_object)
        _object->animate();
     for (unsigned int i = 0; i < _childs.size(); i++)
     {
         _childs[i]->animateScene();
     }
}

void ObjectNode::updateScene(const glm::mat4& mat)
{
    /*if(_object)
        _object->update();
    _transform.update();*/
    setGlobalMatrix(mat);
    if(_object)
        _object->setGlobalMatrix(mat*_transform.getModelMatrix());
    for (unsigned int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->updateScene(mat*_transform.getModelMatrix());
    }
}

//inherit from Transformable
void ObjectNode::setGlobalMatrix(const glm::mat4& sceneMatrix)
{
    _transform.setGlobalMatrix(sceneMatrix);
}

void ObjectNode::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void ObjectNode::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void ObjectNode::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void ObjectNode::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void ObjectNode::setXScale(float scale){
    _transform.setXScale(scale);
}

void ObjectNode::setYScale(float scale){
    _transform.setYScale(scale);
}

void ObjectNode::setZScale(float scale){
    _transform.setZScale(scale);
}

void ObjectNode::setXPos(int x){
    _transform.setXPos(x);
}

void ObjectNode::setXPos(float x){
    _transform.setXPos(x);
}

void ObjectNode::setYPos(int y){
    _transform.setYPos(y);
}

void ObjectNode::setYPos(float y){
    _transform.setYPos(y);
}

void ObjectNode::setZPos(int z){
    _transform.setZPos(z);
}

void ObjectNode::setZPos(float z){
    _transform.setZPos(z);
}

void ObjectNode::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void ObjectNode::move(int direction){
    _transform.move(direction);
}

void ObjectNode::animate(){
    _transform.animate();
}

void ObjectNode::update(){
    _transform.update();
}

void ObjectNode::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void ObjectNode::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void ObjectNode::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void ObjectNode::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void ObjectNode::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void ObjectNode::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void ObjectNode::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void ObjectNode::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void ObjectNode::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void ObjectNode::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void ObjectNode::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void ObjectNode::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
