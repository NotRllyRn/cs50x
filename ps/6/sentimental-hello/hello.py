from cs50 import get_string

# define main function


def main():
    # ask the user for their name
    # print out their name with format string
    name = get_string("What is your name?\n")
    print(f"hello, {name}")


# run the main function
main()