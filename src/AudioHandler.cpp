#include <AudioHandler.hpp>
#include <cmath>
#include <iostream>
#include <future>
#include <vector>

/**
 * Constructor for the AudioHandler class.
 * 
 * This constructor initializes the PortAudio library.
 */
AudioHandler::AudioHandler() : stream(nullptr) {
    PaError err = Pa_Initialize();
    checkErr(err);
}

/**
 * Destructor for the AudioHandler class.
 * 
 * This destructor terminates the PortAudio library.
 */
AudioHandler::~AudioHandler() {
    PaError err = Pa_Terminate();
    checkErr(err);
}

/**
 * Callback function for the PortAudio stream.
 * 
 * This function is called by PortAudio to process audio data.
 * It performs an FFT on the input buffer and displays the resulting spectrum.
 * 
 * @param inputBuffer Pointer to the input audio buffer.
 * @param outputBuffer Pointer to the output audio buffer (not used).
 * @param framesPerBuffer The number of frames in the buffer.
 * @param timeInfo Pointer to time information (not used).
 * @param statusFlags Flags indicating the status of the stream (not used).
 * @param userData Pointer to user data (a CallBackData object containing a Spectrogram and Visualizer).
 * @return paContinue to continue the stream.
 */
int AudioHandler::paCallback(
    const void* inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData
) {
    CallBackData* callbackData = (CallBackData*)userData;
    float* in = (float*)inputBuffer;
    // To avoid errors
    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    std::vector<std::future<void>> futures;

    futures.push_back(std::async(std::launch::async, [=]() {
        callbackData->spectrogram->performFFT(in);
        // callbackData->spectrogram->smoothOutput(5);
        callbackData->visualizer->displaySpectrum(callbackData->spectrogram, callbackData->windowHandler);
    }));

    return paContinue;
}

/**
 * Checks the PortAudio error code and prints an error message if it is not paNoError.
 * 
 * @param err The PortAudio error code to check.
 */
void AudioHandler::checkErr(PaError err) {
    if (err != paNoError) {
        printf("Error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

/**
 * Initializes the input parameters for the PortAudio stream.
 * 
 * @param inputParameters Pointer to the input parameters structure to initialize.
 */
void AudioHandler::initializeInputParameters(PaStreamParameters* inputParameters) {
    inputParameters->device = Pa_GetDefaultInputDevice();
    if (inputParameters->device == paNoDevice) {
        fprintf(stderr, "Error: No default input device.\n");
        exit(EXIT_FAILURE);
    }
    inputParameters->channelCount = NUM_CHANNELS;
    inputParameters->sampleFormat = paFloat32;
    inputParameters->suggestedLatency = Pa_GetDeviceInfo(
        inputParameters->device
    )->defaultLowInputLatency;
    inputParameters->hostApiSpecificStreamInfo = NULL;
}

/**
 * Starts the PortAudio stream.
 * 
 * @param spectrogram Pointer to the Spectrogram object to use.
 * @param visualizer Pointer to the Visualizer object to use.
 */
void AudioHandler::startStream(
    Spectrogram* spectrogram, 
    Visualizer* visualizer,
    WindowHandler* windowHandler
) {
    PaStreamParameters inputParameters;
    initializeInputParameters(&inputParameters);

    PaError err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        paCallback,
        new CallBackData {
            spectrogram,
            visualizer,
            windowHandler
        }
    );
    checkErr(err);

    err = Pa_StartStream(stream);
    checkErr(err);
}

/**
 * Stops the PortAudio stream.
 * 
 * This function stops the stream and then closes it.
 */
void AudioHandler::stopStream() {
    // Stop the stream
    PaError err = Pa_StopStream(stream);
    checkErr(err);

    // Close the stream
    err = Pa_CloseStream(stream);
    checkErr(err);
}