#include <Visualizer.hpp>

/**
 * Displays the spectrum of the given spectrogram.
 * 
 * This function prints a visual representation of the spectrogram's output to the console.
 * The representation is a series of block characters, where the height of each block corresponds to the frequency value at that point in the spectrogram.
 * 
 * @param spectrogram The spectrogram to display.
 */
void Visualizer::displaySpectrum(Spectrogram* spectrogram) const {
    // Set the display size to 200 characters
    int dispSize = 200;
    
    // Print a carriage return to move the cursor to the beginning of the line
    printf("\r");

    // Loop over each character in the display
    for(int i = 0; i < dispSize; i++) {
        // Calculate the proportion of the spectrogram's size that this character represents
        double proportion = i / (double) dispSize;
        
        // Get the frequency value at this point in the spectrogram
        double freq = spectrogram->getOutput()[(int)(spectrogram->getStartIndex() + proportion * spectrogram->getSpectroSize())];

        // Print a block character whose height corresponds to the frequency value
        if(freq < 0.125) {
            printf("▁"); // lowest block
        } else if(freq < 0.25) {
            printf("▂"); // low block
        } else if(freq < 0.375) {
            printf("▃"); // medium-low block
        } else if(freq < 0.5) {
            printf("▄"); // medium block
        } else if(freq < 0.625) {
            printf("▅"); // medium-high block
        } else if(freq < 0.75) {
            printf("▆"); // high block
        } else if(freq < 0.875) {
            printf("▇"); // very high block
        } else {
            printf("█"); // highest block
        }
    }

    // Flush the output buffer to ensure the characters are printed immediately
    fflush(stdout);
}