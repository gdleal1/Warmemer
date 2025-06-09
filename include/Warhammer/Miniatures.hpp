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

//#include "Warhammer/Armies.hpp"

class Miniature
{
public:
    glm::vec4 position;
    std::string object;
    int shaderID;
    int maxHealth;
    int currentHealth;

    Miniature(const glm::vec4& pos, const std::string& obj, int shader, int maxHp, int currHp);

    void Draw() const;
};

