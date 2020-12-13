#include <cs50.h>
#include <stdio.h>

void triple(int foo);

int main(void)
{
    int foo = 4;

    triple(foo);

    printf("%i", foo);
}

void triple(int foo)
{
    foo = 6;
}