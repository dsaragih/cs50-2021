#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool algorithm(long n);

int main(void)
{
    // Asks for user input
    long n = get_long("Number: ");

    // Finds the length of the number
    char str[256];
    int len = sprintf(str, "%li", n);

    // Finds the first, and first two digits of the number
    long first_digit = n / (long) pow((double) 10, (double) len - 1);
    long first_two_digits = n / (long) pow((double) 10, (double) len - 2);

    // Checks if the card complies with Luhn's algorithm
    if (algorithm(n))
    {
        // Checks for AMEX
        if (len == 15 && (first_two_digits == 34 || first_two_digits == 37))
        {
            printf("AMEX\n");
        }

        // Checks for Mastercard
        else if (len == 16 &&
            (
                first_two_digits == 51 ||
                first_two_digits == 52 ||
                first_two_digits == 53 ||
                first_two_digits == 54 ||
                first_two_digits == 55
            ))
        {
            printf("MASTERCARD\n");
        }
        // Checks for VISA
        else if ((len == 13 || len == 16) && first_digit == 4)
        {
            printf("VISA\n");
        }
        // Otherwise invalid
        else
        {
            printf("INVALID\n");
        }
    }
    // Otherwise invalid
    else
    {
        printf("INVALID\n");
    }

};

bool algorithm(long n)
{
    long tmp = n;

    int sum = 0;
    int counter = 0;

    while (tmp >= 1)
    {
        int current_digit = tmp % 10;
        if (counter % 2 == 1)
        {

            if (2*current_digit > 9)
            {
                sum += ((2*current_digit / 10) + (2*current_digit % 10));
            }
            else
            {
                sum += 2*current_digit;
            }
        }
        else
        {
            sum += current_digit;
        }

        tmp /= 10;
        counter++;
    }

    if (sum % 10 == 0)
    {
        return true;
    }

    return false;
};