cmake_minimum_required(VERSION 3.5.0)
project(musicVisualizer VERSION 0.1.0 LANGUAGES C CXX)

add_executable(musicVisualizer 
    main.cpp
    src/Spectrogram.cpp
    src/Visualizer.cpp
    src/AudioHandler.cpp
)
include_directories(musicVisualizer ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(musicVisualizer portaudio rt asound jack pthread fftw3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
