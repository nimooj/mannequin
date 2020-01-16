o = open("woman_tights.obj", "r")
n = open("woman_new.npts", "w")

while True:
	l = o.readline()
	if not l: break

	if l[0] == "v" :
		f, x, y, z = l.split()
		n.write("%s %s %s\n" % (x, y, z))

o.close()
n.close()