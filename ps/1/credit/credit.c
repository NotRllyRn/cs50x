#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get the user credit card
    long card;
    do
    {
        card = get_long("Enter your credit card number: ");
    }
    while (card < 0);

    // define some variables that we will determine later on
    int credit_length = 0, last1, last2, current_digit = card % 10, sum2 = 0;

    // start the card checking algorithm
    while (card != 0)
    {
        // increment the card length up by one
        credit_length++;

        // shift card in the loop
        card /= 10;

        // check if we are on every other one of the card digits
        if (credit_length % 2 == 0)
        {
            // multiplies it by 2
            int first_sum = current_digit * 2;
            int current_small_digit = first_sum % 10;

            // runs the 2nd loop for the seperate values
            while (first_sum != 0)
            {
                // adds to the 2nd sum and goes to the next digit and divides the number by 10 to shift it
                first_sum /= 10;
                sum2 += current_small_digit;
                current_small_digit = first_sum % 10;
            }
        }
        else
        {
            // if on the other part of the every other cycle
            // it will add the number to the 2nd sum
            sum2 += current_digit;
        }

        // finish off the code by getting the next digit to look at
        // and to shift the card over
        // and to save the most recent values of the card to check what type of card it is
        last2 = last1;
        last1 = current_digit;
        current_digit = card % 10;
    }

    // starts the data checking of if the card is valid or not
    if (sum2 % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (last1 == 4 && (credit_length == 16 || credit_length == 13))
    {
        printf("VISA\n");
    }
    else if (last1 == 3 && (last2 == 7 || last2 == 4) && credit_length == 15)
    {
        printf("AMEX\n");
    }
    else if (last1 == 5 && last2 > 0 && last2 < 6 && credit_length == 16)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

    // for debugging
    // printf("%i, %i, %i\n", credit_length, sum2, last1);
}