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
#include "GrahamScan.h"
#include "Landmark.h"
#include "BoneDefinition.h"

#define TIGHTS 0
#define DRESS 1
#define TOP 2
#define PANTS 3
#define SKIRT 4

class HumanOBJ {
public :
	HumanOBJ();
	HumanOBJ(string);
	~HumanOBJ();

	int** neighbor;

	float scaleFactor;

	vector<Vertex> vertices;
	vector<Joint> joints;
	vector<Vertex> textures;
	vector<Vertex> normals;
	vector<Mesh> meshes; // Always Tri-mesh

	vector<Landmark> landmarks;

	vector<int> segmentGroup;
	vector<int> weightGroup;
	vector<float> weightValues;

	Skinning skinning;
	vector<int> bodySegment[SegmentNum]; // vert indices
	vector<int> weightHash[WeightNum]; // vert indices
	vector<float> weightValueHash[WeightNum]; // vert indices

	vector<float>* bra;
	vector<Mesh>* braArea;
	vector<int>* braIndices;
	vector<int>* braEBO;

	vector<float>* underpants;

	Vertex* crotch;

	void setBra();
	void setUnderpants();


	void getVert(int, float*); // DLL
	vector<Vertex>& getVerts();
	void getVerts(float*); // DLL
	vector<int>& getIndices();
	vector<Vertex>& getNormals();
	vector<Joint>& getJoints(string);
	void loadJoints(char*); // DLL

	void getMesh(int, int*); // DLL
	void getIndices(int*); // DLL
	int getVertSize(); // DLL
	int getMeshSize(); // DLL

	int getLandmarkNum(); // DLL
	vector<Landmark>& setLandmarks(string);
	void loadLandmarks(char*); // DLL

	float getBustSize();
	float getWaistSize();
	float getHipSize();

	void setHeight(float);
	void setBustSize(float, float);
	void setWaistSize(float, float);
	void setHipSize(float, float);
	void setArmLength(int, float);
	void setShoulderLength(int, float);

	void setSize(float, int, int, float, float); // DLL
	void setSize(float, float, float, float, float);
	bool resize(float*); // DLL
	float getSize(int); // DLL
	void getSizeName(int, char*); // DLL
	int getSizePathLength(int); // DLL
	void getSizePathPos(int, int, float*); // DLL
	void getSizePathPos(int, float*); // DLL

	float height; 
	float topMostLevel, bottomMostLevel, leftMostLevel, rightMostLevel;
	float leftMostOffset, rightMostOffset;

	int topMostIndex, bottomMostIndex, leftMostIndex, rightMostIndex;

	float bustLevel, waistLevel, hipLevel;
	vector<int> bustConvexIndices, waistConvexIndices, hipConvexIndices;

	float highNeckLevel, lowNeckLevel;
	vector<int> highNeckConvexIndices, lowNeckConvexIndices;
	float shoulderROffset, shoulderLOffset;
	vector<int> shoulderRConvexIndices, shoulderLConvexIndices;
	//vector<int> armpitConvexIndices;
	float elbowROffset, elbowLOffset;
	vector<int> elbowRConvexIndices, elbowLConvexIndices;
	float wristROffset, wristLOffset;
	vector<int> wristRConvexIndices, wristLConvexIndices;

	float highThighRLevel, highThighLLevel;
	vector<int> highThighRConvexIndices, highThighLConvexIndices;
	float kneeRLevel, kneeLLevel;
	vector<int> kneeRConvexIndices, kneeLConvexIndices;
	float ankleRLevel, ankleLLevel;
	vector<int> ankleRConvexIndices, ankleLConvexIndices;

	void setJoint(float, int, float, float);
	void undoJoint();
	void setRigs(float);
	void setFeatures(float);

	void generateBoundingSurface();

	void generateTights(vector<Vertex>);
	void generateDress(vector<int>);
	void generateTop(vector<int>);
	void generatePants(vector<int>);
	void generateSkirt(vector<int>);

	void loadOBJ(string);
	void loadOBJ(char*); // DLL
	void jointExport(CString);
	void writeToOBJ(string);
	void writeToOBJ(CString);
	void writeToOBJ(char*); // DLL
	void writeDressForm(int, CString, vector<int>);

	/*** Boudning Surface ***/
	int getBodyPartNum(char*); // DLL
	int getBodyPartPointNum(int); // DLL
	void getBodyPartPointIndex(int, int*); // DLL
	void getBodyPartPointPos(int, float*); // DLL

	/*** Weight from dummies ***/
	vector<Bone> bones;
	vector<int> boneSegment[BoneNum];
	vector<float> boneWeight[BoneNum];

	void expandJoint();
	void importWeights();
	void defineBones();

	vector<Vertex> origVertices;
	void writeToHuman(CString);

private :
	vector<Mesh> faces;
	vector<int> indices; // Always Tri

	JointTree jointTree;

	float bustSize, waistSize, hipSize;

	int shoulderRIndex, shoulderLIndex; // Index of armhole point with the biggest absolute-val(x value)

	vector<Vertex*> neckPlane;
	vector<Vertex*> shoulderMidPlane, shoulderRPlane, shoulderLPlane;
	vector<Vertex*> elbowRPlane, elbowLPlane, wristRPlane, wristLPlane;
	vector<Vertex*> waistPlane, pelvisMidPlane, pelvisRPlane, pelvisLPlane;
	vector<Vertex*> highThighRPlane, highThighLPlane;
	vector<Vertex*> kneeRPlane, kneeLPlane, ankleRPlane, ankleLPlane;

	void updateRigs();
	void centering(float, float, float);
};
