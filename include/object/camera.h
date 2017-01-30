#ifndef CAMERA_H
#define CAMERA_H

#include "scene/objectnode.h"

#include "util/util.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera : public ObjectNode
{
public:
                                Camera(unsigned int width, unsigned int height);
                                ~Camera();

    /**
     * brief Update the view matrix, model Matrix and skybox matrix
     */
    void                        update();

    const glm::mat4&            getView() const;
    glm::mat4                   computeRotateViewMatrix() const;
    glm::mat4                   getPerspectiveProjection() const;
    glm::mat4                   getOrthoProjection() const;
    glm::mat4                   getProjection() const;

    void                        setPerspectiveProjectionMode();
    void                        setOrthoProjectionMode();

    void                        setFovy(float z);

    void                        setWidth(unsigned int w);
    void                        setHeight(unsigned int h);

    void                        rotate(float longitude, float latitude);
    void                        pitch(float pitchAngle);
    void                        yaw(float yawAngle);
    void                        roll(float rollAngle);
    void                        move(int direction);

    void                        zoomIn();
    void                        zoomOut();
    void                        zoom(float z);
    void                        changeMode(int m);

private:
    int                         _mode;
    float                       _fovy;
    unsigned int                _width;
    unsigned int                _height;

    glm::mat4                   _viewMatrix;
    glm::mat4                   _projectionMatrix;

    glm::vec3                   _eyePosition;
    glm::vec3                   _lookingAtDirection;
    glm::vec3                   _upDirection;

    float                       _latitude;
    float                       _longitude;

    float                       _yawAngle;
    float                       _pitchAngle;
    float                       _rollAngle;

    glm::vec3                   _roll;
    glm::vec3                   _yaw;
    glm::vec3                   _pitch;

    glm::mat4                   _rotateMatrix;

    std::shared_ptr<Object>     _skyBox;
};

#endif // CAMERA_H
