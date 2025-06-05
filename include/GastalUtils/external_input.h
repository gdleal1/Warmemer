#include <GLFW/glfw3.h>
#include "camera.h"
#include "GastalUtils/LookAtCamera.hpp"
#include "GastalUtils/FreeCamera.hpp"

// Variáveis globais que armazenam a última posição do cursor do mouse, para
// que possamos calcular quanto que o mouse se movimentou entre dois instantes
// de tempo. Utilizadas no callback CursorPosCallback() abaixo.
double g_LastCursorPosX, g_LastCursorPosY;
// "g_LeftMouseButtonPressed = true" se o usuário está com o botão esquerdo do mouse
// pressionado no momento atual. Veja função MouseButtonCallback().
bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false; // Análogo para botão direito do mouse
bool g_MiddleMouseButtonPressed = false; // Análogo para botão do meio do mouse

extern LookAtCamera g_lookAtCamera; // Declaração da câmera look-at, definida no arquivo LookAtCamera.cpp
extern FreeCamera g_freeCamera; // Declaração da câmera free, definida no arquivo FreeCamera.cpp
extern bool g_isLookAtUsed; // Declaração do booleano que controla se a câmera look-at está ativa
extern bool g_KeyWPressed; // Tecla W pressionada (movimento para frente)
extern bool g_KeySPressed; // Tecla S pressionada (movimento para trás)
extern bool g_KeyAPressed; // Tecla A pressionada (movimento para esquerda)
extern bool g_KeyDPressed; // Tecla D pressionada (movimento para direita)

// Função callback chamada sempre que o usuário aperta algum dos botões do mouse
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_LeftMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_LeftMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_RightMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_RightMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_RightMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_MiddleMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_MiddleMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_MiddleMouseButtonPressed = false;
    }
}

// Função callback chamada sempre que o usuário movimentar o cursor do mouse em
// cima da janela OpenGL.
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Abaixo executamos o seguinte: caso o botão esquerdo do mouse esteja
    // pressionado, computamos quanto que o mouse se movimento desde o último
    // instante de tempo, e usamos esta movimentação para atualizar os
    // parâmetros que definem a posição da câmera dentro da cena virtual.
    // Assim, temos que o usuário consegue controlar a câmera.

    if (g_LeftMouseButtonPressed)
    {
        // Deslocamento do cursor do mouse em x e y de coordenadas de tela!
        float dx = xpos - g_LastCursorPosX;
        float dy = ypos - g_LastCursorPosY;
    

        if (g_isLookAtUsed){
            g_lookAtCamera.SetCameraTheta(g_lookAtCamera.GetCameraTheta() - 0.01f*dx);
            g_lookAtCamera.SetCameraPhi(g_lookAtCamera.GetCameraPhi() + 0.01f*dy);
        }

        else{
            g_freeCamera.SetCameraTheta(g_freeCamera.GetCameraTheta() - 0.01f*dx);
            g_freeCamera.SetCameraPhi(g_freeCamera.GetCameraPhi() - 0.01f*dy);
        }
        
        // Em coordenadas esféricas, o ângulo phi deve ficar entre -pi/2 e +pi/2.
        float phimax = 3.141592f/2;
        float phimin = -phimax;

        if (g_isLookAtUsed){
            if (g_lookAtCamera.GetCameraPhi() > phimax)
                g_lookAtCamera.SetCameraPhi(phimax);

            if (g_lookAtCamera.GetCameraPhi() < phimin)
                g_lookAtCamera.SetCameraPhi(phimin);
        }

        else{
            if (g_freeCamera.GetCameraPhi() > phimax)
                g_freeCamera.SetCameraPhi(phimax);

            if (g_freeCamera.GetCameraPhi() < phimin)
                g_freeCamera.SetCameraPhi(phimax);
        }
        
    
        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_RightMouseButtonPressed)
    {
        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_MiddleMouseButtonPressed)
    {
        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }
}

// Função callback chamada sempre que o usuário movimenta a "rodinha" do mouse.
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Atualizamos a distância da câmera para a origem utilizando a
    // movimentação da "rodinha", simulando um ZOOM.
    if (g_isLookAtUsed)
        g_lookAtCamera.SetCameraDistance(g_lookAtCamera.GetCameraDistance() - 0.1f * yoffset);

    // Uma câmera look-at nunca pode estar exatamente "em cima" do ponto para
    // onde ela está olhando, pois isto gera problemas de divisão por zero na
    // definição do sistema de coordenadas da câmera. Isto é, a variável abaixo
    // nunca pode ser zero. Versões anteriores deste código possuíam este bug,
    // o qual foi detectado pelo aluno Vinicius Fraga (2017/2).
    const float verysmallnumber = std::numeric_limits<float>::epsilon();
    
    if (g_isLookAtUsed)
        if (g_lookAtCamera.GetCameraDistance() < verysmallnumber)
            g_lookAtCamera.SetCameraDistance(verysmallnumber);
    
}

// Definição da função que será chamada sempre que o usuário pressionar alguma
// tecla do teclado. Veja http://www.glfw.org/docs/latest/input_guide.html#input_key
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    // ======================
    // Não modifique este loop! Ele é utilizando para correção automatizada dos
    // laboratórios. Deve ser sempre o primeiro comando desta função KeyCallback().
    for (int i = 0; i < 10; ++i)
        if (key == GLFW_KEY_0 + i && action == GLFW_PRESS && mod == GLFW_MOD_SHIFT)
            std::exit(100 + i);
    // ======================


    // Se o usuário pressionar a tecla ESC, fechamos a janela.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);


    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        //do something we tdont know yet
    }

    // Se o usuário apertar a tecla L, a variavel booleana g_isLookAtUsed é setada para true
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        g_isLookAtUsed = true;
    }

    // Se o usuário apertar a tecla F, a variavel booleana g_isLookAtUsed é setada para false
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        g_isLookAtUsed = false;
    }

    // Teclas W, A, S, D para movimentação da câmera
    if (key == GLFW_KEY_W){
        if (action == GLFW_PRESS){
            g_KeyWPressed = true;
        }

        else if (action == GLFW_RELEASE){
            g_KeyWPressed = false;
        }

        else if (action == GLFW_REPEAT){
            ;
        }
    }

    if (key == GLFW_KEY_A){
        if (action == GLFW_PRESS){
            g_KeyAPressed = true;
        }

        else if (action == GLFW_RELEASE){
            g_KeyAPressed = false;
        }
        else if (action == GLFW_REPEAT){
            ;
        }
    }

    if (key == GLFW_KEY_S){
        if (action == GLFW_PRESS){
            g_KeySPressed = true;
        }

        else if (action == GLFW_RELEASE){
            g_KeySPressed = false;
        }

        else if (action == GLFW_REPEAT){
            ;
        }
    }

    if (key == GLFW_KEY_D){
        if (action == GLFW_PRESS){
            g_KeyDPressed = true;
        }

        else if (action == GLFW_RELEASE){
            g_KeyDPressed = false;
        }

        else if (action == GLFW_REPEAT){
            ;
        }
    }

}