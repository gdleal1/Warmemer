#include "Warhammer/Miniatures.hpp"


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

void Miniature::MiniatureMove(float delta_t) {

    float phi = 0.0;
    float viewX = cos(phi)*sin(facingTheta);
    float viewY = sin(phi);
    float viewZ = cos(phi)*cos(facingTheta);

    glm::vec4 minViewVector(viewX, viewY, viewZ, 0.0f);
    glm::vec4 minUpVector(0.0f, 1.0f, 0.0f, 0.0f); 
    glm::vec4 minRightVector = crossproduct(minUpVector, minViewVector); 


    if (g_KeyWPressed)
    {
        position += minViewVector * speed * delta_t; 
    }

    if (g_KeySPressed)
    {
        position -= minViewVector * speed * delta_t; 
    }

    if (g_KeyAPressed)
    {
        position += minRightVector * speed * delta_t;         
    }

    if (g_KeyDPressed)
    {
        position -= minRightVector * speed * delta_t;   
    }
}