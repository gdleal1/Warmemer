#pragma once
#include <glm/glm.hpp>

// Estrutura que define uma transição de câmera usando uma curva de Bézier cúbica (3 pontos)
struct CameraTransition {
    bool isTransitioning = false;
    float t = 0.0f;
    float duration = 2.0f; // 1 segundo de transição

    glm::vec4 p0, p1, p2, p3; // pontos da curva de Bézier
};

CameraTransition g_cameraTransition;

// Função que realiza a interpolação de uma curva de Bézier cúbica
glm::vec4 BezierCubic(float delta_t){
    
    g_cameraTransition.t += delta_t / g_cameraTransition.duration;
            
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
            
    interpolatedPosition.w = 1.0f; // Garantir que a posição é homogênea (w = 1)
    return interpolatedPosition;
}


