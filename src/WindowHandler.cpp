#include "WindowHandler.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


WindowHandler::WindowHandler(int width, int height, const char* title, int barCount) {
    this->barCount = barCount;
    this->heights = std::vector<float>(barCount + 1, -1.0f);
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

    printf("Creating window\n");
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

    for(float i = 0; i <= barCount; i++) {
        // Calculate the position of the bar
        float xLeft = -1.0f + i / (barCount / 2.0f);
        float xRight = (-1.0f - 1 / (barCount / 2.0f)) + i / (barCount / 2.0f);
        float height = std::max(std::min(-1.0f + heights[i], 1.0f), -0.995f);
        
        // Create a Bar object
        Bar bar({
            xLeft, -1.0f, 0.0f,    // left bottom 
            xLeft, height, 0.0f,   // left top
            xRight, -1.0f, 0.0f,   // right bottom
            xRight, height, 0.0f   // right top
        },
        {
            0, 1, 2, // Triangle 1
            2, 1, 3  // Triangle 2
        });
        this->renderBar(&bar);
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

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

std::vector<float>& WindowHandler::getHeights() {
    return this->heights;
}

int WindowHandler::getBarCount() {
    return barCount;
}