from cs50 import get_int

scores = []

def main():
    for i in range(3):
        score = get_int("Score: ")
        scores.append(score)

    average = sum(scores) / len(scores)
    print(f"your average was {average}")

main()