#include "stdafx.h"
#include "Pose.h"


Pose::Pose() {
}

Pose::Pose(HumanOBJ* body) {
	human = body;
	vertices = &(body->getVerts());
	joints = &(body->joints);
	segmentGroup = &(body->segmentGroup);

	for (int i = 0; i < segmentGroup->size(); i++) {
		segmentHash[(*segmentGroup)[i]].push_back((*vertices)[i].idx);
	}
}

Pose::~Pose() {

}

void Pose::translate(int jointId, float x, float y, float z) {
	/*
	Joint *js = &(joints->at(jointId));
	Vertex *jv = &js->getCoord();

	vector<Layer>* layerChildren = &(js->getLayers());

	vector<Vertex>* initV = &body->getInitVert();
	vector<Vertex>* verts = &body->getVerts();

	Vertex initJ = body->getJoints().at(jointId).getCoord();

	jv->x = initJ.x - x;
	jv->y = initJ.y - y;
	jv->z = initJ.z - z;

	for ( vector<Layer>::iterator lc = layerChildren->begin(); lc != layerChildren->end(); lc++) {
		vector<Vertex>* layerVerts = &lc->getVerts();

		for (int i = 0; i < layerVerts->size(); i++) {
			(*verts)[(*layerVerts)[i].idx - 1].x = (*initV)[(*layerVerts)[i].idx - 1].x - x;
			(*verts)[(*layerVerts)[i].idx - 1].y = (*initV)[(*layerVerts)[i].idx - 1].y - y;
			(*verts)[(*layerVerts)[i].idx - 1].z = (*initV)[(*layerVerts)[i].idx - 1].z - z;
		}
	}
	*/
}

void Pose::rotate(int jointId, int axis, int side, float degree) {
	float thisRad = -2 * M_PI / 180;

	float radian = degree * M_PI / 180;

	/*
	for (int i = 0; i < armRSegment.size(); i++) {
		Vertex* v = &(*vertices)[armRSegment[i]];

		float x = v->x;
		float y = v->y;

		float tmp_x = 0, tmp_y = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			Vertex jt = (*joints)[v->jointsRelated[j]];

			if (v->jointsRelated[j] == 1) { // Shoulder Mid -> no rotation
				tmp_x += v->jointWeights[j] * (cos(thisRad) * (x - jt.x) - sin(thisRad) * (y - jt.y));
				tmp_y += v->jointWeights[j] * (sin(thisRad) * (x - jt.x) + cos(thisRad)  * (y - jt.y));
			}
			else if (v->jointsRelated[j] == 2) { // Shoulder R -> use rotation Matrix
				tmp_x += v->jointWeights[j] * (cos(thisRad + radian) * (x - jt.x) - sin(thisRad + radian) * (y - jt.y));
				tmp_y += v->jointWeights[j] * (sin(thisRad + radian) * (x - jt.x) + cos(thisRad + radian) * (y - jt.y));
			}

		}

		v->x = tmp_x + (*joints)[Joint_shoulderR].x;
		v->y = tmp_y + (*joints)[Joint_shoulderR].y;
	}
	*/
}