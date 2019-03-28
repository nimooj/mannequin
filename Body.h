#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <cmath>
#define _USE_MATH_DEFINES

#include "Vertex.h"
#include "Mesh.h"

#include "BodyProxies.h"

class Body {
public:
	Body();
	Body(string);
	~Body();

	vector<Vertex> joints;

	// Circular circumference
	int layerSize; 
	//// Scalable layers :
	vector<Vertex> bustLayer;
	vector<Vertex> waistLayer;
	vector<Vertex> hipLayer;
	vector<Vertex> rightArmHoleLayer;
	vector<Vertex> leftArmHoleLayer;
	
	// Groups
	vector<Vertex> wholeGroup;

	vector<Vertex> headGroup;
	vector<Vertex> neckGroup;
	vector<Vertex> torsoUpperGroup;
	vector<Vertex> torsoLowerGroup;
	vector<Vertex> armRightUpperGroup;
	vector<Vertex> armRightLowerGroup;
	vector<Vertex> armLeftUpperGroup;
	vector<Vertex> armLeftLowerGroup;
	vector<Vertex> legRightUpperGroup;
	vector<Vertex> legRightLowerGroup;

	void update(int, float, float, float); // Update Vert
	void writeToOBJ();

	BodyProxies bodyproxies;
private:
	vector<Mesh> headMeshes;

	int idx = 0;
	// Circular circumference
	float bustRadius;
	float waistRadius;
	float hipRadius;

	/*
	vector<int> headIndices;
	vector<int> neckIndices;
	vector<int> torsoUpperIndices;
	vector<int> torsoLowerIndices;
	vector<int> armRightUpperIndices;
	vector<int> armRightLowerIndices;
	vector<int> legRightUpperIndices;
	vector<int> legRightLowerIndices;
	*/

	void makeBody();
	void makeHead();
	void makeNeck();
	void makeTorso();
	void makeArms();
	void makeLegs();
};