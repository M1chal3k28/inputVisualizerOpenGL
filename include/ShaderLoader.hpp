#pragma once 

// Header file for the ShaderLoader class
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

enum ErrType { SHADER, PROGRAM };

// Define the ShaderLoader class
class ShaderLoader {
public:
    // Constructor and destructor
    ShaderLoader(const char* vertex_file_path, const char* fragment_file_path);
    ~ShaderLoader();
    // Getters
    GLuint getProgram();
private:
    // Private member variables
    GLuint program;
    // Private member functions
    void checkCompileErrors(GLuint shader, ErrType type);
};