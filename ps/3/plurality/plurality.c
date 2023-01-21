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
    if (candidate_count == 1)
    {
        printf("%s\n", candidates[0].name);
        return;
    }

    // start a for loop for the bubble sort
    bool pass = true;
    for (int i = 0;; i++)
    {
        // reset the variable i back to one because it needs to compare the next value with its current index and index 9 won't exist
        if (i == candidate_count - 1)
        {
            if (pass == true)
            {
                break;
            }
            i = 0;
            pass = true;
        }

        // make 2 variables for the candidates we are comparing
        candidate can1 = candidates[i];
        candidate can2 = candidates[i + 1];

        // if the first candidate has less votes then we swap their places
        if (can1.votes < can2.votes)
        {
            // set pass to false and switch the candidates
            pass = false;
            candidates[i] = can2;
            candidates[i + 1] = can1;
        }
    }

    // make a variable storing the higest value votes and start a for loop to get the highest vote
    int highest = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        // store the candidate in a variable
        candidate can = candidates[i];
        // if the votes is higher than the highest then it will print the name and store the votes inside the highest variable
        if (can.votes > highest)
        {
            printf("%s\n", can.name);
            highest = can.votes;
        }
        else if (can.votes == highest)
        {
            // if it finds someone else with the same amount of votes then it will print their name aswell.
            printf("%s\n", can.name);
        }
    }
}