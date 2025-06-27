#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <string>
#include <glm/vec3.hpp> 
#include <glad/glad.h>

struct SceneObject
{
    std::string  name;        // Object name
    size_t       first_index; // Index of the first vertex in the indices[] vector
    size_t       num_indices; // Number of object indexes
    GLenum       rendering_mode;          // Rasterization mode (GL_TRIANGLES, etc.)
    GLuint       vertex_array_object_id;  // VAO ID
    glm::vec3    bbox_min; // Bounding box min
    glm::vec3    bbox_max; // Bounding box max
};

#endif // SCENE_OBJECT_H
