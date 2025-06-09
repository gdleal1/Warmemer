#include "Warhammer/Miniatures.hpp"

void BuildMini(Miniature *mini){
    int scale;

    if(mini->shaderID == 2){
        scale = 1.2;
    }
    else{
        scale = 1.0;
    }

    glm::mat4 model = Matrix_Scale(scale, scale, scale) *
                      Matrix_Translate(mini->position.x, mini->position.y, mini->position.z);
    glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(g_object_id_uniform, mini->shaderID); // Dreadnought
    DrawVirtualObject(mini->object.c_str());
}