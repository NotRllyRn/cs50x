from cs50 import get_string

def main():
    before = get_string("Before: ")
    after = before.upper()
    print(f"After:  {after}")

main()