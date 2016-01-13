#pragma once

#include "util.h"

#include "opengl.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
                                Camera(GLuint width, GLuint height);
                                ~Camera();

    glm::mat4                   getView(const glm::core::type::vec3& scenePosVect);
    glm::mat4                   getRotateViewMatrix() const;
    glm::mat4                   getPerspectiveProjection() const;
    glm::mat4                   getOrthoProjection() const;
    glm::mat4                   getProjection() const;

    inline void                 setPerspectiveProjectionMode(){ m_mode = PERSPECTIVE; }
    inline void                 setOrthoProjectionMode(){m_mode = ORTHO; }

    inline void                 setFovy(float z){ if(z <= 100.0f && z >= 10.0f) m_fovy = z;}

    inline void                 setWidth(GLuint w){m_width = w;}
    inline void                 setHeight(GLuint h){m_height = h;}

    void                        rotate(GLfloat longitude, GLfloat latitude);
    void                        pitch(GLfloat pitchAngle);
    void                        yaw(GLfloat yawAngle);
    void                        roll(GLfloat rollAngle);
    void                        move(int direction);

    void                        zoomIn();
    void                        zoomOut();
    void                        zoom(float z);
    void                        changeMode(int m);

//signals:
  //  void                        fovyChanged(float);
    //void                        cameraMooved(int);

private:
    int                         m_mode;
    GLfloat                     m_fovy;
    GLuint                      m_width;
    GLuint                      m_height;

    glm::mat4                   m_viewMatrix;
    glm::mat4                   m_projectionMatrix;

    glm::vec3                   m_eyePosition;
    glm::vec3                   m_lookingAtDirection;
    glm::vec3                   m_upDirection;

    GLfloat                     m_longitude;
    GLfloat                     m_latitude;

    GLfloat                     m_yawAngle;
    GLfloat                     m_pitchAngle;
    GLfloat                     m_rollAngle;

    glm::vec3                   m_roll;
    glm::vec3                   m_yaw;
    glm::vec3                   m_pitch;

    glm::mat4                   m_rotateMatrix;
};

