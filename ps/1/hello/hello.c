#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // gets the name of the user
    string name = get_string("What is your name? ");

    // says hello to the user input
    printf("hello, %s\n", name);
}