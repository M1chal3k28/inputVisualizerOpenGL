// Include necessary header files for the Visualizer, Spectrogram, and AudioHandler classes
#include <Visualizer.hpp>
#include <Spectrogram.hpp>
#include <AudioHandler.hpp>

int main() {
    // Create a Spectrogram object with a buffer size of FRAMES_PER_BUFFER
    Spectrogram spectrogram(FRAMES_PER_BUFFER);
    
    // Create a Visualizer object
    Visualizer visualizer;
    
    // Create an AudioHandler object
    AudioHandler audioHandler;

    // Start the audio stream, passing the spectrogram and visualizer objects as arguments
    audioHandler.startStream(&spectrogram, &visualizer);
    
    // Pause the program for 10 seconds using the Pa_Sleep function
    Pa_Sleep(10000);
    
    // Stop the audio stream
    audioHandler.stopStream();
    
    // Return an exit status of success
    return EXIT_SUCCESS;
}