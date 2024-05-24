f = open("./ed.txt", "r")
r = open("./ed.csv", "w")
l = f.readlines()
counter = 0
sum = 0
lc = 0
averages = [[] for i in range(9)]
n = []
lineC = 0
for line in l:
    print(lineC)
    x = line.split(" ")
    sum += int(x[2])
    counter += 1
    if counter == 10:
        counter = 0
        averages[lc].append(sum / 10)
        sum = 0
        if lc == 0: n.append(int(x[2]))
    lineC += 1
    if lineC == 10:
        lineC = 0
        lc += 1
    
print(averages)
print(n)
for j in range(len(averages[0])):
    r.write(str(n[j]) + ";")
    for i in range(len(averages)):
        r.write(str(averages[i][j]) + ";")
    r.write("\n")

r.close()
f.close()