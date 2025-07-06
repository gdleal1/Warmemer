#include "Camera/cameraTransition.h"


CameraTransition g_cameraTransition;
CameraTransition g_miniatureCameraShootTransition;
CameraTransition g_miniatureToMiniatureTransition;
extern bool g_isLookAtUsed; 
extern bool g_isMiniatureCamera;
extern LookAtCamera g_lookAtCamera;
extern FreeCamera g_freeCameraMiniatures;
extern FreeCamera g_freeCamera;

// Function that interpolates a cubic Bézier curve to the camera position
glm::vec4 BezierCubicPos(CameraTransition& cameraTransition){
            
    if (cameraTransition.t >= 1.0f) {
        cameraTransition.t = 1.0f;
        cameraTransition.isTransitioning = false;
    }

    float t = cameraTransition.t;
    float oneMinusT = 1.0f - t;

    glm::vec4 interpolatedPosition =
        oneMinusT * oneMinusT * oneMinusT * cameraTransition.p0 +
        3.0f * oneMinusT * oneMinusT * t * cameraTransition.p1 +
        3.0f * oneMinusT * t * t * cameraTransition.p2 +
        t * t * t * cameraTransition.p3;
            
    interpolatedPosition.w = 1.0f; // Ensure that the position is homogeneous (w = 1)
    return interpolatedPosition;
}

// Function that interpolates a cubic Bézier curve to the camera's direction vector
glm::vec4 BezierCubicView(CameraTransition& cameraTransition)
{
    if (cameraTransition.t >= 1.0f) {
        cameraTransition.t = 1.0f;
        cameraTransition.isTransitioning = false;
    }

    float t = cameraTransition.t;
    glm::vec4 v0 = cameraTransition.v0;
    glm::vec4 v1 = cameraTransition.v1;
    glm::vec4 v2 = cameraTransition.v2;
    glm::vec4 v3 = cameraTransition.v3;
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
            
    glm::vec4 interpolatedPosition = BezierCubicPos(g_cameraTransition);
    glm::vec4 interpolatedView = BezierCubicView(g_cameraTransition);
            
            
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

void StartShootCameraAnimation(float delta_t)
{
    // Updates the camera transition for the shooting animation
    g_miniatureCameraShootTransition.t += delta_t / g_miniatureCameraShootTransition.duration;

    glm::vec4 interpolatedView = BezierCubicView(g_miniatureCameraShootTransition);
    g_freeCameraMiniatures.SetViewVector(interpolatedView);
}

void SetMiniatureToMiniatureTransition(){
    g_miniatureToMiniatureTransition.isTransitioning = true;
    g_miniatureToMiniatureTransition.t = 0.0f;

    // Current position aand view vector
    g_miniatureToMiniatureTransition.p0 = g_freeCameraMiniatures.GetPosition(); // current position
    g_miniatureToMiniatureTransition.v0 = g_freeCameraMiniatures.GetViewVector(); // current view vector
    
    glm::vec4 minPosition;
    float cameraTheta;

    // Free camera position values
    minPosition = GetCurrentMiniature().position;
    minPosition.y = minPosition.y + 1.5f;
    cameraTheta = GetCurrentMiniature().facingTheta;

    float cameraPhi = 0.0;
    float viewX = cos(cameraPhi)*sin(cameraTheta);
    float viewY = sin(cameraPhi);
    float viewZ = cos(cameraPhi)*cos(cameraTheta);

    g_freeCameraMiniatures.SetPosition(minPosition);
    g_freeCameraMiniatures.SetViewVector(glm::vec4(viewX, viewY, viewZ, 0.0f));

    g_miniatureToMiniatureTransition.p3 = g_freeCameraMiniatures.GetPosition(); // destination

    // Intermidiate control points for the position curve
    glm::vec4 dir = g_miniatureToMiniatureTransition.p3 - g_miniatureToMiniatureTransition.p0;
    g_miniatureToMiniatureTransition.p1 = g_miniatureToMiniatureTransition.p0 + 0.25f * dir;
    g_miniatureToMiniatureTransition.p2 = g_miniatureToMiniatureTransition.p0 + 0.75f * dir;

    g_miniatureToMiniatureTransition.v3 = g_freeCameraMiniatures.GetViewVector(); // destination view vector


    // Intermediate control points for the direction curve
    g_miniatureToMiniatureTransition.v1 = glm::normalize(glm::mix(g_miniatureToMiniatureTransition.v0, g_miniatureToMiniatureTransition.v3, 0.25f));
    g_miniatureToMiniatureTransition.v2 = glm::normalize(glm::mix(g_miniatureToMiniatureTransition.v0, g_miniatureToMiniatureTransition.v3, 0.75f));


}

void StartMiniatureToMiniatureTransition(float delta_t)
{
    // Updates the camera transition for the miniature to miniature transition
    g_miniatureToMiniatureTransition.t += delta_t / g_miniatureToMiniatureTransition.duration;

    glm::vec4 interpolatedPosition = BezierCubicPos(g_miniatureToMiniatureTransition);
    glm::vec4 interpolatedView = BezierCubicView(g_miniatureToMiniatureTransition);

    g_freeCameraMiniatures.SetPosition(interpolatedPosition);
    g_freeCameraMiniatures.SetViewVector(interpolatedView);
}
