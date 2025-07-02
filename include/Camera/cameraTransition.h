#pragma once
#include <glm/glm.hpp>
#include "Camera/LookAtCamera.hpp"
#include "Camera/FreeCamera.hpp"

// Structure that defines a camera transition using a cubic Bézier curve (3 points) 
struct CameraTransition {
    bool isTransitioning = false;
    float t = 0.0f;
    float duration = 2.0f; 

    glm::vec4 p0, p1, p2, p3; // Bézier curve points for position
    glm::vec4 v0, v1, v2, v3; // Bézier curve for the direction vector (view)
};

glm::vec4 BezierCubicPos(CameraTransition& g_cameraTransition);
glm::vec4 BezierCubicView(CameraTransition& cameraTransition);
void StartCameraTransition(float delta_t);
void StartShootCameraAnimation(float delta_t);



