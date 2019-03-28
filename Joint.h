#pragma once

#include "Vertex.h"
#include "Layer.h"

class Joint {
public:
	Joint();
	Joint(int, Vertex);
	~Joint();

	bool hasParent;
	bool hasChildren;

	Vertex getCoord();

	void setParent(int);
	void setChild(int);
	void setChildren(int, int);
	void setChildren(int, int, int);

	void setLayer(Layer&);
	void setLayers(vector<Layer>&);

private:
	int id;
	Vertex coord;

	int parent;
	vector<int> children;

	vector<Layer> layers;
};
