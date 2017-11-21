import random

def lotto(ticket):
    if sorted(ticket) == random.sample(range(1, 50), 6):
        print "Winner"
    print "Loser"

if __name__ == "__main__":
	lotto([1, 2, 3, 4, 5, 6])

