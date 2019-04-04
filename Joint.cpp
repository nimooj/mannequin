#include "stdafx.h"
#include "Joint.h"

Joint::Joint() {
	id = 0;
	coord = Vertex();
	parent = -1;
	hasParent = false;
	hasChildren = false;
}

Joint::Joint(int i, Vertex c) {
	id = i;
	coord = c;
	parent = -1;
	hasParent = false;
	hasChildren = false;
}

Joint::~Joint() {

}

Vertex& Joint::getCoord() {
	return coord;
}

void Joint::setParent(int i) {
	parent = i;
	hasParent = true;
}

void Joint::setChild(int i) {
	children.push_back(i);
	hasChildren = true;
}

void Joint::setChildren(int i0, int i1) {
	children.push_back(i0);
	children.push_back(i1);
	hasChildren = true;
}

void Joint::setChildren(int i0, int i1, int i2) {
	children.push_back(i0);
	children.push_back(i1);
	children.push_back(i2);
	hasChildren = true;
}

int Joint::getParent() {
	return parent;
}

vector<int>& Joint::getChildren() {
	return children;
}

void Joint::setLayer(Layer& l) {
	layers.push_back(l);
}

void Joint::setLayers(vector<Layer>& l) {
	layers.insert(layers.end(), l.begin(), l.end());
}

Layer& Joint::getLayer(int idx) {
	return layers[idx];
}

vector<Layer>& Joint::getLayers() {
	return layers;
}