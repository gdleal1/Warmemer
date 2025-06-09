#include "Warhammer/Armies.hpp"


int ArmySize = 1;

int current_mini_idx;
int current_player_idx;

std::vector<std::vector<Miniature>> Armies(2);

void InitializeArmies() {
    Armies[0] = BuildDreadArmy();
    Armies[1] = BuildOrcMechArmy();
}

void DrawArmies(){
    for (int i = 0; i < ArmySize; ++i)
                {
                    Armies[0][i].Draw(); // Draw the Dreadnought army
                    Armies[0][i].Draw(); // Draw the Orc Mech army
                }
}

std::vector<Miniature> BuildDreadArmy() {
    std::vector<Miniature> minis(ArmySize);
    for (int i = 0; i < ArmySize; ++i) {
        minis[i].position = glm::vec4(-10.0f, -0.4f, -5.5f, 1.0f);
        minis[i].object = "the_dread";
        minis[i].shaderID = 2; // Supondo que o shader ID do dreadnought seja 2
        minis[i].maxHealth = 100;
        minis[i].currentHealth = 100;
    }
    return minis;
}

std::vector<Miniature> BuildOrcMechArmy() {
    std::vector<Miniature> minis(ArmySize);
    for (int i = 0; i < ArmySize; ++i) {
        minis[i].position = glm::vec4(10.5f, -0.4f, 5.0f, 1.0f);
        minis[i].object = "the_orcMech";
        minis[i].shaderID = 3; // Supondo que o shader ID do orcMech seja 3
        minis[i].maxHealth = 100;
        minis[i].currentHealth = 100;
    }
    return minis;
}
