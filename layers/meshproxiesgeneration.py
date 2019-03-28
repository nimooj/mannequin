import sys

sizes = [36, 36, 28, 28, 28, 24, 36, 36, 36, 36, 36, 18, 18, 18, 18, 18, 18, 14, 14, 14, 14, 14, 14, 14, 14]
accumSizes = [0]

for i in range(0, len(sizes)) :
	accumSizes.append(accumSizes[i] + sizes[i])

o = open("meshLineIndex", "r")
f = open("meshProxies", "w")

while True :
	l = o.readline()
	if not l : break
	l1, i1, l2, i2, l3, i3 = l.split()
	in1 = 0; in2 = 0; in3 = 0
	l1 = int(l1)
	l2 = int(l2)
	l3 = int(l3)
	i1 = int(i1)
	i2 = int(i2)
	i3 = int(i3)

	in1 = accumSizes[l1 - 1] + i1
	in2 = accumSizes[l2 - 1] + i2
	in3 = accumSizes[l3 - 1] + i3

	f.write("%d %d %d\n" % (in1, in2, in3))


f.close()
o.close()