# include "Camera/freeCamMove.h"

void FreeCamMove(float delta_t){
    
    if (g_KeyWPressed)
    {
        g_freeCameraMiniatures.MoveFoward(g_speed_cam,delta_t); // Movimenta a camera para frente
    }

    if (g_KeySPressed)
    {
        g_freeCameraMiniatures.MoveBackward(g_speed_cam,delta_t); // Movimenta a camera para tras
    }

    if (g_KeyAPressed)
    {
        g_freeCameraMiniatures.MoveLeft(g_speed_cam,delta_t); // Movimenta a camera para esquerda
    }

    if (g_KeyDPressed)
    {
        g_freeCameraMiniatures.MoveRight(g_speed_cam,delta_t); // Movimenta a camera para direita
    }

    // if (g_KeySpacePressed)
    // {
    //     g_freeCameraMiniatures.MoveUp(g_speed_cam,delta_t); // Movimenta a camera para cima
    // }
    
}