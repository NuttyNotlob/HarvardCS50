#include <cs50.h>
#include <stdio.h>

bool change_ranks(int ranks);

typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[3];
pair pairs_changer[3];

int main(void)
{
    pairs[1].winner = 3;
    pairs[1].loser = 3;

    printf("Winner: %i\nLoser: %i\n", pairs[1].winner, pairs[1].loser);

    pairs_changer[1].winner = 4;
    pairs_changer[1].loser = 4;

    pairs[1] = pairs_changer[1];

    printf("Winner: %i\nLoser: %i\n", pairs[1].winner, pairs[1].loser);
}
