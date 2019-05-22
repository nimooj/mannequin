#include "stdafx.h"
#include "Size.h"


Size::Size() {
	body = new BodyProxies();
	bust = 0;
	waist = 0;
	hip = 0;
}

Size::Size(BodyProxies* bodyproxy) {
	body = bodyproxy;
	bust = getSize(Bust);
	waist = getSize(Waist);
	hip = getSize(Hip);
}

Size::Size(HumanOBJ* humanBody) {
	human = humanBody;
	bust = human->getBustSize();
	waist = human->getWaistSize();
	hip = human->getHipSize();
}

Size::~Size() {

}

float Size::getSize(int layerNum) {
	Layer* layer = &(&body->getBodyLayers())->at(layerNum);
	vector<Vertex>* lv = &layer->getVerts();
	float distance = (*lv)[lv->size() - 1].distance((*lv)[0]);

	for (int i = 0; i < lv->size() - 1; i++) {
		distance += (*lv)[i].distance((*lv)[i + 1]);
	}

	distance *= 10;

	distance = ((int) (distance * 1000)) / (float) 1000;

	return distance;
}

void Size::setSize(int layerNum, float size) {
	// Design weight factor ... width direction, height direction
	vector<Vertex>* verts = &body->getVerts();

	Layer* layer = &(&body->getBodyLayers())->at(layerNum);
	vector<Vertex>* lv = &layer->getVerts();
	Vertex center = layer->getCenter();

	float scaleFactor = 1.0f;

	if (layerNum == Bust) {
		scaleFactor = size / bust;
		bust = size;
	}
	else if (layerNum == Waist) {
		scaleFactor = size / waist;
		waist = size;
	}
	else if (layerNum == Hip) {
		scaleFactor = size / hip;
		hip = size;
	}
	else
		scaleFactor = size / (float)getSize(layerNum);

	for (int i = 0; i < lv->size(); i++) {
		(*verts)[(*lv)[i].idx - 1].x -= center.x;
		(*verts)[(*lv)[i].idx - 1].z -= center.z;

		(*verts)[(*lv)[i].idx - 1].x *= scaleFactor;
		(*verts)[(*lv)[i].idx - 1].z *= scaleFactor;

		(*verts)[(*lv)[i].idx - 1].x += center.x;
		(*verts)[(*lv)[i].idx - 1].z += center.z;
	}
}