
#include "scenenode.h"


SceneNode::SceneNode() : _sceneMatrix(glm::mat4(1.0f))
{
}

void SceneNode::addChild(std::shared_ptr<SceneNode> node)
{
    _childs.push_back(node);
}

void SceneNode::removeChild(std::shared_ptr<SceneNode> node)
{
	int i = 0;
    while (i < _childs.size() && _childs[i] != node)
	{
		i++;
	}
    if (i < _childs.size())
	{
        _childs.erase(_childs.begin() + i);
	}
}

void SceneNode::removeNode(std::shared_ptr<SceneNode> node)
{
	int i = 0;
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
        for (int j = 0; j < _childs.size(); j++)
		{
            _childs[j]->removeNode(node);
		}
	}
}

glm::mat4 SceneNode::getSceneMatrix() const
{
    return _sceneMatrix*_transform.getModelMatrix();
}

void SceneNode::setSceneMatrix(glm::mat4 mat)
{
    _sceneMatrix = mat;
    for (int i = 0; i < _childs.size(); i++)
	{
        _childs[i]->setSceneMatrix(mat);
	}
}

void SceneNode::updateScene(glm::mat4 mat)
{
    _transform.update();
    _sceneMatrix = mat*_transform.getModelMatrix();
    for (int i = 0; i < _childs.size(); i++)
    {
        _childs[i]->updateScene(_sceneMatrix);
    }
}

//inherit from Transformable
void SceneNode::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void SceneNode::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void SceneNode::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void SceneNode::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void SceneNode::setXScale(float scale){
    _transform.setXScale(scale);
}

void SceneNode::setYScale(float scale){
    _transform.setYScale(scale);
}

void SceneNode::setZScale(float scale){
    _transform.setZScale(scale);
}

void SceneNode::setXPos(int x){
    _transform.setXPos(x);
}

void SceneNode::setXPos(float x){
    _transform.setXPos(x);
}

void SceneNode::setYPos(int y){
    _transform.setYPos(y);
}

void SceneNode::setYPos(float y){
    _transform.setYPos(y);
}

void SceneNode::setZPos(int z){
    _transform.setZPos(z);
}

void SceneNode::setZPos(float z){
    _transform.setZPos(z);
}

void SceneNode::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void SceneNode::move(int direction){
    _transform.move(direction);
}

void SceneNode::animate(){
    _transform.animate();
}

void SceneNode::update(){
    _transform.update();
}

void SceneNode::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void SceneNode::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void SceneNode::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void SceneNode::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void SceneNode::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void SceneNode::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void SceneNode::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void SceneNode::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void SceneNode::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void SceneNode::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void SceneNode::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void SceneNode::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
