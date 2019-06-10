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
//#include "Bone.h"
#include "Skinning.h"
#include "GrahamScan.h"
#include "Landmark.h"

class HumanOBJ {
public :
	HumanOBJ();
	HumanOBJ(string);
	~HumanOBJ();

	vector<Mesh> meshes;

	Vertex scaleFactor;
	Vertex translateFactor;
	vector<int> segmentGroup;
	vector<int> weightGroup;
	vector<float> weightValues;

	Skinning skinning;
	vector<int> segmentHash[16];
	vector<int> weightHash[16];
	vector<float> weightValueHash[16];

	vector<Vertex>& getVerts();
	vector<Vertex>& getNormals();
	vector<int>& getIndices();
	vector<Joint>& getJoints(string);

	vector<Landmark>& setLandmarks(string);

	float getBustSize();
	float getWaistSize();
	float getHipSize();

	void setSize(float, float, float, float);
	float height; 
	float topMostLevel, bottomMostLevel;
	float bustLevel, waistLevel, hipLevel;
	vector<int> bustConvexIndices, waistConvexIndices, hipConvexIndices;

	void setJoint(int, float, float);
	void setRigs();
	void setSegments();
	void setFeatures();
	void setWeights();

	void jointExport();
	void writeToOBJ();

	vector<Vertex> vertices;
	vector<Joint> joints;
	vector<Vertex> textures;
	vector<Vertex> normals;

	vector<Landmark> landmarks;

private :
	vector<Mesh> faces;
	vector<int> indices;

	JointTree jointTree;
	vector<Bone> bones;


	float bustSize, waistSize, hipSize;

	int shoulderRIndex, shoulderLIndex; // Index of armhole point with biggest abs(x value)

	vector<Vertex*> neckPlane;
	vector<Vertex*> shoulderMidPlane, shoulderRPlane, shoulderLPlane;
	vector<Vertex*> elbowRPlane, elbowLPlane, wristRPlane, wristLPlane;
	vector<Vertex*> waistPlane, pelvisMidPlane, pelvisRPlane, pelvisLPlane;
	vector<Vertex*> highThighRPlane, highThighLPlane;
	vector<Vertex*> kneeRPlane, kneeLPlane, ankleRPlane, ankleLPlane;

	void bindRigs();
	void updateRigs();

	void centering(float, float, float);
};
