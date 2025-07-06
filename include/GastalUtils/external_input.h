#include <GLFW/glfw3.h>
#include "Camera/camera.h"
#include "Camera/LookAtCamera.hpp"
#include "Camera/FreeCamera.hpp"
#include "Camera/cameraTransition.h"
#include "Warhammer/Armies.hpp"
#include "Camera/camera.h"


double g_LastCursorPosX, g_LastCursorPosY;
bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false; 
bool g_MiddleMouseButtonPressed = false; 
extern bool g_ShowBoundingBoxes;

extern LookAtCamera g_lookAtCamera; 
extern FreeCamera g_freeCameraMiniatures; 
extern CameraTransition g_cameraTransition;
extern CameraTransition g_miniatureCameraShootTransition;
extern CameraTransition g_miniatureToMiniatureTransition;
extern FreeCamera g_freeCamera;
extern bool g_isMiniatureCamera; 
extern bool g_isLookAtUsed; 

extern bool g_KeyWPressed; // W key pressed (forward movement)
extern bool g_KeySPressed; // S key pressed (backward movement)
extern bool g_KeyAPressed; // Key A pressed (movement to the left)
extern bool g_KeyDPressed; // D key pressed (movement to the right)
extern bool g_KeySpacePressed; // Space key pressed (upward movement)

extern std::vector<std::vector<Miniature>> Armies;


// Callback function called whenever the user presses any of the mouse buttons
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // If the user has pressed the left mouse button, we store the
        // current cursor position in the variables g_LastCursorPosX and
        // g_LastCursorPosY.  We also set the variable
        // g_LeftMouseButtonPressed to true, so that we know that the user is
        // pressing the left button.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        // When the user releases the left mouse button, we update the
        // variable below to false.
        g_LeftMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // If the user has pressed the left mouse button, we store the
        // current cursor position in the variables g_LastCursorPosX and
        // g_LastCursorPosY.  We also set the variable
        // g_RightMouseButtonPressed to true, so that we know that the user is
        // pressing the left button.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_RightMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        // When the user releases the left mouse button, we update the
        // variable below to false.
        g_RightMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        // If the user has pressed the left mouse button, we store the
        // current cursor position in the variables g_LastCursorPosX and
        // g_LastCursorPosY.  We also set the variable
        // g_MiddleMouseButtonPressed to true, so that we know that the user is
        // pressing the left button.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_MiddleMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        // When the user releases the left mouse button, we update the
        // variable below to false.
        g_MiddleMouseButtonPressed = false;
    }
}

// Callback function called whenever the user moves the mouse cursor on
// above the OpenGL window.
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Below we do the following: if the left mouse button is
    // pressed, we compute how much the mouse has moved since the last
    // instant of time, and we use this movement to update the
    // parameters that define the position of the camera within the virtual scene.
    // Thus, we have the user being able to control the camera.

    if (g_LeftMouseButtonPressed)
    {
        // Moving the mouse cursor in x and y screen coordinates!
        float dx = xpos - g_LastCursorPosX;
        float dy = ypos - g_LastCursorPosY;
    

        if (g_isLookAtUsed){
            g_lookAtCamera.SetCameraTheta(g_lookAtCamera.GetCameraTheta() - 0.01f*dx);
            g_lookAtCamera.SetCameraPhi(g_lookAtCamera.GetCameraPhi() + 0.01f*dy);
        }

        else{ 
            if (g_isMiniatureCamera){
                g_freeCameraMiniatures.SetCameraTheta(g_freeCameraMiniatures.GetCameraTheta() - 0.01f*dx);
                g_freeCameraMiniatures.SetCameraPhi(g_freeCameraMiniatures.GetCameraPhi() - 0.01f*dy);
                
                // Updates theta of the miniatures too
                GetCurrentMiniature().facingTheta = g_freeCameraMiniatures.GetCameraTheta();
            }

            else{
                g_freeCamera.SetCameraTheta(g_freeCamera.GetCameraTheta() - 0.01f*dx);
                g_freeCamera.SetCameraPhi(g_freeCamera.GetCameraPhi() - 0.01f*dy);
            }
        }
        
        // In spherical coordinates, the phi angle must be between -pi/2 and +pi/2.
        float phimax = 3.141592f/2;
        float phimin = -phimax;

        if (g_isLookAtUsed){
            if (g_lookAtCamera.GetCameraPhi() > phimax)
                g_lookAtCamera.SetCameraPhi(phimax);

            if (g_lookAtCamera.GetCameraPhi() < phimin)
                g_lookAtCamera.SetCameraPhi(phimin);
        }

        else{ 
            if (g_isMiniatureCamera){
                if (g_freeCameraMiniatures.GetCameraPhi() > phimax)
                    g_freeCameraMiniatures.SetCameraPhi(phimax);

                if (g_freeCameraMiniatures.GetCameraPhi() < phimin)
                    g_freeCameraMiniatures.SetCameraPhi(phimax);
                
                // Updates theta of the miniatures too
                GetCurrentMiniature().facingTheta = g_freeCameraMiniatures.GetCameraTheta();
            }

            else{
                if (g_freeCamera.GetCameraPhi() > phimax)
                    g_freeCamera.SetCameraPhi(phimax);

                if (g_freeCamera.GetCameraPhi() < phimin)
                    g_freeCamera.SetCameraPhi(phimax);
            }
        }


        // We update the global variables to store the current position of the
        // cursor as the last known position of the cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_RightMouseButtonPressed)
    {
        // We update the global variables to store the current position of the
        // cursor as the last known position of the cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_MiddleMouseButtonPressed)
    {
        // We update the global variables to store the current position of the
        // cursor as the last known position of the cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }
}

// Callback function called whenever the user moves the mouse wheel.
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // We update the distance from the camera to the origin using the
    // movement of the "wheel", simulating a ZOOM.
    if (g_isLookAtUsed)
        g_lookAtCamera.SetCameraDistance(g_lookAtCamera.GetCameraDistance() - 0.1f * yoffset);

    const float verysmallnumber = std::numeric_limits<float>::epsilon();
    
    if (g_isLookAtUsed)
        if (g_lookAtCamera.GetCameraDistance() < verysmallnumber)
            g_lookAtCamera.SetCameraDistance(verysmallnumber);
    
}

// Definition of the function that will be called whenever the user presses any
// key on the keyboard. See http://www.glfw.org/docs/latest/input_guide.html#input_key
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    for (int i = 0; i < 10; ++i)
        if (key == GLFW_KEY_0 + i && action == GLFW_PRESS && mod == GLFW_MOD_SHIFT)
            std::exit(100 + i);



    // If the user presses the ESC key, we close the window.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);


    // If the user presses the L key, the boolean variable g_isLookAtUsed is set to true and a camera transition is initiated.
    if (key == GLFW_KEY_L && action == GLFW_PRESS && !g_isLookAtUsed) {
        g_isLookAtUsed = true;
        g_cameraTransition.isTransitioning = true;
        g_cameraTransition.t = 0.0f;
        
        // Position
        if (g_isMiniatureCamera) {
            g_cameraTransition.p0 = g_freeCameraMiniatures.GetPosition(); // current position
        } 

        else {
            g_cameraTransition.p0 = g_freeCamera.GetPosition(); // current position
        }
        
        g_cameraTransition.p3 = g_lookAtCamera.GetPosition(); // destination

        glm::vec4 dir = g_cameraTransition.p3 - g_cameraTransition.p0;
        g_cameraTransition.p1 = g_cameraTransition.p0 + 0.25f * dir;
        g_cameraTransition.p2 = g_cameraTransition.p0 + 0.75f * dir;

        // Direction
        if (g_isMiniatureCamera){
            g_cameraTransition.v0 = g_freeCameraMiniatures.GetViewVector();}
        
        else{
            g_cameraTransition.v0 = g_freeCamera.GetViewVector();}
        
        g_cameraTransition.v3 = g_lookAtCamera.GetViewVector();

        // Control points for the intermediate direction curve
        g_cameraTransition.v1 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.25f));
        g_cameraTransition.v2 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.75f));
    }

    // If the user presses the M key, the boolean variable g_isLookAtUsed is set to false and a camera transition is initiated to the miniature free camera.
    if (key == GLFW_KEY_M && action == GLFW_PRESS && g_isLookAtUsed) {
        g_isLookAtUsed = false;
        g_isMiniatureCamera = true; // Set the camera to be the miniature camera
        
        g_cameraTransition.isTransitioning = true;
        g_cameraTransition.t = 0.0f;
        glm::vec4 minPosition;
        float cameraTheta;

              
        // Free camera position values
        minPosition = GetCurrentMiniature().position;
        minPosition.y = minPosition.y + 1.5f;
        cameraTheta = GetCurrentMiniature().facingTheta;

         
        g_freeCameraMiniatures.SetPosition(minPosition);
        float cameraPhi = 0.0;
        float viewX = cos(cameraPhi)*sin(cameraTheta);
        float viewY = sin(cameraPhi);
        float viewZ = cos(cameraPhi)*cos(cameraTheta);
        g_freeCameraMiniatures.SetViewVector(glm::vec4(viewX, viewY, viewZ, 0.0f)); 

        // Position
        g_cameraTransition.p0 = g_lookAtCamera.GetPosition(); // current position
        g_cameraTransition.p3 = g_freeCameraMiniatures.GetPosition(); // destination

        glm::vec4 dir = g_cameraTransition.p3 - g_cameraTransition.p0;
        g_cameraTransition.p1 = g_cameraTransition.p0 + 0.25f * dir;
        g_cameraTransition.p2 = g_cameraTransition.p0 + 0.75f * dir;

        // Direction
        g_cameraTransition.v0 = g_lookAtCamera .GetViewVector();
        g_cameraTransition.v3 = g_freeCameraMiniatures.GetViewVector();

        // Intermediate control points for the direction curve
        g_cameraTransition.v1 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.25f));
        g_cameraTransition.v2 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.75f));

    }

    // If the user presses the F key, the boolean variable g_isLookAtUsed is set to false and a camera transition is initiated to the free camera.
    if (key == GLFW_KEY_F && action == GLFW_PRESS && g_isLookAtUsed){
        g_isLookAtUsed = false;
        g_isMiniatureCamera = false;

        g_cameraTransition.isTransitioning = true;
        g_cameraTransition.t = 0.0f;

        // Position
        g_cameraTransition.p0 = g_lookAtCamera.GetPosition(); // current position
        g_cameraTransition.p3 = g_freeCamera.GetPosition(); // destination

        glm::vec4 dir = g_cameraTransition.p3 - g_cameraTransition.p0;
        g_cameraTransition.p1 = g_cameraTransition.p0 + 0.25f * dir;
        g_cameraTransition.p2 = g_cameraTransition.p0 + 0.75f * dir;

        // Direction
        g_cameraTransition.v0 = g_lookAtCamera .GetViewVector();
        g_cameraTransition.v3 = g_freeCamera.GetViewVector();

        // Intermediate control points for the direction curve
        g_cameraTransition.v1 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.25f));
        g_cameraTransition.v2 = glm::normalize(glm::mix(g_cameraTransition.v0, g_cameraTransition.v3, 0.75f));

    }   

    // If the user presses the B key, a camera transition is initiated to the miniature camera for simulating a recoil.
    if (key == GLFW_KEY_B && action == GLFW_PRESS && g_isMiniatureCamera && !g_isLookAtUsed) {
        // Start the camera shoot animation
        g_miniatureCameraShootTransition.isTransitioning = true;
        g_miniatureCameraShootTransition.t = 0.0f;
        g_miniatureCameraShootTransition.duration = 1.0f;

        glm::vec4 originalView = g_freeCameraMiniatures.GetViewVector();
        
        // Set the control points for the Bézier curve
        g_miniatureCameraShootTransition.v0 = originalView;
        g_miniatureCameraShootTransition.v3 = originalView;
        glm::vec4 upward = glm::vec4(0.0f, 0.3f, 0.0f, 0.0f);
        g_miniatureCameraShootTransition.v1 = glm::normalize(originalView + upward);
        g_miniatureCameraShootTransition.v2 = glm::normalize(originalView + upward);
    }

    // W, A, S, D, SPACE keys for camera movement
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

    if (key == GLFW_KEY_SPACE){
        if (action == GLFW_PRESS){
            g_KeySpacePressed = true;
        }

        else if (action == GLFW_RELEASE){
            g_KeySpacePressed = false;
        }

        else if (action == GLFW_REPEAT){
            ;
        }
    }

    if (key == GLFW_KEY_J && action == GLFW_PRESS)
    {
        g_ShowBoundingBoxes = !g_ShowBoundingBoxes;
    }



}