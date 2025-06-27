#pragma once
#include <glm/glm.hpp>

// Structure that defines a camera transition using a cubic Bézier curve (3 points) 
struct CameraTransition {
    bool isTransitioning = false;
    float t = 0.0f;
    float duration = 2.0f; 

    glm::vec4 p0, p1, p2, p3; // Bézier curve points for position
    glm::vec4 v0, v1, v2, v3; // Bézier curve for the direction vector (view)
};

CameraTransition g_cameraTransition;

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


