
boneMap = []
for i in range(0, 100):
	boneMap.append(-1)

boneMap[0] = 6
boneMap[1] = 5
boneMap[2] = 4
boneMap[3] = 3
boneMap[4] = 2
boneMap[5] = 1
boneMap[6] = 0
boneMap[7] = 0
boneMap[8] = 0
boneMap[9] = 0
boneMap[10] = 0
boneMap[11] = 0
boneMap[12] = 0
boneMap[13] = 0
boneMap[14] = 14
boneMap[15] = 15
boneMap[16] = 16
boneMap[17] = 17
boneMap[18] = 18
boneMap[19] = 19
boneMap[20] = 20

for i in range(21, 46):
	boneMap[i] = 20

boneMap[46] = 32
boneMap[47] = 7
boneMap[48] = 8
boneMap[49] = 9
boneMap[50] = 10
boneMap[51] = 11
boneMap[52] = 12
boneMap[53] = 13

for i in range(54, 79):
	boneMap[i] = 13

boneMap[79] = 31
boneMap[80] = 6
boneMap[82] = 21
boneMap[83] = 22
boneMap[84] = 23
boneMap[85] = 24
boneMap[86] = 25

for i in range(87, 91):
	boneMap[i] = 25

boneMap[91] = 26
boneMap[92] = 27
boneMap[93] = 28
boneMap[94] = 29
boneMap[95] = 30

for i in range(96, 100):
	boneMap[i] = 30


m = open("Male/avatar_man_bone.boneInfo", "r")
gb = []
weight = []

while True:
	l = m.readline()
	if not l: break

	ll = []
	ll = l.split()

	gb.append([boneMap[int(ll[0])], boneMap[int(ll[1])], boneMap[int(ll[2])], boneMap[int(ll[3])]])	
	weight.append([float(ll[4]), float(ll[5]), float(ll[6]), float(ll[7])])


m.close()

m = open("Male/avatar_man_bone_mapped.boneInfo", "w")
for i in range(0, len(gb)):
	m.write("%d %d %d %d %f %f %f %f\n" % (gb[i][0], gb[i][1], gb[i][2], gb[i][3], weight[i][0], weight[i][1], weight[i][2], weight[i][3]))

m.close()


w = open("Female/avatar_woman_bone.boneInfo", "r")
gb = []
weight = []

while True:
	l = w.readline()
	if not l: break

	ll = []
	ll = l.split()

	gb.append([boneMap[int(ll[0])], boneMap[int(ll[1])], boneMap[int(ll[2])], boneMap[int(ll[3])]])	
	weight.append([float(ll[4]), float(ll[5]), float(ll[6]), float(ll[7])])

w.close()

w = open("Female/avatar_woman_bone_mapped.boneInfo", "w")
for i in range(0, len(gb)):
	w.write("%d %d %d %d %f %f %f %f\n" % (gb[i][0], gb[i][1], gb[i][2], gb[i][3], weight[i][0], weight[i][1], weight[i][2], weight[i][3]))
w.close()