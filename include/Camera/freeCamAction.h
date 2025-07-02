#pragma once
#include "Camera/FreeCamera.hpp"
#include "Camera/cameraTransition.h"


extern FreeCamera g_freeCameraMiniatures;
extern FreeCamera g_freeCamera;
extern float g_speed_cam;
extern float g_speed_cam_miniature;
extern bool g_KeyWPressed;
extern bool g_KeySPressed;
extern bool g_KeyAPressed;
extern bool g_KeyDPressed;
extern bool g_KeySpacePressed;

void MiniatureFreeCamAction(float delta_t);
void FreeCamMove(float delta_t); 
    