from enum import Enum
from math import inf # default node weight
import sys

# data = [100, 50, 20, 10]  # feet/minute
# length = 100  # feet

# data = [100, 50, 20, 10, 2.5]
# length = 250

data = [100, 50, 20, 10, 25, 15]
length = 150

## TODO: this should be a class

all_nodes = {}

def make_key(code, type):
    s = ''.join(map(str, code))
    s += 'L' if type == node_type.left else 'R'
    return s

def get_node(code, type):
    hash = make_key(code, type)
    if hash in all_nodes.keys():
        res = all_nodes[hash]
    else:
        res = node(code, inf, type)
        all_nodes[hash] = res
    return res

#####

class node_type(Enum):
    left = 1
    right = 2

class node():
    """ Represents state after one crossing of the bridge """
    def __init__(self, code, weight, type):
        self.code = code
        self.weight = weight
        self.type = type
        self.prev = None
        self.visited = False

    def __str__(self):
        s = 'Node['
        s += 'code: ' + ''.join(map(str, self.code))
        s += 'L' if self.type == node_type.left else 'R'
        s += ', cost: ' + str(self.weight)
        s += ',*' if not self.visited else ', '
        s += ', prev: ' if self.prev == None else ', prev: ' + self.prev
        s += ']'
        return s

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return make_key(self.code, self.type) == make_key(other.code, other.type)

    def __ne__(self, other):
        return not self == other

    def _right_neighbors(self):
        """ neighbors of the left node are right nodes """
        result = []
        index = [i for i, e in enumerate(self.code) if e == 0]
        for i in range(len(index)):
            for j in range(i + 1, len(index)):
                next = self.code.copy()
                next[index[i]] = 1
                next[index[j]] = 1
                cost = max(length/data[index[i]], length/data[index[j]])
                node = get_node(next, node_type.right)
                result.append((node, cost))
        return result

    def _left_neighbors(self):
        """ neighbors of the right node are left nodes """
        result = []
        index = [i for i, e in enumerate(self.code) if e == 1]
        for i in range(len(index)):
            next = self.code.copy()
            next[index[i]] = 0
            cost = length/data[index[i]]
            node = get_node(next, node_type.left)
            result.append((node, cost))
        return result

    def neighbors(self):
        """ neighbors of the node """
        if self.type == node_type.left:
            return self._right_neighbors()
        else:
            return self._left_neighbors()

    def make_key(self):
        s = ''.join(map(str, self.code))
        s += 'L' if self.type == node_type.left else 'R'
        return s
       

def reconstruct(start, end):
    node = end
    key = node.make_key()
    start_key = start.make_key()
    path = []
    while key != start_key:
        node = all_nodes[key]
        path.append((key, node.weight))
        key = node.prev
    path.append((start_key, 0))
    path.reverse()
    return path


def dijkstra(start, end):
    pending = [start]
    while pending:
        current = pending.pop(0)
        # print(current)
        if current.visited:
            continue
        neighbors = current.neighbors()
        for node, cost in neighbors:
            if node.weight > cost + current.weight:
                node.weight = cost + current.weight
                node.prev = make_key(current.code, current.type)
            pending.append(node)
            # print('     ', node)
        current.visited = True

def main():
    start = node([0] * len(data), 0, node_type.left)
    end = node([1] * len(data), inf, node_type.right)
    dijkstra(start, end)
    print("Visited nodes:")
    for code in all_nodes:
        print(code, ':', all_nodes[code])
    print()
    print("Reconstructed path:")
    print(reconstruct(start, end))

if __name__ == "__main__":
    main()
