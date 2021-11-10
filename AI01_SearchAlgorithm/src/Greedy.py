from math import *


def find_next(pos, matrix):
    next = []
    if (pos[0] - 1 >= 0 and matrix[pos[0]-1][pos[1]] != 'x'):
        next.append((pos[0]-1, pos[1]))
    if (pos[0] + 1 < len(matrix) and matrix[pos[0]+1][pos[1]] != 'x'):
        next.append((pos[0]+1, pos[1]))
    if (pos[1] + 1 < len(matrix[0]) and matrix[pos[0]][pos[1] + 1] != 'x'):
        next.append((pos[0], pos[1] + 1))
    if (pos[1] - 1 >= 0 and matrix[pos[0]][pos[1]-1] != 'x'):
        next.append((pos[0], pos[1]-1))
    return next


def heuristic_distance(node, end, bonus_points):
    for _, points in enumerate(bonus_points):
        if node == (points[0], points[1]):
            return points[2]
    return sqrt((node[0] - end[0])**2 + (node[1] - end[1])**2)


def Greedy(matrix, start, end, bonus_points):
    open_list = [start]
    closed_list = []
    while open_list:
        current = open_list.pop(0)
        closed_list.append(current)
        if current == end:
            return closed_list
        for neighbor in find_next(current, matrix):
            if (neighbor not in closed_list):
                open_list.append(neighbor)
        open_list.sort(key=lambda x: heuristic_distance(
            x, end, bonus_points))
    return None
