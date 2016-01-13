#include "transformable.h"

Transform::Transform(QObject *parent) : _translationMatrix(1.0f), _xScaleMatrix(1.0f), _yScaleMatrix(1.0f), _zScaleMatrix(1.0f), _xRotationMatrix(1.0f), _yRotationMatrix(1.0f), _zRotationMatrix(1.0f),
    _xAngle(0.0f), _yAngle(0.0f), _zAngle(0.0f), _xScale(0.0f), _yScale(0.0f), _zScale(0.0f), _xPos(0.0f), _yPos(0.0f), _zPos(0.0f),
    _xRotationSpeed(0.0f), _yRotationSpeed(0.0f), _zRotationSpeed(0.0f), _xTranslationSpeed(0.0f), _yTranslationSpeed(0.0f), _zTranslationSpeed(0.0f),
    _xTranslationSmallAxe(0.0f), _yTranslationSmallAxe(0.0f), _zTranslationSmallAxe(0.0f), _xTranslationBigAxe(0.0f), _yTranslationBigAxe(0.0f), _zTranslationBigAxe(0.0f)
{
}

const glm::core::type::mat4 &Transform::getModelMatrix() const
{
    return _modelMatrix;
}

const glm::core::type::vec4 &Transform::getDirection() const {
    return _xRotationMatrix*_yRotationMatrix*_zRotationMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

void Transform::setModelMatrix(const glm::core::type::mat4 &modelMatrix)
{
    _modelMatrix = modelMatrix;
}

void Transform::setXRotation(float angle)
{
    _xRotationMatrix = glm::rotate(float(angle), glm::vec3(1.0f, 0.0f, 0.0f));
    _xAngle = angle;
}

void Transform::setYRotation(float angle)
{
    _yRotationMatrix = glm::rotate(float(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    _yAngle = angle;
}

void Transform::setZRotation(float angle)
{
    _zRotationMatrix = glm::rotate(float(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    _zAngle = angle;
}

void Transform::setXScale(float scale)
{
    _xScaleMatrix = glm::scale(glm::vec3(float(scale), 1.0f, 1.0f));
    _xScale = scale;
}

void Transform::setYScale(float scale)
{
    _yScaleMatrix = glm::scale(glm::vec3(1.0f, float(scale), 1.0f));
    _yScale = scale;
}

void Transform::setZScale(float scale)
{
    _zScaleMatrix = glm::scale(glm::vec3(1.0f, 1.0f, float(scale)));
    _zScale = scale;
}

void Transform::setXPos(int x)
{
    _xPos = x;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setXPos(float x)
{
    _xPos = x;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setYPos(int y)
{
    _yPos = y;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setYPos(float y)
{
    _yPos = y;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setZPos(int z)
{
    _zPos = z;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setZPos(float z)
{
    _zPos = z;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::setTranslationMatrix(const glm::core::type::vec3 &vector)
{
    _xPos = vector.x;
    _yPos = vector.y;
    _zPos = vector.z;
    _translationMatrix = glm::translate(_xPos, _yPos, _zPos);
}

void Transform::move(int direction)
{
    switch(direction)
    {
    case UP:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(0.0f, 1.0f, 0.0f));
        _yPos++;
        //emit yPositionHasChanged(_yPos);
        break;
    case DOWN:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
        _yPos--;
        //emit yPositionHasChanged(_yPos);
        break;
    case RIGHT:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
        _xPos++;
        //emit xPositionHasChanged(_xPos);
        break;
    case LEFT:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(-1.0f, 0.0f, 0.0f));
        _xPos--;
        //emit xPositionHasChanged(_xPos);
        break;
    case FORWARD:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
        _zPos--;
        //emit zPositionHasChanged(_zPos);
        break;
    case BACKWARD:
        _translationMatrix = glm::translate(_translationMatrix, glm::vec3(0.0f, 0.0f, 1.0f));
        _zPos++;
        //emit zPositionHasChanged(_zPos);
        break;
    default:
        break;
    }
}

void Transform::animate()
{
    if(_xRotationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_xRotationSpeed/1000.0f)) % 360;
        setXRotation(angle);
    }
    if(_yRotationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_yRotationSpeed/1000.0f)) % 360;
        setYRotation(angle);
    }
    if(_zRotationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_zRotationSpeed/1000.0f)) % 360;
        setZRotation(angle);
    }

    if(_xTranslationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_xTranslationSpeed/1000)) % 360;
        setYPos((float)(_xTranslationSmallAxe*cos(((float)angle)*2.0f*3.14f/360.0f)));
        setZPos((float)(_xTranslationBigAxe*sin(((float)angle)*2.0f*3.14f/360.0f)));
    }
    if(_yTranslationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_yTranslationSpeed/1000)) % 360;
        setZPos((float)(_yTranslationSmallAxe*cos(((float)angle)*2.0f*3.14f/360.0f)));
        setXPos((float)(_yTranslationBigAxe*sin(((float)angle)*2.0f*3.14f/360.0f)));
    }
    if(_zTranslationSpeed != 0)
    {
        int angle = (int)(((QTime::currentTime().msecsSinceStartOfDay()))*(_zTranslationSpeed/1000)) % 360;
        setXPos((float)(_zTranslationSmallAxe*cos(((float)angle)*2.0f*3.14f/360.0f)));
        setYPos((float)(_zTranslationBigAxe*sin(((float)angle)*2.0f*3.14f/360.0f)));
    }
}

void Transform::update()
{
    _modelMatrix = _translationMatrix*_xRotationMatrix*_yRotationMatrix*_zRotationMatrix*_xScaleMatrix*_yScaleMatrix*_zScaleMatrix;
}

void Transform::setXRotationSpeed(float speed){
    _xRotationSpeed = speed;
}

void Transform::setYRotationSpeed(float speed){
    _yRotationSpeed = speed;
}

void Transform::setZRotationSpeed(float speed){
    _zRotationSpeed = speed;
}

void Transform::setXTranslationSpeed(float speed){
    _xTranslationSpeed = speed;
}

void Transform::setYTranslationSpeed(float speed){
    _yTranslationSpeed = speed;
}

void Transform::setZTranslationSpeed(float speed){
    _zTranslationSpeed = speed;
}

void Transform::setXTranslationSmallAxe(int l){
    _xTranslationSmallAxe = l;
}

void Transform::setYTranslationSmallAxe(int l){
    _yTranslationSmallAxe = l;
}

void Transform::setZTranslationSmallAxe(int l){
    _zTranslationSmallAxe = l;
}

void Transform::setXTranslationBigAxe(int l){
    _xTranslationSmallAxe = l;
}

void Transform::setYTranslationBigAxe(int l){
    _yTranslationSmallAxe = l;
}

void Transform::setZTranslationBigAxe(int l){
    _zTranslationSmallAxe = l;
}
