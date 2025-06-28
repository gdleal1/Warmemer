#include "Warhammer/Miniatures.hpp"
#include "Collision/collisions.h"

Miniature::Miniature(const glm::vec4& pos,const std::string& obj, float theta, float scale, int shader, int maxHp, int currHp)
    : position(pos), object(obj),facingTheta(theta), size(scale), shaderID(shader), maxHealth(maxHp), currentHealth(currHp){}

void Miniature::Draw() const {

    glm::mat4 model = Matrix_Translate(position.x, position.y, position.z) *
                      Matrix_Scale(size, size, size) *
                      Matrix_Rotate_Y(facingTheta);
    glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(g_object_id_uniform, shaderID);
    DrawVirtualObject(object.c_str());
}

bool Miniature::MiniatureMove(float delta_t, const std::vector<std::vector<Miniature>> &Armies, const std::vector<Miniature> &Structures) {

    float phi = 0.0;
    float viewX = cos(phi)*sin(facingTheta);
    float viewY = sin(phi);
    float viewZ = cos(phi)*cos(facingTheta);

    glm::vec4 minViewVector(viewX, viewY, viewZ, 0.0f);
    glm::vec4 minUpVector(0.0f, 1.0f, 0.0f, 0.0f); 
    glm::vec4 minRightVector = crossproduct(minUpVector, minViewVector); 
    glm::vec4 movement(0.0f);


    if (g_KeyWPressed)
    {
        movement += minViewVector * speed * delta_t; 
    }

    if (g_KeySPressed)
    {
        movement -= minViewVector * speed * delta_t; 
    }

    if (g_KeyAPressed)
    {
        movement += minRightVector * speed * delta_t;         
    }

    if (g_KeyDPressed)
    {
        movement -= minRightVector * speed * delta_t;   
    }

    
    if (CanMove(movement, Armies, Structures)) {
        position += movement;
        return true; // Movement was successful
    }

    return false; // Movement was blocked by collision
    
}

bool Miniature::CanMove(const glm::vec4& movementDelta, const std::vector<std::vector<Miniature>>& Armies, const std::vector<Miniature> &Structures) const
{
    Miniature simulated = *this;
    simulated.position += movementDelta;


    // Check for collisions with other army miniatures 
    for (const auto& army : Armies)
    {
        for (const auto& other : army)
        {
            if (&other != this && MiniaturesAreColliding(simulated, other))
                return false;
        }
    }

    // Check for collisions with structures
    for (const auto& structure : Structures)
    {
        if (MiniaturesAreColliding(simulated, structure))
            return false;
    }

    return true;
}
