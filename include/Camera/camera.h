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

// Free camera for miniatures
extern FreeCamera g_freeCameraMiniatures;

// Free camera
extern FreeCamera g_freeCamera;

// Boolean that controls whether the look-at camera is being used
extern bool g_isLookAtUsed;

// Miniature Free camera movement speed
extern float g_speed_cam_miniature;

// Free camera movement speed
extern float g_speed_cam;

// Boolean to check if the camera is the miniature camera
extern bool g_isMiniatureCamera; 
