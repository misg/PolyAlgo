import sys
from math import factorial

sys.setrecursionlimit(1000000)

class Tree:
    def __init__(self, val, left=None, right=None):
        self.val = val

        self.left = left
        self.right = right

        self.n_nodes = 1

        if (left is not None):
            self.n_nodes += left.n_nodes
        if (right is not None):
            self.n_nodes += right.n_nodes



def construct_tree(tree):
    if (not tree):
        return None

    i, p = 1, 0
    left = ""

    while (tree[i] != '.' or p != 0):
        if (tree[i] == '('):
            p += 1
        if (tree[i] == ')'):
            p -= 1

        left += tree[i]
        i += 1

    i += 1 # we found the root, ignore '.'

    val = ""

    while (tree[i] != '.'):
        val += tree[i]
        i += 1

    i += 1 # ignore '.'

    right = tree[i:-1]

    tree = Tree(int(val), construct_tree(left), construct_tree(right))

    return tree



def max_cost(tree):
    if (tree is None):
        return 0

    if (tree.left is None and tree.right is None):
        return 0

    return tree.val + max(max_cost(tree.left), max_cost(tree.right))



def n_binary_trees(n):
    res = [1, 1]

    for i in range(2, n+1):
        k = 0

        for j in range(1, i+1):
            k += res[j-1] * res[i-j]

        res.append(k)

    return res[n]



def print_infix_order(tree):
    if (tree is None):
        return ""

    print("(", end='')
    print_infix_order(tree.left)
    print("." + tree.val + ".", end='')
    print_infix_order(tree.right)
    print(")", end='')

    return ""

if __name__ == "__main__":
    tree = construct_tree(sys.stdin.readline().rstrip())
    print(max_cost(tree))
    print(n_binary_trees(tree.n_nodes))
