// FreeCamera.cpp
#include "Camera/FreeCamera.hpp"
#include <cmath>
# include "Camera/camera.h"
extern CameraTransition g_miniatureCameraShootTransition;

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


// Checks if the free camera can move to a new position without colliding with armies or structures
bool FreeCamera::CanMove(const glm::vec4& movementDelta,
                         const std::vector<std::vector<Miniature>>& Armies,
                         const std::vector<Miniature>& Structures) const
{
    glm::vec4 newPosition = cameraPositionC + movementDelta;
    BoundingSphere camSphere = { glm::vec3(newPosition), 0.5f }; 

    // Army colision
    for (const auto& army : Armies) {
        for (const auto& other : army) {
            OBB obb = ComputeOBB(other);
            if (SphereIntersectsOBB(camSphere, obb)) {
                return false;
            }
        }
    }

    // Structure collision
    for (const auto& structure : Structures) {
        OBB obb = ComputeOBB(structure);
        if (SphereIntersectsOBB(camSphere, obb)) {
            return false;
        }
    }

    return true;
}

void FreeCamera::MoveFoward(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 wXZ = glm::vec4(w.x, 0.0f, w.z, 0.0f);           // projects w onto the XZ plane
        wXZ = glm::normalize(wXZ);                                 // re-normalize
        cameraPositionC += -1.0f * wXZ * camSpeed * deltaTime;
    }

    else{
        glm::vec4 movementDelta = -1.0f * w * camSpeed * deltaTime;
        
        if (CanMove(movementDelta, Armies, Strucutres)) {
            cameraPositionC += movementDelta; 
        }
        
    }
    
}

void FreeCamera::MoveBackward(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 wXZ = glm::vec4(w.x, 0.0f, w.z, 0.0f);           // projects w onto the XZ plane
        wXZ = glm::normalize(wXZ);                                 // re-normalize
        cameraPositionC += wXZ * camSpeed * deltaTime;
    }

    else{
        glm::vec4 movementDelta = w * camSpeed * deltaTime;
        
        if (CanMove(movementDelta, Armies, Strucutres)) {
            cameraPositionC += movementDelta; 
        }
    }

}

void FreeCamera::MoveLeft(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 uXZ = glm::vec4(u.x, 0.0f, u.z, 0.0f);
        uXZ = glm::normalize(uXZ);
        cameraPositionC += -1.0f * uXZ * camSpeed * deltaTime;
    }

    else{
        glm::vec4 movementDelta =  -1.0f * u * camSpeed * deltaTime;
        if (CanMove(movementDelta, Armies, Strucutres)) {
            cameraPositionC += movementDelta; 
        } 
    }
        
}

void FreeCamera::MoveRight(float camSpeed, float deltaTime){

    if (g_isMiniatureCamera){
        glm::vec4 uXZ = glm::vec4(u.x, 0.0f, u.z, 0.0f);
        uXZ = glm::normalize(uXZ);
        cameraPositionC += uXZ * camSpeed * deltaTime;
    }

    else{
        glm::vec4 movementDelta = u * camSpeed * deltaTime;
        if (CanMove(movementDelta, Armies, Strucutres)) {
            cameraPositionC += movementDelta; 
        } 
    }  
}

void FreeCamera::MoveUp(float camSpeed, float deltaTime){
    glm::vec4 movementDelta = v * camSpeed * deltaTime;
    if (CanMove(movementDelta, Armies, Strucutres)) {
            cameraPositionC += movementDelta; 
    } 
}

void FreeCamera::ShootAnimation(float delta_t) {
    g_miniatureCameraShootTransition.v0 = GetViewVector();
    g_miniatureCameraShootTransition.v3 = GetViewVector();

    // Intermediate control points for the direction curve
    g_miniatureCameraShootTransition.v1 = glm::normalize(glm::mix(g_miniatureCameraShootTransition.v0, g_miniatureCameraShootTransition.v3, 0.25f));
    g_miniatureCameraShootTransition.v2 = glm::normalize(glm::mix(g_miniatureCameraShootTransition.v0, g_miniatureCameraShootTransition.v3, 0.75f));

    g_miniatureCameraShootTransition.t += delta_t / g_miniatureCameraShootTransition.duration;
    glm::vec4 interpolatedView = BezierCubicView(g_miniatureCameraShootTransition);
    SetViewVector(interpolatedView);

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
