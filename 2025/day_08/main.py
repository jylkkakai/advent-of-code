import math

boxes = []
# with open("example.txt", "r") as file:
with open("input.txt", "r") as file:
    for line in file:
        boxes.append([line[:-1]])


dists = []

for i, vali in enumerate(boxes):
    a = vali[0].split(',')
    # print(i, len(dists))
    for j in range(i + 1, len(boxes)):
        b = boxes[j][0].split(',')
        dist = math.sqrt(pow(int(a[0]) - int(b[0]), 2) + pow(int(a[1]) - int(b[1]), 2) + pow(int(a[2]) - int(b[2]), 2))
        if dist > 0:
            dists.append([str(dist), vali[0], boxes[j][0]])

def dis_sort(a):
    return float(a[0])
def len_sort(a):
    return len(a)

dists.sort(key=dis_sort)
# num_pairs = 10
num_pairs = 1000
ans1 = 1
ans2 = 0
for i, dist in enumerate(dists):
    a, b = dist[1:]
    x = 0
    y = 0
    for j, box in enumerate(boxes):
        if a in box:
            x = j
        if b in box:
            y = j
    if x != y:
        boxes[x] = boxes[x] + boxes[y]
        boxes.remove(boxes[y])
    if i == num_pairs - 1:
        boxes.sort(reverse=True, key=len_sort)
        for i in range(3):
            ans1 *= len(boxes[i])
        print("Part 1: ", ans1)
    if len(boxes) == 1:
        ans2 = int(a.split(',')[0]) * int(b.split(',')[0])
        print("Part 2: ", ans2)
        break

