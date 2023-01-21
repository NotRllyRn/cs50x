#include <stdio.h>

int main(void)
{
    int start = 97, total = 0;
    for (int i = 0; i < 26; i++)
    {
        total += start + i;
    }
    printf("%i\n", total);
}