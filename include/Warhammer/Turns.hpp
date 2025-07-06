#include "Warhammer/Armies.hpp"

extern int current_mini_idx; // Index of the current miniature being controlled
extern int current_player_idx; // Index of the current player (0 for Dreadnought, 1 for Orc Mech)

Miniature& GetCurrentMiniature();
void EndMiniTurn();