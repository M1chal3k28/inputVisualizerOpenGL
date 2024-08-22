#include "WindowHandler.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


WindowHandler::WindowHandler(int width, int height, const char* title) {
    this->height = 0;
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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left bottom
         0.5f, -0.5f, 0.0f, // right bottom
        -0.5f,  -0.5f + this->height * 2, 0.0f,  // left top
         0.5f,  -0.5f + this->height * 2, 0.0f,  // right top
    };

    unsigned int indices[] = {
        0, 2, 1,
        1, 2, 3,
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool WindowHandler::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void WindowHandler::setHeight(float height) {
    this->height = height;
}