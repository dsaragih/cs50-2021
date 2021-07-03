#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void substitute(string plaintext, string key);

int main(int argc, string argv[])
{
    // Checks for valid input
    if (argc != 2) // Checks if only two inputs in CLI
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26) // Checks if # of characters is 26
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i])) // Checks that all characters are letters
            {
                printf("Key must only contain the characters of the alphabet\n");
                return 1;
            }
            
            for (int j = i+1; j < n; j++)
            {
                if (argv[1][i] == argv[1][j]) // Checks for duplicates
                {
                    printf("Key must not contain duplicate characters.\n");
                    return 1;
                }
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    
    // Function mutates the plaintext string
    substitute(plaintext, argv[1]);
    string ciphertext = plaintext;
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;

};

void substitute(string plaintext, string key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        if (isupper(c)) // Case if character is uppercase
        {
            int idx = c - 65; // Re-indexes according to key index
            plaintext[i] = toupper(key[idx]);
        }
        else if (islower(c)) // Case if character is lowercase
        {
            int idx = c - 97;
            plaintext[i] = tolower(key[idx]);
        }
    }
}