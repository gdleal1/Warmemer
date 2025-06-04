#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "ObjModel.h"
#include "SceneObject.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <limits>
#include <cassert>

// Declaração da variável global 
extern std::map<std::string, SceneObject> g_VirtualScene;


void BuildTrianglesAndAddToVirtualScene(ObjModel* model); // Constrói representação de um ObjModel como malha de triângulos para renderização
void ComputeNormals(ObjModel* model); // Computa normais de um ObjModel, caso não existam.
#endif // SCENE_BUILDER_H
