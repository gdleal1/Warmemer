#include "Collision/collisions.h"

// Function to check if two miniatures are colliding using their bounding boxes
bool MiniaturesAreColliding(const Miniature& a, const Miniature& b)
{
    const SceneObject& objA = g_VirtualScene[a.object];
    const SceneObject& objB = g_VirtualScene[b.object];

    glm::vec3 aMin = objA.bbox_min + glm::vec3(a.position);
    glm::vec3 aMax = objA.bbox_max + glm::vec3(a.position);

    glm::vec3 bMin = objB.bbox_min + glm::vec3(b.position);
    glm::vec3 bMax = objB.bbox_max + glm::vec3(b.position);

    bool overlapX = (aMin.x <= bMax.x) && (aMax.x >= bMin.x);
    bool overlapY = (aMin.y <= bMax.y) && (aMax.y >= bMin.y);
    bool overlapZ = (aMin.z <= bMax.z) && (aMax.z >= bMin.z);
 
    return overlapX && overlapY && overlapZ;
}
