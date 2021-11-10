# File này chỉ chạy 1 lần duy nhất, toàn bộ bản đồ sẽ được in rõ

with open('../test/maze01.txt', 'w') as outfile:
    outfile.write('0\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx\n')
    outfile.write('x   x   xx xx        x\n')
    outfile.write('x     x     xxxxxxxxxx\n')
    outfile.write('x x    xx  xxxx xxx xx\n')
    outfile.write('  x   x x xx   xxxx  x\n')
    outfile.write('x          xx  xx  x x\n')
    outfile.write('xxxxxxx x      xx  x x\n')
    outfile.write('xxxxxxxxx  x x  xx   x\n')
    outfile.write('x          x x Sx x  x\n')
    outfile.write('xxxxx x  x x x     x x\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx')


with open('../test/maze02.txt', 'w') as outfile:
    outfile.write('0\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx\n')
    outfile.write('x   x   xx xx        x\n')
    outfile.write('x     x     xxx xxxxxx\n')
    outfile.write('x x     x  xxx  xxx xx\n')
    outfile.write('  x   x x xx   xxxx  x\n')
    outfile.write('x       x  xx  xx  x x\n')
    outfile.write('xxxxxxx x      xx  x x\n')
    outfile.write('xxxxxxxxx  x x  xx   x\n')
    outfile.write('x          x x Sx x  x\n')
    outfile.write('xxxxx x  x x x       x\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx')

with open('../test/maze03.txt', 'w') as outfile:
    outfile.write('0\n')

with open('../test/maze04.txt', 'w') as outfile:
    outfile.write('0\n')

with open('../test/maze05.txt', 'w') as outfile:
    outfile.write('0\n')

with open('../test/maze06.txt', 'w') as outfile:
    outfile.write('2\n')
    outfile.write('3 6 -3\n')
    outfile.write('5 14 -1\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx\n')
    outfile.write('x   x   xx xx        x\n')
    outfile.write('x     x     xxxxxxxxxx\n')
    outfile.write('x x   +xx  xxxx xxx xx\n')
    outfile.write('  x   x x xx   xxxx  x\n')
    outfile.write('x          xx +xx  x x\n')
    outfile.write('xxxxxxx x      xx  x x\n')
    outfile.write('xxxxxxxxx  x x  xx   x\n')
    outfile.write('x          x x Sx x  x\n')
    outfile.write('xxxxx x  x x x     x x\n')
    outfile.write('xxxxxxxxxxxxxxxxxxxxxx')

with open('../test/maze07.txt', 'w') as outfile:
    outfile.write('5\n')

with open('../test/maze08.txt', 'w') as outfile:
    outfile.write('10\n')
