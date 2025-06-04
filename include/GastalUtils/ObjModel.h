// ObjModel.h
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <GastalUtils/tiny_obj_loader.h>
#include <vector>
#include <string>
#include <cstdio>
#include <stdexcept>

struct ObjModel
{
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;

    ObjModel(const char* filename, const char* basepath = nullptr, bool triangulate = true);
};

#endif
