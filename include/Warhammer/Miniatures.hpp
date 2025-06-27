#pragma once
#include <glm/vec4.hpp>
#include <string>
#include <vector>
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
    float size;
    int shaderID;
    int maxHealth;
    int currentHealth;
    float speed = 3.0f; 

    Miniature(const glm::vec4& pos, const std::string& obj, float theta, float scale, int shader, int maxHp, int currHp);

    void Draw() const;
    bool MiniatureMove(float delta_t, const std::vector<std::vector<Miniature>> Armies);
    bool CanMove(const glm::vec4& movementDelta, const std::vector<std::vector<Miniature>>& Armies) const;
    
};

