#pragma once

// Contains loader for Shaders and GLFW3 and glad.c headers
#include <ShaderLoader.hpp>
#include <vector>

class WindowHandler {
public:
    WindowHandler(int width, int height, const char* title);
    ~WindowHandler();
    GLFWwindow* getWindow();
    void render();
    bool windowShouldClose();
    void setHeight(float height);
private:
    GLFWwindow* window;
    GLuint programId;
    unsigned int VBO, VAO, EBO;
    float height;
};