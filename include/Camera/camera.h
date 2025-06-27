#pragma once
# include "Camera/LookAtCamera.hpp"
# include "Camera/FreeCamera.hpp"

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
float g_FreeCameraTheta = 0.0f; // Ângulo no plano ZX em relação ao eixo Z
float g_FreeCameraPhi = 0.0f;   // Ângulo em relação ao eixo Y
float g_FreeCameraDistance = 3.5f; // Distância da câmera para a origem

float g_LookAtCameraTheta = 0.0f; // Ângulo no plano ZX em relação ao eixo Z
float g_LookAtCameraPhi = 1.0f;   // Ângulo em relação ao eixo Y
float g_LookAtCameraDistance = 18.0f; // Distância da câmera para a origem

// Camera look at
LookAtCamera g_lookAtCamera(g_LookAtCameraTheta, g_LookAtCameraPhi, g_LookAtCameraDistance);

// Free camera
FreeCamera g_freeCameraMiniatures(g_FreeCameraTheta, g_FreeCameraPhi, g_FreeCameraDistance);

// Booleano que controla se a camera look-at está sendo utilizada
bool g_isLookAtUsed = true;

// Velocidade de movimentacao da camera livre e look-at
float g_speed_cam = 3.0f;
