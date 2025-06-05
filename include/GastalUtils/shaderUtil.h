#pragma once

// Headers abaixo são específicos de C++
#include <string>
#include <fstream>
#include <sstream>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>   // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional

#include <GastalUtils/stb_image.h>

// Variáveis que definem um programa de GPU (shaders). Veja função LoadShadersFromFiles().
extern GLuint g_GpuProgramID;
extern GLint g_model_uniform;
extern GLint g_view_uniform;
extern GLint g_projection_uniform;
extern GLint g_object_id_uniform;
extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;

// Número de texturas carregadas pela função LoadTextureImage()
extern GLuint g_NumLoadedTextures;

void LoadShader(const char* filename, GLuint shader_id);
GLuint LoadShader_Vertex(const char* filename);
GLuint LoadShader_Fragment(const char* filename);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
void LoadTextureImage(const char* filename);
void LoadShadersFromFiles();