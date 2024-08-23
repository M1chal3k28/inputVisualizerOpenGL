#include <Visualizer.hpp>
#include <Bar.hpp>
#include <iostream>
#include <vector>

/**
 * Displays the spectrum of the given spectrogram.
 * 
 * This function prints a visual representation of the spectrogram's output to the console.
 * The representation is a series of block characters, where the height of each block corresponds to the frequency value at that point in the spectrogram.
 * 
 * @param spectrogram The spectrogram to display.
 */
void Visualizer::displaySpectrum(Spectrogram* spectrogram, WindowHandler* windowHandler) const {
    // Set the display size to 200 characters
    int dispSize = windowHandler->getBarCount();
    std::vector<float> heights;

    // Loop over each character in the display
    for(int i = 0; i < dispSize; i++) {
        // Calculate the proportion of the spectrogram's size that this character represents
        double proportion = i / (double) dispSize;
        
        // Get the frequency value at this point in the spectrogram
        double freq = spectrogram->getOutput()[(int)(spectrogram->getStartIndex() + proportion * spectrogram->getSpectroSize())];
        heights.push_back(std::fabs((float)freq) * 2.0f);
    }
    
    windowHandler->setHeights(heights);
}