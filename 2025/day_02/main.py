import math

with open("input.txt", "r") as file:
# with open("example.txt", "r") as file:
# with open("example2.txt", "r") as file:
    data = file.read()[:-1]
    ranges = data.split(",")

    sum1 = 0
    sum2 = 0
    for rang in ranges:
        start,end = rang.split("-")

        # Part 1
        for i in range(int(start), int(end) + 1):
            s = str(i)
            if len(s) % 2:
                continue
            half = int(len(s)/2)
            if s[:half] == s[half:]:
                sum1 += int(s)
 
        # Part 2
        for i in range(int(start), int(end) + 1):
            s = str(i)
            if len(s) < 2:
                continue
            half = int(len(s)/2)
            is_invalid = True 
            for step in range(1, half + 1):
                is_invalid = True 
                seq = s[:step]
                for pos in range(1, int(math.ceil(len(s)/step))):
                    # print("Step: " + str(step) + " Seq: " + str(seq) + " Pos: " + str(pos))
                    if s[:step] != s[pos*step:pos*step+step]:
                        is_invalid = False 
                        break
                if is_invalid:
                    break
            if  is_invalid:
                # print(s)
                sum2 += int(s)


print("Part 1:" + str(sum1))
print("Part 2:" + str(sum2))
