// CS50 2020 Pset5 SPELLER

// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of words in the hashtable
int dictionary_size = 0;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // create a copy of the word
    int n = strlen(word);
    char word_copy[LENGTH + 1];

    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    // Adds null terminator to end string
    word_copy[n] = '\0';

    int indx = hash(word_copy);

    node *head = table[indx];

    while (head != NULL)
    {
        if (strcasecmp(head->word, word_copy) == 0)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }
    return false;
}

//  Hashes word to a number
//  stackoverflow
//  https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/ this was for a prior one that I altered later to ^
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open.\n");
        return false;
    }

    char word[LENGTH + 1];
    // read strings from file one at a time
    while (fscanf(dic, "%s", word) != EOF)
    {

        // malloc a new node for each word
        node *n = malloc(sizeof(node));

        // check if there is enought memory
        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        // hash to obtain a hash value
        int indx = hash(word);

        // insert node into a hash table
        n->next = table[indx];
        table[indx] = n;
        dictionary_size++;
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cur = table[i];
            while (cur != NULL)
            {
                node *temp = cur;
                cur = cur->next;
                free(temp);
            }
            table[i] = NULL;
        }
    }
    return true;
}
