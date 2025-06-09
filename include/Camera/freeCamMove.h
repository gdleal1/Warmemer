#pragma once
#include "Camera/FreeCamera.hpp"

extern FreeCamera g_freeCamera;
extern float g_speed_cam;
extern bool g_KeyWPressed;
extern bool g_KeySPressed;
extern bool g_KeyAPressed;
extern bool g_KeyDPressed;
extern bool g_KeySpacePressed;

void FreeCamMove(float delta_t); 
    