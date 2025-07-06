#pragma once
#include "Collision/collisions.h"
#include "Camera/cameraTransition.h"
#include "Camera/freeCamAction.h"
#include "Warhammer/Turns.hpp"

extern CameraTransition g_cameraTransition;
extern CameraTransition g_miniatureCameraShootTransition;
extern CameraTransition g_miniatureToMiniatureTransition;

void HandleMiniatureCameraActions(float delta_t);

