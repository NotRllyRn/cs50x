#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// declare table with point values for each letter
int POINTS[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

// function that will compute the score of the input word
int compute_score(string word)
{
    // make a variable to store the score and then start a for loop initializing the length of the word
    int score = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // grab the lowercase version of the letter and take away 97 which is index of 'a' in ascii
        int index = tolower(word[i]) - 97;
        if (index >= 0 && index <= 25)
        {
            // if the index is between 'a' and 'z' then it will add points
            score += POINTS[index];
        }
    }
    return score;
}

int main(void)
{
    // ask for player inputs of player1 and player2
    string input1 = get_string("Player1: ");
    string input2 = get_string("Player2: ");

    // compute the scores of the input
    int score1 = compute_score(input1);
    int score2 = compute_score(input2);

    // compare the scores and determine the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    // if have not returned success, then it must be a tie and it will print that.
    printf("Tie!\n");
}