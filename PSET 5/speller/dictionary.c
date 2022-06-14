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
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_val = hash(word);
    for (node *tmp = table[hash_val]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char str[LENGTH + 1];
    strcpy(str, word);
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        char tmp = toupper(str[i]);
        str[i] = tmp;
    }
    const char *str2 = str;
    unsigned long h = 5381;
    int c;
    while ((c = *str2++))
    {
        h = ((h << 5) + h) + c; /* hash * 33 + c */
    }
    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    char dict_word[LENGTH + 1];
    while ((fscanf(dictionary_file, "%s", dict_word)) != EOF)
    {
        int hash_val = hash(dict_word);

        // creates tmp
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }
        strcpy(tmp->word, dict_word);
        tmp->next = table[hash_val];

        // insert tmp
        table[hash_val] = tmp;
    }

    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            size++;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;

            size++;
        }
    }
    return true;
}
