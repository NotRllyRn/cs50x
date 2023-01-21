#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string s = argv[1];
    printf("After: ");
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}