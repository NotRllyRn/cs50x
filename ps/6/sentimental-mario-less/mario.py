from cs50 import get_int

# define main function


def main():
    # prompt the user for the height of the triangle
    height = get_height()

    # loop through the range
    for squares in range(1, height + 1):
        # print the strings (idk this is kind of weird and i don't wanna explain)
        empty = (height - squares)
        print((" " * empty) + ("#" * squares))

# function to get the height but rejects anything less than 1 and more than 8


def get_height():
    n = 0

    # loops until n is meets these conditions
    while n < 1 or n > 8:
        n = get_int("Height: ")

    return n


# run the function
main()