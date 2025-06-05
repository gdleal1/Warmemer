#include "Miniatures.hpp"

Miniature Minis[10];

void BuildMini(Miniature *mini){
    glm::mat4 model = Matrix_Scale(1.2f, 1.2f, 1.2f) *
                      Matrix_Translate(mini->position.x, mini->position.y, mini->position.z);
    glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(g_object_id_uniform, mini->shaderID); // Dreadnought
    DrawVirtualObject(mini->object.c_str());
}