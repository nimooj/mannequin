#pragma once

#include <vector>
#include "BodyProxies.h"

#define axisX 0
#define axisY 1
#define axisZ 2

class Pose {
public:
	Pose();
	~Pose();

	void translate(int, float, float, float); // joint Idx, transformation
	void rotate(int, int, float); // joint Idx, rotation axis, degree
};
