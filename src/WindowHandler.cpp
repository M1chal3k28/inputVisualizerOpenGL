#include "WindowHandler.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


WindowHandler::WindowHandler(int width, int height, const char* title, int barCount) {
    this->barCount = barCount;
    this->heights = std::vector<float>(barCount, -1.0f);
    this->indices = nullptr;
    this->vertices = nullptr;
    this->window = nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        exit(1);
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        exit(-1);
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create and compile our GLSL program from the shaders
    {
        ShaderLoader loader("../src/shader/vertex.glsl", "../src/shader/fragment.glsl");
        this->programId = loader.getProgram();
        glUseProgram(this->programId);
    }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
}

WindowHandler::~WindowHandler() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* WindowHandler::getWindow() {
    return window;
}

void WindowHandler::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(this->programId);

    int ind = 0;
    for(int i = 0; i < 20; i++) {
        Bar bar({
            -1.0f + i / 10.0f, -1.1f, 0.0f,  // left bottom 
            -1.0f + i / 10.0f, -1.0f + heights[ind], 0.0f,  // left top
            (-0.9f - 0.1f / barCount) + i / 10.0f, -1.1f, 0.0f,  // right bottom
            (-0.9f - 0.1f / barCount) + i / 10.0f, -1.0f + heights[ind], 0.0f   // right top
        },
        {
            1, 0, 3,
            0, 2, 3
        });
        this->renderBar(&bar);
        ind++;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool WindowHandler::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void WindowHandler::renderBar(Bar * bar) {
    // Allocate memory for drawing the bar
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, bar->getVertices().size() * sizeof(float), bar->getVertices().data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bar->getIndices().size() * sizeof(unsigned int), bar->getIndices().data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Clear
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void WindowHandler::setHeights(std::vector<float> heights) {
    this->heights = heights;
}

int WindowHandler::getBarCount() {
    return barCount;
}