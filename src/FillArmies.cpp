#include "FillArmies.hpp"


Miniature* BuildDreadArmy(){
    static Miniature Minis[1];
    for (int i = 0; i < 1; ++i) {
        Minis[i].position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        Minis[i].object = "the_dread";
        Minis[i].shaderID = 2; // Supondo que o shader ID do dreadnought seja 1
        Minis[i].maxHealth = 100;
        Minis[i].currentHealth = 100;
    }
    return Minis;
}

Miniature* BuildOrcMechArmy(){
    static Miniature Minis[1];
    for (int i = 0; i < 1; ++i) {
        Minis[i].position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        Minis[i].object = "the_orcMech";
        Minis[i].shaderID = 3; // Supondo que o shader ID do orcMech seja 2
        Minis[i].maxHealth = 100;
        Minis[i].currentHealth = 100;
    }
    return Minis;
}
