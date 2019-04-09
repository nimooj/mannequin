#include "stdafx.h"
#include "Pose.h"


Pose::Pose() {
	body = &BodyProxies();
	joints = &JointTree();
}

Pose::Pose(BodyProxies* bodyproxy) {
	body = bodyproxy;
	joints = &(body->getJointTree());
}

Pose::~Pose() {

}

void Pose::translate(int jointId, float x, float y, float z) {

}

void Pose::rotate(int jointId, int axis, float degree) {
	Joint * js = &(joints->at(jointId));
	vector<int>* jointChildrenIndices;
	vector<Layer>* layerChildren;

	vector<Vertex>* initV = &body->getInitVert();
	vector<Vertex>* verts = &body->getVerts();
	Vertex* jointCoord = &js->getCoord();

	vector<Joint> initJs = body->getJoints();

	// Rotate from init pos of 90 degrees
	//float radian = -abs(90 - degree) * M_PI / 180;
	float radian = degree * M_PI / 180;

	switch (axis) {
	case axisX:
		break;
	case axisY:
		break;
	case axisZ:
		jointChildrenIndices = &(js->getChildren());
		layerChildren = &(js->getLayers());

		for (vector<int>::iterator ji = jointChildrenIndices->begin(); ji != jointChildrenIndices->end(); ji++) {
			Joint *jc = &(joints->at(*ji));

			Vertex initJ = initJs.at(*ji).getCoord();

			Vertex *jv = &jc->getCoord();

			jv->x -= jointCoord->x;
			jv->y -= jointCoord->y;

			float newX = initJ.x - jointCoord->x;
			float newY = initJ.y - jointCoord->y;

			jv->x = cos(radian) * newX - sin(radian) * newY;
			jv->y = sin(radian) * newX + cos(radian) * newY;

			jv->x += jointCoord->x;
			jv->y += jointCoord->y;
		}

		for (vector<Layer>::iterator lc = layerChildren->begin(); lc != layerChildren->end(); lc++) {
			vector<Vertex>* layerVerts = &lc->getVerts();
			Vertex jt = js->getCoord();
			Vertex center = &lc->getCenter();
			float radius = center.distance(jt);

			for (int i = 0; i < layerVerts->size(); i++) {
				(*verts)[(*layerVerts)[i].idx - 1].x -= jt.x;
				(*verts)[(*layerVerts)[i].idx - 1].y -= jt.y;

				float x = (*initV)[(*layerVerts)[i].idx - 1].x - jt.x;
				float y = (*initV)[(*layerVerts)[i].idx - 1].y - jt.y;

				(*verts)[(*layerVerts)[i].idx - 1].x = cos(radian) * x - sin(radian) * y;
				(*verts)[(*layerVerts)[i].idx - 1].y = sin(radian) * x + cos(radian) * y;

				(*verts)[(*layerVerts)[i].idx - 1].x += jt.x;
				(*verts)[(*layerVerts)[i].idx - 1].y += jt.y;

			}
		}

		break;
	}
}