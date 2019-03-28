import sys

sizes = [36, 36, 28, 28, 28, 24, 36, 36, 36, 36, 36, 18, 18, 18, 18, 18, 18, 14, 14, 14, 14, 14, 14, 14, 14]
accumSizes = [0]

for i in range(0, len(sizes)) :
	accumSizes.append(accumSizes[i] + sizes[i])

f = open("meshProxies_", "r")
o = open("meshLineIndex", "w")

while True :
	l = f.readline()
	if not l : break
	in1, in2, in3 = l.split()
	l1 = 0; l2 = 0; l3 = 0
	i1 = 0; i2 = 0; i3 = 0

	in1 = int(in1)
	in2 = int(in2)
	in3 = int(in3)

	for i in range(1, len(accumSizes)):
		if (l1 == 0 and in1 - accumSizes[i] <= 0):
			l1 = i 
			i1 = in1 - accumSizes[l1 - 1]

		if (l2 == 0 and in2 - accumSizes[i] <= 0):
			l2 = i
			i2 = in2 - accumSizes[l2 - 1]

		if (l3 == 0 and in3 - accumSizes[i] <= 0):
			l3 = i
			i3 = in3 - accumSizes[l3 - 1]

		if (l1 != 0 and l2 != 0 and l3 != 0):
			break

	o.write("%d %d %d %d %d %d\n" % (l1, i1, l2, i2, l3, i3))



f.close()
o.close()