main1 = 9
main2 = 10
l1 = open("main/"+str(main1) + ".txt", "r")
l2 = open("main/"+str(main2)+".txt", "r")

v1 = []
v2 = []

while True:
	line1 = l1.readline()
	if not line1 : break

	x, y, z = line1.split()
	x = float(x)
	y = float(y)
	z = float(z)

	v1.append([x, y, z])

while True:
	line2 = l2.readline()
	if not line2 : break

	x, y, z = line2.split()
	x = float(x)
	y = float(y)
	z = float(z)
	v2.append([x, y, z])


l1.close()
l2.close()

# sub layer generation
num = 6
interval = (v1[0][1] - v2[0][1])/float(num)
layerSize = len(v1)

count = 1
y = v1[0][1] - interval

while y > v2[0][1] :
	f = open(str(29 + count) + ".txt", "w")

	for i in range(0, layerSize) :
		x = (v1[i][0] * (num - count) + v2[i][0] * count) / float(num)
		z = (v1[i][2] * (num - count) + v2[i][2] * count)/ float(num)

		f.write("%.3f %.3f %.3f\n" %(x, y, z))

	f.close()
	count += 1


	y -= interval
