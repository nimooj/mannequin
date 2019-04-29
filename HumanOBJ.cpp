#include "stdafx.h"
#include "HumanOBJ.h"

HumanOBJ::HumanOBJ() {

}

HumanOBJ::HumanOBJ(string dir) {
	int idx = 1;
	string line;
	ifstream basics(dir);
	float maxX = -1000, minX = 1000;
	float maxY = -1000, minY = 1000;
	float maxZ = -1000, minZ = 1000;

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
			vertexJointGroup.push_back(0);
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

				indices.push_back(idx1);
				indices.push_back(idx2);
				indices.push_back(idx3);

				normals[idx0 - 1] = tmpnormals[idx0 - 1];
				normals[idx1 - 1] = tmpnormals[idx1 - 1];
				normals[idx2 - 1] = tmpnormals[idx2 - 1];
				normals[idx3 - 1] = tmpnormals[idx3 - 1];
			}
			else if (index.size() == 3) {
				for (int i = index.size() - 1; i >= 0; i--) {
					int idx = atoi(index[i].c_str());

					normals[idx - 1] = tmpnormals[idx - 1];
					indices.push_back(idx);
					//indices.push_back(atoi(index[i].c_str()));
				}
			}
		}
	}

	centering((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
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

void HumanOBJ::setPosing() {
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

}

void HumanOBJ::rig(BodyProxies& body) {
	skinning = Skinning(body);
	skinning.matchRigs(joints);
}

void HumanOBJ::segment() {
	// Result saved in vertexJointGroup
	skinning.segment(vertices, joints, vertexJointGroup);
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

	/*** Auto Rig match && skinning ***/
	skinning.matchRigs(joints);
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