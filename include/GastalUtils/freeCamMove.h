#pragma once
#include "GastalUtils/FreeCamera.hpp"

extern FreeCamera g_freeCamera;
extern float g_speed_cam;
extern bool g_KeyWPressed; // Tecla W pressionada (movimento para frente)
extern bool g_KeySPressed; // Tecla S pressionada (movimento para trás)
extern bool g_KeyAPressed; // Tecla A pressionada (movimento para esquerda)
extern bool g_KeyDPressed; // Tecla D pressionada (movimento para direita)

void FreeCamMove(float delta_t){
    
    if (g_KeyWPressed)
    {
        g_freeCamera.MoveFoward(g_speed_cam,delta_t); // Movimenta a camera para frente
    }

    if (g_KeySPressed)
    {
        g_freeCamera.MoveBackward(g_speed_cam,delta_t); // Movimenta a camera para tras
    }

    if (g_KeyAPressed)
    {
        g_freeCamera.MoveLeft(g_speed_cam,delta_t); // Movimenta a camera para esquerda
    }

    if (g_KeyDPressed)
    {
            g_freeCamera.MoveRight(g_speed_cam,delta_t); // Movimenta a camera para direita
    }
    
}
    