#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// this function will check if an array of characters has duplicate characters
int check_duplicates(char key[], int length)
{
    // start a loop which grabs a character
    for (int i = 0; i < length; i++)
    {
        // puts the character into a variable to checl
        char character = key[i];

        // starts a second loop to check with the table
        for (int i2 = 0; i2 < length; i2++)
        {
            // if its not the same index and the characters are the same
            if (i != i2 && character == key[i2])
            {
                // return false
                return 1;
            }
        }
    }
    // if there are no duplicates then return true
    return 0;
}

int main(int argc, string argv[])
{
    // do input checking to see if the user inputed a valid key
    if (argc != 2)
    {
        // if the arguments is not equal to 2 meaning that the user inputed too many or no arguments then it will remind them on how to use the program
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        // if the key length is not equal to 26 then it will remind the user that the key must be of length 26
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // get the value input and make a key table completely lower case
    string input = argv[1];
    char key[26];

    for (int i = 0; i < 26; i++)
    {
        // makes a char variable to hold the character index we are on
        char character = input[i];

        // checks if its alphabetic
        if (!isalpha(character))
        {
            printf("Enter valid characters in the key.\n");
            return 1;
        }

        // checks if its an upper case letter or not
        if (isupper(character))
        {
            // puts the lower case letter into the table and continues the loop
            key[i] = tolower(character);
        }
        else
        {
            // if it wasn't upper case, just add to the table
            key[i] = character;
        }
    }

    // checks if there are any duplicates
    if (check_duplicates(key, 26))
    {
        printf("No duplicate characters inside your key.\n");
        return 1;
    }

    // gets the string input from the user
    string plain_text = get_string("plaintext:  ");

    // start to calculate the ciphered text with a for loop
    for (int i = 0, length = strlen(plain_text); i < length; i++)
    {
        // declares some variables to use and check for later
        char character = plain_text[i];
        int islow = islower(character);

        // checks if the character is an alphabetic character before continuing with the loop
        if (!isalpha(character))
        {
            continue;
        }

        // calculates the index with a lowercase letter by getting the ascii value of the lowercase letter and removing 97
        int index = tolower(character) - 97;

        // goes into the key table and gets the cipered character and then checks if it should return a lower case or upper case value
        char ciphered_char = key[index];
        if (islow)
        {
            plain_text[i] = ciphered_char;
            continue;
        }
        // if not then return an upper case
        plain_text[i] = toupper(ciphered_char);
    }

    // converts the table into a string
    printf("ciphertext: %s\n", plain_text);
}