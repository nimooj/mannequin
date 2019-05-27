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
	float maxX = -1000, minX = 1000;
	float maxY = -1000, minY = 1000;
	float maxZ = -1000, minZ = 1000;

	bustLevel = 0;
	waistLevel = 0;
	hipLevel = 0;

	vector<Vertex> tmpnormals;
	while (getline(basics, line)) {
		istringstream iss(line);
		string f;
		float x = -1, y = -1, z = -1, w = -1;

		iss >> f >> x >> y >> z >> w;

		if (f == "v") {
			x /= 10;
			y /= 10;
			z /= 10;

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

			vertices.push_back(Vertex(idx, x, y, z));
			idx++;
			/* Initialize vertex-joint group */
			segmentGroup.push_back(0);
		}
		else if (f == "vn") {
			tmpnormals.push_back(Vertex(x, y, z));
			normals.push_back(Vertex());
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
			if (index.size() == 4) {
				int idx0 = atoi(index[3].c_str());
				int idx1 = atoi(index[2].c_str());
				int idx2 = atoi(index[1].c_str());
				int idx3 = atoi(index[0].c_str());

				indices.push_back(idx0);
				indices.push_back(idx1);
				indices.push_back(idx3);
				meshes.push_back(Mesh(vertices[idx0 - 1], vertices[idx1 - 1], vertices[idx3 - 1]));

				indices.push_back(idx1);
				indices.push_back(idx2);
				indices.push_back(idx3);
				meshes.push_back(Mesh(vertices[idx1 - 1], vertices[idx2 - 1], vertices[idx3 - 1]));

				normals[idx0 - 1] = tmpnormals[idx0 - 1];
				normals[idx1 - 1] = tmpnormals[idx1 - 1];
				normals[idx2 - 1] = tmpnormals[idx2 - 1];
				normals[idx3 - 1] = tmpnormals[idx3 - 1];

			}
			else if (index.size() == 3) {
				vector<int> tmpIdx;
				for (int i = index.size() - 1; i >= 0; i--) {
					int idx = atoi(index[i].c_str());
					tmpIdx.push_back(idx);

					normals[idx - 1] = tmpnormals[idx - 1];
					indices.push_back(idx);
					//indices.push_back(atoi(index[i].c_str()));
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

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
	skinning = Skinning();
}

HumanOBJ::~HumanOBJ() {

}

vector<Vertex>& HumanOBJ::getVerts() {
	return vertices;
}

vector<Vertex>& HumanOBJ::getNormals() {
	return normals;
}

vector<int>& HumanOBJ::getIndices() {
	return indices;
}

vector<Joint>& HumanOBJ::getJoints() {
	if (joints.size() == 0) {
		ifstream infile("layers/humanJoints.txt");
		string s;
		int idx = 0;
		while (getline(infile, s)) {
			istringstream iss(s);
			float x, y, z;
			iss >> x >> y >> z;
			joints.push_back(Joint(idx, Vertex(x, y, z)));
			idx++;
		}
		infile.close();
	}
	return joints;
}

void HumanOBJ::setJoint(int jointIdx, float x, float y) {
	vector<Vertex> vinQ;
	for (int i = 0; i < vertices.size(); i++) {
		if (abs(vertices[i].x - x) <= 0.3 && abs(vertices[i].y - y) <= 0.3 )  {
			vinQ.push_back(vertices[i]);
		}
	}

	if (!vinQ.empty()) {
		float maxX = -1000, minX = 1000;
		float maxY = -1000, minY = 1000;
		float maxZ = -1000, minZ = 1000;

		for (int i = 0; i < vinQ.size(); i++) {
			if (minX > vinQ[i].x) {
				minX = vinQ[i].x;
			}
			if (vinQ[i].x > maxX) {
				maxX = vinQ[i].x;
			}
			if (minY > vinQ[i].y) {
				minY = vinQ[i].y;
			}
			if (vinQ[i].y > maxY) {
				maxY = vinQ[i].y;
			}
			if (minZ > vinQ[i].z) {
				minZ = vinQ[i].z;
			}
			if (vinQ[i].z > maxZ) {
				maxZ = vinQ[i].z;
			}
			//joints.push_back(Joint(3,vinQ[i]));
		}

		Vertex tmp = Vertex((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);

		Joint joint = Joint(jointIdx, tmp);
		joints.push_back(joint);
		jointTree.append(joint);
	}
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

	bustSize = dist * 10;

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

	waistSize = dist * 10;

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

	hipSize = dist * 10;

	return hipSize;
}

void HumanOBJ::setThreeSize(float height, float b, float w, float h) {
	float bustScale = b / bustSize;
	float waistScale = w / waistSize;
	float hipScale = h / hipSize;
	float armHoleMovementR = 0;
	float armHoleMovementL = 0;

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

	float range = 0.25;
	for (int i = 0; i < vertIdx.size(); i++) {
		int idx = vertIdx[i];
		if (abs(vertices[idx].y - bustLevel) < range) {
			vertices[idx].x *= bustScale;
			vertices[idx].z *= bustScale;
		}
		else if (abs(vertices[idx].y - waistLevel) < range) {
			vertices[idx].x *= waistScale;
			vertices[idx].z *= waistScale;
		}
		else if (abs(vertices[idx].y - hipLevel) < range) {
			vertices[idx].x *= hipScale;
			vertices[idx].z *= hipScale;
		}
		else if (vertices[idx].y >= bustLevel + range) {
			if (idx == shoulderRIndex) {
				armHoleMovementR = vertices[idx].x*bustScale - vertices[idx].x;
			}
			if (idx == shoulderLIndex) {
				armHoleMovementL = vertices[idx].x*bustScale - vertices[idx].x;
			}

			vertices[idx].x *= bustScale;
			vertices[idx].z *= bustScale;
		}
		else if (vertices[idx].y >= bustLevel + range) {
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
		}
	}
	/*** Move arm ***/
	for (int i = 0; i < armRIdx.size(); i++) {
		vertices[armRIdx[i]].x += armHoleMovementR;
	}
	for (int i = 0; i < armLIdx.size(); i++) {
		vertices[armLIdx[i]].x += armHoleMovementL;
	}

	bustSize = getBustSize();
	waistSize = getWaistSize();
	hipSize = getHipSize();

	height = (topMostLevel - bottomMostLevel) * 10;
	/*** Joint transition ***/
	//updateRigs();
}

void HumanOBJ::setRigs() {
	skinning.setHierarchy(joints);
	skinning.setBones(joints, bones);

	setSegments();
	bindRigs();
	setFeatures();  //... Segment 다 나누면 다시 활성화 필요 for Sizing
	skinning.paintWeights(vertices, joints, weightGroup);
}

void HumanOBJ::setSegments() {
	// Result saved in segmentGroup, segmentHash;
	// segmentGroup.size() == vertices.size() and share indices
	skinning.setSegments(vertices, joints, segmentGroup, weightHash, weightValueHash);
}

void HumanOBJ::setWeights() {
}

void HumanOBJ::setFeatures() {
	float minZ = 1000, maxZ = -1000;
	float minX = 1000, maxX = -1000; 
	float minY = 1000, maxY = -1000;

	for (int i = 0; i < segmentGroup.size(); i++) {
		segmentHash[segmentGroup[i]].push_back(i); // push vertices ARRAY index
	}


	/********************** BUST **********************/
	// Bust : max z val in segment 8
	for (int i = 0; i < segmentHash[Segment_UpperTorso].size(); i++) {
		if (vertices[segmentHash[Segment_UpperTorso][i]].z > maxZ) {
			maxZ = vertices[segmentHash[Segment_UpperTorso][i]].z;
			bustLevel = vertices[segmentHash[Segment_UpperTorso][i]].y;
		}

		if (vertices[segmentHash[Segment_UpperTorso][i]].x < minX) {
			minX = vertices[segmentHash[Segment_UpperTorso][i]].x;
			shoulderRIndex = segmentHash[Segment_UpperTorso][i];
		}

		if (vertices[segmentHash[Segment_UpperTorso][i]].x > maxX) {
			maxX = vertices[segmentHash[Segment_UpperTorso][i]].x;
			shoulderLIndex = segmentHash[Segment_UpperTorso][i];
		}
	}
	/*** Align verts near bust level ***/
	vector<Vertex> nearBust; 
	for (int i = 0; i < segmentHash[Segment_UpperTorso].size(); i++) {
		if (abs(vertices[segmentHash[Segment_UpperTorso][i]].y - bustLevel) <= 0.5) {
			Vertex v = vertices[segmentHash[Segment_UpperTorso][i]];
			nearBust.push_back(Vertex(v.idx, v.x, bustLevel, v.z));
		}
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
	bustSize = dist * 10;
	/**************************************************/

	/********************** WAIST **********************/
	// Waist : min X val around waist level in segment 8 and 9
	minX = 1000;
	minY = 1000;
	Vertex waistJoint = joints[Joint_waist].getCoord();
	vector<int> segment_torso;
	segment_torso.insert(segment_torso.end(), segmentHash[Segment_UpperTorso].begin(), segmentHash[Segment_UpperTorso].end());
	segment_torso.insert(segment_torso.end(), segmentHash[Segment_LowerTorso].begin(), segmentHash[Segment_LowerTorso].end());
	for (int i = 0; i < segment_torso.size(); i++) {
		if (vertices[segment_torso[i]].y < bustLevel && abs(vertices[segment_torso[i]].y - waistJoint.y) <= 0.2) {
			if (vertices[segment_torso[i]].x > 0 && vertices[segment_torso[i]].x < minX) {
				minX = vertices[segment_torso[i]].x;
				waistLevel = vertices[segment_torso[i]].y;
			}
		}

	}
	/*** Align verts near waist level ***/
	vector<Vertex> nearWaist;
	for (int i = 0; i < segment_torso.size(); i++) {
		if (abs(vertices[segment_torso[i]].y - waistLevel) <= 0.5) {
			Vertex v = vertices[segment_torso[i]];
			nearWaist.push_back(Vertex(v.idx, v.x, waistLevel, v.z));
		}
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
	waistSize = dist * 10;
	/***************************************************/

	/********************** Hip **********************/
	// Hip : min Z val around pelvisMid level in segment 9, 10 and 13
	minZ = 1000;
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
	for (int i = 0; i < segment_legs.size(); i++) {
		if (abs(vertices[segment_legs[i]].y - hipLevel) <= 0.5) {
			Vertex v = vertices[segment_legs[i]];
			nearHip.push_back(Vertex(v.idx, v.x, hipLevel, v.z));
		}
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
	hipSize = dist * 10;
	/*************************************************/

	maxY = -1000;
	for (int i = 0; i < segmentHash[Segment_Head].size(); i++) {
		if (vertices[segmentHash[Segment_Head][i]].y > maxY) {
			topMostLevel = vertices[segmentHash[Segment_Head][i]].y;
		}
	}

	minY = 1000;
	vector<int> segment_lowLegs;
	segment_lowLegs.insert(segment_lowLegs.end(), segmentHash[Segment_LowerLegR].begin(), segmentHash[Segment_LowerLegR].end());
	segment_lowLegs.insert(segment_lowLegs.end(), segmentHash[Segment_LowerLegL].begin(), segmentHash[Segment_LowerLegL].end());
	for (int i = 0; i < segment_lowLegs.size(); i++) {
		if (vertices[segment_lowLegs[i]].y < minY) {
			bottomMostLevel = vertices[segment_lowLegs[i]].y;
		}
	}

}

void HumanOBJ::bindRigs() {
	skinning.setBindings(vertices, joints, segmentGroup);
}

void HumanOBJ::updateRigs() {
	skinning.updateRigs(joints);
}

void HumanOBJ::centering(float x, float y, float z) {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x -= x;
		vertices[i].y -= y;
		vertices[i].z -= z;
	}

}

void HumanOBJ::jointExport() {
	ofstream outfile("layers/humanJoints.txt");
	for (int i = 0; i < joints.size(); i++) {
		Vertex v = joints[i].getCoord();
		outfile << v.x << " " << v.y << " " << v.z << endl;
	}
	cout << "Joints exported.\n" << endl;
	outfile.close();

}

void HumanOBJ::writeToOBJ() {
	ofstream outfile("layers/Body.obj");

	for (int i = 0; i < vertices.size(); i++)
		outfile << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;

	for (int i = 0; i < indices.size(); i+=3) {
		int i1 = indices[i];
		int i2 = indices[i+1];
		int i3 = indices[i+2];
		//outfile << "f " << i1 << "\/\/" << i1 << " " << i2 << "\/\/" << i2 << " " << i3 << "\/\/" << i3 << endl;
		outfile << "f " << i1 << " " << i2 << " " << i3 << endl;
	}
	outfile.close();

	//AfxMessageBox(CString("OBJ exported.\n"));
	cout << "OBJ exported.\n" << endl;
}