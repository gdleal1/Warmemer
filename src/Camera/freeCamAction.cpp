# include "Camera/freeCamAction.h"

void MiniatureFreeCamAction(float delta_t){
    
    if (g_KeyWPressed)
    {
        g_freeCameraMiniatures.MoveFoward(g_speed_cam_miniature,delta_t); // Movement of the camera forward
    }

    if (g_KeySPressed)
    {
        g_freeCameraMiniatures.MoveBackward(g_speed_cam_miniature,delta_t); // Movement of the camera backward
    }

    if (g_KeyAPressed)
    {
        g_freeCameraMiniatures.MoveLeft(g_speed_cam_miniature,delta_t); // Movement of the camera to the left
    }

    if (g_KeyDPressed)
    {
        g_freeCameraMiniatures.MoveRight(g_speed_cam_miniature,delta_t); // Movement of the camera to the right
    }

    
}

void FreeCamMove(float delta_t){
    
    if (g_KeyWPressed)
    {
        g_freeCamera.MoveFoward(g_speed_cam,delta_t); // Movement of the camera forward
    }

    if (g_KeySPressed)
    {
        g_freeCamera.MoveBackward(g_speed_cam,delta_t); // Movement of the camera backward
    }

    if (g_KeyAPressed)
    {
        g_freeCamera.MoveLeft(g_speed_cam,delta_t); // Movement of the camera to the left
    }

    if (g_KeyDPressed)
    {
        g_freeCamera.MoveRight(g_speed_cam,delta_t); // Movement of the camera to the right
    }

    if (g_KeySpacePressed)
    {
        g_freeCamera.MoveUp(g_speed_cam,delta_t); // Movement of the camera upward
    }
    
}