
import sys

# data = [100, 50, 20, 10]  # feet/minute
# length = 100  # feet

# data = [100, 50, 20, 10, 2.5]
# length = 250

data = [100, 50, 20, 10, 25, 15]
length = 150

mintime = 100000

def move_back(current, result, sum):
    global mintime
    index = [i for i, e in enumerate(current) if e == 1]
    if len(index) == len(data):
        mintime = min(sum, mintime)
        print(result, sum)
        return
    for i in range(len(index)):
        next = current.copy()
        next[index[i]] = 0
        move_forward(next, result + [next], sum + length/data[index[i]])

def move_forward(current, result, sum):
    index = [i for i, e in enumerate(current) if e == 0]
    if len(index) == 0:
        print(result, sum)
        return
    if len(index) == 1:
        print(result, sum + length/data[index[0]])
        return
    for i in range(len(index)):
        for j in range(i + 1, len(index)):
            next = current.copy()
            next[index[i]] = 1
            next[index[j]] = 1
            move_back(next, result + [next], sum + length/min(data[index[i]], data[index[j]]))

def main():
    current = [0] * len(data)
    move_forward(current, [current], 0)
    print(mintime)

if __name__ == "__main__":
    main()
