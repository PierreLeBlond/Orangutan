#include "object/camera.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

Camera::Camera(unsigned int width, unsigned int height) : _mode(PERSPECTIVE),
 _fovy(75.0f), _width(width), _height(height),
  _eyePosition(glm::vec3(0.0f, 0.0f, 10.0f)),
   _latitude(0.0f), _longitude(0.0f)
{
    _roll = glm::vec3(1.0f, 0.0f, 0.0f);
    _yaw = glm::vec3(0.0f, -1.0f, 0.0f);
    _pitch = glm::cross(_yaw, _roll);

    _yawAngle = 0.0f;
    _pitchAngle = 0.0f;
    _rollAngle = 0.0f;

    _projectionMatrix = glm::perspective(_fovy, (float)_width / (float)_height, 0.001f, 1000.0f);

    yaw(-60);
}


Camera::~Camera()
{
}

void Camera::update()
{
    _viewMatrix = glm::lookAt(_eyePosition, _roll + _eyePosition, -_yaw);
    setModelMatrix(glm::inverse(_viewMatrix));
}

void Camera::rotate(float longitude, float latitude)
{
    _longitude += longitude;
    _latitude += latitude;
}

void Camera::pitch(float pitchAngle)
{
    _pitchAngle = ((int)(_pitchAngle + pitchAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void Camera::yaw(float yawAngle)
{
    _yawAngle = ((int)(_yawAngle + yawAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void Camera::roll(float rollAngle)
{
    _rollAngle = ((int)(_rollAngle + rollAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void Camera::move(int direction)
{
    switch(direction)
    {
    case RIGHT:
        _eyePosition += 0.2f*_pitch;
        break;
    case LEFT:
        _eyePosition -= 0.2f*_pitch;
        break;
    case FORWARD:
        _eyePosition += 0.2f*_roll;
        break;
    case BACKWARD:
        _eyePosition -= 0.2f*_roll;
        break;
    case UP:
        _eyePosition -= _yaw;
        break;
    case DOWN:
        _eyePosition += _yaw;
        break;
    default:
        break;
    }
}

const glm::mat4& Camera::getView() const
{
    return _viewMatrix;
}

glm::mat4 Camera::computeRotateViewMatrix() const
{
    glm::mat4 rotateViewMatrix(1.0f);
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            rotateViewMatrix[j][i] = _viewMatrix[j][i];
    return rotateViewMatrix;
}

glm::mat4 Camera::computePerspectiveProjection() const
{
    return glm::perspective(_fovy, (float)_width / (float)_height, 0.001f, 1000.0f);
}

glm::mat4 Camera::computeOrthoProjection() const
{
    return glm::ortho(-(float)_width*0.001f*_fovy, (float)_width*0.001f*_fovy, -(float)_height*0.001f*_fovy, (float)_height*0.001f*_fovy, 0.0f, 1000.0f);
}

glm::mat4 Camera::computeProjection() const
{
    if(_mode == PERSPECTIVE)
        return computePerspectiveProjection();
    else
        return computeOrthoProjection();
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

void Camera::zoomOut()
{
    if(_fovy < 100.0f)
    {
        _fovy += 10.0f;
        //emit fovyChanged((int)m_fovy);
    }
}

void Camera::zoomIn()
{
    if(_fovy > 10.0f)
    {
        _fovy -= 10.0f;
        //emit fovyChanged((int)m_fovy);
    }
}

void Camera::zoom(float z)
{
    setFovy(z/10);
}

void Camera::changeMode(int m)
{
    _mode = m;
}
