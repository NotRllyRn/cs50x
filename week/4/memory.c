#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3 * sizeof(int));
    x[0] = 72;
    x[1] = 75;
    x[2] = 50;

    printf("%i\n", *x);

    free(x);
}