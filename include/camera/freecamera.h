#ifndef FREE_CAMERA_H
#define FREE_CAMERA_H

#include "camera/camera.h"

class FreeCamera : public Camera
{
public:
                                FreeCamera(unsigned int width, unsigned int height,
                                           const std::string &name = "Free Camera X");

    virtual void                pitch(float pitchAngle);
    virtual void                yaw(float yawAngle);
    virtual void                roll(float rollAngle);

    /**
     * brief Update the model, view and projection matrices.
     * Call it whenever you want to retrieve those.
     */
    virtual void                update();
    virtual void                move(int direction);
};

#endif // FREE_CAMERA_H
