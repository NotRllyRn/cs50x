
def main():
    height = get_height()
    for i in range(height):
        print("#")

    print("?" * 4)

def get_int(s):
    while True:
        try:
            n = int(input(s))
            return n
        except:
            print("That is not an interger!")

def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0:
            return n
        else:
            print("Height has to be greater than 0!")

main()