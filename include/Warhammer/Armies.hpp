#pragma once
#include "Warhammer/Miniatures.hpp"
#include <vector>

extern int ArmySize;

extern int current_mini_idx;
extern int current_player_idx;

extern std::vector<std::vector<Miniature>> Armies;

void DrawArmies();
void InitializeArmies();
std::vector<Miniature> BuildDreadArmy();
std::vector<Miniature> BuildOrcMechArmy();