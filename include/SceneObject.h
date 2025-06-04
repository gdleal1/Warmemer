#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <string>
#include <glm/vec3.hpp> // Para glm::vec3
#include <glad/glad.h>

struct SceneObject
{
    std::string  name;        // Nome do objeto
    size_t       first_index; // Índice do primeiro vértice dentro do vetor indices[]
    size_t       num_indices; // Número de índices do objeto
    GLenum       rendering_mode;          // Modo de rasterização (GL_TRIANGLES, etc.)
    GLuint       vertex_array_object_id;  // ID do VAO
    glm::vec3    bbox_min; // Bounding box min
    glm::vec3    bbox_max; // Bounding box max
};

#endif // SCENE_OBJECT_H
