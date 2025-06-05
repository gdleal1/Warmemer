#pragma once
# include "GastalUtils/LookAtCamera.hpp"
# include "GastalUtils/FreeCamera.hpp"

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
float g_CameraTheta = 0.0f; // Ângulo no plano ZX em relação ao eixo Z
float g_CameraPhi = 0.0f;   // Ângulo em relação ao eixo Y
float g_CameraDistance = 3.5f; // Distância da câmera para a origem

// Camera look at
LookAtCamera g_lookAtCamera(g_CameraTheta, g_CameraPhi, g_CameraDistance);

// Free camera
FreeCamera g_freeCamera(g_CameraTheta, g_CameraPhi, g_CameraDistance);

// Booleano que controla se a camera look-at está sendo utilizada
bool g_isLookAtUsed = true;

// Velocidade de movimentacao da camera livre
float g_speed_cam = 1.0f;
