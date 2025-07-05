#include "Warhammer/Turns.hpp"

int current_mini_idx = 0; // Index of the current miniature being controlled
int current_player_idx = 0; // Index of the current player (0 for Dreadnought, 1 for Orc Mech)

Miniature& GetCurrentMiniature() {
    return Armies[current_player_idx][current_mini_idx];
}

bool EndMiniTurn(){
    Armies[current_player_idx][current_mini_idx].EndTurn(); // End the turn for the current miniature
    
    if (current_mini_idx + 1 < g_ArmySize) {
        current_mini_idx++;
        return true; // Proceed to the next miniature
    } else {
        current_mini_idx = 0; // Reset to the first miniature
        current_player_idx = (current_player_idx + 1) % 2; // Switch players
        return false; // End of turn, switch players
    }
}