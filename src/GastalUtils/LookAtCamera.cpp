// LookAtCamera.cpp
#include "GastalUtils/LookAtCamera.hpp"
#include <cmath>

// Constructor initializes the camera parameters 
LookAtCamera::LookAtCamera(float theta, float phi, float distance)
    : cameraTheta(theta), cameraPhi(phi), cameraDistance(distance),
      cameraLookAtL(0.0f, 0.0f, 0.0f, 1.0f), cameraUpVector(0.0f, 1.0f, 0.0f, 0.0f)
{
    UpdateCamera();
}

// Updates the camera position and view vector based on spherical coordinates
void LookAtCamera::UpdateCamera() {
    radius = cameraDistance;
    coordY = radius * sin(cameraPhi);
    coordZ = radius * cos(cameraPhi) * cos(cameraTheta);
    coordX = radius * cos(cameraPhi) * sin(cameraTheta);

    cameraPositionC = glm::vec4(coordX, coordY, coordZ, 1.0f);
    cameraViewVector = cameraLookAtL - cameraPositionC;
}

void LookAtCamera::SetCameraTheta(float theta) {
    cameraTheta = theta;
    UpdateCamera();
}

void LookAtCamera::SetCameraPhi(float phi) {
    cameraPhi = phi;
    UpdateCamera();
}

void LookAtCamera::SetCameraDistance(float distance) {
    cameraDistance = distance;
    UpdateCamera();
}

float LookAtCamera::GetCameraTheta() const {
    return cameraTheta;
}

float LookAtCamera::GetCameraPhi() const {
    return cameraPhi;
}

float LookAtCamera::GetCameraDistance() const {
    return cameraDistance;
}

glm::mat4 LookAtCamera::GetMatrixCameraView() const {
    return Matrix_Camera_View(cameraPositionC, cameraViewVector, cameraUpVector);
}

glm::mat4 LookAtCamera::GetMatrixPerspective(float nearplane, float farplane, float field_of_view, float screenRatio) const {
    return Matrix_Perspective(field_of_view, screenRatio, nearplane, farplane);
}