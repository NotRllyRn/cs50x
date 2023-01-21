#include "helpers.h"
#include <math.h>

// returns the lower value of x and y
int min(int x, int y)
{
    // returns x if x is less than y
    if (x < y)
    {
        return x;
    }

    // returns y if y is lower than x or if x is equal to y
    return y;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through the height pixels
    for (int row = 0; row < height; row++)
    {
        // loop through the width pixels
        for (int column = 0; column < width; column++)
        {
            // calculates the average of all 3 values and rounds it
            RGBTRIPLE pixel = image[row][column];

            float avr = (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0;
            int ravr = round(avr);

            // sets the new pixel colors
            image[row][column].rgbtRed = ravr;
            image[row][column].rgbtGreen = ravr;
            image[row][column].rgbtBlue = ravr;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loops through the height
    for (int row = 0; row < height; row++)
    {
        // loops through the width
        for (int column = 0; column < width; column++)
        {
            // get the local values to use
            RGBTRIPLE pixel = image[row][column];
            int red = pixel.rgbtRed;
            int green = pixel.rgbtGreen;
            int blue = pixel.rgbtBlue;

            // calculates the new colors of sepia
            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            float sepiaBlue = .272 * red + .534 * green + .131 * blue;

            // sets the new colors and makes sure to round them aswell and also caps them at 255
            image[row][column].rgbtRed = min(255, round(sepiaRed));
            image[row][column].rgbtGreen = min(255, round(sepiaGreen));
            image[row][column].rgbtBlue = min(255, round(sepiaBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through the height
    for (int row = 0; row < height; row++)
    {
        // calculate the middle that it will stop at and will start looping too that point
        int mid = width / 2;
        for (int column = 0; column < mid; column++)
        {
            //  calculates the pixel that we are swapping with
            int swapWith = width - column - 1;

            // stores a temp value so that we can swap the pixels
            RGBTRIPLE tmp = image[row][column];
            image[row][column] = image[row][swapWith];
            image[row][swapWith] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // makes another 2d array of all the color pixels which is basically a copy
    RGBTRIPLE copy[height][width];

    // loops through the height
    for (int row = 0; row < height; row++)
    {
        // loops through the width
        for (int column = 0; column < width; column++)
        {
            // makes an array of 9 to store the 8 pixels surround the current pixel and the pixel itself
            RGBTRIPLE box[9];
            // sets the first pixel to the current pixel
            box[0] = image[row][column];
            // does some arithmetic to find the correspoding 9 pixels and keeps track of how many pixels we have found so far which is set to 1
            int up = row - 1, down = row + 1, left = column - 1, right = column + 1, pixelsFound = 1;

            // checks if we can go up
            if (up >= 0)
            {
                // checks if we can go left and right
                if (left >= 0)
                {
                    // adds the pixel to the array and updates the count
                    box[pixelsFound] = image[up][left];
                    pixelsFound++;
                }
                if (right < width)
                {
                    // adds the pixel to the array and updates the count
                    box[pixelsFound] = image[up][right];
                    pixelsFound++;
                }
                // adds the pixel to the array and updates the count
                box[pixelsFound] = image[up][column];
                pixelsFound++;
            }
            // checks if we can go down
            if (down < height)
            {
                // checks if we can go left and right
                if (left >= 0)
                {
                    // adds the pixel to the array and updates the count
                    box[pixelsFound] = image[down][left];
                    pixelsFound++;
                }
                if (right < width)
                {
                    // adds the pixel to the array and updates the count
                    box[pixelsFound] = image[down][right];
                    pixelsFound++;
                }
                // adds the pixel to the array and updates the count
                box[pixelsFound] = image[down][column];
                pixelsFound++;
            }
            // checks if we can go left and right
            if (left >= 0)
            {
                // adds the pixel to the array and updates the count
                box[pixelsFound] = image[row][left];
                pixelsFound++;
            }
            if (right < width)
            {
                // adds the pixel to the array and updates the count
                box[pixelsFound] = image[row][right];
                pixelsFound++;
            }

            // sets new variables to get the average of all the 3 values
            float avrRed = 0;
            float avrGreen = 0;
            float avrBlue = 0;

            // loops through the array of pixels that we were able to find
            for (int i = 0; i < pixelsFound; i++)
            {
                // adds the values to the variables
                avrRed += box[i].rgbtRed;
                avrGreen += box[i].rgbtGreen;
                avrBlue += box[i].rgbtBlue;
            }

            // gets the average of those values
            avrRed /= (float) pixelsFound;
            avrGreen /= (float) pixelsFound;
            avrBlue /= (float) pixelsFound;

            // rounds the values and sets them to the copy array because we don't want the blur to be effecting the rest of the blur operation
            copy[row][column].rgbtRed = round(avrRed);
            copy[row][column].rgbtGreen = round(avrGreen);
            copy[row][column].rgbtBlue = round(avrBlue);
        }
    }
    // loops through the height
    for (int row = 0; row < height; row++)
    {
        // loops through the width
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = copy[row][column].rgbtRed;
            image[row][column].rgbtGreen = copy[row][column].rgbtGreen;
            image[row][column].rgbtBlue = copy[row][column].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // makes a copy table
    RGBTRIPLE copy[height][width];

    // loops through heigh
    for (int r = 0; r < height; r++)
    {
        // loops through width
        for (int c = 0; c < width; c++)
        {
            // creates 2 arrays to store gx and gy and the rgb values of both
            int Gx[] = {0, 0, 0};
            int Gy[] = {0, 0, 0};

            // checks if we can go down
            if (r + 1 < height)
            {
                // sets a new row variable
                // checks if we can go right or left
                int nr = r + 1;
                if (c + 1 < width)
                {
                    // sets a new column variable and changes all the gx and gy values
                    int nc = c + 1;
                    Gx[0] += image[nr][nc].rgbtRed;
                    Gx[1] += image[nr][nc].rgbtGreen;
                    Gx[2] += image[nr][nc].rgbtBlue;
                    Gy[0] += image[nr][nc].rgbtRed;
                    Gy[1] += image[nr][nc].rgbtGreen;
                    Gy[2] += image[nr][nc].rgbtBlue;
                }
                if (c - 1 >= 0)
                {
                    // sets a new column variable and changes all the gx and gy values
                    int nc = c - 1;
                    Gx[0] -= image[nr][nc].rgbtRed;
                    Gx[1] -= image[nr][nc].rgbtGreen;
                    Gx[2] -= image[nr][nc].rgbtBlue;
                    Gy[0] += image[nr][nc].rgbtRed;
                    Gy[1] += image[nr][nc].rgbtGreen;
                    Gy[2] += image[nr][nc].rgbtBlue;
                }
                // sets the gy values
                Gy[0] += image[nr][c].rgbtRed * 2;
                Gy[1] += image[nr][c].rgbtGreen * 2;
                Gy[2] += image[nr][c].rgbtBlue * 2;
            }
            // checks if we can go up
            if (r - 1 >= 0)
            {
                // sets a new row variable
                // checks if we can go right or left
                int nr = r - 1;
                if (c + 1 < width)
                {
                    // sets a new column variable and changes all the gx and gy values
                    int nc = c + 1;
                    Gx[0] += image[nr][nc].rgbtRed;
                    Gx[1] += image[nr][nc].rgbtGreen;
                    Gx[2] += image[nr][nc].rgbtBlue;
                    Gy[0] -= image[nr][nc].rgbtRed;
                    Gy[1] -= image[nr][nc].rgbtGreen;
                    Gy[2] -= image[nr][nc].rgbtBlue;
                }
                if (c - 1 >= 0)
                {
                    // sets a new column variable and changes all the gx and gy values
                    int nc = c - 1;
                    Gx[0] -= image[nr][nc].rgbtRed;
                    Gx[1] -= image[nr][nc].rgbtGreen;
                    Gx[2] -= image[nr][nc].rgbtBlue;
                    Gy[0] -= image[nr][nc].rgbtRed;
                    Gy[1] -= image[nr][nc].rgbtGreen;
                    Gy[2] -= image[nr][nc].rgbtBlue;
                }
                // sets the gy values
                Gy[0] += image[nr][c].rgbtRed * (-2);
                Gy[1] += image[nr][c].rgbtGreen * (-2);
                Gy[2] += image[nr][c].rgbtBlue * (-2);
            }
            // checks if we can go left
            if (c - 1 >= 0)
            {
                // sets the new column variable
                // and sets the gx variables
                int nc = c - 1;
                Gx[0] += image[r][nc].rgbtRed * -2;
                Gx[1] += image[r][nc].rgbtGreen * -2;
                Gx[2] += image[r][nc].rgbtBlue * -2;
            }
            // checks if we can go right
            if (c + 1 < width)
            {
                // sets the new column variable
                // and sets the gx variables
                int nc = c + 1;
                Gx[0] += image[r][nc].rgbtRed * 2;
                Gx[1] += image[r][nc].rgbtGreen * 2;
                Gx[2] += image[r][nc].rgbtBlue * 2;
            }

            // calculates the new pixel values using square roots and round
            int red = round(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0]));
            int green = round(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1]));
            int blue = round(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2]));

            // uses min function to cap the value at 255
            copy[r][c].rgbtRed = min(255, red);
            copy[r][c].rgbtGreen = min(255, green);
            copy[r][c].rgbtBlue = min(255, blue);
        }
    }

    // duplicaltes the copy table to the image table so that we get the updated image
    for (int row = 0; row < height; row++)
    {
        // loops through the width
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = copy[row][column].rgbtRed;
            image[row][column].rgbtGreen = copy[row][column].rgbtGreen;
            image[row][column].rgbtBlue = copy[row][column].rgbtBlue;
        }
    }
    return;
}