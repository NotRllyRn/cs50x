from cs50 import get_float

# define main function


def main():
    # ask the user for their change and also conver it so that we can easily work with the value
    change = get_change() * 100

    # repeatedly calculates the change from the function and the function returns the amount of coins that fits and the amount of change left
    quarters, change = cal(change, 25)
    dimes, change = cal(change, 10)
    nickels, change = cal(change, 5)

    print(quarters + dimes + nickels + change)


# define the get change function which will ask the user how much they owe


def get_change():
    # keeps asking the user for change until the value is a positive value
    n = -1
    while n < 0:
        n = get_float("Change owed: ")

    return n

# returns the calculated amount that fits inside of change and returns the remainder


def cal(change, remain):
    # calculates the amount of change we get and the remainder of change we owe left
    amount = int(change / remain)
    remainder = change % remain

    # returns those 2 amounts in 1 function
    return (amount, remainder)


# run the main function
main()