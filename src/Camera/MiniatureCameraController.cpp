#include "Camera/MiniatureCameraController.h"

bool shotFiredInThisTransition = false;

void HandleMiniatureCameraActions(float delta_t){
    
    // Miniature camera movement
    if (GetCurrentMiniature().MiniatureMove(delta_t, Armies, Strucutres)) {
        MiniatureFreeCamAction(delta_t);
    }

    // Shoot animation
    if (g_miniatureCameraShootTransition.isTransitioning) {
        StartShootCameraAnimation(delta_t);

        if (!shotFiredInThisTransition) {
            ShootIntersectsOBB(GetCurrentMiniature(), Armies, Strucutres);
            shotFiredInThisTransition = true;
        }
    }

    // Miniature to miniature transition
    else if (shotFiredInThisTransition || g_miniatureToMiniatureTransition.isTransitioning) {
        
        if (!g_miniatureToMiniatureTransition.isTransitioning)
            SetMiniatureToMiniatureTransition();

        StartMiniatureToMiniatureTransition(delta_t);

        if (!g_miniatureToMiniatureTransition.isTransitioning)
            shotFiredInThisTransition = false;
    }
}






