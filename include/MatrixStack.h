#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H


#include <glm/glm.hpp>
#include "matrices.h"
#include <stack>

// Declaração de variáveis globais
extern std::stack<glm::mat4>  g_MatrixStack;


// Funções para manipular a pilha de matrizes
void PushMatrix(glm::mat4 M);
void PopMatrix(glm::mat4& M);


#endif // MATRIX_STACK_H
