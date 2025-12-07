lines1 = []
lines2 = []

with open("input.txt") as file:
# with open("example.txt") as file:
    for line in file:
        lines1.append(line.split())
        lines2.append(line[:-1])

# Part 1
ops = lines1[-1]
lines1.pop()

total = 0
for  i, op in enumerate(ops):
    sum = 0
    if op == '*':
        sum = 1
        for val in lines1:
            sum *= int(val[i])
    else:
        sum = 0
        for val in lines1:
            sum += int(val[i])
    total += sum

print("Part 1: " + str(total))

# Part 2
ops = lines2[-1]
lines2.pop()
total = 0
op = ''
sum = 0
vals = []
i = len(ops) - 1
while i >= 0:
    val = ""
    for line in lines2:
        val += line[i]
    vals.append(val)

    if ops[i] == '*':
        sum = 1
        for val in vals:
            sum *= int(val)
        i -= 1
        vals = []
    elif ops[i] == '+':
        sum = 0
        for val in vals:
            sum += int(val)
        i -= 1
        vals = []
    else:
        i -= 1
        continue
    total += sum
    i -= 1

print("Part 2: " + str(total))
