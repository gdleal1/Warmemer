#pragma once
#include "Warhammer/Miniatures.hpp"
#include <vector>

void DrawArmies();
void InitializeArmies();
std::vector<Miniature> BuildDreadArmy();
std::vector<Miniature> BuildOrcMechArmy();

extern int g_ArmySize;
extern std::vector<std::vector<Miniature>> Armies;