// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 40000;

// Easy variable to give the word count

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // First we hash our word

    unsigned int word_hash = hash(word);

    // Now, we go to that part of the hash table, and check through it until we get to the end of that list (when the next value of the node is NULL)

    node *tmp = table[word_hash];

    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }

        else
        {
            tmp = tmp->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function taken from http://www.cse.yorku.ca/~oz/hash.html
    // Slight edit to make it case insensitive

    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    hash = hash % N;

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // 1. Open the file

    FILE *dict_file = fopen(dictionary, "r");

    if (dict_file == NULL)
    {
        return false;
    }

    char temp_word[LENGTH + 1];

    // 2. Read strings

    while (fscanf(dict_file, "%s", temp_word) != EOF)
    {
        // 3. Create a node

        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return false;
        }

        new_node->next = NULL;
        strcpy(new_node->word, temp_word);

        // 4. Hash the word

        unsigned int hash_num = hash(temp_word);

        // 5. Insert our word into the linked list. We do this by setting our new node to be where the old hash table value pointed, and then setting the hash table value to point at our new node - essentially adding the new word into the start of our list

        new_node->next = table[hash_num];
        table[hash_num] = new_node;

        word_count++;
    }

    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *tmp;

    int FreeCount = 0;

    for (int i = 0; i < N; i++)
    {
        if(table[i] != NULL)
        {
            tmp = table[i];

            while (tmp != NULL)
            {
                cursor = tmp->next;
                free(tmp);
                tmp = cursor;
            }

            FreeCount++;

            free(tmp);

        }

        if(table[i] == NULL)
        {
            FreeCount++;
        }
    }

    if (FreeCount == N)
    {
        return true;
    }

    // TODO
    return false;
}
