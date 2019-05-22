#pragma once

#include <math.h>
#include <vector>
#include <iostream>

//#include "Bone.h"

using namespace std;

class Vertex {
public:
	Vertex();
	Vertex(float, float, float);
	Vertex(int, float, float, float);
	Vertex(int, Vertex);
	Vertex(Vertex*);
	~Vertex();
	
	int idx;
	float x, y, z;
	float nx, ny, nz;
	vector<int> meshIds;
	bool updated = false;

	vector<int> jointsRelated;
	vector<float> jointWeights;

	bool isNull();
	void set();
	void set(float, float, float);
	void del();
	void print();

	bool operator==(const Vertex& v);
	bool operator!=(const Vertex& v);

	Vertex operator+(const Vertex&);
	Vertex operator-(const Vertex&);
	Vertex operator*(const Vertex&);
	Vertex operator+(const float&);
	Vertex operator/(const float&);
	Vertex operator-(const int&);
	Vertex operator*(const float&);

	float distance(Vertex);
	float distanceToLine(Vertex, Vertex);
	float length();
	Vertex closest(vector<Vertex>);
	Vertex closest(float, float, float, float);
	vector<Vertex> firstSecondClosest(vector<Vertex>);

	Vertex subtract(Vertex);
	Vertex add(Vertex);
	Vertex add(float);
	Vertex multiply(float);
	Vertex divide(float);
	Vertex cross(Vertex);
	Vertex dot(Vertex);
	Vertex normalize();

private:
	bool nullFlag;
};