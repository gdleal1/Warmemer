// MatrixStack.cpp
#include "GastalUtils/MatrixStack.h"


// Function that takes the matrix M and stores it at the top of the stack
void PushMatrix(glm::mat4 M)
{
    g_MatrixStack.push(M);
}

// Function that removes the matrix currently on top of the stack and stores it in the variable M
void PopMatrix(glm::mat4& M)
{
    if ( g_MatrixStack.empty() )
    {
        M = Matrix_Identity();
    }
    else
    {
        M = g_MatrixStack.top();
        g_MatrixStack.pop();
    }
}