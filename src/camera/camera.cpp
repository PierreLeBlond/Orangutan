#include "camera/camera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

Camera::Camera(unsigned int width, unsigned int height, const std::string& name) :
    ObjectNode(name),
    _mode(PERSPECTIVE),
    _fovy(75.0f), _width(width), _height(height),
    _eyePosition(glm::vec3(0.0f, 0.0f, -10.0f)),
    _focus(glm::vec3(0.0f, 0.0f, 0.0f)),
    _latitude(0.0f), _longitude(0.0f),
    _yawAngle(0.0f),
    _pitchAngle(0.0f),
    _rollAngle(0.0f),
    _yaw(0.0f, 1.0f, 0.0f),
    _pitch(1.0f, 0.0f, 0.0f),
    _roll(0.0f, 0.0f, 1.0f),
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

void Camera::setFocusObject(std::shared_ptr<Object> focusObject)
{
    _focusObject = focusObject;
}

void Camera::updateFocus()
{
    if(_focusObject != nullptr)
        _focus = _focusObject->getTransform().getGlobalPos();
}

glm::vec3 Camera::getFocus() const
{
    return _focus;
}

void Camera::focus()
{
    std::cout << _focus.x << " " << _focus.y << " " << _focus.z << std::endl;

    _viewMatrix = glm::lookAt(_eyePosition, _eyePosition - _roll, _yaw);
    glm::vec4 focus = _viewMatrix*glm::vec4(_focus, 1.0f);
    _focus = glm::vec3(focus);

    std::cout << _focus.x << " " << _focus.y << " " << _focus.z << std::endl;

    glm::vec3 yawFocusPoint(_focus.x, 0.0f, _focus.z);
    yawFocusPoint = glm::normalize(yawFocusPoint);

    float yawAngle = glm::acos(glm::dot(yawFocusPoint, glm::vec3(0.0f, 0.0f, -1.0f)));
    yawAngle = (yawAngle*180.0f)/3.1415f;

    std::cout << yawAngle << std::endl;

    yaw(yawAngle);

    glm::vec3 pitchFocusPoint(0.0f, _focus.y, _focus.z);
    pitchFocusPoint = glm::normalize(pitchFocusPoint);

    float pitchAngle = glm::acos(glm::dot(pitchFocusPoint, glm::vec3(0.0f, 0.0f, -1.0f)));
    pitchAngle = (pitchAngle*180.0f)/3.1415f;

    std::cout << pitchAngle << std::endl;

    pitch(pitchAngle);
}

void Camera::pitch(float pitchAngle)
{
    _pitchAngle = ((int)(_pitchAngle + pitchAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 1.0f, 0.0f, 0.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, 1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 0.0f, 0.0f, 1.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void Camera::yaw(float yawAngle)
{
    _yawAngle = ((int)(_yawAngle + yawAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 1.0f, 0.0f, 0.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, 1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 0.0f, 0.0f, 1.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void Camera::roll(float rollAngle)
{
    _rollAngle = ((int)(_rollAngle + rollAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 1.0f, 0.0f, 0.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, 1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 0.0f, 0.0f, 1.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}


