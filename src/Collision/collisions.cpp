#include "Collision/collisions.h"

float clamp(float value, float minValue, float maxValue)
{
    if (value < minValue)
        return minValue;
    else if (value > maxValue)
        return maxValue;
    else
        return value;
}


// Function to check if a bounding sphere intersects with an oriented bounding box (OBB)
bool SphereIntersectsOBB(const BoundingSphere& sphere, const OBB& obb)
{
    glm::vec3 d = sphere.center - obb.center;
    glm::vec3 closestPoint = obb.center;

    for (int i = 0; i < 3; ++i) {
        float dist = dotproduct(glm::vec4(d, 0.0f), glm::vec4(obb.axes[i], 0.0f));
        dist = clamp(dist, -obb.halfSizes[i], obb.halfSizes[i]);
        closestPoint += dist * obb.axes[i];
    }

    float distanceSquared = dotproduct(
        glm::vec4(sphere.center - closestPoint, 0.0f),
        glm::vec4(sphere.center - closestPoint, 0.0f)
    );

    return distanceSquared <= sphere.radius * sphere.radius;
}



// Function to compute the Oriented Bounding Box (OBB) for a miniature
OBB ComputeOBB(const Miniature& m)
{
    const SceneObject& obj = g_VirtualScene[m.object];

    glm::vec3 min = obj.bbox_min;
    glm::vec3 max = obj.bbox_max;

    glm::vec3 centerLocal = (min + max) * 0.5f; // Center in local coordinates
    glm::vec3 halfSizes = (max - min) * 0.5f; // Half-sizes in local coordinates

    if (m.object == "the_wall")
    {
        float scaleFactor = 1.5f; // Scale factor for the wall
        halfSizes *= scaleFactor;}

    glm::mat4 rotation = Matrix_Rotate(m.facingTheta, glm::vec4(0, 1, 0, 0)); // Rotate around Y-axis according to facing angle

    glm::vec3 axes[3] = {
        glm::normalize(glm::vec3(rotation * glm::vec4(1, 0, 0, 0))),
        glm::normalize(glm::vec3(rotation * glm::vec4(0, 1, 0, 0))),
        glm::normalize(glm::vec3(rotation * glm::vec4(0, 0, 1, 0)))
    };

    glm::vec3 centerWorld = glm::vec3(rotation * glm::vec4(centerLocal, 1.0f)) + glm::vec3(m.position);

    return { centerWorld, { axes[0], axes[1], axes[2] }, halfSizes };
}

// FONTE: ChatGPT --> This function tests for collision between two OBBs using the Separating Axis Theorem (SAT).
bool TestOBBCollision(const OBB& a, const OBB& b)
{
    const float EPSILON = 1e-6f;
    float R[3][3], AbsR[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            R[i][j] = dotproduct(glm::vec4(a.axes[i], 0.0f), glm::vec4(b.axes[j], 0.0f));
            AbsR[i][j] = std::abs(R[i][j]) + EPSILON;
        }

    glm::vec3 tVec = b.center - a.center;
    glm::vec3 t(
        dotproduct(glm::vec4(tVec, 0.0f), glm::vec4(a.axes[0], 0.0f)),
        dotproduct(glm::vec4(tVec, 0.0f), glm::vec4(a.axes[1], 0.0f)),
        dotproduct(glm::vec4(tVec, 0.0f), glm::vec4(a.axes[2], 0.0f))
    );

    for (int i = 0; i < 3; i++) {
        float ra = a.halfSizes[i];
        float rb = b.halfSizes[0] * AbsR[i][0] + b.halfSizes[1] * AbsR[i][1] + b.halfSizes[2] * AbsR[i][2];
        if (std::abs(t[i]) > ra + rb)
            return false;
    }

    for (int i = 0; i < 3; i++) {
        float ra = a.halfSizes[0] * AbsR[0][i] + a.halfSizes[1] * AbsR[1][i] + a.halfSizes[2] * AbsR[2][i];
        float rb = b.halfSizes[i];
        float tProj = t[0]*R[0][i] + t[1]*R[1][i] + t[2]*R[2][i];
        if (std::abs(tProj) > ra + rb)
            return false;
    }

    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
        float ra = a.halfSizes[(i+1)%3] * AbsR[(i+2)%3][j] + a.halfSizes[(i+2)%3] * AbsR[(i+1)%3][j];
        float rb = b.halfSizes[(j+1)%3] * AbsR[i][(j+2)%3] + b.halfSizes[(j+2)%3] * AbsR[i][(j+1)%3];
        float tProj = t[(i+2)%3]*R[(i+1)%3][j] - t[(i+1)%3]*R[(i+2)%3][j];
        if (std::abs(tProj) > ra + rb)
            return false;
    }

    return true;
}

// Function to check if a ray intersects with an OBB 
bool RayIntersectsOBB(const glm::vec3& rayOrigin,
                      const glm::vec4& rayDir,
                      const OBB& obb,
                      float& tHit)
{
    float tMin = -INFINITY;
    float tMax = INFINITY;

    glm::vec3 p = obb.center - rayOrigin;

    for (int i = 0; i < 3; ++i)
    {
        float e = dotproduct(glm::vec4(obb.axes[i], 0.0f), glm::vec4(p, 0.0f));
        float f = dotproduct(glm::vec4(obb.axes[i], 0.0f), rayDir);


        if (std::abs(f) > 0.0001f) // The ray is not parallel to the plane
        {
            float t1 = (e + obb.halfSizes[i]) / f;
            float t2 = (e - obb.halfSizes[i]) / f;

            if (t1 > t2) std::swap(t1, t2);

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax)
                return false; 
        }
        else
        {
            // The ray is parallel to the plane, but still need to check if the ray is within the bounds of the OBB
            if (-e - obb.halfSizes[i] > 0.0f || -e + obb.halfSizes[i] < 0.0f){
                return false;

            }
                
        }
    }

    tHit = tMin;
    return true;
}

bool ShootIntersectsOBB(const Miniature& shooter,std::vector<std::vector<Miniature>>& Armies,std::vector<Miniature> &Structures)
{
    float phi = 0.0;
    float viewX = cos(phi)*sin(shooter.facingTheta);
    float viewY = sin(phi);
    float viewZ = cos(phi)*cos(shooter.facingTheta);

    glm::vec4 rayDir = glm::normalize(glm::vec4(viewX, viewY, viewZ,0.0f));
    glm::vec3 rayOrigin = glm::vec3(shooter.position);
    float tHit; 

    for (auto& army : Armies)
    {
        for (auto& other : army)
        {
            if (&other != &shooter)
            {
                OBB targetOBB = ComputeOBB(other);
                if (RayIntersectsOBB(rayOrigin, rayDir, targetOBB, tHit))
                {
                    other.currentHealth = 0; 
                    return true;
                }
            }
        }
    }


    for (auto& structure : Structures)
    {
        OBB targetOBB = ComputeOBB(structure);
        if (RayIntersectsOBB(rayOrigin, rayDir, targetOBB, tHit)){
            structure.currentHealth = 0;
            return true;

        }
            
    }

    return false; 

}

bool MiniaturesAreColliding(const Miniature& a, const Miniature& b)
{
    OBB obbA = ComputeOBB(a);
    OBB obbB = ComputeOBB(b);

    return TestOBBCollision(obbA, obbB);
}

