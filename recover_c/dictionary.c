// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int num_word = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *list = table[hash(word)];

    for (node *temp = list; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int number = 0;
    for (int i = 0; word[i] != '\0'; i += 1)
    {
        number += tolower(word[i]) % 3;
    }
    number = (int)sqrt(number);
    return number + tolower(word[0]) % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }


    if (ferror(f))
    {
        fclose(f);
        perror("Error reading the dictionary.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Memoria insuficiente!\n");
            return false;
        }

        strcpy(n->word, word);

        unsigned int uni_hash = hash(word);
        n->next = table[uni_hash];
        table[uni_hash] = n;
        num_word += 1;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i += 1)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
