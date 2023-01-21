from cs50 import get_int

# define the main function


def main():
    # get the height for the pyramid
    # loop through range starting at 1 and goes yp to the max height
    height = get_height()
    for squares in range(1, height + 1):
        # calculates the string for the white space and squares
        white_space = " " * (height - squares)
        squares_string = "#" * squares

        # prints out the line
        print(white_space + squares_string + "  " + squares_string)

# get height function to get the user input


def get_height():
    n = 0

    # loops until n is meets these conditions
    while n < 1 or n > 8:
        n = get_int("Height: ")

    return n


# runs the function
main()