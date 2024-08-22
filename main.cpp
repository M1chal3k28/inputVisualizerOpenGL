// Include necessary header files for the Visualizer, Spectrogram, and AudioHandler classes
#include <Visualizer.hpp>
#include <Spectrogram.hpp>
#include <AudioHandler.hpp>
#include <WindowHandler.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    // Create a WindowHandler object
    WindowHandler windowHandler(WINDOW_WIDTH, WINDOW_HEIGHT, "Music Visualizer");

    // Create a Spectrogram object with a buffer size of FRAMES_PER_BUFFER
    Spectrogram spectrogram(FRAMES_PER_BUFFER);
    
    // Create a Visualizer object
    Visualizer visualizer;
    
    // Create an AudioHandler object
    AudioHandler audioHandler;

    // Start the audio stream, passing the spectrogram and visualizer objects as arguments
    audioHandler.startStream(&spectrogram, &visualizer, &windowHandler);
    
    // Main loop
    while (!windowHandler.windowShouldClose())
    {
        // Swap buffers
        windowHandler.render();
    }
    
    // Stop the audio stream
    audioHandler.stopStream();
    
    // Return an exit status of success
    return EXIT_SUCCESS;
}