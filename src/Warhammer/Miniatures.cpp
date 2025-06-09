#include "Warhammer/Miniatures.hpp"

class Miniature
{
public:
    glm::vec4 position;
    glm::vec4 facing; // Added facing vector for orientation
    std::string object;
    int shaderID;
    int maxHealth;
    int currentHealth;

    Miniature(const glm::vec4& pos, const std::string& obj, int shader, int maxHp, int currHp)
        : position(pos), object(obj), shaderID(shader), maxHealth(maxHp), currentHealth(currHp) {}

    void Draw() const {
        float scale;

        if (shaderID == 2) {
            scale = 1.2f;
        }
        else {
            scale = 1.0f;
        }

        glm::mat4 model = Matrix_Scale(scale, scale, scale) *
                          Matrix_Translate(position.x, position.y, position.z);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, shaderID); // Dreadnought
        DrawVirtualObject(object.c_str());
    }

};