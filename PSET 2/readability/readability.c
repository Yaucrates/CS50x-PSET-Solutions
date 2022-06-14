#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int total_sentences(string text);
int total_letters(string text);
int total_words(string text);

int main(void)
{
    string text = get_string("Text: ");

    //Calculates the total number of letters, words, and sentences
    double letters = total_letters(text);
    double words = total_words(text);
    double sentences = total_sentences(text);

    // Calculates the total number of letters and sentences per 100 words
    double L = (100 * letters) / words;
    double S = (100 * sentences) / words;

    //calculates the grade level
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    //If the grade level is 16+
    if (index > 15)
    {
        printf("Grade 16+\n");
    }

    //If the grade level is lower than grade 1
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    //If the grade level is between 1 and 15, included.
    else
    {
        printf("Grade %i\n", index);
    }
}

int total_sentences(string text)
{
    int total = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            total++;
        }
    }

    return total;
}

int total_words(string text)
{
    int total = 0;

    if (total_letters(text) > 0)
    {
        total++;
    }

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]) != 0)
        {
            total++;
        }
    }

    return total;
}

int total_letters(string text)
{
    int total = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            total++;
        }
    }

    return total;
}