#include <cmath>
#include <cstdio>
#include <cstdlib>


#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// OpenGL library headers
#include <glad/glad.h>   
#include <GLFW/glfw3.h>  

// GLM library headers: creating matrices and vectors.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers with camera-related settings
#include "Camera/camera.h"
#include "Camera/LookAtCamera.hpp"
#include "Camera/FreeCamera.hpp"
#include "Camera/cameraTransition.h"
#include "Camera/freeCamMove.h"

#include "Warhammer/Miniatures.hpp"
#include "Warhammer/Armies.hpp"
#include "Warhammer/Structures.hpp"

// Header with the utilities of the labs made by Prof. Gastal
// and completed in the lab activities
#include "GastalUtils/includes.h"

#include "Collision/collisions.h"

// The virtual scene is a list of named objects, stored in a dictionary
// (map).  See inside the BuildTrianglesAndAddToVirtualScene() function how
// objects are included inside the g_VirtualScene variable, and see in the main() function how
// these are accessed.
std::map<std::string, SceneObject> g_VirtualScene;

// Stack that will store the modeling matrices.
std::stack<glm::mat4>  g_MatrixStack;

// Variable that controls the type of projection used: perspective or orthographic.
bool g_UsePerspectiveProjection = true;

// Variable that controls whether informative text will be shown on the screen.
bool g_ShowInfoText = true;

int main(int argc, char* argv[])
{
    InitializeArmies(); //Inicialize the armies with the default miniatures
    InitializeStructures(); //Initialize the structures in the scene

    // We have initialized the GLFW library, used to create a window of the
    // operating system, where we can render with OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Define the callback for printing GLFW errors in the terminal
    glfwSetErrorCallback(ErrorCallback);

    // Use OpenGL version 3.3 (or higher)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Use the "core" profile, i.e. we will only use the
    // modern OpenGL functions.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Warmemer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Callbacks for keyboard, mouse, cursor position, and scroll events.
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // We define the callback function that will be called whenever the window is
    // resized, thereby changing the size of the framebuffer
    // (the memory region where the image pixels are stored).
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    FramebufferSizeCallback(window, 800, 600); 

    // We print information about the system's GPU in the terminal
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    LoadShadersFromFiles();

    // Load the textures used in the scene
    LoadTextureImage("../../data/steel_texture.jpg");      
    LoadTextureImage("../../data/rustedSteel.jpg");       
    LoadTextureImage("../../data/map.jpg");       
    LoadTextureImage("../../data/concrete.jpg");       


    // We build the representation of geometric objects through triangle meshes
    ObjModel dreadmodel("../../data/dreadUnified.obj");
    ComputeNormals(&dreadmodel);
    BuildTrianglesAndAddToVirtualScene(&dreadmodel);

    ObjModel deamonmodel("../../data/orcMechUnified.obj");
    ComputeNormals(&deamonmodel);
    BuildTrianglesAndAddToVirtualScene(&deamonmodel);

    ObjModel planemodel("../../data/plane.obj");
    ComputeNormals(&planemodel);
    BuildTrianglesAndAddToVirtualScene(&planemodel);

    ObjModel ruinmodel("../../data/wall.obj");
    ComputeNormals(&ruinmodel);
    BuildTrianglesAndAddToVirtualScene(&ruinmodel);

    if ( argc > 1 )
    {
        ObjModel model(argv[1]);
        BuildTrianglesAndAddToVirtualScene(&model);
    }

    // Initialize the code for rendering text.
    TextRendering_Init();

    // Enable the Z-buffer.
    glEnable(GL_DEPTH_TEST);

    // We enable Backface Culling.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    // Previous time for delta time calculation
    float prev_time = (float)glfwGetTime();
    
    while (!glfwWindowShouldClose(window))
    {

        //           R     G     B     A
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // We "paint" all the pixels in the framebuffer with the color defined above,
        // and we also reset all the pixels in the Z-buffer (depth buffer)..
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // We ask the GPU to use the GPU program created above (containing
        // the vertex and fragment shaders).
        glUseProgram(g_GpuProgramID);

        // Update delta time
        float current_time = (float)glfwGetTime();
        float delta_t = current_time - prev_time;
        prev_time = current_time;

        // Updates the LookAt camera or the free camera, depending on the current state
        if (g_cameraTransition.isTransitioning) {
            
            // Updates the camera transition, if it is in progress
            g_cameraTransition.t += delta_t / g_cameraTransition.duration;
            
            glm::vec4 interpolatedPosition = BezierCubicPos();
            glm::vec4 interpolatedView = BezierCubicView();
            
            
            if (g_isLookAtUsed) {
                g_lookAtCamera.SetPosition(interpolatedPosition);
                g_lookAtCamera.SetViewVector(interpolatedView);
            } 


            else {
                g_freeCameraMiniatures.SetPosition(interpolatedPosition);
                g_freeCameraMiniatures.SetViewVector(interpolatedView);
            }
        }


        // Free camera movement with the miniatures
        if (g_isLookAtUsed == false)
        {
            if (Armies[0][0].MiniatureMove(delta_t, Armies)) {
                FreeCamMove(delta_t);
            }
        }


        glm::mat4 view;
        
        if (g_isLookAtUsed){
            view = g_lookAtCamera.GetMatrixCameraView(); // LookAt camera view matrix
        }

        else{
            view = g_freeCameraMiniatures.GetMatrixCameraView(); // Free camera view matrix
        }
        

        // Now we compute the Projection matrix.
        glm::mat4 projection;

        float nearplane = -0.1f;  // Near plane position
        float farplane  = -100.0f; // Far plane position

        // Perspective Projection.
        float field_of_view = 3.141592 / 3.0f;
        projection = g_freeCameraMiniatures.GetMatrixPerspective(nearplane, farplane, field_of_view, g_ScreenRatio);
        
        // We send the "view" and "projection" matrices to the video card
        // (GPU). See the "shader_vertex.glsl" file, where these are
        // effectively applied to all points.
        glUniformMatrix4fv(g_view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
        glUniformMatrix4fv(g_projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));

        #define SPHERE 0
        #define PLANE  1
        #define DREAD 2
        #define ORCMECH 3
        #define RUINS 4

        DrawArmies(); //Draws the armies in the scene
        DrawStructures(); //Draws the structures in the scene

        glm::mat4 model = Matrix_Identity(); 

        model = Matrix_Translate(0.0f, -0.4f, 0.0f) *
                Matrix_Scale(20.0f, 0.01f, 12.0f);
        glUniformMatrix4fv(g_model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
        glUniform1i(g_object_id_uniform, PLANE); // Plane
        DrawVirtualObject("the_plane");

        // We print information on the screen about the number of frames rendered
        // per second (frames per second).
        TextRendering_ShowFramesPerSecond(window);

        // The framebuffer where OpenGL performs the rendering operations is not
        // the same as the one being shown to the user, otherwise
        // it would be possible to see artifacts known as "screen tearing". The
        // call below swaps the buffers, showing the user
        // everything that has been rendered by the functions above.
        // See the link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics
        glfwSwapBuffers(window);

        // We check with the operating system if there has been any interaction from the
        // user (keyboard, mouse, ...). If so, the callback functions
        // previously defined using glfwSet*Callback() will be called
        // by the GLFW library.
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
// set makeprg=cd\ ..\ &&\ make\ run\ >/dev/null
// vim: set spell spelllang=pt_br :

