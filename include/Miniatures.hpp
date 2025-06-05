#include <glm/vec4.hpp>
#include <string>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>  
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "GastalUtils/matricies.h"
#include "GastalUtils/SceneBuilder.h"
#include "GastalUtils/shaderUtil.h"

struct Miniature
{
    glm::vec4 position;
    std::string object;
    int shaderID;
    int maxHealth;
    int currentHealth;
};

Miniature Minis[10];


void BuildMini(Miniature *mini){
    glm::mat4 model = Matrix_Translate(mini->position.x, mini->position.y, mini->position.z) *
                   Matrix_Scale(2.0f, 2.0f, 2.0f);   
    glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(g_object_id_uniform, mini->shaderID); // Dreadnought
    DrawVirtualObject(mini->object.c_str());
}

