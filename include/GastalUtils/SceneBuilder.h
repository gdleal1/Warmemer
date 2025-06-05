#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "GastalUtils/ObjModel.h"
#include "SceneObject.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <limits>
#include <cassert>
#include "GastalUtils/matricies.h"

// Declaração das variáveis globais 
extern std::map<std::string, SceneObject> g_VirtualScene;
extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;


extern void BuildTrianglesAndAddToVirtualScene(ObjModel* model); // Constrói representação de um ObjModel como malha de triângulos para renderização
extern void ComputeNormals(ObjModel* model); // Computa normais de um ObjModel, caso não existam.
extern void DrawVirtualObject(const char* object_name); // Desenha um objeto armazenado em g_VirtualScene

#endif //SCENE_BUILDER_H
