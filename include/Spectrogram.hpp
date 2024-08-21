// Header file for the Spectrogram class

#pragma once

// Include necessary header files
#include <fftw3.h>  // FFTW library for fast Fourier transforms
#include <stdlib.h>  // Standard library for dynamic memory allocation
#include <stdio.h>  // Standard library for input/output operations
#include <cmath>  // Standard library for mathematical functions

// Define constants
#define SAMPLE_RATE 44100.00  // Sample rate of the audio signal
#define FRAMES_PER_BUFFER 512  // Number of frames per buffer
#define NUM_CHANNELS 2  // Number of audio channels (stereo)

#define SPECTRO_FREQ_START 20  // Starting frequency of the spectrogram
#define SPECTRO_FREQ_END 20000  // Ending frequency of the spectrogram

// Define the Spectrogram class
class Spectrogram {
public:
    // Constructor
    Spectrogram(int bufferSize);  // Initialize the spectrogram with a buffer size
    
    // Destructor
    ~Spectrogram();  // Release resources allocated by the spectrogram
    
    // Perform a fast Fourier transform on the input data
    void performFFT(const float * input);  // Input data for the FFT
    
    // Get the output of the spectrogram
    double* getOutput();  // Output data of the spectrogram
    
    // Get the starting index of the spectrogram
    int getStartIndex();  // Starting index of the spectrogram
    
    // Get the size of the spectrogram
    int getSpectroSize();  // Size of the spectrogram
    
private:
    // Private member variables
    int bufferSize;  // Buffer size of the spectrogram
    double* in;  // Input data for the FFT
    double* out;  // Output data of the FFT
    fftw_plan plan;  // FFT plan for the FFTW library
    int startIndex;  // Starting index of the spectrogram
    int spectroSize;  // Size of the spectrogram
};