f = open("Male/avatar_man_tmp.dump", "r")

verts = []
norms = []
texts = []
faces = []

boneIndices = []
boneWeights = []

while True:
	l = f.readline()
	if not l: break

	ls = []
	ls = l.split()

	if (ls[0] == 'vertex') :
		for i in range(0, int(ls[1])):
			lv = f.readline()
			if not lv: break

			lva = []
			lva = lv.split()

			verts.append([float(lva[0])/10, float(lva[1])/10, float(lva[2])/10])
			norms.append([float(lva[3]), float(lva[4]), float(lva[5])])
			texts.append([float(lva[6]), float(lva[7])])
			boneIndices.append([float(lva[8]), float(lva[9]), float(lva[10]), float(lva[11])])
			boneWeights.append([float(lva[12]), float(lva[13]), float(lva[14]), float(lva[15])])

	elif (ls[0] == 'face') :
		for i in range(0, int(ls[1])):
			lf = f.readline()
			if not lf: break

			lfa = []
			lfa = lf.split()

			faces.append([float(lfa[0]) + 1, float(lfa[1]) + 1, float(lfa[2]) + 1])

f.close()

w = open("avatar_man.obj", "w")

for i in range(0, len(verts)):
	w.write("v %f %f %f\n" % (verts[i][0], verts[i][1], verts[i][2]))

for i in range(0, len(norms)):
	w.write("vn %f %f %f\n" % (norms[i][0], norms[i][1], norms[i][2]))

for i in range(0, len(texts)):
	w.write("vt %f %f\n" % (texts[i][0], texts[i][1]))

for i in range(0, len(faces)):
	#w.write("f %d %d %d\n" % (faces[i][0], faces[i][1], faces[i][2]))
	#w.write("f %d//%d %d//%d %d//%d\n" % (faces[i][0], faces[i][0], faces[i][1], faces[i][1], faces[i][2], faces[i][2]))
	w.write("f %d/%d/%d %d/%d/%d %d/%d/%d\n" % (faces[i][0], faces[i][0], faces[i][0], faces[i][1], faces[i][1], faces[i][1], faces[i][2], faces[i][2], faces[i][2]))

w.close()


b = open("Male/avatar_man_bone.boneInfo", "w")

for i in range(0, len(verts)):
	b.write("%d %d %d %d %f %f %f %f\n" % (boneIndices[i][0], boneIndices[i][1], boneIndices[i][2], boneIndices[i][3], boneWeights[i][0], boneWeights[i][1], boneWeights[i][2], boneWeights[i][3]))

b.close()