#pragma once

// Contains loader for Shaders and GLFW3 and glad.c headers
#include <ShaderLoader.hpp>
#include <Bar.hpp>

class WindowHandler {
public:
    WindowHandler(int width, int height, const char* title, int barCount);
    ~WindowHandler();
    GLFWwindow* getWindow();
    void render();
    bool windowShouldClose();
    void renderBar(Bar * bar);
    void setHeights(std::vector<float> heights);
    int getBarCount();
private:
    GLFWwindow* window;
    GLuint programId;
    unsigned int VBO, VAO, EBO;
    float height;

    // for rendering
    unsigned int * indices;
    float * vertices;
    std::vector<float> heights;
    int barCount;
};