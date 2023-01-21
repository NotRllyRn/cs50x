#include <stdio.h>
#include <string.h>

int numbers[] = {5, 2, 7, 4, 1, 6, 3, 0};

void sort(void)
{
    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] > numbers[i + 1])
        {
            int p = numbers[i];
            int p2 = numbers[i + 1];
            numbers[i] = p2;
            numbers[i + 1] = p;
            return sort();
        }
    }
}

int main(void)
{
    sort();
    for (int i = 0; i < 8; i++)
    {
        printf("%i\n", numbers[i]);
    }
}