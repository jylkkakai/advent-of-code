
diag = []
with open("input.txt") as file:
# with open("example.txt") as file:
    for line in file:
        diag.append(line[:-1])

# Part 1
spls = set()
spls.add(diag[0].find('S'))
count = 0
for line in diag:
    tspls = set()
    rspls = set()
    for spl in spls:
        if line[spl] == '^':
            tspls.add(spl - 1)
            tspls.add(spl + 1)
            rspls.add(spl)
            count += 1
    spls.difference_update(rspls)
    spls.update(tspls)
print("Part 1: " + str(count))

# Part 2
count = 0
timelines = [[0 for _ in row] for row in diag]
for y in range(0,len(diag)):
    for x in range(0, len(diag[0])):
        c = diag[y][x]
        n = 1
        if c == 'S':
            timelines[y][x] = 1
        elif c == '^':
            timelines[y][x-1] += timelines[y-1][x]
            timelines[y][x+1] += timelines[y-1][x] + timelines[y-1][x+1]
        else:
            timelines[y][x] = max(timelines[max(y-1,0)][x],timelines[y][x])

count = [sum(i for i in timelines[-1])]
print("Part 2: " + str(count[0]))


