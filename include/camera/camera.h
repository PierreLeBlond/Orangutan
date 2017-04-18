#ifndef CAMERA_H
#define CAMERA_H

#include "scene/objectnode.h"

#include "util/util.h"

class Camera : public ObjectNode
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

    void                        setFocusObject(std::shared_ptr<Object> focusObject);
    void                        updateFocus();
    glm::vec3                   getFocus() const;

    void                        pitch(float pitchAngle);
    void                        yaw(float yawAngle);
    void                        roll(float rollAngle);

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
    glm::vec3                   _focus;
    std::shared_ptr<Object>     _focusObject;

    float                       _latitude;
    float                       _longitude;

    float                       _yawAngle;
    float                       _pitchAngle;
    float                       _rollAngle;

    glm::vec3                   _yaw;
    glm::vec3                   _pitch;
    glm::vec3                   _roll;

    float                       _speed;
};

#endif // CAMERA_H
