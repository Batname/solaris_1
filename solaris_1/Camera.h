#ifndef Camera_h
#define Camera_h

// Std. Includes
#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat YAW        = -90.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  6.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;


class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ), GLfloat yaw = YAW, GLfloat pitch = PITCH) :
        front(glm::vec3( 0.0f, 0.0f, -1.0f )),
        movementSpeed( SPEED ),
        mouseSensitivity( SENSITIVTY ),
        zoom( ZOOM )
    {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors();
    }
    
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVTY),
        zoom(ZOOM)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors();
    }
    
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }
    
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
    {
        GLfloat velocity = movementSpeed * deltaTime;
        
        if (FORWARD == direction) {
            position += front * velocity;
        }
        
        if (BACKWARD == direction) {
            position -= front * velocity;
        }
        
        if (LEFT == direction) {
            position -= right * velocity;
        }
        
        if (RIGHT == direction) {
            position += right * velocity;
        }
    }
    
    void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
    {
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;
        
        yaw += xOffset;
        pitch += yOffset;
        
        if (constrainPitch) {
            if (pitch > 89.0f) {
                pitch = 89.0f;
            }
            
            if (pitch < -89.0f) {
                pitch = -89.0f;
            }
        }
        
        updateCameraVectors();
    }
    
    void ProcessMouseScroll(GLfloat yOffset)
    {

    }
    
    GLfloat GetZoom()
    {
        return zoom;
    }
    
    glm::vec3 GetPosition()
    {
        return position;
    }
    
    glm::vec3 GetFront()
    {
        return front;
    }
    
private:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // Eular Angles
    GLfloat yaw;
    GLfloat pitch;
    
    // Camera options
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;
    
    void updateCameraVectors()
    {
        glm::vec3 _front;
        _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        front = glm::normalize(_front);

        right = glm::normalize(glm::cross(_front, worldUp));
        up = glm::normalize(glm::cross(right, _front));
    }
};

#endif /* Camera_h */
