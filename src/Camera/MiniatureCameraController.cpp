#include "Camera/MiniatureCameraController.h"

bool shotFiredInThisTransition = false;
Miniature* previousMiniature = nullptr;
Miniature* newMiniature = nullptr;

void HandleMiniatureCameraActions(float delta_t){
    
    if (GetCurrentMiniature().MiniatureMove(delta_t, Armies, Strucutres)) {
        MiniatureFreeCamAction(delta_t);
    }

    // Shoot animation
    if (g_miniatureCameraShootTransition.isTransitioning) {
        StartShootCameraAnimation(delta_t);

        if (!shotFiredInThisTransition) {
            ShootIntersectsOBB(GetCurrentMiniature(), Armies, Strucutres);
            previousMiniature = &GetCurrentMiniature(); 
            EndMiniTurn();
            newMiniature = &GetCurrentMiniature();  
            shotFiredInThisTransition = true;
        }
    }

    // Miniature to miniature transition
    else if (shotFiredInThisTransition || g_miniatureToMiniatureTransition.isTransitioning) {

        if (previousMiniature != newMiniature) {
            if (!g_miniatureToMiniatureTransition.isTransitioning)
            {
                SetMiniatureToMiniatureTransition(); 
            }
                
            StartMiniatureToMiniatureTransition(delta_t);
        }

        if (!g_miniatureToMiniatureTransition.isTransitioning)
            shotFiredInThisTransition = false;

    }
}







