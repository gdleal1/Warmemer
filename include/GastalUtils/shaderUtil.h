#pragma once

// Headers below are specific to C++
#include <string>
#include <fstream>
#include <sstream>

// OpenGL library headers
#include <glad/glad.h>   
#include <GLFW/glfw3.h>  

#include <GastalUtils/stb_image.h>

// Variables that define a GPU program (shaders). See LoadShadersFromFiles() function.
extern GLuint g_GpuProgramID;
extern GLint g_model_uniform;
extern GLint g_view_uniform;
extern GLint g_projection_uniform;
extern GLint g_object_id_uniform;
extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;

// Number of textures loaded by the LoadTextureImage() function
extern GLuint g_NumLoadedTextures;

void LoadShader(const char* filename, GLuint shader_id);
GLuint LoadShader_Vertex(const char* filename);
GLuint LoadShader_Fragment(const char* filename);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
void LoadTextureImage(const char* filename);
void LoadShadersFromFiles();