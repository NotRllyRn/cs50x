// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // creates an array of size of the header
    uint8_t header[HEADER_SIZE];

    // it will read and then write the headers
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // creates a buffer variable to store the current value
    int16_t buffer;
    // keeps repeating until it doesn't read anything from the stream
    while (fread(&buffer, sizeof(uint16_t), 1, input))
    {
        // multiplies the buffer by the factor
        buffer *= factor;
        // writes the buffer to the output file
        fwrite(&buffer, sizeof(uint16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
