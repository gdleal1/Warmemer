#include "Warhammer/Miniatures.hpp"
#include "Collision/collisions.h"
#include "Camera/camera.h"
Miniature::Miniature(const glm::vec4& pos, const std::string& obj, float theta, float scale, int shader, int maxHp, int currHp, float movement)
    : position(pos)
    , object(obj)
    , facingTheta(theta)
    , size(scale)
    , shaderID(shader)
    , maxHealth(maxHp)
    , currentHealth(currHp)
    ,maxMovement(movement)
{}

void Miniature::Draw() const {

    if (currentHealth > 0) {
        //Draw miniature itseld
        glm::mat4 model = Matrix_Translate(position.x, position.y, position.z) *
                        Matrix_Scale(size, size, size) *
                        Matrix_Rotate_Y(facingTheta);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, shaderID);
        DrawVirtualObject(object.c_str());


        // Draw health bar
        float healthPercentage = static_cast<float>(currentHealth) / maxHealth;
        glm::vec4 viewVector = g_isLookAtUsed ? g_lookAtCamera.GetViewVector() : g_freeCameraMiniatures.GetViewVector();

        model = Matrix_Translate(position.x, position.y + 2.5f, position.z) *
                Matrix_To_View(viewVector) *
                Matrix_Scale(healthPercentage, 0.05, 0.5) *
                Matrix_Rotate_Y(1.57) *
                Matrix_Rotate_Z(1.57f);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, 6); // RED color for health bar
        DrawVirtualObject("the_plane");
    }
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

    
    if (CanMove(movement, Armies, Structures)){
        if( alreadyMoved < maxMovement) { 
            position += movement;
            alreadyMoved += glm::length(movement);
            return true; // Movement was successful
        }
        return false; // Movement blocked by max movement limit
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

void Miniature::EndTurn() {
    alreadyMoved = 0.0f; // Reset the movement for the next turn
}