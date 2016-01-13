#include "camera.h"

Camera::Camera(GLuint width, GLuint height) : m_mode(PERSPECTIVE), m_fovy(75.0f), m_width(width), m_height(height), m_eyePosition(glm::vec3(0.0f, 0.0f, 0.0f)), m_latitude(0.0f), m_longitude(0.0f)
{
    m_roll = glm::vec3(1.0f, 0.0f, 0.0f);
    m_yaw = glm::vec3(0.0f, -1.0f, 0.0f);
    m_pitch = glm::cross(m_yaw, m_roll);

    m_yawAngle = 0.0f;
    m_pitchAngle = 0.0f;
    m_rollAngle = 0.0f;

    m_projectionMatrix = glm::perspective(m_fovy, (GLfloat)m_width / (GLfloat)m_height, 0.001f, 1000.0f);

    yaw(-60);
}


Camera::~Camera()
{
}

void Camera::rotate(GLfloat longitude, GLfloat latitude)
{
    m_longitude += longitude;
    m_latitude += latitude;
}

void Camera::pitch(GLfloat pitchAngle)
{
    m_pitchAngle = ((int)(m_pitchAngle + pitchAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(m_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(m_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(m_rollAngle, 1.0f, 0.0f, 0.0f);

    m_roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    m_pitch = glm::cross(m_yaw, m_roll);
}

void Camera::yaw(GLfloat yawAngle)
{
    m_yawAngle = ((int)(m_yawAngle + yawAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(m_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(m_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(m_rollAngle, 1.0f, 0.0f, 0.0f);

    m_roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    m_pitch = glm::cross(m_yaw, m_roll);
}

void Camera::roll(GLfloat rollAngle)
{
    m_rollAngle = ((int)(m_rollAngle + rollAngle)) % 360;
    glm::mat4 pitchMatrix = glm::rotate(m_pitchAngle, 0.0f, 0.0f, 1.0f);
    glm::mat4 yawMatrix = glm::rotate(m_yawAngle, 0.0f, -1.0f, 0.0f);
    glm::mat4 rollMatrix = glm::rotate(m_rollAngle, 1.0f, 0.0f, 0.0f);

    m_roll = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_yaw = glm::vec3(rollMatrix*yawMatrix*pitchMatrix*glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

    m_pitch = glm::cross(m_yaw, m_roll);
}

void Camera::move(int direction)
{
    switch(direction)
    {
    case RIGHT:
        m_eyePosition += 0.2f*m_pitch;
        break;
    case LEFT:
        m_eyePosition -= 0.2f*m_pitch;
        break;
    case FORWARD:
        m_eyePosition += 0.2f*m_roll;
        //emit cameraMooved(1);
        break;
    case BACKWARD:
        m_eyePosition -= 0.2f*m_roll;
        //emit cameraMooved(-1);
        break;
    case UP:
        m_eyePosition -= m_yaw;
        break;
    case DOWN:
        m_eyePosition += m_yaw;
        break;
    default:
        break;
    }
}

glm::mat4 Camera::getView(const glm::vec3& scenePosVect)
{
    m_viewMatrix = glm::lookAt(m_eyePosition + scenePosVect, m_roll + m_eyePosition + scenePosVect, -m_yaw);
    return m_viewMatrix;
}

glm::mat4 Camera::getRotateViewMatrix() const
{
    glm::mat4 rotateViewMatrix(1.0f);
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            rotateViewMatrix[j][i] = m_viewMatrix[j][i];
    return rotateViewMatrix;
}

glm::core::type::mat4 Camera::getPerspectiveProjection() const
{
    return glm::perspective(m_fovy, (GLfloat)m_width / (GLfloat)m_height, 0.001f, 1000.0f);
}

glm::core::type::mat4 Camera::getOrthoProjection() const
{
    return glm::ortho(-(float)m_width*0.001f*m_fovy, (float)m_width*0.001f*m_fovy, -(float)m_height*0.001f*m_fovy, (float)m_height*0.001f*m_fovy, 0.0f, 1000.0f);
}

glm::core::type::mat4 Camera::getProjection() const
{
    if(m_mode == PERSPECTIVE)
        return getPerspectiveProjection();
    else
        return getOrthoProjection();
}

void Camera::zoomOut()
{
    if(m_fovy < 100.0f)
    {
        m_fovy += 10.0f;
        //emit fovyChanged((int)m_fovy);
    }
}

void Camera::zoomIn()
{
    if(m_fovy > 10.0f)
    {
        m_fovy -= 10.0f;
        //emit fovyChanged((int)m_fovy);
    }
}

void Camera::zoom(float z)
{
    setFovy(z/10);
}

void Camera::changeMode(int m)
{
    m_mode = m;
}
