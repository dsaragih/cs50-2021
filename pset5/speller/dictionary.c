// Implements a dictionary's functionality
#include <strings.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Counts the number of words loaded into the table
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char tmp[LENGTH + 1];
    for (int k = 0, n = strlen(word); k <= n; k++)
    {
        tmp[k] = tolower(word[k]);
    }
    int n = hash(tmp);
    node *curr = table[n];
    //printf("%i : %i\n", n, hash(word));
    if (table[n] == NULL)
    {
        //printf("Why are you false?\n");
        return false;
    }
    else
    {
        do
        {
            //printf("%s\n", curr->word);
            if (strcasecmp(curr->word, word) == 0)
            {
                return true;
            }
            curr = curr->next;
        }
        while (curr != NULL);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //Sourced from http://www.cse.yorku.ca/~oz/hash.html - djb2 by Dan Bernstein
    unsigned long hash = 5381;
    int c;

    while ((c = *(word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

char buffer[LENGTH + 2];
int i = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //printf("%s\n", dictionary);
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }


    while (fgets(buffer, LENGTH + 2, file) != NULL)
    {

        buffer[strcspn(buffer, "\n")] = 0;
        //printf("%s\n", buffer);
        int n = hash(buffer);
        if (table[n] == NULL)
        {
            node *tmp = malloc(sizeof(node));
            if (tmp == NULL)
            {
                return false;
            }

            strcpy(tmp->word, buffer);
            tmp->next = NULL;
            table[n] = tmp;

            //printf("From the first if: %s\n", table[n]->word);

        }
        else
        {
            node *tmp = malloc(sizeof(node));
            if (tmp == NULL)
            {
                return false;
            }
            strcpy(tmp->word, buffer);
            tmp->next = table[n];
            table[n] = tmp;
            //printf("From the else statement: %s\n", current->word);

        }
        counter++;
        memset(&buffer, 0, strlen(buffer));
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int j = 0; j < N; j++)
    {
        node *curr = table[j];
        node *next = NULL;
        while (curr != NULL)
        {
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    return true;
}