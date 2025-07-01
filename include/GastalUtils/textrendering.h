#include <GLFW/glfw3.h>
#include <string>


// Declaration of auxiliary functions for rendering text within the
// OpenGL window. These functions are defined in the "textrendering.cpp" file.
void TextRendering_Init();
float TextRendering_LineHeight(GLFWwindow* window);
float TextRendering_CharWidth(GLFWwindow* window);
void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);
void TextRendering_ShowFramesPerSecond(GLFWwindow* window);
void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale = 1.0f);
void ShowHelpText(GLFWwindow* window);