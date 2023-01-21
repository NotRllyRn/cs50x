// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 66;
int wordsLoaded = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get the hash index of the word
    // starts a for loop that will keep going through all the nodes at the hash index
    int index = hash(word);
    for (node *n = table[index]; n != NULL; n = n -> next)
    {
        // compares (case insensitive) the words in the current node to see if its the same and then returns it
        if (strcasecmp(n -> word, word) == 0)
        {
            return true;
        }
    }
    // returns false if reached the end of the list and could not find the word
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // creates a new variable to hold the total math value of the hash
    // starts a loop that will iterate through all the letters in the word input
    int total = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // checks if the character is an alphabetical character and continues if not
        if (isalpha(word[i]) == 0)
        {
            continue;
        }

        // gets the upper case value of the letter
        int val = toupper(word[i]);
        if (i % 3 == 0)
        {
            // first interation will add to the value (and % 3 == 0)
            total += val;
        }
        else if (i % 3 == 1)
        {
            // it will add the multiplied value if the 2nd
            total *= val;
        }
        else
        {
            // and lastly it will divide so that it won't overflow (had problems with this function having a word that is too long)
            total /= val;
        }
    }

    // returns the total % 66 because there are 66 buckets. This should ensure that we will have an evenly distrubted bucket list
    return total % 66;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // opens the dictionary file
    // also checks if we succesfully opened it or not and returns if not
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // creates a buffer for the words that we will read
    // starts a for loop that runs until we read until the end of the file
    char word[LENGTH + 1];
    for (int read = fscanf(dict, "%s", word); read != EOF; read = fscanf(dict, "%s", word))
    {
        // allocate memory for the new node for the new word
        // checks if we got enough memory to allocate it
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // closes the dictionary before returning the function
            fclose(dict);
            return false;
        }
        // copies the word into the node
        strcpy(n -> word, word);

        // calculates the hash of the word
        // then it will copy the pointer of the tables index of the hash to the new node we created
        int nodeIndex = hash(word);
        n -> next = table[nodeIndex];

        // then we will update the pointer to point at the new node
        table[nodeIndex] = n;

        // keeps track of how many words we have loaded
        wordsLoaded++;
    }

    // closes the file before we return
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // returns how many words we loaded
    return wordsLoaded;
}

// a recursive function to free up the nodes in the hash table
void freeList(node *n)
{
    // base condiditon to return if there is no node that was inputted
    if (n == NULL)
    {
        return;
    }

    // frees the next node in the current node
    freeList(n -> next);

    // then it frees the current node
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // this will loop through each pointer in the hash table
    for (int i = 0; i < N; i++)
    {
        // frees the current pointer we are looped on
        freeList(table[i]);
    }

    // returns true becuase nothing can go wrong here LOL
    return true;
}
