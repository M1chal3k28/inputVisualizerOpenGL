#pragma once

/**
 * Header file for the Visualizer class.
 * 
 * This class provides functionality for visualizing spectrograms.
 */

#include <Spectrogram.hpp>
#include <WindowHandler.hpp>

/**
 * Class for visualizing spectrograms.
 * 
 * This class provides a single method for displaying the spectrum of a spectrogram.
 */
class Visualizer { 
public:
    /**
     * Displays the spectrum of the given spectrogram.
     * 
     * This method takes a pointer to a Spectrogram object and displays its spectrum.
     * 
     * @param spectrogram The spectrogram to display.
     */
    void displaySpectrum(Spectrogram* spectrogram, WindowHandler* windowHandler) const;
};