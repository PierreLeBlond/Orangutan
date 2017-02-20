#ifndef CAMERA_H
#define CAMERA_H

#include "scene/objectnode.h"

#include "util/util.h"

class Camera : public ObjectNode, public Asset
{
public:
                                Camera(unsigned int width, unsigned int height,
                                       const std::string &name = "Camera X");

    const glm::mat4&            getView() const;
    const glm::mat4&            getProjection() const;

    void                        setPerspectiveProjectionMode();
    void                        setOrthoProjectionMode();

    void                        setFovy(float z);

    void                        setWidth(unsigned int w);
    void                        setHeight(unsigned int h);

    void                        setSpeed(float speed);

    void                        setFocus(std::shared_ptr<Object> focus);

    virtual void                pitch(float pitchAngle) = 0;
    virtual void                yaw(float yawAngle) = 0;
    virtual void                roll(float rollAngle) = 0;

    /**
     * brief Update the model, view and projection matrices.
     * Call it whenever you want to retrieve those.
     */
    virtual void                update() = 0;
    virtual void                move(int direction) = 0;

    void                        focus();

protected:
    int                         _mode;
    int                         _type;
    float                       _fovy;
    unsigned int                _width;
    unsigned int                _height;

    glm::mat4                   _viewMatrix;
    glm::mat4                   _projectionMatrix;

    glm::vec3                   _eyePosition;
    std::shared_ptr<Object>     _focus;

    float                       _latitude;
    float                       _longitude;

    float                       _yawAngle;
    float                       _pitchAngle;
    float                       _rollAngle;

    glm::vec3                   _roll;
    glm::vec3                   _yaw;
    glm::vec3                   _pitch;

    float                       _speed;
};

#endif // CAMERA_H
