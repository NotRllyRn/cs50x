import sys

def main():
    if len(sys.argv) != 2:
        print("Missing command-line argument")
        sys.exit(1)
    else:
        print(f"hello, {sys.argv[1]}")

    sys.exit(0)

main()