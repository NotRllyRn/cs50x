#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: "); // gets variable x from user
    int y = get_int("y: "); // gets variable y from user
    float z = x / (float) y; // adds x and y together

    printf("%.50f\n", z); // prints z or sum on the screen
}