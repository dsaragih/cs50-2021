#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Prototype of helper function
void count(int counter[], string text);

int main(void)
{
    string text = get_string("Text: ");

    // Initializes array that will be filled with letter, word, and sentence count
    int counter[3];
    count(counter, text);

    // Calculates L, S, and index
    float L = (counter[0] / (float) counter[1]) * 100.0;
    float S = (counter[2] / (float) counter[1]) * 100.0;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);


    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
};

void count(int counter[], string text)
{
    // Initializes counters
    int nletters = 0;
    int nwords = 1; // Since the last word will not be proceeded by a space
    int nsentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
       if (isalpha(text[i]))
       {
           nletters++;
       }
       if (text[i] == ' ')
       {
           nwords++;
       }
       if (text[i] == '.' || text[i] == '!' || text[i] == '?')
       {
           nsentences++;
       }
    }
    // Enters the counters into the array
    counter[0] = nletters;
    counter[1] = nwords;
    counter[2] = nsentences;

};