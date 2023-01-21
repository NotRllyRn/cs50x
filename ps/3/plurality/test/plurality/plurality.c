#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // start a loop that loops through the candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // compare the input string and the candidates name to see if they are the same
        if (strcmp(candidates[i].name, name) == 0)
        {
            // if they are then increment their vote up by one and then return true as for the vote has been successfully made.
            candidates[i].votes++;
            return true;
        }
    }
    // this will return false when it goes through the entire loop and did not find any candidates with the input name
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // first it will "sort" through all the candidates and find the one with the highest votes.
    // make a int varaible that holds the current highest vote and then start a for loop that loops through all the candidates.
    int highest = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has more votes than the current highest vote then enter the scope
        if (candidates[i].votes > highest)
        {
            // it will remove the previouse candidates value by looping through every candidate and setting their highest variable to false
            // start a for loop to go through each candidate
            for (int j = 0; j < candidate_count; j++)
            {
                // set the highest varaible to false
                candidates[j].highest = false;
            }

            // then it will set the new candidate with the higher amount of votes to true
            // and then update the highest value varaible so that it can try to find the next highest variable
            candidates[i].highest = true;
            highest = candidates[i].votes;
        }
        // if the candiate did not have higher votes but did have the same amount of votes, then it will enter this scope
        else if (candidates[i].votes == highest)
        {
            // it will just set the candidates variable to true, as they are both the highest.
            candidates[i].highest = true;
        }
    }

    // it wil then start a for loop looping through all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has the highest value variable set to true
        if (candidates[i].highest)
        {
            // it will print the candidates name to the terminal
            printf("%s\n", candidates[i].name);
        }
    }
}