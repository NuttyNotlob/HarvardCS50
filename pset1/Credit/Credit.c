#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Putting my format prototypes here so they work in the main string

int check_length(long card_number);
int check_start_digits(long card_number);
int finding_sum (long card_num);
int checking_card (int card_sum_val, int start_digits);

// Main function, with command-line arguement for the number

int main(void)
{
    // I'm gonna name my variable just to make it easier to understand my code. I can also then change it without losing my initial input

    long card_number = get_long("Please enter your card number");

    // First we check the length of the card number to be able to instantly fail it

    int card_length = check_length(card_number);

    // Next we have a function to find what the first two numbers of the card are. We'll use two despite visa starting with just a 4, then let 40 - 49 be Visa

    int start_digits = check_start_digits(card_number);

    // Now we instantly fail the item with INVALID if it doesn't match the right length, to avoid running the rest of the formula

    if (card_length < 13 || card_length > 16)
    {
        printf("INVALID\n");
        return 1;
    }

    if (start_digits != 34 &&  start_digits != 37 && start_digits != 51 && start_digits != 52 && start_digits != 53 && start_digits != 54 && start_digits != 55 && start_digits != 40  && start_digits != 41  && start_digits != 42 && start_digits != 43 && start_digits != 44 && start_digits != 45 && start_digits != 46 && start_digits != 47 && start_digits != 48 && start_digits != 49)
    {
        printf("INVALID\n");
        return 1;
    }

    // Finding our card total value using a formula I've made

    int card_value = finding_sum(card_number);

    checking_card(card_value, start_digits);

}

// Function for getting the sum using the formula we've been given

int check_length(long card_number)
{
    // Here we just use an int log(10)+1. So for example int log10(143) will be 2, so we just add 1 and we have the length

    int n = (log10(card_number)+1);

    return n;
}

int check_start_digits(long card_number)
{
    // Start by referring to the card length function
    int l = (log10(card_number)+1);

    // Now we use that card length and divde by it -2, to get the int which is the first two digits

    int n = (card_number / pow(10,l-2));

    return n;
}

int finding_sum (long card_num)
{
    // Need to comment this whole section up to explain it

    int sum_total = 0;

    for (int i = 0;  card_num != 0; i++)
    {

        if (i%2 == 0)
        {
            sum_total = sum_total + (card_num % 10);
        }

        else
        {
            int temp_card_mod = card_num % 10;

            if (temp_card_mod < 5)
            {
                sum_total = sum_total + (2 * (card_num % 10));
            }

            else
            {
                temp_card_mod = 2 * temp_card_mod;

                for (int j = 0;  temp_card_mod != 0; j++)
                {
                    sum_total = sum_total + (temp_card_mod % 10);

                    temp_card_mod /= 10;
                }
            }


        }

        card_num /= 10;
    }

    return sum_total;
}

int checking_card (int card_sum_val, int start_digits)
{
    int card_check = card_sum_val % 10;

    if (card_check != 0)
    {
        printf("INVALID\n");
        return 2;
    }

    // Then check the different card combinations of length and starting digits

    else if (start_digits == 34 || start_digits == 37)
    {
        printf("Amex\n");
    }

    else if (start_digits == 51 || start_digits == 52 || start_digits == 53 || start_digits == 54 || start_digits == 55)
    {
        printf("Mastercard\n");
    }

    else if (start_digits == 40 || start_digits == 41 || start_digits == 42 || start_digits == 43 || start_digits == 44 || start_digits == 45 || start_digits == 46 || start_digits == 47 || start_digits == 48 || start_digits == 49)
    {
        printf("Visa\n");
    }

    // Then anything else should be returned as INVALID. Nothing should make it to this point though so I'm returning a different error
    else
    {
        printf("INVALID\n");
    }

    return 3;

}