// FreeCamera.cpp
#include "GastalUtils/FreeCamera.hpp"
#include <cmath>

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

}

void FreeCamera::MoveFoward(float camSpeed, float deltaTime){
    cameraPositionC += -1.0f *w * camSpeed * deltaTime;
}

void FreeCamera::MoveBackward(float camSpeed, float deltaTime){
    cameraPositionC += w * camSpeed * deltaTime;
}

void FreeCamera::MoveLeft(float camSpeed, float deltaTime){
    cameraPositionC += -1.0f *u * camSpeed * deltaTime;
}

void FreeCamera::MoveRight(float camSpeed, float deltaTime){
    cameraPositionC += u * camSpeed * deltaTime;
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
