#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Mesh.h"
#include "JointTree.h"
#include "Skinning.h"

class HumanOBJ {
public :
	HumanOBJ();
	HumanOBJ(string);
	~HumanOBJ();

	Vertex scaleFactor;
	Vertex translateFactor;

	vector<Vertex>& getVerts();
	vector<Vertex>& getNormals();
	vector<int>& getIndices();
	vector<Joint>& getJoints();

	vector<int> vertexJointGroup;

	void setJoint(int, float, float);
	void setPosing();

	void jointExport();
	void writeToOBJ();
	void rig(BodyProxies&);
	void segment();

private :
	vector<Vertex> vertices;
	vector<Vertex> normals;
	vector<Mesh> faces;
	vector<int> indices;

	JointTree jointTree;
	vector<Joint> joints;
	Skinning skinning;


	void centering(float, float, float);
};
