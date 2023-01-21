#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numberOfScores;
    do
    {
        numberOfScores = get_int("How many scores? ");
    }
    while (numberOfScores <= 1);

    int total = 0;
    for (int i = 0; i < numberOfScores; i++)
    {
        total += get_int("Score: ");
    }

    printf("Your average score is: %f\n", total / (float) numberOfScores );
}