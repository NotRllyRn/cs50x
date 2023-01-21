#include <stdio.h>
#include <cs50.h>

// function for repeating a char multiple times
void repeat(char part, int n)
{
    // makes a for loop running n number of times
    for (int j = 0; j < n; j++)
    {
        // prints the part
        printf("%c", part);
    }
}

int main(void)
{
    // get the height the user wants the pyramid to be at
    // runs a loop to get a valid number for the height
    int height;
    do
    {
        height = get_int("How tall do you want the pyramid to be? ");
    }
    while (height < 1 || height > 8);

    // start a loop for the height which runs this code height amount of times
    for (int i = 1; i <= height; i++)
    {
        // calculates how many periods we need to print for the pyramid and runs another loop printing x many periods
        int periods = height - i;
        repeat(' ', periods);

        // prints x amount of blocks depending on loop for the left side of the
        repeat('#', i);

        // goes to the next line because we need to have that pyramid shape
        printf("\n");
    }
}