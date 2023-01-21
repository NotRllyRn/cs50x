#include <stdio.h>
#include <cs50.h>

// function to get a user's input for the amount of cents
int get_cents(void)
{
    // make a new int value
    int change;
    do
    {
        // ask user for int input
        change = get_int("Change owed: ");
    }
    while (change < 0);

    // repeats until user puts in an accepted value and returns the amount of change
    return change;
}

// the base calculation for the coins
int calculate_base(int change, int amount)
{
    return change / amount;
}

// calculates the amount of quarters
int calculate_quarters(int change)
{
    return calculate_base(change, 25);
}

// calculates the amount of dimes
int calculate_dimes(int change)
{
    return calculate_base(change, 10);
}

// calculates the amount of nickels
int calculate_nickels(int change)
{
    return calculate_base(change, 5);
}

// calculates the amount of pennies
int calculate_pennies(int change)
{
    return calculate_base(change, 1);
}

int main(void)
{
    // Prompt user to get cents
    int change = get_cents();

    // Calculates the amount of quarters we have to give
    // Changes the amount of change to the remainder
    int quarters = calculate_quarters(change);
    change %= 25;

    // Calculates the amount of dimes we have to give
    int dimes = calculate_dimes(change);
    change %= 10;

    // Calculates the amount of nickels we have to give
    int nickels = calculate_nickels(change);
    change %= 5;

    // Calculates the amount of pennies we have to give
    int pennies = calculate_pennies(change);
    change %= 1;

    // Get the total sum of coins we owe
    int sum = quarters + dimes + nickels + pennies;

    // Prints to the terminal
    printf("%i\n", sum);
}