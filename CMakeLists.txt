cmake_minimum_required(VERSION 3.21.0)
project(musicVisualizer VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(musicVisualizer 
    main.cpp
    src/Spectrogram.cpp
    src/Visualizer.cpp
    src/AudioHandler.cpp
    src/WindowHandler.cpp
    src/ShaderLoader.cpp
    src/Bar.cpp
    src/glad/glad.c
)
include_directories(musicVisualizer ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(musicVisualizer portaudio rt asound jack pthread fftw3 glfw3 OpenGL::GL GLEW)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
