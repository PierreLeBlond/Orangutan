#ifndef TRACK_BALL_CAMERA_H
#define TRACK_BALL_CAMERA_H

#include "camera/camera.h"
#include "object/object.h"

class TrackBallCamera : public Camera
{
public:
                                TrackBallCamera(unsigned int width, unsigned int height,
                                                const std::string &name = "Track Ball Camera X");

    /**
     * brief Update the model, view and projection matrices.
     * Call it whenever you want to retrieve those.
     */
    virtual void                update();
    virtual void                move(int direction);

private:
    float                       _radius;
};

#endif // TRACK_BALL_CAMERA_H
