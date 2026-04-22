# https://www.luogu.com.cn/problem/P1352

from collections import deque
from itertools import islice
import sys
from typing import Tuple, Deque

input = sys.stdin.readline

class Node:
    def __init__(self, happiness: int):
        self.children: list[Node] = []
        self.dp_take = happiness
        self.dp_not_take = 0

    def add_child(self, child):
        self.children.append(child)

lines = sys.stdin.readlines()
n = int(lines[0])

clerks = list(map(Node, map(int, islice(lines, 1, n + 1))))

headmasters = set(range(n))
for line in islice(lines, n + 1, 2 * n):
    l, k = map(int, line.split())
    l, k = l - 1, k - 1
    clerks[k].add_child(clerks[l])
    headmasters.remove(l)

headmaster = clerks[headmasters.pop()]

stack: Deque[Tuple[Node, int]] = deque()


def push_until_leaf(node: Node):
    while node.children: # not leaf
        stack.append((node, 0))
        node = node.children[0]

push_until_leaf(headmaster)

while stack:
    parent, idx = stack.pop()
    leaf = parent.children[idx]
    parent.dp_take += leaf.dp_not_take
    parent.dp_not_take += max(leaf.dp_take, leaf.dp_not_take)
    idx += 1
    if idx < len(parent.children):
        child = parent.children[idx]
        stack.append((parent, idx))
        push_until_leaf(child)

print(max(headmaster.dp_take, headmaster.dp_not_take))
