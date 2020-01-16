#pragma once

#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES

#include "BodyProxies.h"
#include "HumanOBJ.h"

#define axisX 0
#define axisY 1
#define axisZ 2

#define Right 0
#define Left 1

class Pose {
public:
	Pose();
	Pose(HumanOBJ*);
	~Pose();

	HumanOBJ* human;
	vector<Vertex>* vertices;
	vector<Joint>* joints;
	vector<int>* segmentGroup;
	vector<int> segmentHash[16];
	vector<int> weightHash[16];
	vector<float> weightValueHash[16];

	void translate(int, float, float, float); // joint Idx, transformation
	void rotate(int, int, int, float); // joint Idx, rotation axis, degree

private:
	void update();
};
