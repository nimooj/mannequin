#pragma once

#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES

#include "BodySegments.h"
#include "JointDefinition.h"
#include "Joint.h"
#include "Bone.h"

class Skinning {
public :
	Skinning();
	~Skinning();

	void setHierarchy(vector<Joint>&);
	void setBones(vector<Joint>&, vector<Bone>&);
	void setSegments(vector<Vertex>&, vector<Joint>&, vector<int>&, vector<int>[], vector<float>[]);
	void setBindings(vector<Vertex>&, vector<Joint>&, vector<int>&);
	void paintWeights(vector<Vertex>&, vector<Joint>&, vector<int>&);
	void updateRigs(vector<Joint>&);

	vector<int> armRSegment;
	vector<int> armLSegment;
	vector<int> legRSegment;
	vector<int> legLSegment;

	void rotateAR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateAL(int, float, vector<Vertex>&, vector<Joint>&);

	void rotateLR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateLL(int, float, vector<Vertex>&, vector<Joint>&);
private:
	vector<int> bodySegments[18];
	vector<int> weightIndices;
	vector<int> weightSegment[18];

};
