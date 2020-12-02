#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text)
{
    int numLetters = 0;
    for (int i = 0; text[i] != '\0'; i += 1)
    {
        if (isalnum(text[i]) != 0)
        {

            numLetters += 1;
        }
    }

    return numLetters;
}

int number_of_words(string text)
{
    char asp = (int)39;
    int number_words = 0;
    for (int i = 0; text[i] != '\0'; i += 1)
    {
        int newIndex = i;
        if (text[i + 1] != '\0')
        {
            newIndex = i + 1;
        }
        if (isalnum(text[i]) == 0 && text[i] != '-' && isalnum(text[newIndex]) != 0 && (int)text[newIndex] != 39)
        {
            number_words += 1;

            if (text[i] == asp)
            {
                number_words -= 1;

            }
        }
        else if (text[i + 1] == '\0')
        {
            number_words += 1;

        }

    }
    return number_words;
}

int count_sentence(string text)
{
    int numbers_sentence = 0;
    for (int i = 0; text[i] != '\0'; i += 1)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            numbers_sentence += 1;
        }
    }
    return numbers_sentence;
}

int main(void)
{
    string text = get_string("Set text: \n");
    printf("%i\n", isalnum(text[0]));
    int num_letters = count_letters(text);
    int num_words = number_of_words(text);
    int num_sentence = count_sentence(text);
    float l = 0.0588  * (float) num_letters / num_words * 100;
    float s = 0.296 * (float) num_sentence / num_words * 100;
    float index = round(l - s - 15.8);
    if (index <= 1)
    {
        printf("Before Grade %.0f\n", index);
    }
    else if (index > 1 && index <= 15)
    {
        printf("Grade %.0f\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
}
