#pragma once
# include "Camera/LookAtCamera.hpp"
# include "Camera/FreeCamera.hpp"

extern float g_FreeCameraTheta; // Angle in the ZX plane with respect to the Z axis
extern float g_FreeCameraPhi;   // Angle in relation to the Y axis
extern float g_FreeCameraDistance; // Distance from camera to origin

extern float g_LookAtCameraTheta;
extern float g_LookAtCameraPhi;
extern float g_LookAtCameraDistance;

// Camera look at
extern LookAtCamera g_lookAtCamera;

// Free camera
extern FreeCamera g_freeCameraMiniatures;

// Boolean that controls whether the look-at camera is being used
extern bool g_isLookAtUsed;

// Free camera movement speed
extern float g_speed_cam;
