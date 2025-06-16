#include "Warhammer/Miniatures.hpp"


Miniature::Miniature(const glm::vec4& pos,const std::string& obj, float theta, int shader, int maxHp, int currHp)
    : position(pos), object(obj),facingTheta(theta),shaderID(shader), maxHealth(maxHp), currentHealth(currHp){}

void Miniature::Draw() const {
    float scale;

    if (shaderID == 2) {
        scale = 1.2f;
    }
    else {
        scale = 1.0f;
    }

    glm::mat4 model = Matrix_Translate(position.x, position.y, position.z) *
                      Matrix_Scale(scale, scale, scale) *
                      Matrix_Rotate_Y(facingTheta);
    glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(g_object_id_uniform, shaderID); // Dreadnought
    DrawVirtualObject(object.c_str());
}