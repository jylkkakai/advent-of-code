
ranges =[]
ids = []
# with open("example.txt") as file:
with open("input.txt") as file:
    for line in file:
        if line.isspace():
            break
        ranges.append(line[:-1])
    for line in file:
        ids.append(line[:-1])

# Part 1
count = 0

for r in ranges:
    a, b = r.split('-')
    for i, id in enumerate(ids):
        if int(id) >= int(a) and int(id) <= int(b):
            ids[i] = 0
            count += 1

print("Part 1: " + str(count))

# Part 2 
count = 0
fid = 0 
def sortkey(a):
    return int(a.split('-')[0])
ranges.sort(key=sortkey)

i = 0
while(i < len(ranges) - 1):
    a = ranges[i]
    b = ranges[i + 1]
    if int(b.split('-')[0]) <= int(a.split('-')[1]):
        ranges[i] = a.split('-')[0] + '-' + max(b.split('-')[1], a.split('-')[1])
        ranges.remove(b)
    else:
        i += 1

for r in ranges:
    a, b = r.split('-')
    fid += int(b) - int(a) + 1


print("Part 2: " + str(fid))

