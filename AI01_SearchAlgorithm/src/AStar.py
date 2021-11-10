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


def heuristic_distance(node, end):
    return sqrt((node[0] - end[0])**2 + (node[1] - end[1])**2)


def actual_distance(node, start):
    return sqrt((node[0] - start[0])**2 + (node[1] - start[1])**2)


def total_cost(node, start, end):
    return heuristic_distance(node, end) + actual_distance(node, start)


def reconstruct(nodeFrom, current):
    final = [current]
    while current in nodeFrom:
        current = nodeFrom[current]
        final.append(current)
    return final


# def AStar(matrix, start, end):
    # opened = [start]
    # closed = []
    # while opened:
    # current = opened.pop(0)
    # closed.append(current)
#
    # if current == end:
    # return closed
#
    # for neighbor in find_next(current, matrix):
    # if neighbor not in closed:
    # opened.append(neighbor)
    # opened.sort(key=lambda x: total_cost(x, start, end))
    # return None

def AStar(matrix, start, end):
    F, G = {}, {}
    G[start] = 0
    F[start] = heuristic_distance(start, end)
    closed = []
    opened = [start]
    camefrom = {}

    while opened:
        current = None
        currentF = None
        for pos in opened:
            if current is None or F[pos] < currentF:
                currentF = F[pos]
                current = pos

        if current == end:
            route = [current]
            while current in camefrom:
                current = camefrom[current]
                route.append(current)
            route.reverse()
            return route

        opened.remove(current)
        closed.append(current)
        next_step = find_next(current, matrix)
        for neighbor in next_step:
            if neighbor in closed:
                continue
            candidateG = G[current] + actual_distance(current, start)

            if neighbor not in opened:
                opened.append(neighbor)
            elif candidateG >= G[neighbor]:
                continue

            camefrom[neighbor] = current
            G[neighbor] = candidateG
            H = heuristic_distance(neighbor, end)
            F[neighbor] = G[neighbor] + H
    return None
