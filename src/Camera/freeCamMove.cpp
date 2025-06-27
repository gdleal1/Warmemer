# include "Camera/freeCamMove.h"

void FreeCamMove(float delta_t){
    
    if (g_KeyWPressed)
    {
        g_freeCameraMiniatures.MoveFoward(g_speed_cam,delta_t); // Movement of the camera forward
    }

    if (g_KeySPressed)
    {
        g_freeCameraMiniatures.MoveBackward(g_speed_cam,delta_t); // Movement of the camera backward
    }

    if (g_KeyAPressed)
    {
        g_freeCameraMiniatures.MoveLeft(g_speed_cam,delta_t); // Movement of the camera to the left
    }

    if (g_KeyDPressed)
    {
        g_freeCameraMiniatures.MoveRight(g_speed_cam,delta_t); // Movement of the camera to the right
    }
    
}