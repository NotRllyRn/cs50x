#include <cs50.h>
#include <stdio.h>

float discount(float price, int percent_off)
{
    return price * (100 - percent_off) / 100;
}

int main(void)
{
    float regular = get_float("Regular Price: ");
    int percent_off = get_int("Percent Off: ");
    float sale = discount(regular, percent_off);

    printf("Sale price: %0.2f\n", sale);
}