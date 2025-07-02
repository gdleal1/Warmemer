#pragma once
#include "Warhammer/Miniatures.hpp"
#include "Warhammer/Armies.hpp"
#include "GastalUtils/SceneObject.h" 
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GastalUtils/matricies.h"


extern std::map<std::string, SceneObject> g_VirtualScene;

// Struct to represent an Oriented Bounding Box (OBB)
struct OBB
{
    glm::vec3 center;      // Center of the OBB in world coordinates
    glm::vec3 axes[3];     // Normalized vectors (local x, y, z)
    glm::vec3 halfSizes;   // Half-size along each axis
};

// Struct to represent a Bounding Sphere
struct BoundingSphere {
    glm::vec3 center;
    float radius;
};

bool MiniaturesAreColliding(const Miniature& a, const Miniature& b);
bool ShootIntersectsOBB(const Miniature& shooter, std::vector<std::vector<Miniature>>& Armies, std::vector<Miniature> &Structures);


                      
                     

