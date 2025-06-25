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
#include "GastalUtils/matricies.h"

extern bool g_KeyWPressed;
extern bool g_KeySPressed;
extern bool g_KeyAPressed;
extern bool g_KeyDPressed;

class Miniature
{
public:
    glm::vec4 position;
    std::string object;
    float facingTheta;
    int shaderID;
    int maxHealth;
    int currentHealth;
    float speed = 3.0f; 

    Miniature(const glm::vec4& pos, const std::string& obj, float theta, int shader, int maxHp, int currHp);

    void Draw() const;
    void MiniatureMove(float delta_t);
    
};

