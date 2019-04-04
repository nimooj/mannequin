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

	Vertex& getCoord();

	void setParent(int);
	void setChild(int);
	void setChildren(int, int);
	void setChildren(int, int, int);
	int getParent();
	vector<int>& getChildren();

	void setLayer(Layer&);
	void setLayers(vector<Layer>&);
	Layer& getLayer(int);
	vector<Layer>& getLayers();

private:
	int id;
	Vertex coord;

	int parent;
	vector<int> children;

	vector<Layer> layers;
};
