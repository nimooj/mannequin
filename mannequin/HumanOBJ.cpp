#include "stdafx.h"
#include "HumanOBJ.h"

HumanOBJ::HumanOBJ() {
	bustLevel = 0;
	waistLevel = 0;
	hipLevel = 0;
}

HumanOBJ::HumanOBJ(string dir) {
	int idx = 1;
	string line;
	ifstream basics(dir);
	float maxX = -1000000, minX = 1000000;
	float maxY = -1000000, minY = 1000000;
	float maxZ = -1000000, minZ = 1000000;

	bustLevel = 0;
	waistLevel = 0;
	hipLevel = 0;

	vector<Vertex> tmpnormals, tmptextures;
	while (getline(basics, line)) {
		istringstream iss(line);
		string f;
		float x = -1, y = -1, z = -1, w = -1;

		iss >> f >> x >> y >> z >> w;

		if (f == "v") {
			if (minX > x) {
				minX = x;
				leftMostLevel = x;
			}
			if (x > maxX) {
				maxX = x;
				rightMostLevel = y;
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

			vertices.push_back(Vertex(idx, x, y, z));
			textures.push_back(Vertex());
			normals.push_back(Vertex());
			idx++;
			/* Initialize vertex-joint group */
			segmentGroup.push_back(0);
		}
		else if (f == "vt") {
			tmptextures.push_back(Vertex(x, y , z));
		}
		else if (f == "vn") {
			tmpnormals.push_back(Vertex(x, y, z));
			//normals.push_back(Vertex(x, y, z));
		}
		else if (f == "f") {
			string newLine = line.substr(2, line.length());
			string delimiter1 = " ";
			string delimiter2 = "/";
			size_t pos = 0;
			string token;
			vector<string> ss;
			vector<string> index;
			vector<string> texture;
			vector<string> normal;

			/*** Truncate type area ***/
			while( (pos = newLine.find(delimiter1)) != string::npos ) {
				token = newLine.substr(0, pos);
				ss.push_back(token);
				newLine.erase(0, pos + delimiter1.length());
			}
			ss.push_back(newLine);
			/**************************/

			/*** Get values ***/
			while (!ss.empty()) {
				string sn = ss.back();
				int count = 0;
				//int empty = 1;
				while ((pos = sn.find(delimiter2)) != string::npos) {
					//empty = 0;
					token = sn.substr(0, pos);
					if (count == 0)
						index.push_back(token);
					else if (count == 1 && !tmptextures.empty())
						texture.push_back(token);
					sn.erase(0, pos + delimiter2.length());
					count++;
				}
				//if (empty)
					//index.push_back(sn);
				if (count == 0)
					index.push_back(sn);
				//if (!empty && count == 2 )
				if (count == 2)
					normal.push_back(sn);
				
				ss.pop_back();
			}
			/******************/

			if (index.size() == 4) {
				int i0 = atoi(index[3].c_str());
				int i1 = atoi(index[2].c_str());
				int i2 = atoi(index[1].c_str());
				int i3 = atoi(index[0].c_str());

				if (i0 < 0) {
					i0 = vertices.size() + i0 + 1;
					i1 = vertices.size() + i1 + 1;
					i2 = vertices.size() + i2 + 1;
					i3 = vertices.size() + i3 + 1;
				}
				if (texture.size() > 0) {
					int t0 = atoi(texture[3].c_str());
					int t1 = atoi(texture[2].c_str());
					int t2 = atoi(texture[1].c_str());
					int t3 = atoi(texture[0].c_str());
					if (t0 < 0) {
						t0 = tmptextures.size() + t0 + 1;
						t1 = tmptextures.size() + t1 + 1;
						t2 = tmptextures.size() + t2 + 1;
						t3 = tmptextures.size() + t3 + 1;
					}
					if (tmptextures.size() > 0) {
						textures[i0 - 1] = tmptextures[t0 - 1];
						textures[i1 - 1] = tmptextures[t1 - 1];
						textures[i2 - 1] = tmptextures[t2 - 1];
						textures[i3 - 1] = tmptextures[t3 - 1];
					}
				}

				if (normal.size() > 0) {
					int n0 = atoi(normal[3].c_str());
					int n1 = atoi(normal[2].c_str());
					int n2 = atoi(normal[1].c_str());
					int n3 = atoi(normal[0].c_str());

					if (n0 < 0) {
						n0 = tmpnormals.size() + n0 + 1;
						n1 = tmpnormals.size() + n1 + 1;
						n2 = tmpnormals.size() + n2 + 1;
						n3 = tmpnormals.size() + n3 + 1;
					}

					if (tmpnormals.size() > 0) {
						normals[i0 - 1] = tmpnormals[n0 - 1];
						normals[i1 - 1] = tmpnormals[n1 - 1];
						normals[i2 - 1] = tmpnormals[n2 - 1];
						normals[i3 - 1] = tmpnormals[n3 - 1];
					}
				}

				indices.push_back(i0);
				indices.push_back(i1);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i0 - 1], vertices[i1 - 1], vertices[i3 - 1]));

				indices.push_back(i1);
				indices.push_back(i2);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]));
			}
			else if (index.size() == 3) {
				vector<int> tmpIdx;
				for (int i = index.size() - 1; i >= 0; i--) {
					int idx = atoi(index[i].c_str());
					if (texture.size() > 0) {
						int t = atoi(texture[i].c_str());
						if (t < 0) {
							t = tmptextures.size() + t + 1;
						}
						if (tmptextures.size() > 0)
							textures[idx - 1] = tmptextures[t - 1];
					}
					if (normal.size() > 0) {
						int n = atoi(normal[i].c_str());
						if (n < 0) {
							n = tmpnormals.size() + n + 1;
						}
						if (tmpnormals.size() > 0)
							normals[idx - 1] = tmpnormals[n - 1];
					}

					if (idx < 0) {
						idx = vertices.size() + idx + 1;
					}

					tmpIdx.push_back(idx);

					indices.push_back(idx);
				}
				meshes.push_back(Mesh(vertices[tmpIdx[0] - 1], vertices[tmpIdx[1] - 1], vertices[tmpIdx[2] - 1]));
			}
		}
	}

	/*** Assign tri-mesh ids to vertices ***/
	for (int i = 0; i < meshes.size(); i++) {
		int index1 = meshes[i].index1;
		int index2 = meshes[i].index2;
		int index3 = meshes[i].index3;
		
		vertices[index1 - 1].meshIds.push_back(i);
		vertices[index2 - 1].meshIds.push_back(i);
		vertices[index3 - 1].meshIds.push_back(i);
	}

	topMostLevel = maxY;
	bottomMostLevel = minY;
	leftMostOffset = minX;
	rightMostOffset = maxX;

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);

	topMostLevel -= (minY + maxY) / 2;
	bottomMostLevel -= (minY + maxY) / 2;
	leftMostLevel -= (minY + maxY) / 2;
	rightMostLevel -= (minY + maxY) / 2;
	leftMostOffset -= (minX + maxX) / 2;
	rightMostOffset -= (minX + maxX) / 2;

	skinning = Skinning();

	/*** Create neighbor matrix ***/
	neighbor = (int**)malloc(sizeof(int*) * vertices.size());
	for (int i = 0; i < vertices.size(); i++) {
		neighbor[i] = (int*)malloc(sizeof(int) * vertices.size());

		for (int j = 0; j < vertices.size(); j++) {
			*(neighbor[i] + j) = 0;
		}
	}

	for (int i = 0; i < meshes.size(); i++) {
		int id1 = meshes[i].index1 - 1;
		int id2 = meshes[i].index2 - 1;
		int id3 = meshes[i].index3 - 1;

		*(neighbor[id1] + id1) = 1;
		*(neighbor[id1] + id2) = 1;
		*(neighbor[id1] + id3) = 1;

		*(neighbor[id2] + id1) = 1;
		*(neighbor[id2] + id2) = 1;
		*(neighbor[id2] + id3) = 1;

		*(neighbor[id3] + id1) = 1;
		*(neighbor[id3] + id2) = 1;
		*(neighbor[id3] + id3) = 1;
	}
}

HumanOBJ::~HumanOBJ() {
	/*** Destroy neighbor matrix ***/
	for (int i = 0; i < vertices.size(); i++) {
		free(neighbor[i]);
	}
	free(neighbor);
}

int HumanOBJ::getLandmarkNum() {
	return landmarks.size();
}

void HumanOBJ::getVert(int i, float* coord) {
	coord[0] = vertices[i].x;
	coord[1] = vertices[i].y;
	coord[2] = vertices[i].z;
}

vector<Vertex>& HumanOBJ::getVerts() {
	return vertices;
}

void HumanOBJ::getVerts(float* coord) {
	int j = 0;
	for (int i = 0; i < vertices.size(); i++) {
		coord[j++] = vertices[i].x;
		coord[j++] = vertices[i].y;
		coord[j++] = vertices[i].z;
	}
}

void HumanOBJ::getMesh(int idx, int* node) {
	node[0] = meshes[idx].index1;
	node[1] = meshes[idx].index2;
	node[2] = meshes[idx].index3;
}

vector<int>& HumanOBJ::getIndices() {
	return indices;
}

void HumanOBJ::getIndices(int* node) {
	int j = 0; 
	for (int i = 0; i < indices.size(); i+=3) {
		node[j++] = indices[i];
		node[j++] = indices[i + 1];
		node[j++] = indices[i + 2];
	}
}

vector<Vertex>& HumanOBJ::getNormals() {
	return normals;
}

int HumanOBJ::getVertSize() {
	return vertices.size();
}

int HumanOBJ::getMeshSize() {
	return meshes.size();
}

vector<Joint>& HumanOBJ::getJoints(string dir) {
	joints.clear();

	ifstream infile(dir);
	string s;
	int idx = 0;
	int line = 0;
	Joint joint;

	while (getline(infile, s)) {
		if (s == "") {
			line = -1;
		}
		if (line == 0) {
			istringstream iss(s);
			float x, y, z;
			iss >> x >> y >> z;
			joint = Joint(idx, Vertex(x, y, z));
			idx++;
			joints.push_back(joint);
		}
		/*
		else if (line == 1) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				joint.relatedVerts.push_back(atoi(ss[i].c_str()));
			}
			joints.push_back(joint);
		}
		*/

		line++;
	}
	infile.close();

	return joints;
}

void HumanOBJ::loadJoints(char* dir) {
	joints.clear();

	ifstream infile(dir);
	string s;
	int idx = 0;
	int line = 0;
	Joint joint;

	while (getline(infile, s)) {
		if (s == "") {
			line = -1;
		}
		if (line == 0) {
			istringstream iss(s);
			float x, y, z;
			iss >> x >> y >> z;
			joint = Joint(idx, Vertex(x, y, z));
			idx++;
			joints.push_back(joint);
		}
		/*
		else if (line == 1) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				joint.relatedVerts.push_back(atoi(ss[i].c_str()));
			}
			joints.push_back(joint);
		}
		*/

		line++;
	}
	infile.close();


}

void HumanOBJ::loadLandmarks(char* dir) {
	landmarks.clear();

	ifstream infile(dir);
	string s;
	int line = 0;

	Landmark l;
	while (getline(infile, s)) {
		if (s == "") {
			line = -1;
		}

		if (line == 0) {
			l = Landmark();
			l.name = s.c_str();
		}
		else if (line == 1) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.type = t;
		}
		else if (line == 2) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.level = t;
		}
		else if (line == 3) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.value = t;
		}
		else if (line == 4) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				l.region.push_back(atoi(ss[i].c_str()));
			}
		}
		else if (line == 5) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				l.vertIdx.push_back(atoi(ss[i].c_str()));
			}
			landmarks.push_back(l);
		}

		line++;
	}

	infile.close();
}

vector<Landmark>& HumanOBJ::setLandmarks(string dir) {
	landmarks.clear();

	ifstream infile(dir);
	string s;
	int line = 0;

	Landmark l;
	while (getline(infile, s)) {
		if (s == "") {
			line = -1;
		}

		if (line == 0) {
			l = Landmark();
			l.name = s.c_str();
		}
		else if (line == 1) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.type = t;
		}
		else if (line == 2) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.level = t;
		}
		else if (line == 3) {
			istringstream iss(s);
			float t = 0;
			iss >> t;
			l.value = t;
		}
		else if (line == 4) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				l.region.push_back(atoi(ss[i].c_str()));
			}
		}
		else if (line == 5) {
			string delimiter1 = " ";
			size_t pos = 0;
			string token;
			vector<string> ss;

			while( (pos = s.find(delimiter1)) != string::npos ) {
				token = s.substr(0, pos);
				ss.push_back(token);
				s.erase(0, pos + delimiter1.length());
			}

			for (int i = 0; i < ss.size(); i++) {
				l.vertIdx.push_back(atoi(ss[i].c_str()));
			}
			landmarks.push_back(l);
		}

		line++;
	}

	infile.close();

	return landmarks;
}

void HumanOBJ::undoJoint() {
	joints.pop_back();
}

void HumanOBJ::setJoint(float s, int jointIdx, float x, float y) {
	vector<Vertex> vinQ; // Vertex In Question
	vector<int> jinds;
	vector<int> invinQ;
	int trial = 0;
	float range = 1/s;

	if (joints.size() < JointNum) {
		Vertex l = Vertex(x, y, 1000/s);
		Vertex l_norm = Vertex(0, 0, -1);

		for (int i = 0; i < meshes.size(); i++) {
			int flag = 0;
			Vertex normal = meshes[i].normal.normalize();
			Vertex l_dot = l_norm.dot(normal);

			if (l_dot.sum() != 0) {
				Vertex p = vertices[meshes[i].index1 - 1];
				Vertex p_l = l - p;
				Vertex p_l_dot = p_l.dot(normal);
				Vertex l_norm_dot = l_norm.dot(normal);

				float d = p_l_dot.sum() / l_norm_dot.sum();

				Vertex intersection = l - l_norm.multiply(d);

				/*** Intersection must lie on the mesh ***/
				// 1. Calculate barycentric coordinates.
				Vertex t1 = vertices[meshes[i].index1 - 1];
				Vertex t2 = vertices[meshes[i].index2 - 1];
				Vertex t3 = vertices[meshes[i].index3 - 1];

				// 1.1. Flatten to xz-plane
				float denominator = t1.x * (t2.y - t3.y) + t2.x * (t3.y - t1.y) + t3.x * (t1.y - t2.y);

				float u = (intersection.x * (t2.y - t3.y) + t2.x * (t3.y - intersection.y) + t3.x * (intersection.y - t2.y)) / denominator;
				float v  = (t1.x * (intersection.y - t3.y) + intersection.x * (t3.y - t1.y) + t3.x * (t1.y - intersection.y)) / denominator;
				float w = (t1.x * (t2.y - intersection.y) +  t2.x * (intersection.y - t1.y) + intersection.x * (t1.y - t2.y)) / denominator;

				// 2. Check if they are in range [0, 1].
				if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1) {
					// 3. If 2 is true, then it is within the mesh.
					vinQ.push_back(intersection);
				}
			}
		}

		if (vinQ.size() > 0) {
			float jx = 0;
			float jy = 0;
			float jz = 0;
			for (int i = 0; i < vinQ.size(); i++) {
				jx += vinQ[i].x;
				jy += vinQ[i].y;
				jz += vinQ[i].z;
			}

			jx /= vinQ.size();
			jy /= vinQ.size();
			jz /= vinQ.size();

			Vertex* tmp = new Vertex(jx, jy, jz);
			// Center align joints
			if (jointIdx == Joint_neck || jointIdx == Joint_shoulderMid || jointIdx == Joint_waist || jointIdx == Joint_pelvisMid)
				tmp->x = 0;

			Joint* joint = new Joint(jointIdx, tmp);
			joints.push_back(*joint);
		}
	}
	else {
		AfxMessageBox(_T("Cannot declare a new joint!"));
	}
}

/*** Invoked when join export ***/
void HumanOBJ::expandJoint() {
	int jointIdx = JointNum;


	Vertex* joint = new Joint(jointIdx, );
	joints.push_back(*joint);
}

float HumanOBJ::getBustSize() {
	float dist = 0;
	Vertex prevV, currV;
	for (int i = 1; i < bustConvexIndices.size(); i++) {
		prevV = vertices[bustConvexIndices[i - 1] - 1];
		currV = vertices[bustConvexIndices[i] - 1];

		prevV.y = bustLevel;
		currV.y = bustLevel;

		dist += currV.distance(prevV);
	}

	prevV = vertices[bustConvexIndices[bustConvexIndices.size() - 1] - 1];
	currV = vertices[bustConvexIndices[0] - 1];

	prevV.y = bustLevel;
	currV.y = bustLevel;

	dist += currV.distance(prevV);

	bustSize = dist ;

	return bustSize;
}

float HumanOBJ::getWaistSize() {
	float dist = 0;
	Vertex prevV, currV;
	for (int i = 1; i < waistConvexIndices.size(); i++) {
		prevV = vertices[waistConvexIndices[i - 1] - 1];
		currV = vertices[waistConvexIndices[i] - 1];

		prevV.y = waistLevel;
		currV.y = waistLevel;

		dist += currV.distance(prevV);
	}

	prevV = vertices[waistConvexIndices[waistConvexIndices.size() - 1] - 1];
	currV = vertices[waistConvexIndices[0] - 1];

	prevV.y = waistLevel;
	currV.y = waistLevel;

	dist += currV.distance(prevV);

	waistSize = dist;

	return waistSize;
}

float HumanOBJ::getHipSize() {
	float dist = 0;
	Vertex prevV, currV;
	for (int i = 1; i < hipConvexIndices.size(); i++) {
		prevV = vertices[hipConvexIndices[i - 1] - 1];
		currV = vertices[hipConvexIndices[i] - 1];

		prevV.y = hipLevel;
		currV.y = hipLevel;

		dist += currV.distance(prevV);
	}

	prevV = vertices[hipConvexIndices[hipConvexIndices.size() - 1] - 1];
	currV = vertices[hipConvexIndices[0] - 1];

	prevV.y = hipLevel;
	currV.y = hipLevel;

	dist += currV.distance(prevV);

	hipSize = dist;

	return hipSize;
}

void HumanOBJ::setHeight(float h) {
	float bustScale = 1;
	float waistScale = 1;
	float hipScale = 1;
	float heightScale = h / height;

	vector<int> vertIdx;

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperArmR].begin(), segmentHash[Segment_UpperArmR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerArmR].begin(), segmentHash[Segment_LowerArmR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_HandR].begin(), segmentHash[Segment_HandR].end());

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperArmL].begin(), segmentHash[Segment_UpperArmL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerArmL].begin(), segmentHash[Segment_LowerArmL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_HandL].begin(), segmentHash[Segment_HandL].end());

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Head].begin(), segmentHash[Segment_Head].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Neck].begin(), segmentHash[Segment_Neck].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegR].begin(), segmentHash[Segment_UpperLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegR].begin(), segmentHash[Segment_LowerLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootR].begin(), segmentHash[Segment_FootR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegL].begin(), segmentHash[Segment_UpperLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegL].begin(), segmentHash[Segment_LowerLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootL].begin(), segmentHash[Segment_FootL].end());

	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];
		vertices[idx].y *= heightScale;
	}
	for (int i = 0; i < joints.size(); i++) {
		Vertex j = joints[i].getCoord();
		joints[i].setCoord(j.x, j.y * heightScale, j.z);
	}

	bustLevel *= heightScale;
	waistLevel *= heightScale;
	hipLevel *= heightScale;

	topMostLevel *= heightScale;
	bottomMostLevel *= heightScale;
	height = topMostLevel - bottomMostLevel;

	for (int i = 0; i < landmarks.size(); i++) {
		landmarks[i].level *= heightScale;
	}
}

void HumanOBJ::setBustSize(float s, float b) {
	float bustScale = b / bustSize;
	float waistScale = 1;
	float armHoleMovementRx = 0;
	float armHoleMovementLx = 0;

	vector<int> armRIdx;
	vector<int> armLIdx;
	vector<int> vertIdx;

	vector<int> relatedJointsR;
	vector<int> relatedJointsL;

	armRIdx.insert(armRIdx.end(), segmentHash[Segment_UpperArmR].begin(), segmentHash[Segment_UpperArmR].end());
	armRIdx.insert(armRIdx.end(), segmentHash[Segment_LowerArmR].begin(), segmentHash[Segment_LowerArmR].end());
	armRIdx.insert(armRIdx.end(), segmentHash[Segment_HandR].begin(), segmentHash[Segment_HandR].end());

	armLIdx.insert(armLIdx.end(), segmentHash[Segment_UpperArmL].begin(), segmentHash[Segment_UpperArmL].end());
	armLIdx.insert(armLIdx.end(), segmentHash[Segment_LowerArmL].begin(), segmentHash[Segment_LowerArmL].end());
	armLIdx.insert(armLIdx.end(), segmentHash[Segment_HandL].begin(), segmentHash[Segment_HandL].end());

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Head].begin(), segmentHash[Segment_Head].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Neck].begin(), segmentHash[Segment_Neck].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());

	relatedJointsR.push_back(Joint_shoulderR);
	relatedJointsR.push_back(Joint_elbowR);
	relatedJointsR.push_back(Joint_wristR);

	relatedJointsL.push_back(Joint_shoulderL);
	relatedJointsL.push_back(Joint_elbowL);
	relatedJointsL.push_back(Joint_wristL);

	float range = 1/(s*8);
	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];
		if (idx == shoulderRIndex) {
			armHoleMovementRx = vertices[idx].x*bustScale - vertices[idx].x;
		}
		if (idx == shoulderLIndex) {
			armHoleMovementLx = vertices[idx].x*bustScale - vertices[idx].x;
		}

		if (abs(vertices[idx].y - bustLevel) < range) {
			vertices[idx].x *= bustScale;
			vertices[idx].z *= bustScale;
		}
		else if (vertices[idx].y >= bustLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vn = vertices[idx];
			Vertex vb = vertices[idx];

			float a = (topMostLevel - v->y);
			float b = (v->y - (bustLevel + range));

			vn.x *= 1;
			vn.z *= 1;
			vb.x *= bustScale;
			vb.z *= bustScale;

			v->x = (vn.x*b + vb.x*a) / (a+b);
			v->z = (vn.z*b + vb.z*a) / (a+b);
		}
		else if (vertices[idx].y <= bustLevel - range && vertices[idx].y >= waistLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vb = vertices[idx];
			Vertex vw = vertices[idx];

			float a = (bustLevel - range) - v->y;
			float b = v->y - (waistLevel + range);

			vb.x *= bustScale;
			vb.z *= bustScale;
			vw.x *= waistScale;
			vw.z *= waistScale;

			v->x = (vb.x*b + vw.x*a) / (a+b);
			v->z = (vb.z*b + vw.z*a) / (a+b);
		}
	}

	/*** Move arm ***/
	for (int i = 0; i < armRIdx.size(); i++) {
		vertices[armRIdx[i]].x += armHoleMovementRx;
	}
	for (int i = 0; i < armLIdx.size(); i++) {
		vertices[armLIdx[i]].x += armHoleMovementLx;
	}

	for (int i = 0; i < relatedJointsR.size(); i++) {
		Vertex j = joints[relatedJointsR[i]].getCoord();
		joints[relatedJointsR[i]].setCoord(j.x + armHoleMovementRx, j.y, j.z);
	}
	for (int i = 0; i < relatedJointsL.size(); i++) {
		Vertex j = joints[relatedJointsL[i]].getCoord();
		joints[relatedJointsL[i]].setCoord(j.x + armHoleMovementLx, j.y, j.z);
	}

	bustSize = getBustSize();
	landmarks[1].value = bustSize;

	updateRigs();
}

void HumanOBJ::setWaistSize(float s, float w) {
	float bustScale = 1;
	float waistScale = w / waistSize;
	float hipScale = 1;

	vector<int> vertIdx;
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Head].begin(), segmentHash[Segment_Head].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Neck].begin(), segmentHash[Segment_Neck].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegR].begin(), segmentHash[Segment_UpperLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegR].begin(), segmentHash[Segment_LowerLegR].end());

	float range = 1/(s*8);
	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];

		if (abs(vertices[idx].y - waistLevel) < range) {
			vertices[idx].x *= waistScale;
			vertices[idx].z *= waistScale;
		}
		else if (vertices[idx].y <= bustLevel - range && vertices[idx].y > waistLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vb = vertices[idx];
			Vertex vw = vertices[idx];

			float a = (bustLevel - range) - v->y;
			float b = v->y - (waistLevel + range);

			vb.x *= bustScale;
			vb.z *= bustScale;
			vw.x *= waistScale;
			vw.z *= waistScale;

			v->x = (vb.x*b + vw.x*a) / (a + b);
			v->z = (vb.z*b + vw.z*a) / (a + b);
		}
		else if (vertices[idx].y < waistLevel - range && vertices[idx].y > hipLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vw = vertices[idx];
			Vertex vh = vertices[idx];

			float a = (waistLevel -range) - v->y;
			float b = v->y - (hipLevel + range);

			vw.x *= waistScale;
			vw.z *= waistScale;
			vh.x *= hipScale;
			vh.z *= hipScale;

			v->x = (vw.x*b + vh.x*a) / (a + b);
			v->z = (vw.z*b + vh.z*a) / (a + b);
		}
	}

	waistSize = getWaistSize();
	landmarks[2].value = waistSize;
	updateRigs();
}

void HumanOBJ::setHipSize(float s, float h) {
	float bustScale = 1;
	float waistScale = 1;
	float hipScale = h / hipSize;

	vector<int> vertIdx;
	vector<int> relatedJoints;

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegR].begin(), segmentHash[Segment_UpperLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegR].begin(), segmentHash[Segment_LowerLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootR].begin(), segmentHash[Segment_FootR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegL].begin(), segmentHash[Segment_UpperLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegL].begin(), segmentHash[Segment_LowerLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootL].begin(), segmentHash[Segment_FootL].end());

	relatedJoints.push_back(Joint_pelvisR);
	relatedJoints.push_back(Joint_kneeR);
	relatedJoints.push_back(Joint_ankleR);
	relatedJoints.push_back(Joint_pelvisL);
	relatedJoints.push_back(Joint_kneeL);
	relatedJoints.push_back(Joint_ankleL);

	float range = 1/(s*8);
	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];
		if (abs(vertices[idx].y - hipLevel) < range) {
			vertices[idx].x *= hipScale;
			vertices[idx].z *= hipScale;
		}
		else if (vertices[idx].y <= waistLevel - range && vertices[idx].y >= hipLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vw = vertices[idx];
			Vertex vh = vertices[idx];

			float a = (waistLevel - range) - v->y;
			float b = v->y - (hipLevel + range);

			vw.x *= waistScale;
			vw.z *= waistScale;
			vh.x *= hipScale;
			vh.z *= hipScale;

			v->x = (vw.x*b + vh.x * a) / (a+b);
			v->z = (vw.z*b + vh.z * a) / (a+b);
		}
		else if (vertices[idx].y <= hipLevel - range) {
			Vertex* v = &vertices[idx];
			Vertex vh = vertices[idx];
			Vertex vf = vertices[idx];

			float a = (hipLevel - range) - v->y;
			float b = (v->y - bottomMostLevel);

			vh.x *= hipScale;
			vh.z *= hipScale;
			vf.x *= 1;
			vf.z *= 1;

			v->x = (vh.x*b + vf.x * a) / (a+b);
			v->z = (vh.z*b + vf.z * a) / (a+b);
		}

	}

	for (int i = 0; i < relatedJoints.size(); i++) {
		Vertex j = joints[relatedJoints[i]].getCoord();
		Vertex j_h = joints[relatedJoints[i]].getCoord();
		Vertex j_f = joints[relatedJoints[i]].getCoord();

		float a = (hipLevel - range) - j.y;
		float b = j.y - bottomMostLevel;

		j_h.x *= hipScale;
		j_h.z *= hipScale;
		j_f.x *= 1;
		j_f.z *= 1;

		j.x = (j_h.x * b + j_f.x * a) / (a + b);
		j.z = (j_h.z * b + j_f.z * a) / (a + b);

		joints[relatedJoints[i]].setCoord(j.x, j.y, j.z);
	}

	hipSize = getHipSize();
	landmarks[2].value = hipSize;
	updateRigs();
}

void HumanOBJ::setSize(float s, int type, int index, float oldSize, float newSize) {
	float scale = newSize / oldSize;
	vector<int> sections(landmarks[index].region);
	float movement = 0;

	int upperTorsoFlag = 0, lowerTorsoFlag = 0;

	if (index == 0 || type == Girth) { // Handle height here
		float level = landmarks[index].level;

		float topLevel = 0;
		float bottomLevel = 0;

		vector<float> bigger, smaller;

		for (int i = 0; i < landmarks.size(); i++) {
			if (i != index) {
				float thisLevel = landmarks[i].level;
				if (thisLevel > level) {
					bigger.push_back(thisLevel);
				}
				else if (thisLevel < level) {
					smaller.push_back(thisLevel);
				}
			}
		}

		sort(bigger.begin(), bigger.end());
		sort(smaller.begin(), smaller.end(), greater<float>());

		if (!bigger.empty()) {
			topLevel = bigger[0];
		}
		else {
			topLevel = topMostLevel;
		}
		if (!smaller.empty()) {
			bottomLevel = smaller[0];
		}
		else {
			bottomLevel = bottomMostLevel;
		}

		float range = 1/s;
		int trial = 0;

		vector<int> rangeVs;
		while (rangeVs.size() < 12 && trial < 20) {
			rangeVs.clear();

			for (int i = 0; i < sections.size(); i++) {
				for (int j = 0; j < segmentHash[sections[i]].size(); j++) {
					int idx = segmentHash[sections[i]][j];

					if (abs(vertices[idx].y - level) < range) {
						rangeVs.push_back(idx);
					}
				}
			}

			range += range/8;
			trial++;
		}

		for (int i = 0; i < sections.size(); i++) {
			for (int j = 0; j < segmentHash[sections[i]].size(); j++) {
				int idx = segmentHash[sections[i]][j];

				if (abs(vertices[idx].y - level) < range) {
					vertices[idx].x *= scale;
					vertices[idx].z *= scale;
				}
				else if (vertices[idx].y < topLevel && vertices[idx].y >= level + range) {
					Vertex* v = &vertices[idx];
					Vertex v_upper = vertices[idx];
					Vertex v_lower = vertices[idx];

					float toUpper = (topLevel)-v->y;
					float toLower = v->y - (level + range);

					v_upper.x *= 1;
					v_upper.z *= 1;
					v_lower.x *= scale;
					v_lower.z *= scale;

					v->x = (v_upper.x * toLower + v_lower.x * toUpper) / (toUpper + toLower);
					v->z = (v_upper.z * toLower + v_lower.z * toUpper) / (toUpper + toLower);
				}
				else if (vertices[idx].y <= level - range && vertices[idx].y > bottomLevel) {
					Vertex* v = &vertices[idx];
					Vertex v_upper = vertices[idx];
					Vertex v_lower = vertices[idx];

					float toUpper = (level - range) - v->y;
					float toLower = v->y - (bottomLevel);

					v_upper.x *= scale;
					v_upper.z *= scale;
					v_lower.x *= 1;
					v_lower.z *= 1;

					v->x = (v_upper.x * toLower + v_lower.x * toUpper) / (toUpper + toLower);
					v->z = (v_upper.z * toLower + v_lower.z * toUpper) / (toUpper + toLower);
				}
			}
		}
	}
	else if ( type == Length ) {
		/*** TODO :: Deformations of length type landmarks other than Upper/Lower Torso ***/

		for (int i = 0; i < sections.size(); i++) {
			for (int j = 0; j < segmentHash[sections[i]].size(); j++) {
				int idx = segmentHash[sections[i]][j];

				if (sections[i] == Segment_UpperTorso) {
					upperTorsoFlag = 1;
					float jointDiff = joints[Joint_waist].getCoord().y*scale - joints[Joint_waist].getCoord().y;
					Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
					Vertex waist = joints[Joint_waist].getCoord();

					float y_start = shoulderMid.y;
					float y_end = waist.y;

					float da = y_start - vertices[idx].y;
					float db = vertices[idx].y - y_end;

					vertices[idx].y = (y_start * db + (y_end - jointDiff) * da) / (da + db);
				}
				else if (sections[i] == Segment_LowerTorso) {
					lowerTorsoFlag = 1;
					float jointDiff = joints[Joint_waist].getCoord().y*scale - joints[Joint_waist].getCoord().y;

					Vertex waist = joints[Joint_waist].getCoord();
					Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();

					float y_start = waist.y;
					float y_end = pelvisMid.y;

					float da = y_start - vertices[idx].y;
					float db = vertices[idx].y - y_end;

					vertices[idx].y = ((y_start - jointDiff)* db + y_end * da) / (da + db);
				}
				else {
					vertices[idx].y *= scale;
				}
			}
		}
	}

	if (upperTorsoFlag) {
		float jointDiff = joints[Joint_waist].getCoord().y*scale - joints[Joint_waist].getCoord().y;
		for (int i = 0; i < segmentHash[Segment_LowerTorso].size(); i++) {
			int idx = segmentHash[Segment_LowerTorso][i];
			Vertex waist = joints[Joint_waist].getCoord();
			Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();

			float y_start = waist.y;
			float y_end = pelvisMid.y;

			float da = y_start - vertices[idx].y;
			float db = vertices[idx].y - y_end;

			vertices[idx].y = ((y_start - jointDiff)* db + y_end * da) / (da + db);
		}
	}
	if (lowerTorsoFlag) {
		float jointDiff = joints[Joint_waist].getCoord().y*scale - joints[Joint_waist].getCoord().y;
		for (int i = 0; i < segmentHash[Segment_UpperTorso].size(); i++) {
			int idx = segmentHash[Segment_UpperTorso][i];
			Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
			Vertex waist = joints[Joint_waist].getCoord();

			float y_start = shoulderMid.y;
			float y_end = waist.y;

			float da = y_start - vertices[idx].y;
			float db = vertices[idx].y - y_end;

			vertices[idx].y = (y_start * db + (y_end - jointDiff) * da) / (da + db);
		}
	}

	updateRigs();
}

void HumanOBJ::setSize(float s, float _height, float b, float w, float h) {
	float bustScale = b / bustSize;
	float waistScale = w / waistSize;
	float hipScale = h / hipSize;
	float armHoleMovementRx = 0;
	float armHoleMovementLx = 0;

	float heightScale = _height / height;

	vector<int> armRIdx;
	vector<int> armLIdx;
	vector<int> vertIdx;
	armRIdx.insert(armRIdx.end(), segmentHash[Segment_UpperArmR].begin(), segmentHash[Segment_UpperArmR].end());
	armRIdx.insert(armRIdx.end(), segmentHash[Segment_LowerArmR].begin(), segmentHash[Segment_LowerArmR].end());
	armRIdx.insert(armRIdx.end(), segmentHash[Segment_HandR].begin(), segmentHash[Segment_HandR].end());

	armLIdx.insert(armLIdx.end(), segmentHash[Segment_UpperArmL].begin(), segmentHash[Segment_UpperArmL].end());
	armLIdx.insert(armLIdx.end(), segmentHash[Segment_LowerArmL].begin(), segmentHash[Segment_LowerArmL].end());
	armLIdx.insert(armLIdx.end(), segmentHash[Segment_HandL].begin(), segmentHash[Segment_HandL].end());

	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Head].begin(), segmentHash[Segment_Head].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_Neck].begin(), segmentHash[Segment_Neck].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegR].begin(), segmentHash[Segment_UpperLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegR].begin(), segmentHash[Segment_LowerLegR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootR].begin(), segmentHash[Segment_FootR].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_UpperLegL].begin(), segmentHash[Segment_UpperLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_LowerLegL].begin(), segmentHash[Segment_LowerLegL].end());
	vertIdx.insert(vertIdx.end(), segmentHash[Segment_FootL].begin(), segmentHash[Segment_FootL].end());

	float range = 1/(s*8);
	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];
		if (abs(vertices[idx].y - bustLevel) < range) {
			vertices[idx].x *= bustScale;
			vertices[idx].z *= bustScale;
			vertices[idx].y *= heightScale;
		}
		else if (abs(vertices[idx].y - waistLevel) < range) {
			vertices[idx].x *= waistScale;
			vertices[idx].z *= waistScale;
			vertices[idx].y *= heightScale;
		}
		else if (abs(vertices[idx].y - hipLevel) < range) {
			vertices[idx].x *= hipScale;
			vertices[idx].z *= hipScale;
			vertices[idx].y *= heightScale;
		}
		else if (vertices[idx].y >= bustLevel + range) {
			if (idx == shoulderRIndex) {
				armHoleMovementRx = vertices[idx].x*bustScale - vertices[idx].x;
			}
			if (idx == shoulderLIndex) {
				armHoleMovementLx = vertices[idx].x*bustScale - vertices[idx].x;
			}
			Vertex* v = &vertices[idx];
			Vertex vn = vertices[idx];
			Vertex vb = vertices[idx];

			float a = (topMostLevel - v->y);
			float b = (v->y - bustLevel);

			vn.x *= 1;
			vn.z *= 1;
			vb.x *= bustScale;
			vb.z *= bustScale;

			v->x = (vn.x*b + vb.x*a) / (a+b);
			v->z = (vn.z*b + vb.z*a) / (a+b);
			v->y *= heightScale;

		}
		else if (vertices[idx].y <= bustLevel - range && vertices[idx].y >= waistLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vb = vertices[idx];
			Vertex vw = vertices[idx];

			float a = (bustLevel - v->y);
			float b = (v->y - waistLevel);

			vb.x *= bustScale;
			vb.z *= bustScale;
			vw.x *= waistScale;
			vw.z *= waistScale;

			v->x = (vb.x*b + vw.x*a) / (a+b);
			v->z = (vb.z*b + vw.z*a) / (a+b);
			v->y *= heightScale;
		}
		else if (vertices[idx].y <= waistLevel - range && vertices[idx].y >= hipLevel + range) {
			Vertex* v = &vertices[idx];
			Vertex vw = vertices[idx];
			Vertex vh = vertices[idx];

			float a = (waistLevel- v->y);
			float b = (v->y - hipLevel);

			vw.x *= waistScale;
			vw.z *= waistScale;
			vh.x *= hipScale;
			vh.z *= hipScale;

			v->x = (vw.x*b + vh.x * a) / (a+b);
			v->z = (vw.z*b + vh.z * a) / (a+b);
			v->y *= heightScale;
		}
		else if (vertices[idx].y <= hipLevel - range) {
			Vertex* v = &vertices[idx];
			Vertex vh = vertices[idx];
			Vertex vf = vertices[idx];

			float a = (hipLevel- v->y);
			float b = (v->y - bottomMostLevel);

			vh.x *= hipScale;
			vh.z *= hipScale;
			vf.x *= 1;
			vf.z *= 1;

			v->x = (vh.x*b + vf.x * a) / (a+b);
			v->z = (vh.z*b + vf.z * a) / (a+b);
			v->y *= heightScale;
		}
	}
	/*** Move arm ***/
	for (int i = 0; i < armRIdx.size(); i++) {
		vertices[armRIdx[i]].x += armHoleMovementRx;
		vertices[armRIdx[i]].y *= heightScale;
	}
	for (int i = 0; i < armLIdx.size(); i++) {
		vertices[armLIdx[i]].x += armHoleMovementLx;
		vertices[armLIdx[i]].y *= heightScale;
		
	}

	bustLevel *= heightScale;
	waistLevel *= heightScale;
	hipLevel *= heightScale;
	topMostLevel *= heightScale;
	bottomMostLevel *= heightScale;

	bustSize = getBustSize();
	waistSize = getWaistSize();
	hipSize = getHipSize();

	landmarks[0].value = topMostLevel - bottomMostLevel;
	landmarks[1].value = bustSize;
	landmarks[2].value = waistSize;
	landmarks[3].value = hipSize;

	for (int i = 0; i < landmarks.size(); i++) {
		landmarks[i].level *= heightScale;
	}

	updateRigs();
}

bool HumanOBJ::resize(float* sizes) {
	if (sizeof(sizes)/sizeof(float) > landmarks.size()) {
		return false;
	}

	for (int i = 0; i < sizeof(sizes)/sizeof(float); i++) {
		setSize(scaleFactor, landmarks[i].type, i, landmarks[i].value, sizes[i]);
	}

	return true;
}

void HumanOBJ::getSizeName(int idx, char* n) {
	strcpy(n, (CStringA) landmarks[idx].name);
}

float HumanOBJ::getSize(int idx) {
	return landmarks[idx].value;
}

int HumanOBJ::getSizePathLength(int idx) {
	return landmarks[idx].vertIdx.size();
}

void HumanOBJ::getSizePathPos(int idx, int n, float* coord) {
	coord[0] = vertices[landmarks[idx].vertIdx[n]].x;
	coord[1] = vertices[landmarks[idx].vertIdx[n]].y;
	coord[2] = vertices[landmarks[idx].vertIdx[n]].z;
}

void HumanOBJ::getSizePathPos(int idx, float* coord) {
	int j = 0;
	for (int i = 0; i < landmarks[idx].vertIdx.size(); i++) {
		coord[j++] = vertices[landmarks[idx].vertIdx[i]].x;
		coord[j++] = vertices[landmarks[idx].vertIdx[i]].y;
		coord[j++] = vertices[landmarks[idx].vertIdx[i]].z;
	}
}

void HumanOBJ::setRigs(float s) {
	skinning.setSegments(vertices, joints, segmentGroup, weightHash, weightValueHash);
	skinning.setBindings(vertices, joints);
	setFeatures(s);  //... Segment 다 나누면 다시 활성화 필요 for Sizing
}

void HumanOBJ::setFeatures(float s) {
	float minZ = 1000/s, maxZ = -1000/s;
	float minX = 1000/s, maxX = -1000/s; 
	float minY = 1000/s, maxY = -1000/s;
	vector<int> inds;
	vector<int> secs;
	if (landmarks.size() == 0) {
		for (int i = 0; i < segmentGroup.size(); i++) {
			segmentHash[segmentGroup[i]].push_back(i); // push vertices ARRAY index
		}

		/*** HEIGHT ***/
		int topLevelIdx = 0;
		for (int i = 0; i < segmentHash[Segment_Head].size(); i++) {
			if (vertices[segmentHash[Segment_Head][i]].y > maxY) {
				topMostLevel = vertices[segmentHash[Segment_Head][i]].y;
				topLevelIdx = segmentHash[Segment_Head][i];
				maxY = topMostLevel;
			}
		}

		int bottomLevelIdx = 0;
		vector<int> segment_lowLegs;
		segment_lowLegs.insert(segment_lowLegs.end(), segmentHash[Segment_FootR].begin(), segmentHash[Segment_FootR].end());
		segment_lowLegs.insert(segment_lowLegs.end(), segmentHash[Segment_FootL].begin(), segmentHash[Segment_FootL].end());
		for (int i = 0; i < segment_lowLegs.size(); i++) {
			if (vertices[segment_lowLegs[i]].y < minY) {
				bottomMostLevel = vertices[segment_lowLegs[i]].y;
				bottomLevelIdx = segment_lowLegs[i];
				minY = bottomMostLevel;
			}
		}

		height = (topMostLevel - bottomMostLevel);

		inds.push_back(topLevelIdx + 1);
		inds.push_back(bottomLevelIdx + 1);
		secs.push_back(Segment_Head);
		secs.push_back(Segment_FootR);
		secs.push_back(Segment_FootL);
		landmarks.push_back(Landmark(_T("Height"), secs, Length, height, 0, inds));
		/**************/

		/********************** BUST **********************/
		maxY = -1000/s;
		minY = 1000/s;
		// Bust : max z val in segment 8
		for (int i = 0; i < segmentHash[Segment_UpperTorso].size(); i++) {
			if (vertices[segmentHash[Segment_UpperTorso][i]].z > maxZ && vertices[segmentHash[Segment_UpperTorso][i]].y > joints[Joint_waist].getCoord().y) {
				maxZ = vertices[segmentHash[Segment_UpperTorso][i]].z;
				bustLevel = vertices[segmentHash[Segment_UpperTorso][i]].y;
			}

			/*** Get Shoulder Index ***/
			if (vertices[segmentHash[Segment_UpperTorso][i]].x < minX) {
				minX = vertices[segmentHash[Segment_UpperTorso][i]].x;
				shoulderRIndex = segmentHash[Segment_UpperTorso][i];
			}

			if (vertices[segmentHash[Segment_UpperTorso][i]].x > maxX) {
				maxX = vertices[segmentHash[Segment_UpperTorso][i]].x;
				shoulderLIndex = segmentHash[Segment_UpperTorso][i];
			}
			/**************************/
		}

		/*** Bust level calibration ***/
		Vertex neck = joints[Joint_neck].getCoord();
		Vertex waist = joints[Joint_waist].getCoord();
		if (bustLevel < (neck.y + waist.y) / 2) {
			bustLevel = (neck.y + waist.y) / 2;
		}
		/******************************/

		/*** Align verts near bust level ***/
		vector<Vertex> nearBust;
		int trial = 0;
		float range = 0.5 * 1/s;
		while (nearBust.size() < 12 && trial < 20) {
			nearBust.clear();

			for (int i = 0; i < segmentHash[Segment_UpperTorso].size(); i++) {
				if (abs(vertices[segmentHash[Segment_UpperTorso][i]].y - bustLevel) <= range) {
					Vertex v = vertices[segmentHash[Segment_UpperTorso][i]];
					nearBust.push_back(Vertex(v.idx, v.x, bustLevel, v.z));
				}
			}
			range += range/8;
			trial++;
		}
		/*** Get convex hull***/
		GrahamScan g = GrahamScan(nearBust);
		vector<Vertex> bustConvex = g.GenerateConvexHull();
		float dist = 0;
		for (int i = 1; i < bustConvex.size(); i++) {
			dist += bustConvex[i].distance(bustConvex[i - 1]);
			bustConvexIndices.push_back(bustConvex[i].idx);
		}
		dist += bustConvex[bustConvex.size() - 1].distance(bustConvex[0]);
		bustSize = dist;

		inds.clear();
		secs.clear();
		inds.insert(inds.end(), bustConvexIndices.begin(), bustConvexIndices.end());
		secs.push_back(Segment_UpperTorso);

		landmarks.push_back(Landmark(_T("Bust"), secs, Girth, bustSize, bustLevel, inds));
		/**************************************************/

		/********************** WAIST **********************/
		// Waist : min X val around waist level in segment 8 and 9
		minX = 1000/s;
		minY = 1000/s;
		Vertex waistJoint = joints[Joint_waist].getCoord();
		vector<int> segment_torso;
		//segment_torso.insert(segment_torso.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
		segment_torso.insert(segment_torso.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
		for (int i = 0; i < segment_torso.size(); i++) {
			if (vertices[segment_torso[i]].y < bustLevel) {
				if (abs(vertices[segment_torso[i]].x) < minX && abs(vertices[segment_torso[i]].y - joints[Joint_waist].getCoord().y) < range) {
					minX = abs(vertices[segment_torso[i]].x);
					waistLevel = vertices[segment_torso[i]].y;
				}
			}
		}
		/*** Align verts near waist level ***/
		vector<Vertex> nearWaist;
		trial = 0;
		range = 0.5 * 1/s;
		while (nearWaist.size() < 12 && trial < 20) {
			nearWaist.clear();
			for (int i = 0; i < segment_torso.size(); i++) {
				if (abs(vertices[segment_torso[i]].y - waistLevel) <= range) {
					Vertex v = vertices[segment_torso[i]];
					nearWaist.push_back(Vertex(v.idx, v.x, waistLevel, v.z));
				}
			}
			range += range/8;
			trial++;
		}
		/*** Get convex hull***/
		g = GrahamScan(nearWaist);
		vector<Vertex> waistConvex = g.GenerateConvexHull();
		dist = 0;
		for (int i = 1; i < waistConvex.size(); i++) {
			dist += waistConvex[i].distance(waistConvex[i - 1]);
			waistConvexIndices.push_back(waistConvex[i].idx);
		}
		dist += waistConvex[waistConvex.size() - 1].distance(waistConvex[0]);
		waistSize = dist;

		inds.clear();
		secs.clear();
		inds.insert(inds.end(), waistConvexIndices.begin(), waistConvexIndices.end());
		secs.push_back(Segment_UpperTorso);
		secs.push_back(Segment_LowerTorso);
		landmarks.push_back(Landmark(_T("Waist"), secs, Girth, waistSize, waistLevel, inds));
		/***************************************************/


		/********************** Hip **********************/
		// Hip : min Z val around pelvisMid level in segment 9, 10 and 13
		minZ = 1000/s;
		Vertex pelvisJoint = joints[Joint_pelvisMid].getCoord();
		vector<int> segment_legs;
		segment_legs.insert(segment_legs.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
		segment_legs.insert(segment_legs.end(), segmentHash[Segment_UpperLegR].begin(), segmentHash[Segment_UpperLegR].end());
		segment_legs.insert(segment_legs.end(), segmentHash[Segment_UpperLegL].begin(), segmentHash[Segment_UpperLegL].end());
		for (int i = 0; i < segment_legs.size(); i++) {
			if (abs(vertices[segment_legs[i]].y - pelvisJoint.y) <= 1) {
				if (vertices[segment_legs[i]].z < minZ) {
					minZ = vertices[segment_legs[i]].z;
					hipLevel = vertices[segment_legs[i]].y;
				}
			}
		}
		/*** Align verts near hip level ***/
		vector<Vertex> nearHip;
		trial = 0;
		range = 0.5 * 1/s;
		while (nearHip.size() < 12 && trial < 10) {
			nearHip.clear();

			for (int i = 0; i < segment_legs.size(); i++) {
				if (abs(vertices[segment_legs[i]].y - hipLevel) <= range) {
					Vertex v = vertices[segment_legs[i]];
					nearHip.push_back(Vertex(v.idx, v.x, hipLevel, v.z));
				}
			}
			range += range/8;
			trial++;
		}
		/*** Get convex hull***/
		g = GrahamScan(nearHip);
		vector<Vertex> hipConvex = g.GenerateConvexHull();
		dist = 0;
		for (int i = 1; i < hipConvex.size(); i++) {
			dist += hipConvex[i].distance(hipConvex[i - 1]);
			hipConvexIndices.push_back(hipConvex[i].idx);
		}
		dist += hipConvex[hipConvex.size() - 1].distance(hipConvex[0]);
		hipSize = dist;

		inds.clear();
		secs.clear();
		inds.insert(inds.end(), hipConvexIndices.begin(), hipConvexIndices.end());
		secs.push_back(Segment_LowerTorso);
		secs.push_back(Segment_UpperLegR);
		secs.push_back(Segment_UpperLegL);
		landmarks.push_back(Landmark(_T("Hip"), secs, Girth, hipSize, hipLevel, inds));
		/*************************************************/

		/********************** Neck **********************/
	}
	else {
		bustSize = landmarks[1].value;
		bustLevel = landmarks[1].level;
		bustConvexIndices.insert(bustConvexIndices.end(), landmarks[1].vertIdx.begin(), landmarks[1].vertIdx.end());

		waistSize = landmarks[2].value;
		waistLevel = landmarks[2].level;
		waistConvexIndices.insert(waistConvexIndices.end(), landmarks[2].vertIdx.begin(), landmarks[2].vertIdx.end());

		hipSize = landmarks[3].value;
		hipLevel = landmarks[3].level;
		hipConvexIndices.insert(hipConvexIndices.end(), landmarks[3].vertIdx.begin(), landmarks[3].vertIdx.end());
	}
}

void HumanOBJ::updateRigs() {
	skinning.updateRigs(vertices, joints);
}

void HumanOBJ::centering(float x, float y, float z) {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x -= x;
		vertices[i].y -= y;
		vertices[i].z -= z;
	}
}

void HumanOBJ::jointExport(CString path) {
	ofstream outfile(path + _T("_joints.Joint"));

	for (int i = 0; i < joints.size(); i++) {
		Vertex v = joints[i].getCoord();
		outfile << v.x << " " << v.y << " " << v.z << endl;

		/*
		for (int j = 0; j < joints[i].relatedVerts.size(); j++) {
			outfile << joints[i].relatedVerts[j] << " ";
		}
		*/
		outfile << endl << endl;
	}
	AfxMessageBox(_T("Joints exported.\n"));
	outfile.close();
}

void HumanOBJ::loadOBJ(string dir) {
	int idx = 1;
	string line;
	ifstream basics(dir);
	float maxX = -1000000, minX = 1000000;
	float maxY = -1000000, minY = 1000000;
	float maxZ = -1000000, minZ = 1000000;

	bustLevel = 0;
	waistLevel = 0;
	hipLevel = 0;

	vector<Vertex> tmpnormals, tmptextures;
	while (getline(basics, line)) {
		istringstream iss(line);
		string f;
		float x = -1, y = -1, z = -1, w = -1;

		iss >> f >> x >> y >> z >> w;

		if (f == "v") {
			if (minX > x) {
				minX = x;
				leftMostLevel = x;
			}
			if (x > maxX) {
				maxX = x;
				rightMostLevel = y;
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

			vertices.push_back(Vertex(idx, x, y, z));
			textures.push_back(Vertex());
			normals.push_back(Vertex());
			idx++;
			/* Initialize vertex-joint group */
			segmentGroup.push_back(0);
		}
		else if (f == "vt") {
			tmptextures.push_back(Vertex(x, y , z));
		}
		else if (f == "vn") {
			tmpnormals.push_back(Vertex(x, y, z));
			//normals.push_back(Vertex(x, y, z));
		}
		else if (f == "f") {
			string newLine = line.substr(2, line.length());
			string delimiter1 = " ";
			string delimiter2 = "/";
			size_t pos = 0;
			string token;
			vector<string> ss;
			vector<string> index;
			vector<string> texture;
			vector<string> normal;

			/*** Truncate type area ***/
			while( (pos = newLine.find(delimiter1)) != string::npos ) {
				token = newLine.substr(0, pos);
				ss.push_back(token);
				newLine.erase(0, pos + delimiter1.length());
			}
			ss.push_back(newLine);
			/**************************/

			/*** Get values ***/
			while (!ss.empty()) {
				string sn = ss.back();
				int count = 0;
				//int empty = 1;
				while ((pos = sn.find(delimiter2)) != string::npos) {
					//empty = 0;
					token = sn.substr(0, pos);
					if (count == 0)
						index.push_back(token);
					else if (count == 1 && !tmptextures.empty())
						texture.push_back(token);
					sn.erase(0, pos + delimiter2.length());
					count++;
				}
				//if (empty)
					//index.push_back(sn);
				if (count == 0)
					index.push_back(sn);
				//if (!empty && count == 2 )
				if (count == 2)
					normal.push_back(sn);
				
				ss.pop_back();
			}
			/******************/

			if (index.size() == 4) {
				int i0 = atoi(index[3].c_str());
				int i1 = atoi(index[2].c_str());
				int i2 = atoi(index[1].c_str());
				int i3 = atoi(index[0].c_str());

				if (i0 < 0) {
					i0 = vertices.size() + i0 + 1;
					i1 = vertices.size() + i1 + 1;
					i2 = vertices.size() + i2 + 1;
					i3 = vertices.size() + i3 + 1;
				}
				if (texture.size() > 0) {
					int t0 = atoi(texture[3].c_str());
					int t1 = atoi(texture[2].c_str());
					int t2 = atoi(texture[1].c_str());
					int t3 = atoi(texture[0].c_str());
					if (t0 < 0) {
						t0 = tmptextures.size() + t0 + 1;
						t1 = tmptextures.size() + t1 + 1;
						t2 = tmptextures.size() + t2 + 1;
						t3 = tmptextures.size() + t3 + 1;
					}
					if (tmptextures.size() > 0) {
						textures[i0 - 1] = tmptextures[t0 - 1];
						textures[i1 - 1] = tmptextures[t1 - 1];
						textures[i2 - 1] = tmptextures[t2 - 1];
						textures[i3 - 1] = tmptextures[t3 - 1];
					}
				}

				if (normal.size() > 0) {
					int n0 = atoi(normal[3].c_str());
					int n1 = atoi(normal[2].c_str());
					int n2 = atoi(normal[1].c_str());
					int n3 = atoi(normal[0].c_str());

					if (n0 < 0) {
						n0 = tmpnormals.size() + n0 + 1;
						n1 = tmpnormals.size() + n1 + 1;
						n2 = tmpnormals.size() + n2 + 1;
						n3 = tmpnormals.size() + n3 + 1;
					}

					if (tmpnormals.size() > 0) {
						normals[i0 - 1] = tmpnormals[n0 - 1];
						normals[i1 - 1] = tmpnormals[n1 - 1];
						normals[i2 - 1] = tmpnormals[n2 - 1];
						normals[i3 - 1] = tmpnormals[n3 - 1];
					}
				}

				indices.push_back(i0);
				indices.push_back(i1);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i0 - 1], vertices[i1 - 1], vertices[i3 - 1]));

				indices.push_back(i1);
				indices.push_back(i2);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]));
			}
			else if (index.size() == 3) {
				vector<int> tmpIdx;
				for (int i = index.size() - 1; i >= 0; i--) {
					int idx = atoi(index[i].c_str());
					if (texture.size() > 0) {
						int t = atoi(texture[i].c_str());
						if (t < 0) {
							t = tmptextures.size() + t + 1;
						}
						if (tmptextures.size() > 0)
							textures[idx - 1] = tmptextures[t - 1];
					}
					if (normal.size() > 0) {
						int n = atoi(normal[i].c_str());
						if (n < 0) {
							n = tmpnormals.size() + n + 1;
						}
						if (tmpnormals.size() > 0)
							normals[idx - 1] = tmpnormals[n - 1];
					}

					if (idx < 0) {
						idx = vertices.size() + idx + 1;
					}

					tmpIdx.push_back(idx);

					indices.push_back(idx);
				}
				meshes.push_back(Mesh(vertices[tmpIdx[0] - 1], vertices[tmpIdx[1] - 1], vertices[tmpIdx[2] - 1]));
			}
		}
	}

	/*** Assign tri-mesh ids to vertices ***/
	for (int i = 0; i < meshes.size(); i++) {
		int index1 = meshes[i].index1;
		int index2 = meshes[i].index2;
		int index3 = meshes[i].index3;
		
		vertices[index1 - 1].meshIds.push_back(i);
		vertices[index2 - 1].meshIds.push_back(i);
		vertices[index3 - 1].meshIds.push_back(i);
	}

	topMostLevel = maxY;
	bottomMostLevel = minY;
	leftMostOffset = minX;
	rightMostOffset = maxX;

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);

	topMostLevel -= (minY + maxY) / 2;
	bottomMostLevel -= (minY + maxY) / 2;
	leftMostLevel -= (minY + maxY) / 2;
	rightMostLevel -= (minY + maxY) / 2;
	leftMostOffset -= (minX + maxX) / 2;
	rightMostOffset -= (minX + maxX) / 2;

	cout << vertices.size() << endl;

	skinning = Skinning();
}

void HumanOBJ::loadOBJ(char* dir) {
	int idx = 1;
	string line;
	ifstream basics(dir);
	float maxX = -1000000, minX = 1000000;
	float maxY = -1000000, minY = 1000000;
	float maxZ = -1000000, minZ = 1000000;

	bustLevel = 0;
	waistLevel = 0;
	hipLevel = 0;

	vector<Vertex> tmpnormals, tmptextures;
	while (getline(basics, line)) {
		istringstream iss(line);
		string f;
		float x = -1, y = -1, z = -1, w = -1;

		iss >> f >> x >> y >> z >> w;

		if (f == "v") {
			if (minX > x) {
				minX = x;
				leftMostLevel = x;
			}
			if (x > maxX) {
				maxX = x;
				rightMostLevel = y;
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

			vertices.push_back(Vertex(idx, x, y, z));
			textures.push_back(Vertex());
			normals.push_back(Vertex());
			idx++;
			/* Initialize vertex-joint group */
			segmentGroup.push_back(0);
		}
		else if (f == "vt") {
			tmptextures.push_back(Vertex(x, y , z));
		}
		else if (f == "vn") {
			tmpnormals.push_back(Vertex(x, y, z));
			//normals.push_back(Vertex(x, y, z));
		}
		else if (f == "f") {
			string newLine = line.substr(2, line.length());
			string delimiter1 = " ";
			string delimiter2 = "/";
			size_t pos = 0;
			string token;
			vector<string> ss;
			vector<string> index;
			vector<string> texture;
			vector<string> normal;

			/*** Truncate type area ***/
			while( (pos = newLine.find(delimiter1)) != string::npos ) {
				token = newLine.substr(0, pos);
				ss.push_back(token);
				newLine.erase(0, pos + delimiter1.length());
			}
			ss.push_back(newLine);
			/**************************/

			/*** Get values ***/
			while (!ss.empty()) {
				string sn = ss.back();
				int count = 0;
				//int empty = 1;
				while ((pos = sn.find(delimiter2)) != string::npos) {
					//empty = 0;
					token = sn.substr(0, pos);
					if (count == 0)
						index.push_back(token);
					else if (count == 1 && !tmptextures.empty())
						texture.push_back(token);
					sn.erase(0, pos + delimiter2.length());
					count++;
				}
				//if (empty)
					//index.push_back(sn);
				if (count == 0)
					index.push_back(sn);
				//if (!empty && count == 2 )
				if (count == 2)
					normal.push_back(sn);
				
				ss.pop_back();
			}
			/******************/

			if (index.size() == 4) {
				int i0 = atoi(index[3].c_str());
				int i1 = atoi(index[2].c_str());
				int i2 = atoi(index[1].c_str());
				int i3 = atoi(index[0].c_str());

				if (i0 < 0) {
					i0 = vertices.size() + i0 + 1;
					i1 = vertices.size() + i1 + 1;
					i2 = vertices.size() + i2 + 1;
					i3 = vertices.size() + i3 + 1;
				}
				if (texture.size() > 0) {
					int t0 = atoi(texture[3].c_str());
					int t1 = atoi(texture[2].c_str());
					int t2 = atoi(texture[1].c_str());
					int t3 = atoi(texture[0].c_str());
					if (t0 < 0) {
						t0 = tmptextures.size() + t0 + 1;
						t1 = tmptextures.size() + t1 + 1;
						t2 = tmptextures.size() + t2 + 1;
						t3 = tmptextures.size() + t3 + 1;
					}
					if (tmptextures.size() > 0) {
						textures[i0 - 1] = tmptextures[t0 - 1];
						textures[i1 - 1] = tmptextures[t1 - 1];
						textures[i2 - 1] = tmptextures[t2 - 1];
						textures[i3 - 1] = tmptextures[t3 - 1];
					}
				}

				if (normal.size() > 0) {
					int n0 = atoi(normal[3].c_str());
					int n1 = atoi(normal[2].c_str());
					int n2 = atoi(normal[1].c_str());
					int n3 = atoi(normal[0].c_str());

					if (n0 < 0) {
						n0 = tmpnormals.size() + n0 + 1;
						n1 = tmpnormals.size() + n1 + 1;
						n2 = tmpnormals.size() + n2 + 1;
						n3 = tmpnormals.size() + n3 + 1;
					}

					if (tmpnormals.size() > 0) {
						normals[i0 - 1] = tmpnormals[n0 - 1];
						normals[i1 - 1] = tmpnormals[n1 - 1];
						normals[i2 - 1] = tmpnormals[n2 - 1];
						normals[i3 - 1] = tmpnormals[n3 - 1];
					}
				}

				indices.push_back(i0);
				indices.push_back(i1);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i0 - 1], vertices[i1 - 1], vertices[i3 - 1]));

				indices.push_back(i1);
				indices.push_back(i2);
				indices.push_back(i3);
				meshes.push_back(Mesh(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]));
			}
			else if (index.size() == 3) {
				vector<int> tmpIdx;
				for (int i = index.size() - 1; i >= 0; i--) {
					int idx = atoi(index[i].c_str());
					if (texture.size() > 0) {
						int t = atoi(texture[i].c_str());
						if (t < 0) {
							t = tmptextures.size() + t + 1;
						}
						if (tmptextures.size() > 0)
							textures[idx - 1] = tmptextures[t - 1];
					}
					if (normal.size() > 0) {
						int n = atoi(normal[i].c_str());
						if (n < 0) {
							n = tmpnormals.size() + n + 1;
						}
						if (tmpnormals.size() > 0)
							normals[idx - 1] = tmpnormals[n - 1];
					}

					if (idx < 0) {
						idx = vertices.size() + idx + 1;
					}

					tmpIdx.push_back(idx);

					indices.push_back(idx);
				}
				meshes.push_back(Mesh(vertices[tmpIdx[0] - 1], vertices[tmpIdx[1] - 1], vertices[tmpIdx[2] - 1]));
			}
		}
	}

	/*** Assign tri-mesh ids to vertices ***/
	for (int i = 0; i < meshes.size(); i++) {
		int index1 = meshes[i].index1;
		int index2 = meshes[i].index2;
		int index3 = meshes[i].index3;
		
		vertices[index1 - 1].meshIds.push_back(i);
		vertices[index2 - 1].meshIds.push_back(i);
		vertices[index3 - 1].meshIds.push_back(i);
	}

	topMostLevel = maxY;
	bottomMostLevel = minY;
	leftMostOffset = minX;
	rightMostOffset = maxX;

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);

	topMostLevel -= (minY + maxY) / 2;
	bottomMostLevel -= (minY + maxY) / 2;
	leftMostLevel -= (minY + maxY) / 2;
	rightMostLevel -= (minY + maxY) / 2;
	leftMostOffset -= (minX + maxX) / 2;
	rightMostOffset -= (minX + maxX) / 2;

	cout << vertices.size() << endl;
	skinning = Skinning();
}

void HumanOBJ::writeToOBJ(string path) {
	CString p(path.c_str());
	ofstream outfile(p + _T("_exported.obj"));

	for (int i = 0; i < vertices.size(); i++)
		outfile << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;

	for (int i = 0; i < indices.size(); i+=3) {
		int i1 = indices[i];
		int i2 = indices[i+1];
		int i3 = indices[i+2];
		outfile << "f " << i1 << " " << i2 << " " << i3 << endl;
	}
	outfile.close();

	AfxMessageBox(_T("File exported.\n"));
}

void HumanOBJ::writeToOBJ(CString path) {
	ofstream outfile(path + _T("_exported.obj"));

	for (int i = 0; i < vertices.size(); i++)
		outfile << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;

	for (int i = 0; i < indices.size(); i+=3) {
		int i1 = indices[i];
		int i2 = indices[i+1];
		int i3 = indices[i+2];
		outfile << "f " << i1 << " " << i2 << " " << i3 << endl;
	}

	outfile.close();
	AfxMessageBox(_T("File exported.\n"));
}

void HumanOBJ::writeToOBJ(char* path) {
	ofstream outfile(path);

	for (int i = 0; i < vertices.size(); i++)
		outfile << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;

	for (int i = 0; i < indices.size(); i+=3) {
		int i1 = indices[i];
		int i2 = indices[i+1];
		int i3 = indices[i+2];
		outfile << "f " << i1 << " " << i2 << " " << i3 << endl;
	}


	outfile.close();
}

void HumanOBJ::generateBoundingSurface() {

}

void HumanOBJ::generateTights(vector<Vertex> verts) {
	int** adjacencyMatrix;
	vector<int> z_plus_binary_index, z_minus_binary_index, x_plus_binary_index, x_minus_binary_index;

	adjacencyMatrix = (int**) malloc(sizeof(int*) * verts.size());
	for (int i = 0; i < verts.size(); i++) {
		adjacencyMatrix[i] = (int*) malloc(sizeof(int) * verts.size());
		for (int j = 0; j < verts.size(); j++) {
			*(adjacencyMatrix[i] + j) = 0;
		}
	}

	for (int i = 0; i < verts.size(); i++) {
		if (verts[i].x >= 0) {
			x_plus_binary_index.push_back(i);
		}
		if (verts[i].z >= 0) {
			z_plus_binary_index.push_back(i);
		}
		if (verts[i].x < 0) {
			x_minus_binary_index.push_back(i);
		}
		if (verts[i].z < 0) {
			z_minus_binary_index.push_back(i);
		}
	}

	int trial = 0;
	float radius = 1 / scaleFactor;
	while (trial < 10) {
		for (int i = 0; i < z_plus_binary_index.size(); i++) {
			Vertex vi = verts[z_plus_binary_index[i]];

			for (int j = 0; j < z_plus_binary_index.size(); j++) {
				Vertex vj = verts[z_plus_binary_index[j]];

				if (vi.distance(vj) <= 2 * radius) {
					*(adjacencyMatrix[i] + j) = 1;
					*(adjacencyMatrix[j] + i) = 1;
				}
			}
		}

		trial += 1;
		radius += radius;
	}

	trial = 0;
	radius = 1 / scaleFactor;
	while (trial < 10) {
		for (int i = 0; i < z_minus_binary_index.size(); i++) {
			Vertex vi = verts[z_minus_binary_index[i]];

			for (int j = 0; j < z_minus_binary_index.size(); j++) {
				Vertex vj = verts[z_minus_binary_index[j]];

				if (vi.distance(vj) <= 2 * radius) {
					*(adjacencyMatrix[i] + j) = 1;
					*(adjacencyMatrix[j] + i) = 1;
				}
			}
		}

		trial += 1;
		radius += radius;
	}

	trial = 0;
	radius = 1 / scaleFactor;
	while (trial < 10) {
		for (int i = 0; i < x_plus_binary_index.size(); i++) {
			Vertex vi = verts[x_plus_binary_index[i]];

			for (int j = 0; j < x_plus_binary_index.size(); j++) {
				Vertex vj = verts[x_plus_binary_index[j]];

				if (vi.distance(vj) <= 2 * radius) {
					*(adjacencyMatrix[i] + j) = 1;
					*(adjacencyMatrix[j] + i) = 1;
				}
			}
		}

		trial += 1;
		radius += radius;
	}

	trial = 0;
	radius = 1 / scaleFactor;
	while (trial < 10) {
		for (int i = 0; i < x_minus_binary_index.size(); i++) {
			Vertex vi = verts[x_minus_binary_index[i]];

			for (int j = 0; j < x_minus_binary_index.size(); j++) {
				Vertex vj = verts[x_minus_binary_index[j]];

				if (vi.distance(vj) <= 2 * radius) {
					*(adjacencyMatrix[i] + j) = 1;
					*(adjacencyMatrix[j] + i) = 1;
				}
			}
		}

		trial += 1;
		radius += radius;
	}


	for (int i = 0; i < verts.size(); i++) {
		free(adjacencyMatrix[i]);
	}
	free(adjacencyMatrix);
}

void HumanOBJ::generateDress(vector<int> bodySegments) {
}

void HumanOBJ::generateTop(vector<int> bodySegments) {

}

void HumanOBJ::generatePants(vector<int> bodySegments) {
}

void HumanOBJ::generateSkirt(vector<int> bodySegments) {
}

void HumanOBJ::writeDressForm(int type, CString path, vector<int> bodyParts) {
	CString fullPath(path);

	if (type == TIGHTS) {
		fullPath = path + _T("_tights.obj");
		//generateTights(bodyParts);
	}
	else if (type == DRESS) {
		fullPath = path + _T("_dress.obj");
	}
	else if (type == TOP) {
		fullPath = path + _T("_top.obj");
	}
	else if (type == PANTS) {
		fullPath = path + _T("_pants.obj");
	}
	else if (type == SKIRT) {
		fullPath = path + _T("_skirt.obj");
	}

	ofstream outfile(fullPath);

	vector<Vertex> layers;
	vector<Vertex> convexVerts;

	vector<int> verts(vertices.size(), -1);
	vector<int> meshCount(meshes.size(), 0);

	int newIdx = 0;
	float height = vertices[segmentHash[bodyParts[0]][0]].y;

	for (int i = 0; i < bodyParts.size(); i++) {
		for (int j = 0; j < segmentHash[bodyParts[i]].size(); j++) {
			Vertex v = vertices[segmentHash[bodyParts[i]][j]];

			if (abs(v.y - height) < 1 / scaleFactor) {
				layers.push_back(v);
			}
			else {
				GrahamScan g = GrahamScan(layers);
				vector<Vertex> convex = g.GenerateConvexHull();

				for (int k = 0; k < convex.size() - 1; k++) {
					outfile << "v " << convex[k].x << " " << convex[k].y << " " << convex[k].z << endl;

					verts[convex[k].idx - 1] = newIdx + 1;
					newIdx++;

					convexVerts.push_back(convex[k]);

					/*
					for (int l = 0; l < meshes.size(); l++) {
						if (meshes[l].has(convex[k].idx)) {
							meshCount[l] += 1;
						}
					}
					*/
				}

				height = v.y;
				layers.clear();
			}

			/*
			outfile << "v " << v.x << " " << v.y << " " << v.z << endl;

			verts[v.idx - 1] = newIdx + 1;
			newIdx++;

			for (int k = 0; k < meshes.size(); k++) {
				if (meshes[k].has(v.idx)) {
					meshCount[k] += 1;
				}
			}
			*/
		}
	}


	if (type == TIGHTS) {
		generateTights(convexVerts);
	}

	/*
	for (int i = 0; i < meshCount.size(); i++) {
		if (meshCount[i] == 3) {
			outfile << "f " << verts[meshes[i].index1 - 1] << " " << verts[meshes[i].index2 - 1] << " " << verts[meshes[i].index3 - 1] << endl;
		}
	}
	*/



	outfile.close();
	AfxMessageBox(_T("Dressform exported.\n"));
}

int HumanOBJ::getBodyPartNum(char* name) {
	if (name == "Head") {
		return Segment_Head;
	}
	if (name == "Neck") {
		return Segment_Neck;
	}
	if (name == "Upper Torso") {
		return Segment_UpperTorso;
	}
	if (name == "Lower Torso") {
		return Segment_LowerTorso;
	}
	if (name == "Upper Arm R") {
		return Segment_UpperArmR;
	}
	if (name == "Upper Arm L") {
		return Segment_UpperArmL;
	}
	if (name == "Lower Arm R") {
		return Segment_LowerArmR;
	}
	if (name == "Lower Arm L") {
		return Segment_LowerArmL;
	}
	if (name == "Hand R") {
		return Segment_HandR;
	}
	if (name == "Hand L") {
		return Segment_HandL;
	}
	if (name == "Upper Leg R") {
		return Segment_UpperLegR;
	}
	if (name == "Upper Leg L") {
		return Segment_UpperLegL;
	}
	if (name == "Lower Leg R") {
		return Segment_LowerLegR;
	}
	if (name == "Lower Leg L") {
		return Segment_LowerLegL;
	}
	if (name == "Foot R") {
		return Segment_FootR;
	}
	if (name == "Foot L") {
		return Segment_FootL;
	}

	return -1;
}

int HumanOBJ::getBodyPartPointNum(int part) {
	return segmentHash[part].size();
}

void HumanOBJ::getBodyPartPointIndex(int part, int* nums) {
	int j = 0;
	for (int i = 0; i < segmentHash[part].size(); i++) {
		nums[j++] = segmentHash[part][i];
	}
}

void HumanOBJ::getBodyPartPointPos(int part, float* coords) {
	int j = 0;
	for (int i = 0; i < segmentHash[part].size(); i++) {
		coords[j++] = vertices[segmentHash[part][i]].x;
		coords[j++] = vertices[segmentHash[part][i]].y;
		coords[j++] = vertices[segmentHash[part][i]].z;
	}
}