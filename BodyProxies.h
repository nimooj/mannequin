#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#include "Vertex.h"
#include "Mesh.h"
#include "Layer.h"
#include "LayerTree.h"
#include "JointTree.h"

#include "BodyLayerDefinition.h"
#include "JointDefinition.h"


class BodyProxies {
public:
	BodyProxies();
	BodyProxies(string);
	~BodyProxies();

	LayerTree& getBodyLayers();
	JointTree& getJointTree();
	vector<Joint>& getJoints();

	vector<Vertex>& getVerts();
	vector<int>& getIndices();
	vector<Vertex>& getNormals();

	void updateBodyProxies(vector<Vertex>);
	void writeToOBJ(vector<Vertex>*, vector<int>*, vector<Vertex>*);

private:
	vector<Vertex> baseVert;
	vector<Mesh> baseMesh;
	vector<int> baseIndices;
	vector<Vertex> baseNormal;

	void centering(float, float, float);
	void setPosing();

	LayerTree bodyLayers;
	JointTree jointTree;

	Layer *neck;
	Layer *shoulderTop, *shoulderTopMid, *shoulderMid, *shoulderMidArmpit, *armpit;
	Layer *armpitBust, *bust, *waist, *hip, *crotch;
	Layer *highThighR, *highThighL;
	Layer *kneeR, *kneeL;
	Layer *ankleR, *ankleL;
	Layer *armHoleR, *armHoleL;
	Layer *armpitR, *armpitL;
	Layer *elbowR, *elbowL;
	Layer *wristR, *wristL;

	vector<Joint> joints;

};
