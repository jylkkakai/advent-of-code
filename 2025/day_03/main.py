
# with open("example.txt", "r") as file:
with open("input.txt", "r") as file:
    total1 = 0
    total2 = 0
    for line in file: 
        line = line[:-1]
        # print(line)
        # Part 1
        jolt = [line[0], line[1]] 
        for i in range(2, len(line)):
            if int(jolt[1]) > int(jolt[0]):
                jolt[0] = jolt[1]
                jolt[1] = line[i]
            elif int(line[i]) > int(jolt[1]):
                # print(jolt[1], line[i])
                jolt[1] = line[i]

        # print(jolt)
        total1 += int(jolt[0])*10 + int(jolt[1])

        # Part 2
        jolt = list(line[:12])
        for i in range(12, len(line)):
            for j in range(0, len(jolt) - 1):
                if int(jolt[j]) < int(jolt[j + 1]):
                    jolt[j:-1] = jolt[j + 1:]
                    jolt[11] = line[i]
                    break
            if int(line[i]) > int(jolt[11]):
                jolt[11] = line[i]

        # print(int("".join(jolt)))
        total2 += int("".join(jolt))
print("Part 1: " + str(total1))
print("Part 2: " + str(total2))
