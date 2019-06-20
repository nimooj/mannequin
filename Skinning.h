#pragma once

#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES

#include "BodySegments.h"
#include "JointDefinition.h"
#include "Joint.h"
#include "Bone.h"

#define Axis_X 0
#define Axis_Y 1
#define Axis_Z 2

class Skinning {
public :
	Skinning();
	~Skinning();

	int axis = 0;

	void setHierarchy(vector<Joint>&);
	void setBones(vector<Joint>&, vector<Bone>&);
	void setSegments(vector<Vertex>&, vector<Joint>&, vector<int>&, vector<int>[], vector<float>[]);
	void setBindings(vector<Vertex>&, vector<Joint>&);
	void paintWeights(int, vector<Vertex>&, vector<Joint>&);
	void updateRigs(vector<Vertex>&, vector<Joint>&);

	vector<int> armRSegment;
	vector<int> armLSegment;
	vector<int> elbowRSegment;
	vector<int> elbowLSegment;

	vector<int> legRSegment;
	vector<int> legLSegment;
	vector<int> kneeRSegment;
	vector<int> kneeLSegment;

	vector<int> bodySegment[SegmentNum];

	void bendTorso(int, float, vector<Vertex>&, vector<Joint>&);

	void rotateArmR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateArmL(int, float, vector<Vertex>&, vector<Joint>&);

	void rotateElbowR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateElbowL(int, float, vector<Vertex>&, vector<Joint>&);

	void rotateLegR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateLegL(int, float, vector<Vertex>&, vector<Joint>&);

	void rotateKneeR(int, float, vector<Vertex>&, vector<Joint>&);
	void rotateKneeL(int, float, vector<Vertex>&, vector<Joint>&);

private:
	vector<int> weightIndices;
	vector<int> weightSegment[18];
};
