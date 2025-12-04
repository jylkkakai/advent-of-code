
# with open("example.txt", "r") as file:
with open("input.txt", "r") as file:
    total1 = 0
    for line in file: 
        line = line[:-1]
        # print(line)
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
print("Part 1: " + str(total1))
