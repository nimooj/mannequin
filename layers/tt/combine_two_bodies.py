v1 = open("body_vertices.txt", "r")

bv = []

while True:
	l = v1.readline()
	if not l: break

	x, y, z = l.split()
	x = float(x)
	y = float(y) - 0.75
	z = float(z) - 0.15
	scale = 1.1
	bv.append([x*scale, y*scale,z*scale])
v1.close()

v2 = open("Alesia_body_vertices.txt", "r")
av = []
while True:
	l = v2.readline()
	if not l: break

	x, y, z = l.split()
	x = float(x)
	y = float(y)
	z = float(z)
	av.append([x,y,z])
v2.close()

f1 = open("body_mesh.txt", "r")
bm = []
while True:
	l = f1.readline()
	if not l:break
	l = l.split()

	if len(l) == 3 : 
		bm.append([float(l[0]), float(l[1]), float(l[2])])
	elif len(l) == 4 : 
		bm.append([float(l[0]), float(l[1]), float(l[2]), float(l[3])])

f1.close()

f2 = open("Alesia_body_mesh.txt", "r")
am = []
bm_size = len(bv)
while True:
	l = f2.readline()
	if not l:break
	l = l.split()
	
	if len(l) == 3 :
		am.append([bm_size + float(l[0]), bm_size + float(l[1]), bm_size + float(l[2])])

	elif len(l) == 4:
		am.append([bm_size + float(l[0]), bm_size + float(l[1]), bm_size + float(l[2]), bm_size+float(l[3])])

f2.close()

tots = open("combined_body.obj", "w")

for v in bv:
	tots.write("v %.3f %.3f %.3f\n" % (v[0], v[1], v[2]))

for v in av:
	tots.write("v %.3f %.3f %.3f\n" % (v[0], v[1], v[2]))

for v in bm :
	if len(v) == 3:
		tots.write("f %d %d %d\n" %(v[0],v[1], v[2]))
	elif len(v) == 4:
		tots.write("f %d %d %d %d\n" %(v[0],v[1], v[2], v[3]))

for v in am :
	if len(v) == 3:
		tots.write("f %d %d %d\n" %(v[0],v[1], v[2]))
	elif len(v) == 4:
		tots.write("f %d %d %d %d\n" %(v[0],v[1], v[2], v[3]))

tots.close()