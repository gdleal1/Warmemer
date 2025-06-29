#include "GastalUtils/shaderUtil.h"

GLuint g_GpuProgramID = 0;
GLint g_model_uniform;
GLint g_view_uniform;
GLint g_projection_uniform;
GLint g_object_id_uniform;
GLint g_bbox_min_uniform;
GLint g_bbox_max_uniform;

GLuint g_NumLoadedTextures = 0;

// Auxiliary function, used by the two functions above. Loads GPU code from
// a GLSL file and compiles it.
void LoadShader(const char* filename, GLuint shader_id)
{
    // We read the text file indicated by the variable "filename"
    // and place its contents in memory, pointed to by the variable
    // "shader_string".
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    // Defines the GLSL shader code, contained in the string “shader_string”
    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    // Compiles the GLSL shader code (at runtime)
    glCompileShader(shader_id);

    // Check if any errors or warnings occurred during compilation
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    // We allocate memory to store the compilation log.
    // The "new" call in C++ is equivalent to C's "malloc()".
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    // Prints any compilation errors or warnings in the terminal
    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    
    delete [] log;
}

// Load a Vertex Shader from a GLSL file. See definition of LoadShader() below.
GLuint LoadShader_Vertex(const char* filename)
{
    // We have created an identifier (ID) for this shader, stating that it
    // will be applied to the vertices.
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    // Load and compile the shader
    LoadShader(filename, vertex_shader_id);

    // Returns the ID generated above
    return vertex_shader_id;
}

// Load a Fragment Shader from a GLSL file. See definition of LoadShader() below.
GLuint LoadShader_Fragment(const char* filename)
{
    // We have created an identifier (ID) for this shader, stating that it
    // will be applied to the fragments.
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Load and compile the shader
    LoadShader(filename, fragment_shader_id);

    // Returns the ID generated above
    return fragment_shader_id;
}

// This function creates a GPU program, which must contain a
// Vertex Shader and a Fragment Shader.
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    // We create an identifier (ID) for this GPU program
    GLuint program_id = glCreateProgram();

    // Definition of the two GLSL shaders to be executed by the program
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    // Linking the above shaders to the program
    glLinkProgram(program_id);

    // We check if any errors occurred during linking
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    // Prints any linking errors in the terminal
    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        // We allocate memory to store the compilation log.
        // The "new" call in C++ is equivalent to C's "malloc()".
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";

        
        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

    
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

   
    return program_id;
}


// Function that loads an image to be used as a texture
void LoadTextureImage(const char* filename)
{
    printf("Carregando imagem \"%s\"... ", filename);

    // First we read the disk image
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

    if ( data == NULL )
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }

    printf("OK (%dx%d).\n", width, height);

    // Now we create objects on the GPU with OpenGL to store the texture
    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now we send the image read from the disk to the GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint textureunit = g_NumLoadedTextures;
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(textureunit, sampler_id);

    stbi_image_free(data);

    g_NumLoadedTextures += 1;
}


// Function that loads the vertex and fragment shaders that will be
// used for rendering. See slides 180-200 of the document Aula_03_Rendering_Pipeline_Grafico.pdf.
void LoadShadersFromFiles()
{
    GLuint vertex_shader_id = LoadShader_Vertex("../../src/shader_vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("../../src/shader_fragment.glsl");

    // Delete the previous GPU program, if it exists.
    if ( g_GpuProgramID != 0 )
        glDeleteProgram(g_GpuProgramID);

    // We create a GPU program using the shaders loaded above.
    g_GpuProgramID = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

    // We look up the address of the variables defined within the Vertex Shader.
    // We will use these variables to send data to the video card
    // (GPU)! See the files "shader_vertex.glsl" and "shader_fragment.glsl".
    g_model_uniform      = glGetUniformLocation(g_GpuProgramID, "model"); 
    g_view_uniform       = glGetUniformLocation(g_GpuProgramID, "view"); 
    g_projection_uniform = glGetUniformLocation(g_GpuProgramID, "projection"); 
    g_object_id_uniform  = glGetUniformLocation(g_GpuProgramID, "object_id"); 
    g_bbox_min_uniform   = glGetUniformLocation(g_GpuProgramID, "bbox_min");
    g_bbox_max_uniform   = glGetUniformLocation(g_GpuProgramID, "bbox_max");

    // Variables in “shader_fragment.glsl” for accessing texture images
    glUseProgram(g_GpuProgramID);
    glUniform1i(glGetUniformLocation(g_GpuProgramID, "TextureImage0"), 0);
    glUniform1i(glGetUniformLocation(g_GpuProgramID, "TextureImage1"), 1);
    glUniform1i(glGetUniformLocation(g_GpuProgramID, "TextureImage2"), 2);
    glUniform1i(glGetUniformLocation(g_GpuProgramID, "TextureImage3"), 3);
    glUniform1i(glGetUniformLocation(g_GpuProgramID, "TextureImage4"), 4);
    glUseProgram(0);
}