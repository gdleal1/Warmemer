#include "Camera/camera.h"

// Variables that define the camera in spherical coordinates, controlled by the
// user via the mouse (see CursorPosCallback() function). The effective
// position of the camera is calculated within the main() function, inside the
// rendering loop.
float g_FreeCameraTheta = 0.0f; // Angle in the ZX plane with respect to the Z axis
float g_FreeCameraPhi = 0.0f;   // Angle in relation to the Y axis
float g_FreeCameraDistance = 3.5f; // Distance from camera to origin

float g_LookAtCameraTheta = 0.0f; 
float g_LookAtCameraPhi = 1.0f;   
float g_LookAtCameraDistance = 18.0f; 

// Boolean to check if the camera is the miniature camera
bool g_isMiniatureCamera = true;

// Camera look at
LookAtCamera g_lookAtCamera(g_LookAtCameraTheta, g_LookAtCameraPhi, g_LookAtCameraDistance);

// Free camera for miniatures
FreeCamera g_freeCameraMiniatures(g_FreeCameraTheta, g_FreeCameraPhi, g_FreeCameraDistance);

// Free camera
FreeCamera g_freeCamera(g_FreeCameraTheta, g_FreeCameraPhi, g_FreeCameraDistance);

// Boolean that controls whether the look-at camera is being used
bool g_isLookAtUsed = true;

// Free camera movement speed
float g_speed_cam = 5.0f;

// Miniature Free camera movement speed
float g_speed_cam_miniature = 3.0f;

