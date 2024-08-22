#pragma once

// Contains loader for Shaders and GLFW3 and glad.c headers
#include <ShaderLoader.hpp>

class WindowHandler {
public:
    WindowHandler(int width, int height, const char* title);
    ~WindowHandler();
    GLFWwindow* getWindow();
    void render();
    bool windowShouldClose();
private:
    GLFWwindow* window;
    GLuint vertexbuffer;
    GLuint programId;
};