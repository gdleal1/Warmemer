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
                    Armies[1][i].Draw(); // Draw the Orc Mech army
                }
}

std::vector<Miniature> BuildDreadArmy() {
    std::vector<Miniature> minis;
    for (int i = 0; i < ArmySize; ++i) {
        Miniature mini(
            glm::vec4(-9.0f, -0.4f, -5.5f, 1.0f), // position
            "the_dread",                            // object
            1.00f,                                 //Facing angle
            2,                                      // shaderID
            100,                                    // maxHealth
            100                                     // currentHealth
        );
        minis.push_back(mini);
    }
    return minis;
}

std::vector<Miniature> BuildOrcMechArmy() {
    std::vector<Miniature> minis;
    for (int i = 0; i < ArmySize; ++i) {
        Miniature mini(
            glm::vec4(11.0f, -0.4f, 5.5f, 1.0f),    // position
            "the_orcMech",                          // object
            -2.0f,                                  //Facing angle
            3,                                      // shaderID
            100,                                    // maxHealth
            100                                     // currentHealth
        );
        minis.push_back(mini);
    }
    return minis;
}
