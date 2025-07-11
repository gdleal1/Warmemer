#include "Warhammer/Structures.hpp"

std::vector<Miniature> Strucutres;

void InitializeStructures() {
    
    Strucutres.push_back(Miniature(
        glm::vec4(2.6f, -0.4f, 0.6f, 1.0f), // position
        "the_wall",                         // object
        0.00f,                               // Facing angle
        1.5f,                                 // size
        4,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));

    Strucutres.push_back(Miniature(
        glm::vec4(0.6f, -0.4f, 2.6f, 1.0f), // position
        "the_wall",                         // object
        1.57f,                               // Facing angle
        1.5f,                                 // size
        4,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));

    
    Strucutres.push_back(Miniature(
        glm::vec4(-2.6f, -0.4f, -0.6f, 1.0f), // position
        "the_wall",                         // object
        0.00f,                               // Facing angle
        1.5f,                                 // size
        4,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));

    
    Strucutres.push_back(Miniature(
        glm::vec4(-0.6f, -0.4f, -2.6f, 1.0f), // position
        "the_wall",                         // object
        1.57f,                               // Facing angle
        1.5f,                                 // size
        4,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));

    Strucutres.push_back(Miniature(
        glm::vec4(10.0f, -0.4f, -5.0f, 1.0f), // position
        "the_container",                    // object
        -0.79f,                               // Facing angle
        1.0f,                                 // size
        0,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));

    Strucutres.push_back(Miniature(
        glm::vec4(-10.0f, -0.4f, 5.0f, 1.0f), // position
        "the_container",                    // object
        -0.79f,                               // Facing angle
        1.0f,                                 // size
        0,                                    // shaderID
        100,                                  // maxHealth
        100,                                   // currentHealth
        0.0f                                  // maxMovement
    ));
}

void DrawStructures() {
    for (const auto& structure : Strucutres) {
        structure.Draw(); // Draw each structure in the scene
    }
}