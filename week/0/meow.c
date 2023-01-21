#include <cs50.h>
#include <stdio.h>

void meow(int n);

int main(void)
{
    int n = get_int("How many times do you want to meow? ");
    meow(n);
}

void meow(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("meow\n");
    }
}

