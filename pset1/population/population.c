#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end;
    // TODO: Prompt for start size
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    int n = start;
    int counter = 0;
    while (n < end)
    {
        n += (n / 3 - n / 4);
        counter++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", counter);
}