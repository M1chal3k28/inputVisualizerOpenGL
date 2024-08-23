#include <Spectrogram.hpp>
#include <vector>
#include <iostream>

// Constructor for the Spectrogram class
Spectrogram::Spectrogram(int bufferSize) : bufferSize(bufferSize) {
    // Allocate memory for the input and output arrays
    in = (double*)malloc(sizeof(double) * bufferSize);
    out = (double*)malloc(sizeof(double) * bufferSize);

    // Check if memory allocation was successful
    if(in == NULL || out == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    printf("Initializing FFT\n");
    // Create a plan for the FFT
    plan = fftw_plan_r2r_1d(
        bufferSize,
        in,
        out,
        FFTW_DHT,
        FFTW_EXHAUSTIVE
    );

    // Calculate the starting index and size of the spectrogram
    double sampleRatio = bufferSize / SAMPLE_RATE;
    startIndex = std::ceil(sampleRatio * SPECTRO_FREQ_START);
    spectroSize = std::min(
        std::ceil(sampleRatio * SPECTRO_FREQ_END),
        bufferSize / 2.0
    ) - startIndex;
}

// Destructor for the Spectrogram class
Spectrogram::~Spectrogram() {
    // Destroy the FFT plan and free the allocated memory
    fftw_destroy_plan(plan);
    free(in);
    free(out);
}

// Perform a fast Fourier transform on the input data
void Spectrogram::performFFT(const float * input) {
    double maxVal = 0.0;
    for(int i = 0; i < bufferSize; i+=2) {
        in[i] = (double)input[i];
    }
    fftw_execute(plan);
}

void Spectrogram::smoothOutput(int windowSize) {
    std::vector<double> smoothed(spectroSize, 0.0);
    for(int i = 0; i < spectroSize; i++) {
        int start = std::max(0, i - windowSize);
        int end = std::min(spectroSize - 1, i + windowSize);
        for(int j = start; j <= end; j++) {
            smoothed[i] += out[j];
        }
        smoothed[i] /= (end - start + 1);
    }
    std::copy(smoothed.begin(), smoothed.end(), out);
}


// Get the output of the spectrogram
double* Spectrogram::getOutput() {
    // Return the output array
    return out;
}

// Get the starting index of the spectrogram
int Spectrogram::getStartIndex() {
    // Return the starting index
    return startIndex;
}

// Get the size of the spectrogram
int Spectrogram::getSpectroSize() {
    // Return the size of the spectrogram
    return spectroSize;
}