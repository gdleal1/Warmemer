// FreeCamera.hpp
#ifndef FREECAMERA_HPP
#define FREECAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "Warhammer/Armies.hpp"
#include "Collision/collisions.h"


// Declare functions for camera transformations
glm::mat4 Matrix_Camera_View(glm::vec4 camera_position_c, glm::vec4 camera_view_vector, glm::vec4 camera_up_vector);
glm::mat4 Matrix_Perspective(float field_of_view, float aspect, float near, float far);
float norm(glm::vec4 v);
glm::vec4 crossproduct(glm::vec4 u, glm::vec4 v);



class FreeCamera {
private:
    float cameraTheta;
    float cameraPhi;
    float cameraDistance;

    
    float viewX;
    float viewY;
    float viewZ;

    glm::vec4 cameraPositionC =glm::vec4(0.0f, 5.0f, 0.0f, 1.0f); //Initial camera position

    glm::vec4 cameraViewVector;
    glm::vec4 cameraUpVector;

    glm::vec4 w;
    glm::vec4 u;
    glm::vec4 v;

    void UpdateCamera();
    

public:
    FreeCamera(float theta, float phi, float distance);

    void SetCameraTheta(float theta);
    void SetCameraPhi(float phi);
    void SetCameraDistance(float distance);

    glm::mat4 GetMatrixCameraView() const;
    glm::mat4 GetMatrixPerspective(float nearplane, float farplane, float field_of_view, float screenRatio) const;
    float GetCameraTheta() const;
    float GetCameraPhi() const;
    float GetCameraDistance() const;

    void SetPosition(glm::vec4 position);
    glm::vec4 GetPosition();

    void SetViewVector(glm::vec4 viewVector);
    glm::vec4 GetViewVector();

    BoundingSphere GetBoundingSphereAt(const glm::vec4& pos) const;
    
        

    void MoveFoward(float camSpeed, float deltaTime);
    void MoveBackward(float camSpeed, float deltaTime);
    void MoveLeft(float camSpeed, float deltaTime);
    void MoveRight(float camSpeed, float deltaTime);
    void MoveUp(float camSpeed, float deltaTime);
        
};

#endif // FREECAMERA_HPP
