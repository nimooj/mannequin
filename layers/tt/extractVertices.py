f = open("Body.obj", "r")
o = open("body_vertices.txt", "w")

v = []

maxZ = -100
minZ = 100

maxX = -100
minX = 100

maxY = -100
minY = 100

while True:
	line = f.readline()
	if not line : break

	if line[0] == "v" :
		x, y, z = line[2:].split()
		#o.write("%s %s %s\n" %(x, y, z))
		v.append([float(x), float(y), float(z)])
		if (maxZ < float(z)) :
			maxZ = float(z)
		if (minZ > float(z)) :
			minZ = float(z)

		if (maxX < float(x)) :
			maxX = float(x)
		if (minX > float(x)) :
			minX = float(x)

		if (maxY < float(y)) :
			maxY = float(y)
		if (minY > float(y)) :
			minY = float(y)

f.close()

center = [(maxX + minX)/2, (maxY + minY)/2, (maxZ + minZ)/2]

for i in v  :
	o.write("%.3f %.3f %.3f\n" % (i[0]-center[0], i[1]-center[1], i[2]-center[2]))

o.close()



f = open("Alesia_body.obj", "r")
o = open("Alesia_body_vertices.txt", "w")
v = []

maxZ = -100
minZ = 100

maxX = -100
minX = 100

maxY = -100
minY = 100

while True:
	line = f.readline()
	if not line : break

	if line[0] == "v" :
		x, y, z = line[2:].split()
		#o.write("%s %s %s\n" %(x, y, z))
		v.append([float(x), float(y), float(z)])
		if (maxZ < float(z)) :
			maxZ = float(z)
		if (minZ > float(z)) :
			minZ = float(z)

		if (maxX < float(x)) :
			maxX = float(x)
		if (minX > float(x)) :
			minX = float(x)

		if (maxY < float(y)) :
			maxY = float(y)
		if (minY > float(y)) :
			minY = float(y)

f.close()

center = [(maxX + minX)/2, (maxY + minY)/2, (maxZ + minZ)/2]

for i in v  :
	o.write("%.3f %.3f %.3f\n" % ((i[0]-center[0])/10, (i[1]-center[1])/10, (i[2]-center[2])/10))

o.close()

