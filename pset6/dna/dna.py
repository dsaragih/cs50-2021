import sys
import csv
import re

# Checks that input is as required
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")


STRs = []  # Array that stores the STRs in consideration
data = []  # Array of dictionaries with the name and STRs being considered
seq = ''   # String that contains the text file

with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        # Adds the data points to the data array
        data.append(row)

        # Appends the STRs to the STRs array
    for key in data[0].keys():
        if key != 'name':
            STRs.append(key)


with open(sys.argv[2]) as t:
    # Reads the text file into memory
    seq = t.read()

max_dict = {}  # Initalizes space to store the STRs

for STR in STRs:

    maxm = 0  # Maximum counter for every STR
    counter = 1  # Counter for each instance of an STR, initialized to 1 to consider the first STR found

    # Finds the starting indices of all instances of STR
    indices = [m.start() for m in re.finditer(STR, seq)]

    for i in range(len(indices) - 1):
        # If the difference between two consecutive indices are of length STR,
        # then they are consecutive STRs
        if indices[i + 1] - indices[i] == len(STR):
            # Counts how many STRs we have found that are consecutive
            counter += 1
        else:
            # If the difference are not of length STR
            # then there is a gap which breaks the chain
            if counter > maxm:
                # If the previous chain is longer than the longest chain found, update maxm
                maxm = counter

            # Resets counter to 1, preparing for the next chain
            counter = 1

    # Checks if counter is greater than longest chain yet
    if counter > maxm:
        maxm = counter

    # Input this maximum to the dictionary
    max_dict[STR] = maxm


def find_match():
    # Iterates over all persons under consideration
    for person in data:

        # If the number of consecutive STRs is the same as that in max_dict,
        # the conditional will yield True, if not then False
        if all([int(person[key]) == max_dict[key] for key in person.keys() if key != 'name']):
            # Only if all STRs yield True, then the person's name will be returned
            return person['name']

    # If no one in the array has the same STR data as that in max_dict, "No match" is returned
    return "No match"


print(find_match())