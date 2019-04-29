#pragma once

#include <vector>

#include "BodySegments.h"
#include "Joint.h"
#include "BodyProxies.h"

class Skinning {
public :
	Skinning();
	Skinning(BodyProxies&);
	~Skinning();

	void matchRigs(vector<Joint>&);
	void segment(vector<Vertex>&, vector<Joint>&, vector<int>&);
private:
	vector<Joint>* defaultRig;

	vector<int> bodySegments[18];
};
