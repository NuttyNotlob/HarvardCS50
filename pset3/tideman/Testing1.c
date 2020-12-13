#include <cs50.h>
#include <stdio.h>

void change(int number[]);

typedef struct
{
    int winner;
    int loser;
}
pair;

int main(void)
{
    int foo[1];

    foo[0] = 4;

    change(foo);

    printf("%i", foo[0]);
}

void change(int number[])
{
    number[0] = 6;
}