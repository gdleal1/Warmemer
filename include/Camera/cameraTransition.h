#pragma once
#include <glm/glm.hpp>

// Estrutura que define uma transição de câmera usando uma curva de Bézier cúbica (3 pontos)
struct CameraTransition {
    bool isTransitioning = false;
    float t = 0.0f;
    float duration = 2.0f; // 1 segundo de transição

    glm::vec4 p0, p1, p2, p3; // pontos da curva de Bézier para posição
    glm::vec4 v0, v1, v2, v3; // Curva Bézier para o vetor de direção (view)
};

CameraTransition g_cameraTransition;

// Função que realiza a interpolação de uma curva de Bézier cúbica para a posição da camera
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
            
    interpolatedPosition.w = 1.0f; // Garantir que a posição é homogênea (w = 1)
    return interpolatedPosition;
}

// Função que realiza a interpolação de uma curva de Bézier cúbica para o vetor de direção da camera
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

    interpolatedView.w = 0.0f; // Garantir que o vetor de direção é homogêneo (w = 0)
    return glm::normalize(interpolatedView); 
}


