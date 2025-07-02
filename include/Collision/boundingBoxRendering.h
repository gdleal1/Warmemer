#include <glad/glad.h>    
#include <glm/glm.hpp>
#include <iostream>
#include "Collision/collisions.h"

// FONTE: CHATGPT --> Functions for bounding box rendering
GLuint boxVAO = 0, boxVBO = 0, boxEBO = 0;
GLuint boxShaderProgram = 0;


const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";


const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0); // vermelho
}
)";

GLuint CompileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Erro compilando shader: " << infoLog << std::endl;
    }
    return shader;
}

void InitBoundingBoxRenderer()
{
    
    glm::vec3 boxVertices[8] = {
        {-0.5f, -0.5f, -0.5f}, // 0
        { 0.5f, -0.5f, -0.5f}, // 1
        { 0.5f,  0.5f, -0.5f}, // 2
        {-0.5f,  0.5f, -0.5f}, // 3
        {-0.5f, -0.5f,  0.5f}, // 4
        { 0.5f, -0.5f,  0.5f}, // 5
        { 0.5f,  0.5f,  0.5f}, // 6
        {-0.5f,  0.5f,  0.5f}  // 7
    };

    
    GLuint boxIndices[24] = {
        0,1, 1,2, 2,3, 3,0, 
        4,5, 5,6, 6,7, 7,4, 
        0,4, 1,5, 2,6, 3,7  
    };

    
    glGenVertexArrays(1, &boxVAO);
    glGenBuffers(1, &boxVBO);
    glGenBuffers(1, &boxEBO);

    glBindVertexArray(boxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    boxShaderProgram = glCreateProgram();
    glAttachShader(boxShaderProgram, vertexShader);
    glAttachShader(boxShaderProgram, fragmentShader);
    glLinkProgram(boxShaderProgram);

    
    int success;
    glGetProgramiv(boxShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(boxShaderProgram, 512, NULL, infoLog);
        std::cerr << "Erro linkando shader program: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void DrawOBB(const OBB& obb, GLuint shaderProgram, GLuint boxVAO, const glm::mat4& view, const glm::mat4& projection)
{
    glUseProgram(shaderProgram);

    
    glm::mat4 model(1.0f);

    
    model[0] = glm::vec4(obb.axes[0] * obb.halfSizes.x * 2.0f, 0.0f);
    
    model[1] = glm::vec4(obb.axes[1] * obb.halfSizes.y * 2.0f, 0.0f);
    
    model[2] = glm::vec4(obb.axes[2] * obb.halfSizes.z * 2.0f, 0.0f);
    
    model[3] = glm::vec4(obb.center, 1.0f);

    
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

    
    glBindVertexArray(boxVAO);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

