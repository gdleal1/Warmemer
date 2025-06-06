# include "GastalUtils/freeCamMove.h"

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

    if (g_KeySpacePressed)
    {
        g_freeCamera.MoveUp(g_speed_cam,delta_t); // Movimenta a camera para cima
    }
    
}