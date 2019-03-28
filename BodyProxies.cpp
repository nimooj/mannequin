#include "stdafx.h"
#include "BodyProxies.h"

BodyProxies::BodyProxies() {
	int fileNum = 0;
	int idx = 1;
	int layerIdx = 1;

	string s;
	vector<Vertex> layer;

	bodyLayers = LayerTree();
	jointTree = JointTree();

	//Verts
	ifstream infile0("layers/neck.txt");
	ifstream infile1("layers/shoulderTop.txt");
	ifstream infile2("layers/shoulderTopMid.txt");
	ifstream infile3("layers/shoulderMid.txt");
	ifstream infile4("layers/shoulderMidArmpit.txt");
	ifstream infile5("layers/armpit.txt");
	ifstream infile6("layers/armpitBust.txt");
	ifstream infile7("layers/bust.txt");
	ifstream infile8("layers/waist.txt");
	ifstream infile9("layers/hip.txt");
	ifstream infile10("layers/crotch.txt");
	ifstream infile11("layers/highThighR.txt");
	ifstream infile12("layers/highThighL.txt");
	ifstream infile13("layers/kneeR.txt");
	ifstream infile14("layers/kneeL.txt");
	ifstream infile15("layers/ankleR.txt");
	ifstream infile16("layers/ankleL.txt");

	ifstream infile17("layers/armHoleR.txt");
	ifstream infile18("layers/armpitR.txt");
	ifstream infile19("layers/elbowR.txt");
	ifstream infile20("layers/wristR.txt");

	ifstream infile21("layers/armHoleL.txt");
	ifstream infile22("layers/armpitL.txt");
	ifstream infile23("layers/elbowL.txt");
	ifstream infile24("layers/wristL.txt");

	// 0
	if (infile0.is_open()) {
		while (getline(infile0, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile0.close();
	neck = Layer(layer);
	bodyLayers.append(layerIdx, neck);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 1
	if (infile1.is_open()) {
		while (getline(infile1, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile1.close();
	shoulderTop = Layer(layer);
	bodyLayers.append(layerIdx, shoulderTop);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 2
	if (infile2.is_open()) {
		while (getline(infile2, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile2.close();
	shoulderTopMid = Layer(layer);
	bodyLayers.append(layerIdx, shoulderTopMid);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 3
	if (infile3.is_open()) {
		while (getline(infile3, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile3.close();
	shoulderMid = Layer(layer);
	bodyLayers.append(layerIdx, shoulderMid);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 4
	if (infile4.is_open()) {
		while (getline(infile4, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile4.close();
	shoulderMidArmpit = Layer(layer);
	bodyLayers.append(layerIdx, shoulderMidArmpit);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 5
	if (infile5.is_open()) {
		while (getline(infile5, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile5.close();
	armpit = Layer(layer);
	bodyLayers.append(layerIdx, armpit);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 6
	if (infile6.is_open()) {
		while (getline(infile6, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile6.close();
	armpitBust = Layer(layer);
	bodyLayers.append(layerIdx, armpitBust);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 7
	if (infile7.is_open()) {
		while (getline(infile7, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile7.close();
	bust = Layer(layer);
	bodyLayers.append(layerIdx, bust);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 8
	if (infile8.is_open()) {
		while (getline(infile8, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile8.close();
	waist = Layer(layer);
	bodyLayers.append(layerIdx, waist);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 9
	if (infile9.is_open()) {
		while (getline(infile9, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile9.close();
	hip = Layer(layer);
	bodyLayers.append(layerIdx, hip);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 10
	if (infile10.is_open()) {
		while (getline(infile10, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile10.close();
	crotch = Layer(layer);
	bodyLayers.append(layerIdx, crotch);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 11
	if (infile11.is_open()) {
		while (getline(infile11, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile11.close();
	highThighR = Layer(layer);
	bodyLayers.append(layerIdx, highThighR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 12
	if (infile12.is_open()) {
		while (getline(infile12, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile12.close();
	highThighL = Layer(layer);
	bodyLayers.append(layerIdx, highThighL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 13
	if (infile13.is_open()) {
		while (getline(infile13, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile13.close();
	kneeR = Layer(layer);
	bodyLayers.append(layerIdx, kneeR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 14
	if (infile14.is_open()) {
		while (getline(infile14, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile14.close();
	kneeL = Layer(layer);
	bodyLayers.append(layerIdx, kneeL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 15
	if (infile15.is_open()) {
		while (getline(infile15, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile15.close();
	ankleR = Layer(layer);
	bodyLayers.append(layerIdx, ankleR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 16
	if (infile16.is_open()) {
		while (getline(infile16, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile16.close();
	ankleL = Layer(layer);
	bodyLayers.append(layerIdx, ankleL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 17
	if (infile17.is_open()) {
		while (getline(infile17, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile17.close();
	armHoleR = Layer(layer);
	bodyLayers.append(layerIdx, armHoleR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 18
	if (infile18.is_open()) {
		while (getline(infile18, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile18.close();
	armpitR = Layer(layer);
	bodyLayers.append(layerIdx, armpitR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 19
	if (infile19.is_open()) {
		while (getline(infile19, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile19.close();
	elbowR = Layer(layer);
	bodyLayers.append(layerIdx, elbowR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 20
	if (infile20.is_open()) {
		while (getline(infile20, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile20.close();
	wristR = Layer(layer);
	bodyLayers.append(layerIdx, wristR);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 21
	if (infile21.is_open()) {
		while (getline(infile21, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile21.close();
	armHoleL = Layer(layer);
	bodyLayers.append(layerIdx, armHoleL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 22
	if (infile22.is_open()) {
		while (getline(infile22, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile22.close();
	armpitL = Layer(layer);
	bodyLayers.append(layerIdx, armpitL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 23
	if (infile23.is_open()) {
		while (getline(infile23, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile23.close();
	elbowL = Layer(layer);
	bodyLayers.append(layerIdx, elbowL);
	fileNum++;
	layerIdx++;
	layer.clear();
	// 24
	if (infile24.is_open()) {
		while (getline(infile24, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile24.close();
	wristL = Layer(layer);
	bodyLayers.append(layerIdx, wristL);
	fileNum++;
	layerIdx++;
	layer.clear();

	ifstream meshFile("layers/meshProxies");
	if (meshFile.is_open()) {
		while (getline(meshFile, s)) {
			istringstream sstr(s);
			int i1 = 0, i2 = 0, i3 = 0;

			sstr >> i1 >> i2 >> i3;

			baseIndices.push_back(i1);
			baseIndices.push_back(i2);
			baseIndices.push_back(i3);

			baseMesh.push_back(Mesh(i1, i2,  i3, baseVert[i1 - 1], baseVert[i2 - 1], baseVert[i3 - 1]));
		}
	}
	meshFile.close();

	for (int i = 0; i < baseVert.size(); i++) {
		int numFaces = 0;
		Vertex tmpNormal = Vertex();

		for (int j = 0; j < baseMesh.size(); j++) {
			if (baseMesh[j].has(baseVert[i].idx)) {
				tmpNormal = tmpNormal + baseMesh[j].normal;
				numFaces++;
			}
		}

		baseNormal.push_back(tmpNormal / numFaces);
	}

	joints.push_back(Joint(0, neck.getCenter()));
	joints.push_back(Joint(1, shoulderTop.getCenter())); // shoulder top
	joints.push_back(Joint(2, armHoleR.getCenter()));
	joints.push_back(Joint(3, elbowR.getCenter()));
	joints.push_back(Joint(4, wristR.getCenter()));
	joints.push_back(Joint(5, waist.getCenter()));
	joints.push_back(Joint(6, hip.getCenter()));
	joints.push_back(Joint(7, highThighR.getCenter()));
	joints.push_back(Joint(8, kneeR.getCenter()));
	joints.push_back(Joint(9, ankleR.getCenter()));
	joints.push_back(Joint(10, highThighL.getCenter()));
	joints.push_back(Joint(11, kneeL.getCenter()));
	joints.push_back(Joint(12, ankleL.getCenter()));
	joints.push_back(Joint(13, armHoleL.getCenter()));
	joints.push_back(Joint(14, elbowL.getCenter()));
	joints.push_back(Joint(15, wristL.getCenter()));

	setPosing();
}

BodyProxies::BodyProxies(string dir) {
	int idx = 1;
	float maxX = 0, minX = 0;
	float maxY = 0, minY = 0;
	float maxZ = 0, minZ = 0;
	vector<Vertex> horizontal;
	vector<Vertex> vertical;

	string line;
	ifstream basics(dir);

	while (getline(basics, line)) {
		istringstream iss(line);
		string f;
		float x, w, y, z;
		iss >> f >> x >> y >> z >> w;
		if (f == "v") {
			/*
			baseVert.push_back(Vertex(idx, x*10, y*10, z*10));
			idx++;
			if (minX > x * 10) {
				minX = x * 10;
			}
			if (x * 10 > maxX) {
				maxX = x * 10;
			}
			if (minY > y * 10) {
				minY = y * 10;
			}
			if (y * 10 > maxY) {
				maxY = y * 10;
			}
			if (minZ > z * 10) {
				minZ = z * 10;
			}
			if (z * 10 > maxZ) {
				maxZ = z * 10;
			}
			*/
			baseVert.push_back(Vertex(idx, x, y, z));
			idx++;
			if (minX > x ) {
				minX = x;
			}
			if (x > maxX) {
				maxX = x;
			}
			if (minY > y) {
				minY = y;
			}
			if (y > maxY) {
				maxY = y;
			}
			if (minZ > z) {
				minZ = z;
			}
			if (z > maxZ) {
				maxZ = z;
			}
		}
		else if (f == "f") {
			baseMesh.push_back(Mesh(baseVert[x-1], baseVert[y-1], baseVert[z-1], baseVert[w-1]));
		}
	}

	sort(baseMesh.begin(), baseMesh.end(), [](Mesh &a, Mesh &b) { return a.center.y > b.center.y; });
	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);

	/* Write newly alinged obj file
	*/
	ofstream outfile;
	outfile.open("newLowpoly.obj");
	outfile << "# Newly aligned obj by mjKang" << endl << endl;

	for (int i = 0; i < baseVert.size(); i++) {
		outfile << "v " << baseVert[i].x << " " << baseVert[i].y << " " << baseVert[i].z << endl;
	}
	for (int i = 0; i < baseMesh.size(); i++) {
		outfile << "f " << baseMesh[i].index1 << " " << baseMesh[i].index2 << " " << baseMesh[i].index3 << " " << baseMesh[i].index4 << endl;
	}
	outfile.close();
}

BodyProxies::~BodyProxies() {

}

void BodyProxies::setPosing() {
	// Parent-Child definition
	joints[Joint_neck].setChild(Joint_shoulderTop);

	joints[Joint_shoulderTop].setParent(Joint_neck);
	joints[Joint_shoulderTop].setChildren(Joint_shoulderR, Joint_waist, Joint_shoulderL);

	joints[Joint_shoulderR].setParent(Joint_shoulderTop);
	joints[Joint_shoulderR].setChild(Joint_elbowR);

	joints[Joint_elbowR].setParent(Joint_shoulderR);
	joints[Joint_elbowR].setChild(Joint_wristR);

	joints[Joint_wristR].setParent(Joint_elbowR);

	joints[Joint_waist].setParent(Joint_shoulderTop);
	joints[Joint_waist].setChild(Joint_pelvis);

	joints[Joint_pelvis].setParent(Joint_waist);
	joints[Joint_pelvis].setChildren(Joint_pelvisR, Joint_pelvisL);

	joints[Joint_pelvisR].setParent(Joint_pelvis);
	joints[Joint_pelvisR].setChild(Joint_kneeR);

	joints[Joint_kneeR].setParent(Joint_pelvisR);
	joints[Joint_kneeR].setChild(Joint_ankleR);

	joints[Joint_ankleR].setParent(Joint_kneeR);

	joints[Joint_pelvisL].setParent(Joint_pelvis);
	joints[Joint_pelvisL].setChild(Joint_kneeL);

	joints[Joint_kneeL].setParent(Joint_pelvisL);
	joints[Joint_kneeL].setChild(Joint_ankleL);

	joints[Joint_ankleL].setParent(Joint_kneeL);

	joints[Joint_shoulderL].setParent(Joint_shoulderTop);
	joints[Joint_shoulderL].setChild(Joint_elbowL);

	joints[Joint_elbowL].setParent(Joint_shoulderL);
	joints[Joint_elbowL].setChild(Joint_wristL);

	joints[Joint_wristL].setParent(Joint_elbowL);

	// Form JointTree
	for (vector<Joint>::iterator jt = joints.begin(); jt != joints.end(); jt++) {
		jointTree.append(*jt);
	}

	// Linking layers
	vector<Layer> ls;

	ls.push_back(neck);
	ls.push_back(shoulderTop);
	joints[Joint_neck].setLayers(ls);
	ls.clear();

	ls.push_back(shoulderTop);
	ls.push_back(shoulderTopMid);
	ls.push_back(shoulderMidArmpit);
	ls.push_back(armpit);
	joints[Joint_shoulderTop].setLayers(ls);
	ls.clear();

	ls.push_back(armpitBust);
	ls.push_back(bust);
	ls.push_back(waist);
	ls.push_back(hip);
	joints[Joint_waist].setLayers(ls);
	ls.clear();

	ls.push_back(waist);
	ls.push_back(hip);
	ls.push_back(crotch);
	joints[Joint_pelvis].setLayers(ls);
	ls.clear();

	ls.push_back(highThighR);
	ls.push_back(kneeR);
	ls.push_back(ankleR);
	joints[Joint_pelvisR].setLayers(ls);
	ls.clear();

	ls.push_back(kneeR);
	ls.push_back(ankleR);
	joints[Joint_kneeR].setLayers(ls);
	ls.clear();

	joints[Joint_ankleR].setLayer(ankleR);

	ls.push_back(highThighL);
	ls.push_back(kneeL);
	ls.push_back(ankleL);
	joints[Joint_pelvisL].setLayers(ls);
	ls.clear();

	ls.push_back(kneeL);
	ls.push_back(ankleL);
	joints[Joint_kneeL].setLayers(ls);
	ls.clear();

	joints[Joint_ankleL].setLayer(ankleL);

	ls.push_back(armHoleR);
	ls.push_back(elbowR);
	ls.push_back(wristR);
	joints[Joint_shoulderR].setLayers(ls);
	ls.clear();

	ls.push_back(elbowR);
	ls.push_back(wristR);
	joints[Joint_elbowR].setLayers(ls);
	ls.clear();

	joints[Joint_wristR].setLayer(wristR);

	ls.push_back(armHoleL);
	ls.push_back(elbowL);
	ls.push_back(wristL);
	joints[Joint_shoulderL].setLayers(ls);
	ls.clear();

	ls.push_back(elbowL);
	ls.push_back(wristL);
	joints[Joint_elbowL].setLayers(ls);
	ls.clear();

	joints[Joint_wristL].setLayer(wristL);
}

vector<Vertex> BodyProxies::getVerts() {
	return baseVert;
}

vector<int> BodyProxies::getIndices() {
	return baseIndices;
}

vector<Vertex> BodyProxies::getNormals() {
	return baseNormal;
}

LayerTree BodyProxies::getBodyLayers() {
	return bodyLayers;
}

JointTree BodyProxies::getJointTree() {
	return jointTree;
}

void BodyProxies::updateBodyProxies() {

}

void BodyProxies::centering(float x, float y, float z) {
	for (int i = 0; i < baseVert.size(); i++) {
		baseVert[i].x -= x;
		baseVert[i].y -= y;
		baseVert[i].z -= z;
	}
}
void BodyProxies::writeToOBJ(vector<Vertex> vert, vector<int> ind, vector<Vertex> norm) {
	ofstream outfile("layers/Body.obj");

	for (int i = 0; i < vert.size(); i++)
		outfile << "v " << vert[i].x << " " << vert[i].y << " " << vert[i].z << endl;

	for (int i = 0; i < norm.size(); i++)
		outfile << "vn " << norm[i].x << " " << norm[i].y << " " << norm[i].z << endl;

	/*
	for (int i = 0; i < ind.size(); i += 3)
		outfile << "f " << ind[i] << " " << ind[i + 1] << " " << ind[i + 2] << endl;
	*/

	for (int i = 0; i < baseMesh.size(); i++) {
		int i1 = baseMesh[i].index1;
		int i2 = baseMesh[i].index2;
		int i3 = baseMesh[i].index3;

		outfile << "f " << i1 << "\/\/" << i1 << " " << i2 << "\/\/" << i2 << " " << i3 << "\/\/" << i3 << endl;
	}
	outfile.close();

	//AfxMessageBox(CString("OBJ exported.\n"));
	cout << "OBJ exported.\n" << endl;
}
