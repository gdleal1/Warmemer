#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "GastalUtils/ObjModel.h"
#include "SceneObject.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <limits>
#include <cassert>
#include "GastalUtils/matricies.h"

// Declaration of global variables 
extern std::map<std::string, SceneObject> g_VirtualScene;
extern GLint g_bbox_min_uniform;
extern GLint g_bbox_max_uniform;


extern void BuildTrianglesAndAddToVirtualScene(ObjModel* model); // Builds a representation of an ObjModel as a mesh of triangles for rendering
extern void ComputeNormals(ObjModel* model); // Computes normals of an ObjModel if they don't exist.
extern void DrawVirtualObject(const char* object_name); // Draw an object stored in g_VirtualScene

#endif //SCENE_BUILDER_H
