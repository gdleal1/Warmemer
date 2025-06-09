#pragma once
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

extern Miniature Minis[10];


void BuildMini(Miniature *mini);

