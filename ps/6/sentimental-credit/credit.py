from cs50 import get_string

# define the main function with the main logic


def main():
    # ask the user for their credit card number
    number = get_string("Number: ")

    # define a total variable and get the array of the string (the number) from the user.
    total = 0
    arr = seperate(number)

    # declare a variable to keep track on what we are suppose to be doing with the numbers
    # starts a loop going backwards through the card
    on = 0
    for i in range(len(arr) - 1, -1, -1):
        # makes sure that the number gets converted to an int for performing calculations
        n = int(arr[i])

        # checks what iteration we are on but its the oposite since we start on 0 index of i
        if on % 2 == 0:
            # adds every other number backwards to a total
            total += n
        else:
            # multiplies that number by 2 and seperates the total into a string
            before = n * 2
            b_arr = seperate(str(before))

            # adds each indivisual number to the total
            for number in b_arr:
                total += int(number)

        # update the count so we can keep track what to do next
        on += 1

    # check if its valid
    # and get the first 2 characters of the credit card number
    valid = total % 10 == 0
    beg = int(arr[0] + arr[1])

    # does a bunch of checking to see if the cards are valid or not like checking the length and the first 2 numbers in the card
    if not valid:
        print("INVALID")
    elif beg in [34, 37] and len(arr) == 15:
        print("AMEX")
    elif beg in [51, 52, 53, 54, 55] and len(arr) == 16:
        print("MASTERCARD")
    elif arr[0] == "4" and (len(arr) in [13, 16]):
        print("VISA")
    else:
        print("INVALID")

# function that takes a string as input and returns an array of characters of the string


def seperate(s):
    # create the array
    seperated = []

    # loop through the string
    for c in s:
        # append to array
        seperated.append(c)

    return seperated


# run the main function
main()