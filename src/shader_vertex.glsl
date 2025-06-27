#version 330 core

// Vertex attributes received as input ("in") by the Vertex Shader.
// See the BuildTrianglesAndAddToVirtualScene() function in "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

// Matrices computed in the C++ code and sent to the GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Vertex attributes that will be generated as output by the Vertex Shader.
// ** These will be interpolated by the rasterizer! ** thus generating values
// for each fragment, which will be received as input by the Fragment
// Shader. See the file "shader_fragment.glsl".
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;

void main()
{
    // The gl_Position variable defines the final position of each vertex
    // MANDATORY in "normalized device coordinates" (NDC), where each
    // coefficient will be between -1 and 1 after division by w.
    // See {+NDC2+}.
    //
    // The code in "main.cpp" defines the vertices of the models in coordinates
    // local to each model (array model_coefficients). Below, we use
    // modeling operations, camera definition, and projection, to compute
    // the final coordinates in NDC (gl_Position variable). After executing
    // this Vertex Shader, the video card (GPU) will do the division by W.

    gl_Position = projection * view * model * model_coefficients;

    // As the variables above (type vec4) are vectors with 4 coefficients,
    // it is also possible to access and modify each coefficient independently
    //. These are indexed by the names x, y, z, and w (in that
    // order, i.e. 'x' is the first coefficient, 'y' is the second, ...):
    //
    // gl_Position.x = model_coefficients.x;
    // gl_Position.y = model_coefficients.y;
    // gl_Position.z = model_coefficients.z;
    // gl_Position.w = model_coefficients.w;
    //

    // Now we define other attributes of the vertices that will be interpolated by the
    // rasterizer to generate unique attributes for each fragment generated.

    // Position of the current vertex in the global (World) coordinate system.
    position_world = model * model_coefficients;

    // Position of the current vertex in the model's local coordinate system.
    position_model = model_coefficients;

    // Normal of the current vertex in the global coordinate system (World).
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // Texture coordinates obtained from the OBJ file (if they exist!)
    texcoords = texture_coefficients;
}

