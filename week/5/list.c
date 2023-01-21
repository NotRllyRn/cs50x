#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // allocate a new array to store 3 intergers
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    // store the 3 intergers with the array of 3
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // stuff happened

    // create a temporary variable that points to the array of 4
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        // if we could not get more memory then we will free the other list and exit
        free(list);
        return 2;
    }

    // makes the list pointer point to the temporary array
    list = tmp;
    // set the new value
    list[3] = 4;

    // prints out the array with the numbers
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // frees the list of the new array tmp
    free(list);
}