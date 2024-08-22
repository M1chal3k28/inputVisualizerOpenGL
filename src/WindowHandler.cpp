#include "WindowHandler.hpp"
#include <stdlib.h>
#include <stdio.h>

WindowHandler::WindowHandler(int width, int height, const char* title) {
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

    glClearColor(1.0f, 1.0f, 0.9f, 1.0f);

    // Create and compile our GLSL program from the shaders
    {
        ShaderLoader loader("./src/shader/vertex.glsl", "./src/shader/fragment.glsl");
        this->programId = loader.getProgram();
    }

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
}

WindowHandler::~WindowHandler() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* WindowHandler::getWindow() {
    return window;
}

void WindowHandler::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool WindowHandler::windowShouldClose() {
    return glfwWindowShouldClose(window);
}