from cs50 import get_string

# Retrieves text from CLI
text = get_string('Text: ')

# Initalizes counters for L = letter, S = sentence, and W = word
L = 0
S = 0
W = 1

# Loops through every element of the text
for el in text:
    # Checks if alphabetical, if so adds 1 to L
    if el.isalpha():
        L += 1

    # If el is a space, it indicates a word. W is initialized as 1 because of the last word
    elif el == ' ':
        W += 1

    # Checks for the declared punctuation, which indicates a sentence
    elif el == '.' or el == '?' or el == '!':
        S += 1

# Calculates indices
L = (L / W) * 100
S = (S / W) * 100
index = 0.0588 * L - 0.296 * S - 15.8

# Handles special index values
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")