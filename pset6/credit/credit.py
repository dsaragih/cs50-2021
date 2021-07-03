from cs50 import get_string
import math

while True:
    number = get_string("Number: ")
    try:
        int(number)
        break
    except:
        pass


length = len(number)
first_digit = number[0]
first_two_digits = number[:2]


def algorithm(n=number):
    total = 0 # Initializes the sum

    # Iterates over the digits, starting from the end to bc reference is at the second to last number
    for i in range(-1, -length - 1, -1):
        if i % 2 == 0: # If the current digit is every other number starting from the second last
            # The digit is multiplied
            digit = 2*int(n[i])

            # If the result is a two digit number, we split the number
            if digit > 9:
                # And then add the two digits
                total += (math.floor(digit / 10) + digit % 10)
            else:
                # Otherwise, add the digit itself
                total += digit
        else:
            total += int(n[i])
    return total % 10 == 0 # Returns whether or not the sum is a multiple of 10


if (algorithm()):
    if (length == 15 and (first_two_digits == '34' or first_two_digits == '37')):
        print("AMEX\n")
    elif length == 16 and (int(first_two_digits) in range(51, 56)): # Cheks if first two digits b/w 51 and 55
        print("MASTERCARD\n")
    elif (length == 13 or length == 16) and first_digit == '4':
        print("VISA\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")