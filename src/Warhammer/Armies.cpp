#include "Warhammer/Armies.hpp"


int g_ArmySize = 1;
bool g_isDreadArmy = true; // Flag to indicate if the Dreadnought army is being used
int current_mini_idx;
int current_player_idx;

std::vector<std::vector<Miniature>> Armies(2);

void InitializeArmies() {
    Armies[0] = BuildDreadArmy();
    Armies[1] = BuildOrcMechArmy();
}

void DrawArmies(){
    for (int i = 0; i < g_ArmySize; ++i)
                {
                    Armies[0][i].Draw(); // Draw the Dreadnought army
                    Armies[1][i].Draw(); // Draw the Orc Mech army
                }
}

std::vector<Miniature> BuildDreadArmy() {
    std::vector<Miniature> minis;
    for (int i = 0; i < g_ArmySize; ++i) {
        Miniature mini(
            glm::vec4(-9.0f, -0.4f, -5.5f, 1.0f), // position
            "the_dread",                            // object
            1.0f,                                 //Facing angle
            1.2f,                                // size
            2,                                      // shaderID
            100,                                    // maxHealth
            50                                     // currentHealth
        );
        minis.push_back(mini);
    }
    return minis;
}

std::vector<Miniature> BuildOrcMechArmy() {
    std::vector<Miniature> minis;
    for (int i = 0; i < g_ArmySize; ++i) {
        Miniature mini(
            glm::vec4(11.0f, -0.4f, 5.5f, 1.0f),    // position
            "the_orcMech",                          // object
            -2.0f,                                  //Facing angle
            1.0f,                                // size
            3,                                      // shaderID
            100,                                    // maxHealth
            100                                     // currentHealth
        );
        minis.push_back(mini);
    }
    return minis;
}
