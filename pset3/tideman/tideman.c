#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sort_comp(const void *pair1, const void *pair2);

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
bool loop_check(int w, int l);

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
    // This fuinction essentially loops through all the candidates - if the name given is the same as any of
    // the candidates, it sets the ranks value for our given rank to that candidate's name

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // First I'm going to make an array of the rank for each candidate

    int candidates_ranks[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (ranks[i] == j)
            {
                candidates_ranks[j] = i + 1;
            }
        }
    }

    // Once I have that array, I check the rank of each candidate against every other candidate's
    // If it's lower, they're more preferred, so I add one to the preferences array for that comparison

    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            if (candidates_ranks[x] < candidates_ranks[y])
            {
                preferences[x][y]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // So here I need to look against each pair and compare it to it's counter pair to see if it's value is higher in the preferences array

    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // If it is higher, I add the pair to my pairs array, and increase the pair count

                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count++;

            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), sort_comp);
}

// Our comparator function for our qsort
int sort_comp(const void *a, const void *b)
{
    pair *pair1 = (pair *)a;
    pair *pair2 = (pair *)b;

    return (preferences[(*pair2).winner][(*pair2).loser] - preferences[(*pair2).loser][(*pair2).winner]) - (preferences[(*pair1).winner][(*pair1).loser] - preferences[(*pair1).loser][(*pair1).winner]);

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (loop_check(pairs[i].winner, pairs[i].loser) != true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }

    return;
}

bool loop_check(int w, int l)
{
    if (locked[l][w] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][w] == true)
        {
            return loop_check(i, l);
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Go through each candidate. If no other candidate beats them, they're a winner

    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
        }

        // Checking for a value of candidate_count as it means no candidate beat them

        if (false_count == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

