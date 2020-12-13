// Need a few libraries for this, so need to first include these

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Next, we need the function prototypes to be able to declare them later

int count_letters(string input_string);
int count_words(string input_string);
int count_sentences(string input_string);
int get_grade(int letters, int words, int sentences);

int main(void)
{
    // Start by getting our input string

    string input_text = get_string("Text: ");

    // Now we need a function for finding the amount of letters in the text paragraph, letters only

    int number_letters = count_letters(input_text);

    printf("%i letter(s)\n", number_letters);

    // Unfortunately C can't output an array from a function, so we need to have separate funcitons to make each of these. So now for words

    int number_words = count_words(input_text);

    printf("%i word(s)\n", number_words);

    // And finally the number of sentences

    int number_sentences = count_sentences(input_text);

    printf("%i sentence(s)\n", number_sentences);

    // Now we have all that, we just calculate the Grade

    int grade = get_grade(number_letters, number_words, number_sentences);

    // And finally, we just need conditions for Grade less than 1, or higher than 16, otherwise we print the Grade

    if (grade >= 16)
    {
        printf("Grade: 16+");
    }

    else if (grade >= 16)
    {
        printf("Before Grade 1");
    }

    else
    {
        printf("Grade: %i\n", grade);
    }

}

int count_letters(string input_string)
{
    // Setting the starting parameters of the function by finding the string length inclusive of all punctuation and spaces

    int n = strlen(input_string);

    int sum_tot = 0;

    // Now we loop through all characters in the string and add one to our total if it's a letter, using the ASCII numbering

    for (int i = 0; i < n; i++)
    {
        if ((input_string[i] >= 65 && input_string[i] <= 90) || (input_string[i] >= 97 && input_string[i] <= 122))
        {
            sum_tot++;
        }
    }

    // Finally we return the sum value

    return sum_tot;
}

int count_words(string input_string)
{
    // Setting the starting parameters of the function by finding the string length inclusive of all punctuation and spaces

    int n = strlen(input_string);

    // Here, our word count starts at 1 as there will be one more words than spaces because by counting spaces we're essentially counting words with a space before them, which is everything except the first word (e.g. 'I am here' only has two spaces, but three words)

    int sum_tot = 1;

    // Now we loop through all characters in the string and add one to our total if it's a space, using the ASCII numbering

    for (int i = 0; i < n; i++)
    {
        if (input_string[i] ==32)
        {
            sum_tot++;
        }
    }

    // Finally we return the sum value

    return sum_tot;
}

int count_sentences(string input_string)
{
    // Setting the starting parameters of the function by finding the string length inclusive of all punctuation and spaces

    int n = strlen(input_string);

    int sum_tot = 0;

    // Now we loop through all characters in the string and add one to our total if it's a '.', '!' or '?', using the ASCII numbering

    for (int i = 0; i < n; i++)
    {
        if (input_string[i] == 33 || input_string[i] == 63 || input_string[i] == 46)
        {
            sum_tot++;
        }
    }

    // Finally we return the sum value

    return sum_tot;
}

int get_grade(int letters, int words, int sentences)
{
    // First we find the values needed for our calculation
    // We start by finding the amount of letters per hundred words

    float lphw = 100 * (float)letters / (float)words;

    // Now the sentences per hundred words

    float sphw = 100 * (float)sentences / (float)words;

    // And finally we find the grade with the Coleman-Liau index

    float grade_calc = 0.0588 * lphw - 0.296 * sphw - 15.8;

    int grade_output = round(grade_calc);

    return grade_output;
}