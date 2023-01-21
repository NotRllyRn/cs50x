#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // checks if the # of arguments is more than 1 because we need a forensic image
    if (argc == 1)
    {
        return 1;
    }

    // opens the forensic image with fopen
    // then it checks if it was able to be opened
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        return 2;
    }

    // stores a new pointer for future reference
    // 2 int variables for the # of jpgs the program has made and what the last read of fread was
    // the name of the current jpgfile
    // and a buffer for the 512 bytes we are currently looking at
    FILE *img;
    int jpegs = 0, read = 512;
    char *jpgName = malloc(8);
    uint8_t buffer[512];

    // does a while loop until the last read did not read 512 bytes because its the end of the file
    while (read == 512)
    {
        // read the raw file
        // then checks for the first 4 bytes to be a certain hexadecimal number to detect if its a jpg file
        read = fread(buffer, sizeof(uint8_t), 512, raw);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it is, then it will check if we have already made a jpg file or not
            if (jpegs == 0)
            {
                // if its the first one then it will create a name for it and store it in a variable
                // then it will set the current img pointer to the new img in memory with fopen
                // then it will write to the img the 512 bytes and also update the count of jpgs
                sprintf(jpgName, "%03i.jpg", jpegs);
                img = fopen(jpgName, "w");
                fwrite(buffer, sizeof(uint8_t), read, img);
                jpegs++;
            }
            else
            {
                // if we are already writing to a jpg, then it will close that jpg first
                fclose(img);

                // then it will do all the other stuff mentioned above
                sprintf(jpgName, "%03i.jpg", jpegs);
                img = fopen(jpgName, "w");
                fwrite(buffer, sizeof(uint8_t), read, img);
                jpegs++;
            }
        }
        // else if the new 512 byte chunk of data is not a new jpg
        else
        {
            // we will check if we have already started on a jpg
            if (jpegs != 0)
            {
                // if we have then it will keep writing to that jpg because the jpg has more data to write down
                fwrite(buffer, sizeof(uint8_t), read, img);
            }
        }
    }

    // frees space from the space we allocated for the name
    free(jpgName);

    // closes both the img we are currently writing on and the forensics file.
    fclose(img);
    fclose(raw);
}