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


def BFS(matrix, start, end):
    open_list, visited = [start], [start]
    closed_list = []
    while open_list:
        current = open_list.pop(0)
        closed_list.append(current)
        if current == end:
            return closed_list
        for neighbor in find_next(current, matrix):
            if neighbor not in visited:
                open_list.append(neighbor)
                visited.append(neighbor)
    return closed_list
