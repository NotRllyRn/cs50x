import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        # if the argument count is not equal to 3 then we have to tell the user how to use the program and also exit the program
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    dna_data = {}

    # opens the csv file and makes a dict reader
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        # goes through each row
        for row in reader:
            # gets the name and pops the name out of the dict
            name = row["name"]
            row.pop("name")

            # creates a new dict in the new variable
            dna_data[name] = {}

            # copies all the values from the row to the new dict but makes sure to convert them to intergers
            for key in row.keys():
                dna_data[name][key] = int(row[key])

    # TODO: Read DNA sequence file into a variable
    dna_sequence = ""

    # opens file and creates a reader instance
    with open(sys.argv[2], "r") as file:
        reader = csv.reader(file)

        # goes through each row
        for row in reader:
            # adds the dna sequence to a string
            dna_sequence += row[0]

    # TODO: Find longest match of each STR in DNA sequence
    # makes a new table store the number of repeated str's we fine
    # gets the first person in the dna data list
    dna_sequences = {}
    first_person = list(dna_data.values())[0]

    # loops through all the subsequences and puts them in the dna sequence dict
    for key in first_person.keys():
        dna_sequences[key] = 0

    # goes through all the keys in the dict and finds the longest match in the sequence provided
    # updates the dict with the longest sequence found
    for key in dna_sequences.keys():
        total = longest_match(dna_sequence, key)
        dna_sequences[key] = total

    # TODO: Check database for matching profiles
    # goes through all the people data
    for name in dna_data.keys():
        # gets their sequences
        person = dna_data[name]

        # creates a variable to check if someone matches
        # loops through their keys and checks if the sequence repeats do not match
        same = True
        for key in person.keys():
            if person[key] != dna_sequences[key]:
                # if they don't they it will set the true variable to false
                same = False

        # if they succesfully pass with all the same repeats then it will print their name and exit the program
        if same:
            print(name)
            sys.exit(0)

    # if it did not find a match then it will print out no match and exit the program safely.
    print("No match")
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
