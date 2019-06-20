#pragma once

#include <vector>

#include "BodySegments.h"
#include "Vertex.h"
#include "Joint.h"
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
	Landmark(CString, vector<int>, float, float, float, vector<int>);
	~Landmark();

	bool SetGirthFeature(vector<int>&, vector<int>&, vector<Vertex>&, float);
	bool SetLengthFeature(vector<int>&, vector<Joint>&);

	CString name;
	int type;
	float value;

	float level; // for Girth feature

	vector<int> region;
	vector<int> vertIdx;
};
