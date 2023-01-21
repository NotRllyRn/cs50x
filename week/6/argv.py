from sys import argv

def main():
    if len(argv) == 2:
        print(f"hello, {argv[1]}")
    else:
        print("hello, world")

    for arg in argv[1:]:
        print(arg)

main()