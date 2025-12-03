
# with open("example.txt", "r") as lines:
with open("input.txt", "r") as lines:
    answer1 = 0
    answer2 = 0
    result = 50
    old_result = 50
    
    for line in lines:
        num = int(line[1:-1])
        if line[0] == 'R':
            result += num 
            result = result % 100
            answer2 += int((old_result + num)/100) 
        elif line[0] == 'L':
            result -= num 
            if result == 0:
                answer2 += 1
            if result < 0:
                if old_result != 0:
                    answer2 += 1
                answer2 += int((num - old_result)/100) 
                result = result % 100
        if result == 0:
            answer1 += 1
        old_result = result

print("Part 1:\t" + str(answer1))
print("Part 2:\t" + str(answer2))
