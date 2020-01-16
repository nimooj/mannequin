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
	neck = new Layer(layer);
	bodyLayers.append(layerIdx, *neck);
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
	shoulderTop = new Layer(layer);
	bodyLayers.append(layerIdx, *shoulderTop);
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
	shoulderTopMid = new Layer(layer);
	bodyLayers.append(layerIdx, *shoulderTopMid);
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
	shoulderMid = new Layer(layer);
	bodyLayers.append(layerIdx, *shoulderMid);
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
	shoulderMidArmpit = new Layer(layer);
	bodyLayers.append(layerIdx, *shoulderMidArmpit);
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
	armpit = new Layer(layer);
	bodyLayers.append(layerIdx, *armpit);
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
	armpitBust = new Layer(layer);
	bodyLayers.append(layerIdx, *armpitBust);
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
	bust = new Layer(layer);
	bodyLayers.append(layerIdx, *bust);
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
	waist = new Layer(layer);
	bodyLayers.append(layerIdx, *waist);
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
	hip = new Layer(layer);
	bodyLayers.append(layerIdx, *hip);
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
	crotch = new Layer(layer);
	bodyLayers.append(layerIdx, *crotch);
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
	highThighR = new Layer(layer);
	bodyLayers.append(layerIdx, *highThighR);
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
	highThighL = new Layer(layer);
	bodyLayers.append(layerIdx, *highThighL);
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
	kneeR = new Layer(layer);
	bodyLayers.append(layerIdx, *kneeR);
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
	kneeL = new Layer(layer);
	bodyLayers.append(layerIdx, *kneeL);
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
	ankleR = new Layer(layer);
	bodyLayers.append(layerIdx, *ankleR);
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
	ankleL = new Layer(layer);
	bodyLayers.append(layerIdx, *ankleL);
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
	armHoleR = new Layer(layer);
	bodyLayers.append(layerIdx, *armHoleR);
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
	armpitR = new Layer(layer);
	bodyLayers.append(layerIdx, *armpitR);
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
	elbowR = new Layer(layer);
	bodyLayers.append(layerIdx, *elbowR);
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
	wristR = new Layer(layer);
	bodyLayers.append(layerIdx, *wristR);
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
	armHoleL = new Layer(layer);
	bodyLayers.append(layerIdx, *armHoleL);
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
	armpitL = new Layer(layer);
	bodyLayers.append(layerIdx, *armpitL);
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
	elbowL = new Layer(layer);
	bodyLayers.append(layerIdx, *elbowL);
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
	wristL = new Layer(layer);
	bodyLayers.append(layerIdx, *wristL);
	fileNum++;
	layerIdx++;
	layer.clear();

	/* Import sub-layers */
	// 25
	ifstream infile25("layers/sublayers/26.txt");
	if (infile25.is_open()) {
		while (getline(infile25, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile25.close();
	layerIdx++;
	layer.clear();
	// 26
	ifstream infile26("layers/sublayers/27.txt");
	if (infile26.is_open()) {
		while (getline(infile26, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile26.close();
	layerIdx++;
	layer.clear();
	// 27
	ifstream infile27("layers/sublayers/28.txt");
	if (infile27.is_open()) {
		while (getline(infile27, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile27.close();
	layerIdx++;
	layer.clear();
	// 28
	ifstream infile28("layers/sublayers/29.txt");
	if (infile28.is_open()) {
		while (getline(infile28, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile28.close();
	layerIdx++;
	layer.clear();
	/*** Waist - Hip ***/
	// 29
	ifstream infile29("layers/sublayers/30.txt");
	if (infile29.is_open()) {
		while (getline(infile29, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile29.close();
	layerIdx++;
	layer.clear();
	// 30
	ifstream infile30("layers/sublayers/31.txt");
	if (infile30.is_open()) {
		while (getline(infile30, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile30.close();
	layerIdx++;
	layer.clear();
	// 31
	ifstream infile31("layers/sublayers/32.txt");
	if (infile31.is_open()) {
		while (getline(infile31, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile31.close();
	layerIdx++;
	layer.clear();
	// 32
	ifstream infile32("layers/sublayers/33.txt");
	if (infile32.is_open()) {
		while (getline(infile32, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile32.close();
	layerIdx++;
	layer.clear();
	// 33
	ifstream infile33("layers/sublayers/34.txt");
	if (infile33.is_open()) {
		while (getline(infile33, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile33.close();
	layerIdx++;
	layer.clear();
	// 35
	ifstream infile34("layers/sublayers/35.txt");
	if (infile34.is_open()) {
		while (getline(infile34, s)) {
			istringstream iss(s);
			Vertex v;
			iss >> v.x >> v.y >> v.z;
			v.set();

			baseVert.push_back(Vertex(idx, v));
			layer.push_back(Vertex(idx, v));
			idx++;
		}
	}
	infile34.close();
	layerIdx++;
	layer.clear();

	////////////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////////////

	// Calculate normals
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

	joints.push_back(Joint(0, neck->getCenter()));
	joints.push_back(Joint(1, shoulderTop->getCenter())); // shoulder top
	joints.push_back(Joint(2, armHoleR->getCenter()));
	joints.push_back(Joint(3, elbowR->getCenter()));
	joints.push_back(Joint(4, wristR->getCenter()));
	joints.push_back(Joint(5, waist->getCenter()));
	joints.push_back(Joint(6, hip->getCenter()));
	joints.push_back(Joint(7, Vertex(highThighR->getCenter().x, crotch->getCenter().y, highThighR->getCenter().z)));
	joints.push_back(Joint(8, highThighR->getCenter()));
	joints.push_back(Joint(9, kneeR->getCenter()));
	joints.push_back(Joint(10, ankleR->getCenter()));
	joints.push_back(Joint(11, Vertex(highThighL->getCenter().x, crotch->getCenter().y, highThighL->getCenter().z)));
	joints.push_back(Joint(12, highThighL->getCenter()));
	joints.push_back(Joint(13, kneeL->getCenter()));
	joints.push_back(Joint(14, ankleL->getCenter()));
	joints.push_back(Joint(15, armHoleL->getCenter()));
	joints.push_back(Joint(16, elbowL->getCenter()));
	joints.push_back(Joint(17, wristL->getCenter()));

	initVert.insert(initVert.begin(), baseVert.begin(), baseVert.end());

	/*
	vertices.insert(vertices.end(), baseVert.begin(), baseVert.end());
	normals.insert(normals.end(), baseNormal.begin(), baseNormal.end());
	indices.insert(indices.end(), baseIndices.begin(), baseIndices.end());
	meshes.insert(meshes.end(), baseMesh.begin(), baseMesh.end());
	*/

	//subdivision(Bust, Waist, 4);
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
		float x = -1, y = -1, z = -1, w = -1;

		iss >> f >> x >> y >> z >> w;

		if (minX > x) {
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

		if (f == "v") {
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
		else if (f == "vn") {
			baseNormal.push_back(Vertex(x, y, z));
		}
		else if (f == "f") {
			string newLine = line.substr(2, line.length());
			string delimiter1 = " ";
			string delimiter2 = "//";
			size_t pos = 0;
			string token;
			vector<string> ss;
			vector<string> index;

			while( (pos = newLine.find(delimiter1)) != string::npos ) {
				token = newLine.substr(0, pos);
				ss.push_back(token);
				newLine.erase(0, pos + delimiter1.length());
			}
			ss.push_back(newLine);

			while (!ss.empty()) {
				string sn = ss.back();
				while ((pos = sn.find(delimiter2)) != string::npos) {
					token = sn.substr(0, pos);
					index.push_back(token);
					sn.erase(0, pos + delimiter2.length());
				}
				ss.pop_back();
			}
			for (int i = index.size() - 1; i >= 0; i--) {
				baseIndices.push_back(atoi(index[i].c_str()));
			}

		}
	}

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
}

BodyProxies::~BodyProxies() {

}

void BodyProxies::subdivision(int layer1, int layer2, int num) {
	vector<Layer> lt = bodyLayers.getAllLayers();
	vector<Vertex> l1 = lt[layer1].getVerts();
	vector<Vertex> l2 = lt[layer2].getVerts();

	int layerSize = l1.size();
	float interval = (l1[0].y - l2[0].y) / (float) num;

	// Assign new vertex index from the last
	int vIdx = l1.size();

	int count = 1;
	for (float y = l1[0].y - interval; y > l2[0].y; y -= interval) {
		vector<Vertex> newLayerVerts;
		vector<Mesh> newMeshes;

		for (int i = 0; i < layerSize; i++) {
			float x = (l1[i].x * (num - count) + l2[i].x * count)/count;
			float z = (l1[i].z * (num - count) + l2[i].z * count)/count;
			Vertex newV = Vertex(vIdx, x, y, z);
			newLayerVerts.push_back(newV);

			if (i == layerSize - 1) {
			}
			else {
				//if (x < 0)
					//newMeshes.push_back(Mesh(vIdx - layerSize, vIdx - (layerSize - 1), vIdx, , , newV));


			}

			vIdx++;
		}

		Layer newLayer = Layer(newLayerVerts);
		bodyLayers.insert(layer1 + (count - 1), newLayer);

		count++;
	}

	/* Update :
	*			 vertices
	*			 normals ... meshes
	*			 indices
	*/
	//update();

}

void BodyProxies::setPosing() {
	// Parent-Child definition
	joints[Joint_neck].setChild(Joint_shoulderMid);

	joints[Joint_shoulderMid].setParent(Joint_neck);
	joints[Joint_shoulderMid].setChildren(Joint_shoulderR, Joint_waist, Joint_shoulderL);

	joints[Joint_shoulderR].setParent(Joint_shoulderMid);
	joints[Joint_shoulderR].setChildren(Joint_elbowR, Joint_wristR);

	joints[Joint_elbowR].setParent(Joint_shoulderR);
	joints[Joint_elbowR].setChild(Joint_wristR);

	joints[Joint_wristR].setParent(Joint_elbowR);

	joints[Joint_waist].setParent(Joint_shoulderMid);
	joints[Joint_waist].setChild(Joint_pelvisMid);

	joints[Joint_pelvisMid].setParent(Joint_waist);
	joints[Joint_pelvisMid].setChildren(Joint_pelvisR, Joint_pelvisL);

	joints[Joint_pelvisR].setParent(Joint_pelvisMid);
	joints[Joint_pelvisR].setChildren(Joint_highLegR, Joint_kneeR, Joint_ankleR);

	joints[Joint_highLegR].setParent(Joint_pelvisR);
	joints[Joint_highLegR].setChildren(Joint_kneeR, Joint_ankleR);

	joints[Joint_kneeR].setParent(Joint_highLegR);
	joints[Joint_kneeR].setChild(Joint_ankleR);

	joints[Joint_ankleR].setParent(Joint_kneeR);

	joints[Joint_pelvisL].setParent(Joint_pelvisMid);
	joints[Joint_pelvisL].setChildren(Joint_highLegL, Joint_kneeL, Joint_ankleL);

	joints[Joint_highLegL].setParent(Joint_pelvisL);
	joints[Joint_highLegL].setChildren(Joint_kneeL, Joint_ankleL);

	joints[Joint_kneeL].setParent(Joint_pelvisL);
	joints[Joint_kneeL].setChild(Joint_ankleL);

	joints[Joint_ankleL].setParent(Joint_kneeL);

	joints[Joint_shoulderL].setParent(Joint_shoulderMid);
	joints[Joint_shoulderL].setChildren(Joint_elbowL, Joint_wristL);

	joints[Joint_elbowL].setParent(Joint_shoulderL);
	joints[Joint_elbowL].setChild(Joint_wristL);

	joints[Joint_wristL].setParent(Joint_elbowL);

	// Linking layers
	vector<Layer> ls;

	ls.push_back(*neck);
	ls.push_back(*shoulderTop);
	joints[Joint_neck].setLayers(ls);
	ls.clear();

	ls.push_back(*shoulderTop);
	ls.push_back(*shoulderTopMid);
	ls.push_back(*shoulderMidArmpit);
	ls.push_back(*armpit);
	joints[Joint_shoulderMid].setLayers(ls);
	ls.clear();

	ls.push_back(*armpitBust);
	ls.push_back(*bust);
	ls.push_back(*waist);
	ls.push_back(*hip);
	joints[Joint_waist].setLayers(ls);
	ls.clear();

	ls.push_back(*waist);
	ls.push_back(*hip);
	ls.push_back(*crotch);
	joints[Joint_pelvisMid].setLayers(ls);
	ls.clear();

	ls.push_back(*highThighR);
	ls.push_back(*kneeR);
	ls.push_back(*ankleR);
	joints[Joint_pelvisR].setLayers(ls);
	ls.clear();

	//ls.push_back(*kneeR);
	ls.push_back(*ankleR);
	joints[Joint_kneeR].setLayers(ls);
	ls.clear();

	//joints[Joint_ankleR].setLayer(*ankleR);

	ls.push_back(*highThighL);
	ls.push_back(*kneeL);
	ls.push_back(*ankleL);
	joints[Joint_pelvisL].setLayers(ls);
	ls.clear();

	//ls.push_back(*kneeL);
	ls.push_back(*ankleL);
	joints[Joint_kneeL].setLayers(ls);
	ls.clear();

	//joints[Joint_ankleL].setLayer(*ankleL);

	//ls.push_back(*armHoleR);
	ls.push_back(*armpitR);
	ls.push_back(*elbowR);
	ls.push_back(*wristR);
	joints[Joint_shoulderR].setLayers(ls);
	ls.clear();

	//ls.push_back(*elbowR);
	ls.push_back(*wristR);
	joints[Joint_elbowR].setLayers(ls);
	ls.clear();

	//joints[Joint_wristR].setLayer(*wristR);

	//ls.push_back(*armHoleL);
	ls.push_back(*armpitL);
	ls.push_back(*elbowL);
	ls.push_back(*wristL);
	joints[Joint_shoulderL].setLayers(ls);
	ls.clear();

	//ls.push_back(*elbowL);
	ls.push_back(*wristL);
	joints[Joint_elbowL].setLayers(ls);
	ls.clear();

	//joints[Joint_wristL].setLayer(*wristL);

	// Form JointTree
	for (vector<Joint>::iterator jt = joints.begin(); jt != joints.end(); jt++) {
		jointTree.append(*jt);
	}
}

vector<Vertex>& BodyProxies::getInitVert() {
	return initVert;
}

vector<Vertex>& BodyProxies::getVerts() {
	return baseVert;
}

vector<int>& BodyProxies::getIndices() {
	return baseIndices;
}

vector<Vertex>& BodyProxies::getNormals() {
	return baseNormal;
}

LayerTree& BodyProxies::getBodyLayers() {
	return bodyLayers;
}

JointTree& BodyProxies::getJointTree() {
	return jointTree;
}

vector<Joint>& BodyProxies::getJoints() {
	return joints;
}

void BodyProxies::update() {

}

void BodyProxies::updateBodyProxies(vector<Vertex> v) {
	// update layer tree with baseVert
	// update joint tree
}

void BodyProxies::centering(float x, float y, float z) {
	for (int i = 0; i < baseVert.size(); i++) {
		baseVert[i].x -= x;
		baseVert[i].y -= y;
		baseVert[i].z -= z;
	}
}

void BodyProxies::attachHead() {
	ifstream headFile("layers/Head.obj");
	string s;

	vector<Vertex> normals;

	int vIdx = 1;
	if (headFile.is_open()) {
		while (getline(headFile, s)) {
			istringstream iss(s);
			string type;
			float i1 = -1, i2 = -1, i3 = -1, i4 = -1;
			iss >> type >> i1 >> i2 >> i3 >> i4;

			if (type == "v") {
				head.push_back(Vertex(vIdx, i1/10, i2/10 - 8, i3/10));
				vIdx++;
			}
			else if (type == "vn") {
				normals.push_back(Vertex(i1, i2, i3));
			}
			else if (type == "f") {
				if (i4 != -1) {
					vector<int> i;
					i.push_back(i1);
					i.push_back(i2);
					i.push_back(i3);
					i.push_back(i4);

					headIndices.push_back(i);
				}
				else {
					vector<int> i;
					i.push_back(i1);
					i.push_back(i2);
					i.push_back(i3);

					headIndices.push_back(i);
				}

			}
		}
	}
	headFile.close();

	vector<int> originIdx;
	int baseVInitSize = baseVert.size();

	int idx = baseVert.size() + 1;
	for (int i = 0; i < head.size(); i++) {
		originIdx.push_back(head[i].idx);
		baseVert.push_back(Vertex(idx, head[i]));
		idx++;
	}

	for (int i = 0; i < headIndices.size(); i++) {
		for (int j = 0; j < headIndices[i].size(); j++) {
			baseIndices.push_back(headIndices[i][j] + baseVInitSize);
		}
		int i1 = headIndices[i][0] + baseVInitSize;
		int i2 = headIndices[i][1] + baseVInitSize;
		int i3 = headIndices[i][2] + baseVInitSize;
		baseMesh.push_back(Mesh(i1, i2, i3, baseVert[i1 - 1], baseVert[i2 - 1], baseVert[i3 - 1]));
	}

	for (int i = 0; i < normals.size(); i++) {
		baseNormal.push_back(normals[i]);
	}


	/*
	for (int i = baseVInitSize; i < baseVert.size(); i++) {
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
	*/
}

void BodyProxies::writeToOBJ(vector<Vertex>* vert, vector<int>* ind, vector<Vertex>* norm) {
	ofstream outfile("layers/Body.obj");

	for (int i = 0; i < vert->size(); i++)
		outfile << "v " << (*vert)[i].x << " " << (*vert)[i].y << " " << (*vert)[i].z << endl;

	for (int i = 0; i < ind->size(); i+=3) {
		int i1 = (*ind)[i];
		int i2 = (*ind)[i+1];
		int i3 = (*ind)[i+2];
		//outfile << "f " << i1 << "\/\/" << i1 << " " << i2 << "\/\/" << i2 << " " << i3 << "\/\/" << i3 << endl;
		outfile << "f " << i1 << " " << i2 << " " << i3 << endl;
	}
	outfile.close();

	ofstream joutfile("layers/joints.txt");
	for (int i = 0; i < joints.size(); i++) {
		Vertex v = joints[i].getCoord();
		joutfile << v.x << " " << v.y << " " << v.z << endl;
	}
	joutfile.close();


	//AfxMessageBox(CString("OBJ exported.\n"));
	cout << "OBJ exported.\n" << endl;
}
