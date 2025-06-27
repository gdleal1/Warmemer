#include <GLFW/glfw3.h>
#include <cstdio>

float g_ScreenRatio = 0;


// Definition of the function that will be called whenever the window of the
// operating system is resized, consequently changing the size of the
// framebuffer (memory region where the image pixels are stored).
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // We indicate that we want to render in the entire region of the framebuffer. The
    // function "glViewport" defines the mapping of "normalized device
    // coordinates" (NDC) to "pixel coordinates".  This is the
    // "Screen Mapping" or "Viewport Mapping" operation seen in class ({+ViewportMapping2+}).
    glViewport(0, 0, width, height);

    // We have also updated the ratio that defines the proportion of the window (width /
    // height), which will be used to define the projection matrices,
    // so that no distortions occur during the "Screen Mapping" process
    // above, when NDC is mapped to pixel coordinates. See slides 205-215 of the document Aula_09_Projecoes.pdf.
    //
    // The cast to float is necessary because integers are rounded when
    // they are divided!
    g_ScreenRatio = (float)width / height;
}

// Define the callback for printing GLFW errors in the terminal
void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}