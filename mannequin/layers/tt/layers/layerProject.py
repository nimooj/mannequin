import numpy as np
import math

v1 = open("Alesia_body_vertices.txt", "r")
alesia = []
while True:
	l = v1.readline()
	if not l: break

	x, y, z = l.split()
	x = float(x)
	y = float(y) + 0.75
	z = float(z) + 0.15

	alesia.append(np.array([x,y,z]))
v1.close()

v2 = open("Alesia_body_mesh.txt", "r")
alesia_mesh = []
alesia_center_points = []
while True:
	line = v2.readline()
	if not line : break

	l = line.split()

	if len(l) == 3 :
		in1 = int(l[0])
		in2 = int(l[1])
		in3 = int(l[2])

		mesh = np.array([alesia[in1 - 1], alesia[in2 - 1], alesia[in3 - 1]])
		alesia_mesh.append(mesh)
		alesia_center_points.append(np.sum(mesh, axis=0)/3)

	elif len(l) == 4 :
		in1 = int(l[0])
		in2 = int(l[1])
		in3 = int(l[2])
		in4 = int(l[3])

		mesh = np.array([alesia[in1 - 1], alesia[in2 - 1], alesia[in3 - 1], alesia[in4 - 1]])
		alesia_mesh.append(mesh)
		alesia_center_points.append(np.sum(mesh, axis=0)/4)
v2.close()


flatten_alesia = []
f = open("Alesia_flat.txt", "w")
for v in alesia :
	f.write("%.3f\t%.3f\n" % (v[0], v[1]))
f.close()


"""
startHeight = 9
endHeight = -9
interval = 0.2
radius = 2
floors = 1
layerSize = 0

f = open("cylinder.txt", "w")
height = startHeight
while height > endHeight :
	layerSize = 0
	degree = 0
	while degree < 360 :
		f.write("%f %f %f\n" % (radius * math.cos(math.radians(degree)), height, radius * math.sin(math.radians(degree))))
		degree += 5
		layerSize += 1

	height -= interval
	floors += 1

f.close()

f = open("cylinder_mesh.txt", "w")
index = 1
while index < floors - 1 :
	for i in range(0, layerSize - 1) :
		f.write("%d %d %d %d\n" % (layerSize * (index - 1) + i + 1, layerSize * (index - 1) + i + 2, layerSize * index + i + 2, layerSize * index + i + 1))
	# 36 1 37 72
	f.write("%d %d %d %d\n" % (index * layerSize, index * layerSize - (layerSize - 1), index * layerSize + 1, (index + 1) * layerSize))
	index += 1

f.close()
"""

### Import layers ###
#f = open("body_vertices.txt", "r")
f = open("cylinder.txt", "r")
layerHeight = 0
vertices = []
while True:
	line = f.readline()
	if not line : break

	x, y, z = line.split()
	x = float(x)
	y = float(y)
	z = float(z)
	vertices.append(np.array([x, y, z]))

	#layerHeight = y
f.close()
#####################

### Select meshes in problem ###
"""
alesia_consider = [] # Array of meshes ... [[vertex1, vertex2, vertex3, vertex4], ..., [vertex1, vertex2, vertex3, vertex4]]
for i, m in enumerate(alesia_center_points) :
	if m[1] < layerHeight + 0.3 and m[1] > layerHeight - 0.3 :
		alesia_consider.append(alesia_mesh[i]) 
"""
################################

### Find closest mesh from each layer point ###
newVertices = []
layerHeight = vertices[0][1]
for lv in vertices:
	if lv[1] == layerHeight :
		alesia_consider = []
		alesia_consider_idx = []
		for i, m in enumerate(alesia_center_points) :
			if m[1] < layerHeight + 0.1 and m[1] > layerHeight - 0.1 :
				alesia_consider.append(alesia_mesh[i]) 
				alesia_consider_idx.append(i)
	else : layerHeight = lv[1]

	distance = 1000
	normal = []
	center = np.array([0, 0, 0])
	for i, p in enumerate(alesia_consider) :
		######## TUESDAY TO DO :: GET INTERSECTION OF lv-center and Mesh in question #######
		"""
		u = np.subtract(p[1], p[0])
		v = np.subtract(p[2], p[0])
		tmp_n = np.cross(u, v)
		n = tmp_n / np.sqrt(np.power(tmp_n, 2).sum()) 

		point_to_surface = np.subtract(lv, p[0])	

		if abs(np.dot(point_to_surface, n)) < distance :
			distance = abs(np.dot(point_to_surface, n))
			closest_mesh = p
			length = len(closest_mesh)
			center = closest_mesh.sum(axis = 0) / length
			center[1] = lv[1]

	### Project to closest mesh ###
	newVertices.append(center)
	"""
	##############################
###############################################

print(newVertices)

o = open("new_Vertices.txt", "w")
for v in newVertices :
	if len(v) > 0 :
		o.write("%.3f %.3f %.3f\n" % (v[0], v[1], v[2]))	
o.close()

o = open("newBody.obj", "w")
for v in newVertices :
	if len(v) > 0 :
		o.write("v %.3f %.3f %.3f\n" % (v[0], v[1], v[2]))	

m = open("cylinder_mesh.txt", "r")
while True :
	line = m.readline()
	if not line : break

	o.write("f %s" % (line))

m.close()
o.close()
