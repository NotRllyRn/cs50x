from cs50 import get_string
from re import split

# define main function for all the main logic


def main():
    # get user input text
    text = get_string("Text: ")

    # gets the words and letters and sentences from functions and calculates the per 100 words for letters and sentences
    words = get_word_count(text)
    l_perWords = get_letter_count(text) / words * 100
    s_perWords = get_sentence_count(text) / words * 100

    # calculate the grade with the formula
    score = 0.0588 * l_perWords - 0.296 * s_perWords - 15.8

    # checks if the score is less than 1 or more than 16 and prints accordingly
    if score < 1:
        print("Before Grade 1")
    elif score > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(score)}")

# Loops through each character in a string and finds the letters


def get_letter_count(s):
    # define total letter count and loops through each character of string
    total = 0
    for c in s:
        # check if the character is an alphabetic character and adds to total if so
        if c.isalpha():
            total += 1

    return total

# loops through characters and finds . ? and !


def get_sentence_count(s):
    # define total sentences and loops through each character
    total = 0
    for c in s:
        # checks if its the end of a sentence and adds to the total
        if c in [".", "?", "!"]:
            total += 1

    return total

# splits the string and returns the length of the array


def get_word_count(s):
    # comment of the function says it all
    return len(split(" ", s))


# runs the main logic after all the functions are defined
main()