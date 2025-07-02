#include "Camera/cameraTransition.h"

CameraTransition g_cameraTransition;
CameraTransition g_cameraShootTransition;
extern bool g_isLookAtUsed; 
extern bool g_isMiniatureCamera;
extern LookAtCamera g_lookAtCamera;
extern FreeCamera g_freeCameraMiniatures;
extern FreeCamera g_freeCamera;

// Function that interpolates a cubic Bézier curve to the camera position
glm::vec4 BezierCubicPos(){
            
    if (g_cameraTransition.t >= 1.0f) {
        g_cameraTransition.t = 1.0f;
        g_cameraTransition.isTransitioning = false;
    }

    float t = g_cameraTransition.t;
    float oneMinusT = 1.0f - t;

    glm::vec4 interpolatedPosition =
        oneMinusT * oneMinusT * oneMinusT * g_cameraTransition.p0 +
        3.0f * oneMinusT * oneMinusT * t * g_cameraTransition.p1 +
        3.0f * oneMinusT * t * t * g_cameraTransition.p2 +
        t * t * t * g_cameraTransition.p3;
            
    interpolatedPosition.w = 1.0f; // Ensure that the position is homogeneous (w = 1)
    return interpolatedPosition;
}

// Function that interpolates a cubic Bézier curve to the camera's direction vector
glm::vec4 BezierCubicView()
{
    float t = g_cameraTransition.t;
    glm::vec4 v0 = g_cameraTransition.v0;
    glm::vec4 v1 = g_cameraTransition.v1;
    glm::vec4 v2 = g_cameraTransition.v2;
    glm::vec4 v3 = g_cameraTransition.v3;
    float oneMinusT = 1.0f - t;

    glm::vec4 interpolatedView =
        oneMinusT * oneMinusT * oneMinusT * v0 +
        3.0f * oneMinusT * oneMinusT * t * v1 +
        3.0f * oneMinusT * t * t * v2 +
        t * t * t * v3;

    interpolatedView.w = 0.0f; // Ensure that the direction vector is homogeneous (w = 0)
    
    return glm::normalize(interpolatedView); 
}

void StartCameraTransition(float delta_t)
{
    // Updates the camera transition, if it is in progress
    g_cameraTransition.t += delta_t / g_cameraTransition.duration;
            
    glm::vec4 interpolatedPosition = BezierCubicPos();
    glm::vec4 interpolatedView = BezierCubicView();
            
            
    if (g_isLookAtUsed) {
        g_lookAtCamera.SetPosition(interpolatedPosition);
        g_lookAtCamera.SetViewVector(interpolatedView);
    } 


    else {
        if (g_isMiniatureCamera) {
            g_freeCameraMiniatures.SetPosition(interpolatedPosition);
            g_freeCameraMiniatures.SetViewVector(interpolatedView);
        }

        else {
            g_freeCamera.SetPosition(interpolatedPosition);
            g_freeCamera.SetViewVector(interpolatedView);
        }

    }

}