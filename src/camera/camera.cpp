#include "camera/camera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

Camera::Camera(unsigned int width, unsigned int height, const std::string& name) :
    Asset(name),
    _mode(PERSPECTIVE),
    _fovy(75.0f), _width(width), _height(height),
    _eyePosition(glm::vec3(0.0f, 0.0f, 10.0f)),
    _latitude(0.0f), _longitude(0.0f),
    _speed(1.0f)
{
    focus();
}

const glm::mat4& Camera::getView() const
{
    return _viewMatrix;
}

const glm::mat4& Camera::getProjection() const
{
    return _projectionMatrix;
}

void Camera::setPerspectiveProjectionMode()
{
    _mode = PERSPECTIVE;
}

void Camera::setOrthoProjectionMode()
{
    _mode = ORTHO;
}

void Camera::setFovy(float z)
{
    if(z <= 100.0f && z >= 10.0f) _fovy = z;
}

void Camera::setWidth(unsigned int w)
{
    _width = w;
}

void Camera::setHeight(unsigned int h)
{
    _height = h;
}

void Camera::setSpeed(float speed)
{
    _speed = speed;
}

void Camera::setFocus(std::shared_ptr<Object> focus)
{
    _focus = focus;
}

void Camera::focus()
{
    if(_focus)
    {
        _roll = _focus->getTransform().getGlobalPos() - _eyePosition;
        _roll = glm::normalize(_roll);
    }
    else
    {
        _roll = glm::vec3(1.0f, 0.0, 0.0f);
    }
   _yaw = glm::vec3(0.0f, -1.0f, 0.0f);
   _pitch = glm::cross(_yaw, _roll);

   _yawAngle = 0.0f;
   _pitchAngle = 0.0f;
   _rollAngle = 0.0f;
}

