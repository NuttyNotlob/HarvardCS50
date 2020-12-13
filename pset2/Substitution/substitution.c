#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Usual function prototypes

int all_letter_check(string checked_string);
void print_cipher(string message, string key);

// And now for our actual program

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must add a key containing all and only 26 letters as a command-line arguement\n");

        return 1;
    }

    // We need 3 validations of the argument now we know we have one here - first checking the string is 26 characters, second checking it only contains letters, and third checking it contains each letter

    // First checking the length

    if (strlen(argv[1]) != 26)
    {
        printf("Error, command-line argument must be 26 characters\n");

        return 1;
    }

    // Now to check it only contains letters

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] <= 64 || (argv[1][i] >= 91 && argv[1][i] <= 96) || argv[1][i] >= 123)
        {
            printf("Command-line argument must only contain letters\n");

            return 1;
        }
    }

    // And last but not least our third and most complicated check to ensure all letters are present. We do this by checking all the letters, against the string, not the string against the letters

    int check = all_letter_check(argv[1]);

    if (check == 1)
    {
        printf("Command-line argument must contain all 26 letters in either uppercase or lowercase\n");

        return 1;
    }

    // Now, to make a string that is made up of the lowercase and uppercase version of the input string, so we have a full key

    char key[52];

    for (int i = 0; i < 26; i++)
    {
        key[i] = tolower(argv[1][i]);
        key[i+26] = toupper(argv[1][i]);
    }

    // Now we have our key set up, we need to get an input of what the user wants to encrypt

    string initial_message = get_string("plaintext: ");

    // Now we need to encrypt our initial message. For this we'll print each letter individually, rather than make a new string. First we want to just print our bit saying ciphertext

    printf("ciphertext: ");

    // Now we print each letter individually using the cipher.

    print_cipher(initial_message, key);

    printf("\n");

    return 0;

}

int all_letter_check(string checked_string)
{
    int total_sum_check = 0;

    for (int c = 65; c < 91; c++)
    {
        int ind_sum_check = 0;

        for(int i = 0, n = strlen(checked_string); i < n; i++)
        {
            if(checked_string[i] == c || checked_string[i] == c + 32)
            {
                ind_sum_check++;
            }
        }

        if (ind_sum_check > 0)
        {
            total_sum_check++;
        }
    }

    if (total_sum_check == 26)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}

void print_cipher(string message, string key)
{
    // Will loop through all the characters in the string

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        // Function need to differentiate betwen lower and uppercase characters. First we check for lowercase

        if (message[i] >= 97 && message[i] <= 122)
        {
            printf("%c", key[message[i]-97]);
        }

        // And now for the uppercase

        if (message[i] >= 65 && message[i] <= 90)
        {
            printf("%c", key[message[i]-39]);
        }
    }

}