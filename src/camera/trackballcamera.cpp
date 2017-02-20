#include "camera/trackballcamera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

TrackBallCamera::TrackBallCamera(unsigned int width, unsigned int height,
                                 const std::string &name) :
    Camera(width, height, name),
    _radius(10.0f)
{
}

void TrackBallCamera::pitch(float pitchAngle)
{
    _pitchAngle = ((int)(_pitchAngle - pitchAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void TrackBallCamera::yaw(float yawAngle)
{
    _yawAngle = ((int)(_yawAngle + yawAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void TrackBallCamera::roll(float rollAngle)
{
    _rollAngle = ((int)(_rollAngle + rollAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(_rollAngle, 1.0f, 0.0f, 0.0f);

    _roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    _yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    _pitch = glm::cross(_yaw, _roll);
}

void TrackBallCamera::update()
{
    _eyePosition = _focus->getTransform().getGlobalPos()+_radius*_roll;
    _viewMatrix = glm::lookAt(_eyePosition, _focus->getTransform().getGlobalPos(), -_yaw);
    if(PERSPECTIVE == _mode)
        _projectionMatrix = glm::perspective(_fovy, (float)_width / (float)_height,
                                             0.001f, 1000.0f);
    if(ORTHO == _mode)
        _projectionMatrix = glm::ortho(-(float)_width*0.001f*_fovy,
                                       (float)_width*0.001f*_fovy,
                                       -(float)_height*0.001f*_fovy,
                                       (float)_height*0.001f*_fovy, 0.0f, 1000.0f);
    setModelMatrix(glm::inverse(_viewMatrix));
}

void TrackBallCamera::move(int direction)
{
    switch(direction)
    {
      case RIGHT:
        yaw(_speed*-5);
        break;
      case LEFT:
        yaw(_speed*5);
        break;
      case FORWARD:
        _radius -= _speed*0.1f;
        break;
      case BACKWARD:
        _radius += _speed*0.1f;
        break;
      case UP:
        pitch(_speed*-5);
        break;
      case DOWN:
        pitch(_speed*5);
        break;
      default:
        break;
    }
}

