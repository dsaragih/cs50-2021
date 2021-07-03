#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Asks user to enter the height between 1 and 8 inclusive
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Creates the pyramid
    for (int i = 0; i < height; i++)
    {
        // Creates the empty space to the left
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // The left pyramid structure
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Creates the spacing b/w left and right blocks
        printf("  ");

        // Creates the right hand blocks
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // Moves down a level
        printf("\n");
    }
};