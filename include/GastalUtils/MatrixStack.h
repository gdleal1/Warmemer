#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H


#include <glm/glm.hpp>
#include "GastalUtils/matricies.h"
#include <stack>

// Declaration of global variables
extern std::stack<glm::mat4>  g_MatrixStack;


// Functions to manipulate the matrix stack
void PushMatrix(glm::mat4 M);
void PopMatrix(glm::mat4& M);


#endif // MATRIX_STACK_H
