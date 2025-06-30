// FreeCamera.cpp
#include "Camera/FreeCamera.hpp"
#include <cmath>
# include "Camera/camera.h"

// Constructor initializes the camera parameters 
FreeCamera::FreeCamera(float theta, float phi, float distance)
    : cameraTheta(theta), cameraPhi(phi), cameraDistance(distance),
      cameraUpVector(0.0f, 1.0f, 0.0f, 0.0f)
{
    UpdateCamera();
}

// Updates the camera position and view vector based on spherical coordinates
void FreeCamera::UpdateCamera() {
    
    viewX = cos(cameraPhi)*sin(cameraTheta);
    viewY = sin(cameraPhi);
    viewZ = cos(cameraPhi)*cos(cameraTheta);

    
    cameraViewVector = glm::vec4(viewX, viewY, viewZ, 0.0f);

    w = (-1.0f * cameraViewVector) / norm(cameraViewVector);
    u = crossproduct(cameraUpVector,w)/norm(crossproduct(cameraUpVector,w));
    v = crossproduct(w,u);

}

void FreeCamera::MoveFoward(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 wXZ = glm::vec4(w.x, 0.0f, w.z, 0.0f);           // projects w onto the XZ plane
        wXZ = glm::normalize(wXZ);                                 // re-normalize
        cameraPositionC += -1.0f * wXZ * camSpeed * deltaTime;
    }

    else{
        cameraPositionC += -1.0f * w * camSpeed * deltaTime; // Move the camera forward
    }
    
}

void FreeCamera::MoveBackward(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 wXZ = glm::vec4(w.x, 0.0f, w.z, 0.0f);           // projects w onto the XZ plane
        wXZ = glm::normalize(wXZ);                                 // re-normalize
        cameraPositionC += wXZ * camSpeed * deltaTime;
    }

    else
        cameraPositionC += w * camSpeed * deltaTime; // Move the camera backward
}

void FreeCamera::MoveLeft(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 uXZ = glm::vec4(u.x, 0.0f, u.z, 0.0f);
        uXZ = glm::normalize(uXZ);
        cameraPositionC += -1.0f * uXZ * camSpeed * deltaTime;
    }

    else
        cameraPositionC += -1.0f * u * camSpeed * deltaTime; // Move the camera left
    
}

void FreeCamera::MoveRight(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 uXZ = glm::vec4(u.x, 0.0f, u.z, 0.0f);
        uXZ = glm::normalize(uXZ);
        cameraPositionC += uXZ * camSpeed * deltaTime;
    }

    else
        cameraPositionC += u * camSpeed * deltaTime; // Move the camera right
    
}

void FreeCamera::MoveUp(float camSpeed, float deltaTime){
    cameraPositionC += v * camSpeed * deltaTime;
}

void FreeCamera::SetCameraTheta(float theta) {
    cameraTheta = theta;
    UpdateCamera();
}

void FreeCamera::SetCameraPhi(float phi) {
    cameraPhi = phi;
    UpdateCamera();
}

void FreeCamera::SetCameraDistance(float distance) {
    cameraDistance = distance;
    UpdateCamera();
}

float FreeCamera::GetCameraTheta() const {
    return cameraTheta;
}

float FreeCamera::GetCameraPhi() const {
    return cameraPhi;
}

float FreeCamera::GetCameraDistance() const {
    return cameraDistance;
}

void FreeCamera::SetPosition(glm::vec4 position) {
    cameraPositionC = position;
    
}

glm::vec4 FreeCamera::GetPosition() {
    return cameraPositionC;
}

void FreeCamera::SetViewVector(glm::vec4 viewVector) {
    cameraViewVector = viewVector;
    w = (-1.0f * cameraViewVector) / norm(cameraViewVector);
    u = crossproduct(cameraUpVector,w)/norm(crossproduct(cameraUpVector,w));

}

glm::vec4 FreeCamera::GetViewVector() {
    return cameraViewVector;}

glm::mat4 FreeCamera::GetMatrixCameraView() const {
    return Matrix_Camera_View(cameraPositionC, cameraViewVector, cameraUpVector);
}

glm::mat4 FreeCamera::GetMatrixPerspective(float nearplane, float farplane, float field_of_view, float screenRatio) const {
    return Matrix_Perspective(field_of_view, screenRatio, nearplane, farplane);
}
