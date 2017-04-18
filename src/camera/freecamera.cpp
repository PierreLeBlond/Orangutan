#include "camera/freecamera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

FreeCamera::FreeCamera(unsigned int width, unsigned int height, const std::string& name) :
    Camera(width, height, name)
{
}

void FreeCamera::update()
{
    _viewMatrix = glm::lookAt(_eyePosition, _eyePosition - _roll, _yaw);
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

void FreeCamera::move(int direction)
{
    switch(direction)
    {
    case RIGHT:
        _eyePosition += 0.2f*_pitch*_speed;
        break;
    case LEFT:
        _eyePosition -= 0.2f*_pitch*_speed;
        break;
    case FORWARD:
        _eyePosition += 0.2f*_roll*_speed;
        break;
    case BACKWARD:
        _eyePosition -= 0.2f*_roll*_speed;
        break;
    case UP:
        _eyePosition -= _yaw*_speed;
        break;
    case DOWN:
        _eyePosition += _yaw*_speed;
        break;
    default:
        break;
    }
}
