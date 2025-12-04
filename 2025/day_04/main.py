import numpy as np


grid = []
with open("input.txt") as file:
# with open("example.txt") as file:
    grid = []
    for line in file:
        grid.append(list(line[:-1]))


ngrid = np.array(grid)
rows, cols = ngrid.shape
rolls1 = 0
rolls2 = 0
# Part 1
for i in range(0, rows):
    for j in range(0, cols):
        if ngrid[i, j] == '@':
            cnt = np.count_nonzero(ngrid[max(i - 1, 0): min(i + 2, rows), max(j - 1, 0): min(j + 2, cols)] == '@')
            if cnt < 5:
                rolls1 += 1

# Part 2
removed = True
while(removed):
    removed = False
    for i in range(0, rows):
        for j in range(0, cols):
            if ngrid[i, j] == '@':
                cnt = np.count_nonzero(ngrid[max(i - 1, 0): min(i + 2, rows), max(j - 1, 0): min(j + 2, cols)] == '@')
                if cnt < 5:
                    rolls2 += 1
                    removed = True
                    ngrid[i, j] = '.'
                 
print("Part 1: " + str(rolls1))
print("Part 2: " + str(rolls2))
