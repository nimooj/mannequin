#pragma once

#include <vector>

#include "BodySegments.h"
#include "Vertex.h"
#include "GrahamScan.h"

#define Girth 0
#define Length 1

class Landmark {
public:
	Landmark();
	Landmark(CString, float);
	Landmark(CString, float, float);
	Landmark(CString, float, float, vector<int>);
	Landmark(CString, float, float, float, vector<int>);
	~Landmark();

	void SetGirthFeature(vector<int>&, vector<Vertex>&, float);


	CString name;
	float type;
	float value;
	float level;
	vector<int> vertIdx;
};
