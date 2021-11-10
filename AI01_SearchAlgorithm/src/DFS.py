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


def DFS(matrix, start, end):
    stack, visited = [start], [start]
    route = []
    while (stack):
        n = stack.pop()
        route.append(n)
        if n == end:
            # route.append(i for i in stack if i in visited)
            # print(route)
            return route

        next_step = find_next(n, matrix)
        print(next_step)

        for x in next_step:
            if x not in visited:
                visited.append(x)
                stack.append(x)
    return None
