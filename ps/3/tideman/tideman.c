#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check if the candidate exist in the candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the candidate names match
        if (strcmp(candidates[i], name) == 0)
        {
            // set the voters rank preference to the index of the candidate and then return true
            ranks[rank] = i;
            return true;
        }
    }

    // return false if it could not find a candidate with the right name
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // start a for loop that will repeat the # of candidate times - 1
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // start a for loop that will just go through the rest of the array that we have not checked
        for (int j = i + 1; j < candidate_count; j++)
        {
            // updates the preferences that the voter has to the preferences array
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop through all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // then loop through all the cadidates again that we need to compare too
        for (int j = 0; j < candidate_count; j++)
        {
            // get the number of preferences of each candidate
            int prefered1 = preferences[i][j];
            int prefered2 = preferences[j][i];

            // check to see if the first candidate has a higher amount of preference
            if (prefered1 > prefered2)
            {
                // make a new pair and set the winner and loser
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // update the pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // create a new bool to check if the function has done a pass over
    bool passed = true;
    for (int i = 0;; i++)
    {
        // checks if the current iteration is on the max
        if (i == candidate_count - 1)
        {
            // checks if it has done a pass with no switches
            if (passed)
            {
                // if it has then it will break and it is done sorting
                break;
            }
            // if not then it will set passed back to true and set the iteration back to 0
            passed = true;
            i = 0;
        }

        // defines the 2 pairs
        pair pair1 = pairs[i];
        pair pair2 = pairs[i + 1];

        // get the different in votes of each pair
        int difference1 = preferences[pair1.winner][pair1.loser] - preferences[pair1.loser][pair1.winner];
        int difference2 = preferences[pair2.winner][pair2.loser] - preferences[pair2.loser][pair2.winner];

        // checks if difference in the first pair's votes is smaller than the 2nd one
        if (difference1 < difference2)
        {
            // it will set pass to false so that it knows to keep sorting
            passed = false;

            // it will then switch the pairs places
            pairs[i] = pair2;
            pairs[i + 1] = pair1;
        }
    }
    return;
}

// create a function for recursive calling
bool islocked(int on, int check)
{
    // loop the number of candidate times
    for (int i = 0; i < candidate_count; i++)
    {
        // if finds that the candidate has a lock on the current index
        if (locked[on][i])
        {
            // it will check if that locked cadidate is the check
            if (check == i)
            {
                // it will return true if is
                return true;
            }

            // if the index is not the current check, then it will recursively call it self to see if it will intercept later down the path.
            if (islocked(i,  check))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // it will loop the number of pairs times
    for (int i = 0; i < pair_count; i++)
    {
        // it checks if the loser has a loop all the way back to the winner
        if (!islocked(pairs[i].loser, pairs[i].winner))
        {
            // if it doesn't then it will lock the winner to the loser so this would not create a loop
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // loop # of candidates times
    for (int i = 0; i < candidate_count; i++)
    {
        // make a variable to remember if the candidate is locked or not
        // then loop # of candidate times again
        bool locked_ = false;
        for (int j = 0; j < candidate_count; j++)
        {
            // if j candidate is locked to i candidate then it would change locked to true
            if (locked[j][i])
            {
                locked_ = true;
            }
        }

        // if the candidate is not locked by anyone at all
        if (!locked_)
        {
            // then this candidate is the winner so print the name and then return
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}