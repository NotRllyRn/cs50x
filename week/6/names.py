import sys

names = ["Bill", "Charlie", "Fred", "Ron"]

if "Ron" in names:
    print("Found")
    sys.exit(0)

print("Not Found")
sys.exit(1)