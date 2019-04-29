filename = "Alesia_body"
f = open(filename + ".obj", "r")

vertices = []
normals = []
meshes = []

vnormals = []

while True:
	line = f.readline()
	if not line : break

	if line[0:2] == "v " :
		x, y, z = line[2:].split()
		x = float(x)
		y = float(y)
		z = float(z)
		vertices.append([x/10, y/10, z/10])
		vnormals.append([])

	if line[0:2] == "vn" :
		x, y, z = line[2:].split()
		x = float(x)
		y = float(y)
		z = float(z)
		normals.append([x, y, z])

	if line[0:2] == "f " :
		l = line[2:].split()

		if len(l) == 3:
			l1 = l[0]
			l2 = l[1]
			l3 = l[2]

			if "/" in l1 :
				vIdx1, tIdx1, nIdx1 = l1.split("/")
				vIdx2, tIdx2, nIdx2 = l2.split("/")
				vIdx3, tIdx3, nIdx3 = l3.split("/")

				vIdx1 = int(vIdx1)
				vIdx2 = int(vIdx2)
				vIdx3 = int(vIdx3)

				if tIdx1 != "":
					tIdx1 = int(tIdx1)
					tIdx2 = int(tIdx2)
					tIdx3 = int(tIdx3)

				if nIdx1 != "":
					nIdx1 = int(nIdx1)
					nIdx2 = int(nIdx2)
					nIdx3 = int(nIdx3)

				vnormals[vIdx1 - 1] = [vIdx1, normals[nIdx1 - 1]]
				vnormals[vIdx2 - 2] = [vIdx2, normals[nIdx2 - 2]]
				vnormals[vIdx3 - 3] = [vIdx3, normals[nIdx3 - 3]]
			else :
				vIdx1 = float(l1)
				vIdx2 = float(l2)
				vIdx3 = float(l3)

			#meshes.append([vertices[vIdx1 - 1], vertices[vIdx2 - 1], vertices[vIdx3 - 1]])
			meshes.append([vIdx1, vIdx2, vIdx3])

		elif len(l) == 4:
			l1 = l[0]
			l2 = l[1]
			l3 = l[2]
			l4 = l[3]

			if "/" in l1 :
				vIdx1, tIdx1, nIdx1 = l1.split("/")
				vIdx2, tIdx2, nIdx2 = l2.split("/")
				vIdx3, tIdx3, nIdx3 = l3.split("/")
				vIdx4, tIdx4, nIdx4 = l4.split("/")

				vIdx1 = int(vIdx1)
				vIdx2 = int(vIdx2)
				vIdx3 = int(vIdx3)
				vIdx4 = int(vIdx4)

				if tIdx1 != "":
					tIdx1 = int(tIdx1)
					tIdx2 = int(tIdx2)
					tIdx3 = int(tIdx3)
					tIdx4 = int(tIdx4)

				if nIdx1 != "":
					nIdx1 = int(nIdx1)
					nIdx2 = int(nIdx2)
					nIdx3 = int(nIdx3)
					nIdx4 = int(nIdx4)

				vnormals[vIdx1 - 1] = [vIdx1, normals[nIdx1 - 1]]
				vnormals[vIdx2 - 2] = [vIdx2, normals[nIdx2 - 2]]
				vnormals[vIdx3 - 3] = [vIdx3, normals[nIdx3 - 3]]
				vnormals[vIdx4 - 4] = [vIdx4, normals[nIdx4 - 4]]
			else :
				vIdx1 = l1
				vIdx2 = l2
				vIdx3 = l3
				vIdx4 = l4

			#meshes.append([vertices[vIdx1 - 1], vertices[vIdx2 - 1], vertices[vIdx3 - 1], vertices[vIdx4 - 1]])
			meshes.append([vIdx1, vIdx2, vIdx3, vIdx4])


f.close()

"""
if len(vnormals)>0 :
	o = open(filename + "_normals.txt", "w")
	for i, v in enumerate(vnormals) :
		o.write("%d %.3f %.3f %.3f\n" %(v[0], v[1][0], v[1][1], v[1][2]))
	o.close()
"""

o = open(filename + "_mesh.txt", "w")
for i, v in enumerate(meshes) : 
	if len(meshes[i]) == 3 :
		o.write("%d %d %d\n" % (v[0], v[1], v[2]))
	elif len(meshes[i]) == 4 :
		o.write("%d %d %d %d\n" % (v[0], v[1], v[2], v[3]))

o.close()
