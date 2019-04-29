#include "stdafx.h"
#include "Skinning.h"

Skinning::Skinning() {
}

Skinning::Skinning(BodyProxies& b) {
	defaultRig = &(b.getJoints());
}

Skinning::~Skinning() {

}

void Skinning::matchRigs(vector<Joint>& rig) {
	if (!defaultRig->empty() && defaultRig->size() == rig.size()) {
		float moveX = 0, moveY = 0, moveZ = 0;
		for (int i = 0; i < rig.size(); i++) {
			Vertex* dv = &((*defaultRig)[i].getCoord());
			Vertex rv = rig[i].getCoord();

			moveX = dv->x - rv.x;
			moveY = dv->y - rv.y;
			moveZ = dv->z - rv.z;

			dv->x = rv.x;
			dv->y = rv.y;
			dv->z = rv.z;
		}
	}
}

void Skinning::segment(vector<Vertex>& vertices, vector<Joint>& joints, vector<int>& resultOfAllocation) {
	vector<Vertex> jointGroup;
	for (int j = 0; j < joints.size(); j++) {
		Vertex v = joints[j].getCoord();
		v.idx = j; // store joint id in vertex id
		jointGroup.push_back(v);
	}

	vector<int> tmpSegment[18];
	for (int i = 0; i < vertices.size(); i++) {
		Vertex closestJoint = vertices[i].closest(jointGroup);
		resultOfAllocation[i] = closestJoint.idx;

		//tmpSegment[closestJoint.idx].push_back(vertices[i].idx);
		tmpSegment[closestJoint.idx].push_back(i); // Push real vertex index for the benefit of access
	}

	vector<int> newSegment[16];
	// Head
	Vertex j = joints[Joint_neck].getCoord();
	for (int i = 0; i < tmpSegment[Joint_neck].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_neck][i]];
		if (v.y >= j.y) {
			newSegment[Segment_Head].push_back(v.idx);
		}
		else {
			newSegment[Segment_Neck].push_back(v.idx);
		}
	}

	// Neck
	j = joints[Joint_shoulderMid].getCoord();
	for (int i = 0; i < tmpSegment[Joint_shoulderMid].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_shoulderMid][i]];
		if (v.y >= j.y) {
			newSegment[Segment_Neck].push_back(v.idx);
		}
		else {
			newSegment[Segment_UpperTorso].push_back(v.idx);
		}
	}

	// Upper Torso
	j = joints[Joint_shoulderR].getCoord();
	for (int i = 0; i < tmpSegment[Joint_shoulderR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_shoulderR][i]];
		if (v.x >= j.x) {
			newSegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			newSegment[Segment_UpperArmR].push_back(v.idx);
		}
	}

	j = joints[Joint_shoulderL].getCoord();
	for (int i = 0; i < tmpSegment[Joint_shoulderL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_shoulderL][i]];
		if (v.x <= j.x) {
			newSegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			newSegment[Segment_UpperArmL].push_back(v.idx);
		}
	}

	j = joints[Joint_waist].getCoord();
	for (int i = 0; i < tmpSegment[Joint_waist].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_waist][i]];
		if (v.y >= j.y) {
			newSegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			newSegment[Segment_LowerTorso].push_back(v.idx);
		}
	}

	// Lower Torso
	j = joints[Joint_pelvisMid].getCoord();
	for (int i = 0; i < tmpSegment[Joint_pelvisMid].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_pelvisMid][i]];
		if (v.y >= j.y) {
			newSegment[Segment_LowerTorso].push_back(v.idx);
		}
		else if (v.x < j.x) {
			newSegment[Segment_UpperLegR].push_back(v.idx);
		}
		else if (v.x >= j.x) {
			newSegment[Segment_UpperLegL].push_back(v.idx);
		}
	}

	j = joints[Joint_pelvisR].getCoord();
	for (int i = 0; i < tmpSegment[Joint_pelvisR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_pelvisR][i]];
		if (v.y >= j.y) {
			newSegment[Segment_LowerTorso].push_back(v.idx);
		}
		else {
			newSegment[Segment_UpperLegR].push_back(v.idx);
		}
	}

	j = joints[Joint_pelvisL].getCoord();
	for (int i = 0; i < tmpSegment[Joint_pelvisL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_pelvisL][i]];
		if (v.y >= j.y) {
			newSegment[Segment_LowerTorso].push_back(v.idx);
		}
		else {
			newSegment[Segment_UpperLegL].push_back(v.idx);
		}
	}

	// Upper Leg 
	j = joints[Joint_highLegR].getCoord();
	for (int i = 0; i < tmpSegment[Joint_highLegR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_highLegR][i]];
		newSegment[Segment_UpperLegR].push_back(v.idx);
	}
	
	j = joints[Joint_kneeR].getCoord();
	Vertex n = joints[Joint_highLegR].getCoord() - j;

	for (int i = 0; i < tmpSegment[Joint_kneeR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_kneeR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_UpperLegR].push_back(v.idx);
		}
		else {
			newSegment[Segment_LowerLegR].push_back(v.idx);
		}
	}

	j = joints[Joint_highLegL].getCoord();
	for (int i = 0; i < tmpSegment[Joint_highLegL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_highLegL][i]];
		newSegment[Segment_UpperLegL].push_back(v.idx);
	}

	j = joints[Joint_kneeL].getCoord();
	n = joints[Joint_highLegL].getCoord() - j;

	for (int i = 0; i < tmpSegment[Joint_kneeL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_kneeL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_UpperLegL].push_back(v.idx);
		}
		else {
			newSegment[Segment_LowerLegL].push_back(v.idx);
		}
	}
	
	// Lower Leg 
	j = joints[Joint_ankleR].getCoord();
	n = joints[Joint_kneeR].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_ankleR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_ankleR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_LowerLegR].push_back(v.idx);
		}
		else {
			newSegment[Segment_FootR].push_back(v.idx);
		}
	}

	j = joints[Joint_ankleL].getCoord();
	n = joints[Joint_kneeL].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_ankleL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_ankleL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_LowerLegL].push_back(v.idx);
		}
		else {
			newSegment[Segment_FootL].push_back(v.idx);
		}
	}

	// Upper Arm
	j = joints[Joint_elbowR].getCoord();
	n = joints[Joint_shoulderR].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_elbowR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_elbowR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_UpperArmR].push_back(v.idx);
		}
		else {
			newSegment[Segment_LowerArmR].push_back(v.idx);
		}
	}

	j = joints[Joint_elbowL].getCoord();
	n = joints[Joint_shoulderL].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_elbowL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_elbowL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_UpperArmL].push_back(v.idx);
		}
		else {
			newSegment[Segment_LowerArmL].push_back(v.idx);
		}
	}

	// Lower Arm
	j = joints[Joint_wristR].getCoord();
	n = joints[Joint_elbowR].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_wristR].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_wristR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_LowerArmR].push_back(v.idx);
		}
		else {
			newSegment[Segment_HandR].push_back(v.idx);
		}
	}

	j = joints[Joint_wristL].getCoord();
	n = joints[Joint_elbowL].getCoord() - j;
	for (int i = 0; i < tmpSegment[Joint_wristL].size(); i++) {
		Vertex v = vertices[tmpSegment[Joint_wristL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			newSegment[Segment_LowerArmL].push_back(v.idx);
		}
		else {
			newSegment[Segment_HandL].push_back(v.idx);
		}
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < newSegment[i].size(); j++) {
			//resultOfAllocation.push_back();
			resultOfAllocation[newSegment[i][j] - 1] = i;
		}
		cout << i << " : " << newSegment[i].size() << endl;
	}

}