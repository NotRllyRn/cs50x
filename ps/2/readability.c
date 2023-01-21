#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// returns the amount of letters that are in a string
int count_letters(string text, int length)
{
    // delclare a variable to store letters int and start a for loop that will go through each character of the text
    int letters = 0;
    for (int i = 0; i < length; i++)
    {
        // checks with the isalpha function to see if the character on the current loop is an alphabetic character (thanks ctype library)
        if (isalpha(text[i]))
        {
            letters++;
        }
        // increments letters up by one if true
    }
    return letters;
}

// returns the amount of words that are in a string
int count_words(string text, int length)
{
    // delclare a variable to store words int and start a for loop that will go through each character of the text
    int words = 0;
    for (int i = 0; i < length; i++)
    {
        // checks if current index in text is a space, if it is, then it will increment words up by 1
        if (text[i] == 32)
        {
            words++;
        }
    }
    return words + 1;
}

// returns the amount of sentences that are in a string
int count_sentences(string text, int length)
{
    // delclare a variable to store letters int and start a for loop that will go through each character of the text
    int sentences = 0;
    for (int i = 0; i < length; i++)
    {
        // store the character in a variable to easily access it
        char character = text[i];
        if (character == 33 || character == 46 || character == 63)
        {
            sentences++;
        }
        // increment the sentence variable up by one if true
    }
    return sentences;
}

int main(void)
{
    // get the input from the user and make a variable length to get an already determined length of the string
    string input = get_string("Input: ");
    int length = strlen(input);

    // compute the amount of words, letters, and sentences
    int letters = count_letters(input, length);
    int words = count_words(input, length);
    int sentences = count_sentences(input, length);

    //printf("%i letters\n%i words\n%i sentences\n", letters, words, sentences);

    // now calculate the reading level of the text
    float avr_letters = (float) letters / words * 100;
    float avr_sentences = (float) sentences / words * 100;
    float float_reading_level = 0.0588 * avr_letters - 0.296 * avr_sentences - 15.8;

    // round the float to an interger
    int reading_level = round(float_reading_level);

    // do checks to see if its below or above reading level 1 or 16
    if (reading_level < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (reading_level > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    // if have not returned, then the reading level must be 1-16
    printf("Grade %i\n", reading_level);
}