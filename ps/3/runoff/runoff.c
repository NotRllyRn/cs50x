#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // run a for loop that will go through each canidate and try to check if the name exists
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the names are the same
        if (strcmp(candidates[i].name, name) == 0)
        {
            // add the vote preference to the voter and return true
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // reset all the candidate votes because we are going to update them
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // run a for loop that will go through all the voters and see their prefereces
    for (int i = 0; i < voter_count; i++)
    {
        // make a variable to see if the voter has already had a vote counted
        bool counted = false;
        for (int j = 0; j < candidate_count; j++)
        {
            // it will get the preference index of the candidate they want to vote for
            // and it will check if the candidate is valid to be voted for
            int preference = preferences[i][j];
            if (!counted && !candidates[preference].eliminated)
            {
                // it will increment the candidate's vote count and make sure the voter cannot vote again until the next round.
                candidates[preference].votes++;
                counted = true;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // calculate the amount of votes that a candidate needs to win
    // then run a for loop to find a candidate has more than 50%
    int half = voter_count / 2.0 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate has more than 50% of votes
        if (candidates[i].votes >= half)
        {
            // it will print out their name and return true
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // return false if no one has won the vote
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // define a variable to find the lowest number of votes a candidate has and start a loop to compare the variables and find the lowest vote count.
    int lowest = 101;
    for (int i = 0; i < candidate_count; i++)
    {
        // sets the current candidate into a variable
        // checks if the candidate is valid to be counted for and also checks if their vote count is lower then the current one in the variable
        candidate current = candidates[i];
        if (!current.eliminated && current.votes < lowest)
        {
            // if its lower then it will set the lowest count to their count of votes
            lowest = current.votes;
        }
    }
    return lowest;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // start a loop that will check if all the candidates that are still in the election has the minimum amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // return false if it finds a candidate that is still in the vote that has more than the minimum
            return false;
        }
    }

    // it will return true if it doesn't find a candidate that is still in the election and has a higher score than the minimum
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // start a for loop that will check if candidates have the min number of votes and it will eliminate them if they do.
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has the same number votes as min
        if (candidates[i].votes == min)
        {
            // it will eliminate the candidate from the vote
            candidates[i].eliminated = true;
        }
    }
    return;
}