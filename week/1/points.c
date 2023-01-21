#include <cs50.h>
#include <stdio.h>

int main(void)
{
    const int MINE = 20;
    int hours = get_int("How many hours did you code last week? ");

    if (hours < MINE)
    {
        printf("You coded less than me!\n");
    }
    else if (hours > MINE)
    {
        printf("You coded more than me!\n");
    }
    else
    {
        printf("You coded the same amount of time as me.\n");
    }
}