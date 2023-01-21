from cs50 import get_string

a = get_string("Do you agree? ").upper()

if a in ["Y", "YES"]:
    print("Cool brah")
elif a in ["N", "NO"]:
    print("not cool man")