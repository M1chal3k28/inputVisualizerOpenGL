// Header file for the AudioHandler class

#pragma once

// Include necessary header files
#include <portaudio.h>
#include <Spectrogram.hpp>
#include <Visualizer.hpp>
#include <WindowHandler.hpp>

// Define the AudioHandler class
class AudioHandler {
public:
    // Constructor
    AudioHandler();
    
    // Destructor
    ~AudioHandler();
    
    // Start the audio stream
    void startStream(Spectrogram* spectrogram, Visualizer* visualizer, WindowHandler* windowHandler);
    
    // Stop the audio stream
    void stopStream();
    
private:
    // Private member variables
    PaStream *stream;
    struct CallBackData {
        Spectrogram* spectrogram;
        Visualizer* visualizer;
        WindowHandler* windowHandler;
    };
    
    // Private member functions
    void checkErr(PaError err);
    static int paCallback(const void* inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void* userData);
    void initializeInputParameters(PaStreamParameters* inputParameters);
};