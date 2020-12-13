#include <stdio.h>
#include <cs50.h>

// Putting my format prototypes here so they work in the main string

int get_valid_number(string prompt, int i, int j);
void print_number_lines(int h);
void print_spaces (int h, int i);
void print_hashes(int h, int i);

// Main function. This asks for a number, then uses the other functions to print out a number of lines dependent on the height

int main(void)
{
    int height = get_valid_number("Please choose a height of your pyramid between 1 and 8 inclusive", 1, 8);

    print_number_lines(height);
}

// Function to get a number between 1 and 8 inclusive

int get_valid_number(string prompt, int i, int j)
{
    int n = 0;
    while (i > n || j < n)
    {
         n = get_int("%s", prompt);
    }
    return n;
}

void print_number_lines(int h)
{
    int i = 1;
    while (i<=h)
    {
        print_spaces(h, i);
        print_hashes(h, i);
        printf("  ");
        print_hashes(h, i);
        print_spaces(h, i);
        printf("\n");
        i++;
    }
}

void print_spaces (int h, int i)
{
    int a = 0;

    while (a<(h-i))
    {
        printf(" ");
        a++;
    }
}

void print_hashes(int h, int i)
{
    int b = 0;

    while (b<i)
    {
        printf("#");
        b++;
    }
}