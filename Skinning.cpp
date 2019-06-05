#include "stdafx.h"
#include "Skinning.h"

Skinning::Skinning() {
}

Skinning::~Skinning() {

}

void Skinning::setHierarchy(vector<Joint>& joints) {
	if (!joints.empty()) {
		// Parent-Child definition
		joints[Joint_neck].setChild(Joint_shoulderMid);

		joints[Joint_shoulderMid].setParent(Joint_neck);
		joints[Joint_shoulderMid].setChildren(Joint_shoulderR, Joint_waist, Joint_shoulderL);

		joints[Joint_shoulderR].setParent(Joint_shoulderMid);
		joints[Joint_shoulderR].setChildren(Joint_elbowR, Joint_wristR);

		joints[Joint_elbowR].setParent(Joint_shoulderR);
		joints[Joint_elbowR].setChild(Joint_wristR);

		joints[Joint_wristR].setParent(Joint_elbowR);

		joints[Joint_waist].setParent(Joint_shoulderMid);
		joints[Joint_waist].setChild(Joint_pelvisMid);

		joints[Joint_pelvisMid].setParent(Joint_waist);
		joints[Joint_pelvisMid].setChildren(Joint_pelvisR, Joint_pelvisL);

		joints[Joint_pelvisR].setParent(Joint_pelvisMid);
		joints[Joint_pelvisR].setChildren(Joint_highLegR, Joint_kneeR, Joint_ankleR);

		joints[Joint_highLegR].setParent(Joint_pelvisR);
		joints[Joint_highLegR].setChildren(Joint_kneeR, Joint_ankleR);

		joints[Joint_kneeR].setParent(Joint_highLegR);
		joints[Joint_kneeR].setChild(Joint_ankleR);

		joints[Joint_ankleR].setParent(Joint_kneeR);

		joints[Joint_pelvisL].setParent(Joint_pelvisMid);
		joints[Joint_pelvisL].setChildren(Joint_highLegL, Joint_kneeL, Joint_ankleL);

		joints[Joint_highLegL].setParent(Joint_pelvisL);
		joints[Joint_highLegL].setChildren(Joint_kneeL, Joint_ankleL);

		joints[Joint_kneeL].setParent(Joint_pelvisL);
		joints[Joint_kneeL].setChild(Joint_ankleL);

		joints[Joint_ankleL].setParent(Joint_kneeL);

		joints[Joint_shoulderL].setParent(Joint_shoulderMid);
		joints[Joint_shoulderL].setChildren(Joint_elbowL, Joint_wristL);

		joints[Joint_elbowL].setParent(Joint_shoulderL);
		joints[Joint_elbowL].setChild(Joint_wristL);

		joints[Joint_wristL].setParent(Joint_elbowL);

		/*** Set segments ***/
		joints[Joint_neck].setRelatedSegment(Segment_Head);
		joints[Joint_neck].setRelatedSegment(Segment_Neck);

		joints[Joint_shoulderMid].setRelatedSegment(Segment_Neck);

		joints[Joint_shoulderR].setRelatedSegment(Segment_UpperArmR);
		joints[Joint_shoulderR].setRelatedSegment(Segment_LowerArmR);
		joints[Joint_shoulderR].setRelatedSegment(Segment_HandR);

		joints[Joint_elbowR].setRelatedSegment(Segment_LowerArmR);
		joints[Joint_elbowR].setRelatedSegment(Segment_HandR);

		joints[Joint_wristR].setRelatedSegment(Segment_HandR);

		joints[Joint_shoulderL].setRelatedSegment(Segment_UpperArmL);
		joints[Joint_shoulderL].setRelatedSegment(Segment_LowerArmL);
		joints[Joint_shoulderL].setRelatedSegment(Segment_HandL);

		joints[Joint_elbowL].setRelatedSegment(Segment_LowerArmL);
		joints[Joint_elbowL].setRelatedSegment(Segment_HandL);

		joints[Joint_wristL].setRelatedSegment(Segment_HandL);

		joints[Joint_waist].setRelatedSegment(Segment_UpperTorso);
		joints[Joint_waist].setRelatedSegment(Segment_LowerTorso);

		joints[Joint_pelvisMid].setRelatedSegment(Segment_LowerTorso);

		joints[Joint_pelvisR].setRelatedSegment(Segment_UpperLegR);
		joints[Joint_pelvisR].setRelatedSegment(Segment_LowerLegR);
		joints[Joint_pelvisR].setRelatedSegment(Segment_FootR);

		joints[Joint_highLegR].setRelatedSegment(Segment_UpperLegR);
		joints[Joint_highLegR].setRelatedSegment(Segment_LowerLegR);
		joints[Joint_highLegR].setRelatedSegment(Segment_FootR);

		joints[Joint_kneeR].setRelatedSegment(Segment_LowerLegR);
		joints[Joint_kneeR].setRelatedSegment(Segment_FootR);

		joints[Joint_ankleR].setRelatedSegment(Segment_FootR);

		joints[Joint_pelvisL].setRelatedSegment(Segment_UpperLegL);
		joints[Joint_pelvisL].setRelatedSegment(Segment_LowerLegL);
		joints[Joint_pelvisL].setRelatedSegment(Segment_FootL);

		joints[Joint_highLegL].setRelatedSegment(Segment_UpperLegL);
		joints[Joint_highLegL].setRelatedSegment(Segment_LowerLegL);
		joints[Joint_highLegL].setRelatedSegment(Segment_FootL);

		joints[Joint_kneeL].setRelatedSegment(Segment_LowerLegL);
		joints[Joint_kneeL].setRelatedSegment(Segment_FootL);

		joints[Joint_ankleL].setRelatedSegment(Segment_FootL);
	}
}

void Skinning::setBones(vector<Joint>& joints, vector<Bone>& bones) {
	bones.push_back(Bone(joints[Joint_neck], joints[Joint_shoulderMid]));
	bones.push_back(Bone(joints[Joint_shoulderMid], joints[Joint_shoulderR]));
	bones.push_back(Bone(joints[Joint_shoulderMid], joints[Joint_shoulderL]));
	bones.push_back(Bone(joints[Joint_shoulderR], joints[Joint_elbowR]));
	bones.push_back(Bone(joints[Joint_elbowR], joints[Joint_wristR]));
	bones.push_back(Bone(joints[Joint_elbowL], joints[Joint_wristL]));
	bones.push_back(Bone(joints[Joint_shoulderMid], joints[Joint_waist]));
	bones.push_back(Bone(joints[Joint_waist], joints[Joint_pelvisMid]));
	bones.push_back(Bone(joints[Joint_pelvisMid], joints[Joint_pelvisR]));
	bones.push_back(Bone(joints[Joint_pelvisMid], joints[Joint_pelvisL]));
	bones.push_back(Bone(joints[Joint_pelvisR], joints[Joint_kneeR]));
	bones.push_back(Bone(joints[Joint_kneeR], joints[Joint_ankleR]));
	bones.push_back(Bone(joints[Joint_pelvisL], joints[Joint_kneeL]));
	bones.push_back(Bone(joints[Joint_kneeL], joints[Joint_ankleL]));
}

void Skinning::setSegments(vector<Vertex>& vertices, vector<Joint>& joints, vector<int>& segmentResult, vector<int> weightResult[], vector<float> weightValues[]) {
	vector<Vertex> jointGroup;
	for (int j = 0; j < joints.size(); j++) {
		Vertex v = joints[j].getCoord();
		v.idx = j; // store joint id in vertex id
		jointGroup.push_back(v);
	}

	for (int i = 0; i < vertices.size(); i++) {
		Vertex closestJoint = vertices[i].closest(jointGroup);
		weightSegment[closestJoint.idx].push_back(i); // Push real vertex index for the benefit of access
	}

	// Head
	Vertex j = joints[Joint_neck].getCoord();
	for (int i = 0; i < weightSegment[Joint_neck].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_neck][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_Head].push_back(v.idx);
		}
		else {
			bodySegment[Segment_Neck].push_back(v.idx);
		}
	}

	// Neck
	j = joints[Joint_shoulderMid].getCoord();
	for (int i = 0; i < weightSegment[Joint_shoulderMid].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderMid][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_Neck].push_back(v.idx);
		}
		else {
			bodySegment[Segment_UpperTorso].push_back(v.idx);
		}
	}

	// Upper Torso
	j = joints[Joint_shoulderR].getCoord();
	for (int i = 0; i < weightSegment[Joint_shoulderR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderR][i]];
		if (v.x >= j.x) {
			bodySegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			bodySegment[Segment_UpperArmR].push_back(v.idx);
		}
	}

	j = joints[Joint_shoulderL].getCoord();
	for (int i = 0; i < weightSegment[Joint_shoulderL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderL][i]];
		if (v.x <= j.x) {
			bodySegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			bodySegment[Segment_UpperArmL].push_back(v.idx);
		}
	}

	j = joints[Joint_waist].getCoord();
	for (int i = 0; i < weightSegment[Joint_waist].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_waist][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_UpperTorso].push_back(v.idx);
		}
		else {
			bodySegment[Segment_LowerTorso].push_back(v.idx);
		}
	}

	// Lower Torso
	j = joints[Joint_pelvisMid].getCoord();
	for (int i = 0; i < weightSegment[Joint_pelvisMid].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisMid][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_LowerTorso].push_back(v.idx);
		}
		else if (v.x < j.x) {
			bodySegment[Segment_UpperLegR].push_back(v.idx);
		}
		else if (v.x >= j.x) {
			bodySegment[Segment_UpperLegL].push_back(v.idx);
		}
	}

	j = joints[Joint_pelvisR].getCoord();
	for (int i = 0; i < weightSegment[Joint_pelvisR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisR][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_LowerTorso].push_back(v.idx);
		}
		else {
			bodySegment[Segment_UpperLegR].push_back(v.idx);
		}
	}

	j = joints[Joint_pelvisL].getCoord();
	for (int i = 0; i < weightSegment[Joint_pelvisL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisL][i]];
		if (v.y >= j.y) {
			bodySegment[Segment_LowerTorso].push_back(v.idx);
		}
		else {
			bodySegment[Segment_UpperLegL].push_back(v.idx);
		}
	}

	// Upper Leg 
	j = joints[Joint_highLegR].getCoord();
	for (int i = 0; i < weightSegment[Joint_highLegR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_highLegR][i]];
		bodySegment[Segment_UpperLegR].push_back(v.idx);
	}

	j = joints[Joint_kneeR].getCoord();
	Vertex n = joints[Joint_highLegR].getCoord() - j;

	for (int i = 0; i < weightSegment[Joint_kneeR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_UpperLegR].push_back(v.idx);
		}
		else {
			bodySegment[Segment_LowerLegR].push_back(v.idx);
		}
	}

	j = joints[Joint_highLegL].getCoord();
	for (int i = 0; i < weightSegment[Joint_highLegL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_highLegL][i]];
		bodySegment[Segment_UpperLegL].push_back(v.idx);
	}

	j = joints[Joint_kneeL].getCoord();
	n = joints[Joint_highLegL].getCoord() - j;

	for (int i = 0; i < weightSegment[Joint_kneeL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_UpperLegL].push_back(v.idx);
		}
		else {
			bodySegment[Segment_LowerLegL].push_back(v.idx);
		}
	}

	// Lower Leg 
	j = joints[Joint_ankleR].getCoord();
	n = joints[Joint_kneeR].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_ankleR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_ankleR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_LowerLegR].push_back(v.idx);
		}
		else {
			bodySegment[Segment_FootR].push_back(v.idx);
		}
	}

	j = joints[Joint_ankleL].getCoord();
	n = joints[Joint_kneeL].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_ankleL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_ankleL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_LowerLegL].push_back(v.idx);
		}
		else {
			bodySegment[Segment_FootL].push_back(v.idx);
		}
	}

	// Upper Arm
	j = joints[Joint_elbowR].getCoord();
	n = joints[Joint_shoulderR].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_elbowR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_UpperArmR].push_back(v.idx);
		}
		else {
			bodySegment[Segment_LowerArmR].push_back(v.idx);
		}
	}

	j = joints[Joint_elbowL].getCoord();
	n = joints[Joint_shoulderL].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_elbowL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_UpperArmL].push_back(v.idx);
		}
		else {
			bodySegment[Segment_LowerArmL].push_back(v.idx);
		}
	}

	// Lower Arm
	j = joints[Joint_wristR].getCoord();
	n = joints[Joint_elbowR].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_wristR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_wristR][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_LowerArmR].push_back(v.idx);
		}
		else {
			bodySegment[Segment_HandR].push_back(v.idx);
		}
	}

	j = joints[Joint_wristL].getCoord();
	n = joints[Joint_elbowL].getCoord() - j;
	for (int i = 0; i < weightSegment[Joint_wristL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_wristL][i]];
		Vertex u = v - j;
		Vertex dotProduct = n.dot(u);
		if (dotProduct.x + dotProduct.y + dotProduct.z >= 0) {
			bodySegment[Segment_LowerArmL].push_back(v.idx);
		}
		else {
			bodySegment[Segment_HandL].push_back(v.idx);
		}
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < bodySegment[i].size(); j++) {
			segmentResult[bodySegment[i][j] - 1] = i;
		}
	}

	/*** NEW WEIGHT SEGMENT FOR ARM RIGHT ***/
	/*** ElbowR ***/
	vector<int> tmpElbowR;
	for (int i = 0; i < weightSegment[Joint_elbowR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowR][i]];
		Vertex shoulderR = joints[Joint_shoulderR].getCoord();
		if (v.x < shoulderR.x) {
			tmpElbowR.push_back(weightSegment[Joint_elbowR][i]);
		}
	}
	weightSegment[Joint_elbowR].clear();
	weightSegment[Joint_elbowR].insert(weightSegment[Joint_elbowR].end(), tmpElbowR.begin(), tmpElbowR.end());
	/**************/

	/*** ShoulderR ***/
	vector<int> tmpShoulderR;
	for (int i = 0; i < weightSegment[Joint_shoulderR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderR][i]];
		Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
		Vertex shoulderR = joints[Joint_shoulderR].getCoord();

		if (v.x < shoulderR.x - 0.3) {
			tmpShoulderR.push_back(weightSegment[Joint_shoulderR][i]);
		}
		else {
			if (v.x < shoulderMid.x) {
				tmpShoulderR.push_back(weightSegment[Joint_shoulderR][i]);
			}
		}
	}

	for (int i = 0; i < weightSegment[Joint_shoulderMid].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderMid][i]];
		Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
		Vertex shoulderR = joints[Joint_shoulderR].getCoord();

		if (v.x < shoulderMid.x) {
			tmpShoulderR.push_back(weightSegment[Joint_shoulderMid][i]);
		}
	}

	weightSegment[Joint_shoulderR].clear();
	weightSegment[Joint_shoulderR].insert(weightSegment[Joint_shoulderR].end(), tmpShoulderR.begin(), tmpShoulderR.end());

	armRSegment.insert(armRSegment.end(), weightSegment[Joint_shoulderR].begin(), weightSegment[Joint_shoulderR].end());
	armRSegment.insert(armRSegment.end(), weightSegment[Joint_elbowR].begin(), weightSegment[Joint_elbowR].end());
	armRSegment.insert(armRSegment.end(), weightSegment[Joint_wristR].begin(), weightSegment[Joint_wristR].end());

	tmpElbowR.clear();
	for (int i = 0; i < weightSegment[Joint_elbowR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowR][i]];
		Vertex elbowR = joints[Joint_elbowR].getCoord();

		Vertex n = joints[Joint_wristR].getCoord() - joints[Joint_elbowR].getCoord();
		Vertex dot = v.dot(n);

		if (dot.x + dot.y + dot.z < 0 && v.distance(elbowR) < 0.05) {
			tmpElbowR.push_back(weightSegment[Joint_elbowR][i]);
		}
		else if (dot.x + dot.y + dot.z >= 0) {
			tmpElbowR.push_back(weightSegment[Joint_elbowR][i]);
		}
	}
	weightSegment[Joint_elbowR].clear();
	weightSegment[Joint_elbowR].insert(weightSegment[Joint_elbowR].end(), tmpElbowR.begin(), tmpElbowR.end());
	elbowRSegment.insert(elbowRSegment.end(), weightSegment[Joint_elbowR].begin(), weightSegment[Joint_elbowR].end());
	elbowRSegment.insert(elbowRSegment.end(), weightSegment[Joint_wristR].begin(), weightSegment[Joint_wristR].end());
	/*****************/

	/*** NEW WEIGHT SEGMENT FOR ARM LEFT ***/
	/*** ElbowL ***/
	vector<int> tmpElbowL;
	for (int i = 0; i < weightSegment[Joint_elbowL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowL][i]];
		Vertex shoulderL = joints[Joint_shoulderL].getCoord();
		if (v.x > shoulderL.x) {
			tmpElbowL.push_back(weightSegment[Joint_elbowL][i]);
		}
	}
	weightSegment[Joint_elbowL].clear();
	weightSegment[Joint_elbowL].insert(weightSegment[Joint_elbowL].end(), tmpElbowL.begin(), tmpElbowL.end());

	/**************/

	/*** ShoulderL ***/
	vector<int> tmpShoulderL;
	for (int i = 0; i < weightSegment[Joint_shoulderL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderL][i]];
		Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
		Vertex shoulderL = joints[Joint_shoulderL].getCoord();

		if (v.x > shoulderL.x + 0.3) {
			tmpShoulderL.push_back(weightSegment[Joint_shoulderL][i]);
		}
		else {
			if (v.x > shoulderMid.x) {
				tmpShoulderL.push_back(weightSegment[Joint_shoulderL][i]);
			}
		}
	}

	for (int i = 0; i < weightSegment[Joint_shoulderMid].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_shoulderMid][i]];
		Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
		Vertex shoulderL = joints[Joint_shoulderL].getCoord();

		if (v.x > shoulderMid.x) {
			tmpShoulderL.push_back(weightSegment[Joint_shoulderMid][i]);
		}
	}

	weightSegment[Joint_shoulderL].clear();
	weightSegment[Joint_shoulderL].insert(weightSegment[Joint_shoulderL].end(), tmpShoulderL.begin(), tmpShoulderL.end());

	armLSegment.insert(armLSegment.end(), weightSegment[Joint_shoulderL].begin(), weightSegment[Joint_shoulderL].end());
	armLSegment.insert(armLSegment.end(), weightSegment[Joint_elbowL].begin(), weightSegment[Joint_elbowL].end());
	armLSegment.insert(armLSegment.end(), weightSegment[Joint_wristL].begin(), weightSegment[Joint_wristL].end());

	tmpElbowL.clear();
	for (int i = 0; i < weightSegment[Joint_elbowL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_elbowL][i]];
		Vertex elbowL = joints[Joint_elbowL].getCoord();

		Vertex n = joints[Joint_wristL].getCoord() - joints[Joint_elbowL].getCoord();
		Vertex dot = v.dot(n);

		if (dot.x + dot.y + dot.z < 0 && v.distance(elbowL) < 0.05) {
			tmpElbowL.push_back(weightSegment[Joint_elbowL][i]);
		}
		else if (dot.x + dot.y + dot.z >= 0) {
			tmpElbowL.push_back(weightSegment[Joint_elbowL][i]);
		}
	}
	weightSegment[Joint_elbowL].clear();
	weightSegment[Joint_elbowL].insert(weightSegment[Joint_elbowL].end(), tmpElbowL.begin(), tmpElbowL.end());
	elbowLSegment.insert(elbowLSegment.end(), weightSegment[Joint_elbowL].begin(), weightSegment[Joint_elbowL].end());
	elbowLSegment.insert(elbowLSegment.end(), weightSegment[Joint_wristL].begin(), weightSegment[Joint_wristL].end());
	/*****************/

	/*** NEW WEIGHT SEGMENT FOR LEG RIGHT ***/
	vector<int> tmpPelvisR;
	for (int i = 0; i < weightSegment[Joint_pelvisR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisR][i]];
		Vertex waist = joints[Joint_waist].getCoord();
		Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();

		if (v.y < (pelvisMid.y*2 + waist.y) / 3) {
			tmpPelvisR.push_back(weightSegment[Joint_pelvisR][i]);
		}
	}

	weightSegment[Joint_pelvisR].clear();
	weightSegment[Joint_pelvisR].insert(weightSegment[Joint_pelvisR].end(), tmpPelvisR.begin(), tmpPelvisR.end());

	legRSegment.insert(legRSegment.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_pelvisR].begin(), weightSegment[Joint_pelvisR].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_highLegR].begin(), weightSegment[Joint_highLegR].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_kneeR].begin(), weightSegment[Joint_kneeR].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_ankleR].begin(), weightSegment[Joint_ankleR].end());

	vector<int> tmpKneeR;
	for (int i = 0; i < weightSegment[Joint_kneeR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeR][i]];
		Vertex pelvisR = joints[Joint_pelvisR].getCoord();
		Vertex kneeR = joints[Joint_kneeR].getCoord();
		Vertex ankleR = joints[Joint_ankleR].getCoord();

		Vertex n = ankleR - kneeR;
		Vertex dot = n.dot(v);

		if (dot.x + dot.y + dot.z < 0 && v.distance(kneeR) < 0.1) {
			tmpKneeR.push_back(weightSegment[Joint_kneeR][i]);
		}
		else if (dot.x + dot.y + dot.z >= 0) {
			tmpKneeR.push_back(weightSegment[Joint_kneeR][i]);
		}
	}

	weightSegment[Joint_kneeR].clear();
	weightSegment[Joint_kneeR].insert(weightSegment[Joint_kneeR].end(), tmpKneeR.begin(), tmpKneeR.end());

	kneeRSegment.insert(kneeRSegment.end(), weightSegment[Joint_kneeR].begin(), weightSegment[Joint_kneeR].end());
	kneeRSegment.insert(kneeRSegment.end(), weightSegment[Joint_ankleR].begin(), weightSegment[Joint_ankleR].end());

	/*** NEW WEIGHT SEGMENT FOR LEG LEFT ***/
	vector<int> tmpPelvisL;
	for (int i = 0; i < weightSegment[Joint_pelvisL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisL][i]];
		Vertex waist = joints[Joint_waist].getCoord();
		Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();

		if (v.y < (pelvisMid.y*2 + waist.y) / 3) {
			tmpPelvisL.push_back(weightSegment[Joint_pelvisL][i]);
		}
	}

	weightSegment[Joint_pelvisL].clear();
	weightSegment[Joint_pelvisL].insert(weightSegment[Joint_pelvisL].end(), tmpPelvisL.begin(), tmpPelvisL.end());

	legLSegment.insert(legLSegment.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_pelvisL].begin(), weightSegment[Joint_pelvisL].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_highLegL].begin(), weightSegment[Joint_highLegL].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_kneeL].begin(), weightSegment[Joint_kneeL].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_ankleL].begin(), weightSegment[Joint_ankleL].end());

	vector<int> tmpKneeL;
	for (int i = 0; i < weightSegment[Joint_kneeL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeL][i]];
		Vertex pelvisL = joints[Joint_pelvisL].getCoord();
		Vertex kneeL = joints[Joint_kneeL].getCoord();
		Vertex ankleL = joints[Joint_ankleL].getCoord();

		Vertex n = ankleL - kneeL;
		Vertex dot = n.dot(v);

		if (dot.x + dot.y + dot.z < 0 && v.distance(kneeL) < 0.05) {
			tmpKneeL.push_back(weightSegment[Joint_kneeL][i]);
		}
		else {
			tmpKneeL.push_back(weightSegment[Joint_kneeL][i]);
		}
	}

	weightSegment[Joint_kneeL].clear();
	weightSegment[Joint_kneeL].insert(weightSegment[Joint_kneeL].end(), tmpKneeL.begin(), tmpKneeL.end());

	kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_kneeL].begin(), weightSegment[Joint_kneeL].end());
	kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_ankleL].begin(), weightSegment[Joint_ankleL].end());

	kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_kneeL].begin(), weightSegment[Joint_kneeL].end());
	kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_ankleL].begin(), weightSegment[Joint_ankleL].end());
}

void Skinning::setBindings(vector<Vertex>& vertices, vector<Joint>& joints, vector<int>& segmentGroup) {
	vector<int> segments[16];
	for (int i = 0; i < segmentGroup.size(); i++) {
		segments[segmentGroup[i]].push_back(i);
	}

	//relatedSegments - CCW : minZ -> minX -> maxZ -> maxX;
	vector<Vertex*> tmp;
	vector<int> tmpIdx;
	float minZ = 1000, maxZ = -1000;
	float minX = 1000, maxX = -1000;
	float minY = 1000, maxY = -1000;
	/*** Neck ***/
	Vertex neck = joints[Joint_neck].getCoord();
	for (int i = 0; i < segments[Segment_Head].size(); i++) {
		Vertex* v = &vertices[segments[Segment_Head][i]];
		if (abs(neck.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_Head][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_neck].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_neck].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_neck].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_neck].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** ShoulderMid ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
	for (int i = 0; i < segments[Segment_Neck].size(); i++) {
		Vertex* v = &vertices[segments[Segment_Neck][i]];
		if (abs(shoulderMid.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_Neck][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_shoulderMid].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_shoulderMid].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_shoulderMid].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_shoulderMid].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Waist ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex waist = joints[Joint_waist].getCoord();
	for (int i = 0; i < segments[Segment_UpperTorso].size(); i++) {
		Vertex* v = &vertices[segments[Segment_UpperTorso][i]];
		if (abs(waist.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_UpperTorso][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_waist].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_waist].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_waist].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_waist].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Pelvis Mid ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();
	for (int i = 0; i < segments[Segment_LowerTorso].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerTorso][i]];
		if (abs(pelvisMid.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerTorso][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_pelvisMid].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_pelvisMid].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_pelvisMid].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_pelvisMid].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Pelvis R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex pelvisR = joints[Joint_pelvisR].getCoord();
	for (int i = 0; i < segments[Segment_LowerTorso].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerTorso][i]];
		if (abs(pelvisR.x - v->x) < 0.3 && abs(pelvisR.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerTorso][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_pelvisR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_pelvisR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_pelvisR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_pelvisR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Pelvis L ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex pelvisL = joints[Joint_pelvisL].getCoord();
	for (int i = 0; i < segments[Segment_LowerTorso].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerTorso][i]];
		if (abs(pelvisL.x - v->x) < 0.3 && abs(pelvisL.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerTorso][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_pelvisL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_pelvisL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_pelvisL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_pelvisL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** High Thigh R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex highLegR = joints[Joint_highLegR].getCoord();
	for (int i = 0; i < segments[Segment_UpperLegR].size(); i++) {
		Vertex* v = &vertices[segments[Segment_UpperLegR][i]];
		if (abs(highLegR.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_UpperLegR][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_highLegR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_highLegR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_highLegR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_highLegR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** High Thigh L ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex highLegL = joints[Joint_highLegL].getCoord();
	for (int i = 0; i < segments[Segment_UpperLegL].size(); i++) {
		Vertex* v = &vertices[segments[Segment_UpperLegL][i]];
		if (abs(highLegL.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_UpperLegL][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_highLegL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_highLegL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_highLegL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_highLegL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Knee R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex kneeR = joints[Joint_kneeR].getCoord();
	for (int i = 0; i < segments[Segment_LowerLegR].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerLegR][i]];
		if (abs(kneeR.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerLegR][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_kneeR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_kneeR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_kneeR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_kneeR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Knee L ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex kneeL = joints[Joint_kneeL].getCoord();
	for (int i = 0; i < segments[Segment_LowerLegL].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerLegL][i]];
		if (abs(kneeL.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerLegL][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_kneeL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_kneeL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_kneeL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_kneeL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Ankle R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex ankleR = joints[Joint_ankleR].getCoord();
	for (int i = 0; i < segments[Segment_LowerLegR].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerLegR][i]];
		if (abs(ankleR.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerLegR][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_ankleR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_ankleR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_ankleR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_ankleR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Ankle L ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex ankleL = joints[Joint_ankleL].getCoord();
	for (int i = 0; i < segments[Segment_LowerLegL].size(); i++) {
		Vertex* v = &vertices[segments[Segment_LowerLegL][i]];
		if (abs(ankleL.y - v->y) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_LowerLegL][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_ankleL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_ankleL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->z < minZ) {
			minZ = tmp[i]->z;
			joints[Joint_ankleL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->z > maxZ) {
			maxZ = tmp[i]->z;
			joints[Joint_ankleL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** Shoulder R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex shoulderR = joints[Joint_shoulderR].getCoord();
	for (int i = 0; i < segments[Segment_UpperArmR].size(); i++) {
		Vertex* v = &vertices[segments[Segment_UpperArmR][i]];
		if (abs(shoulderR.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_UpperArmR][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_shoulderR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_shoulderR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_shoulderR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_shoulderR].setRelatedVerts(2, tmpIdx[i]);
		}

	}
	/*** Shoulder L ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	Vertex shoulderL = joints[Joint_shoulderL].getCoord();
	for (int i = 0; i < segments[Segment_UpperArmL].size(); i++) {
		Vertex* v = &vertices[segments[Segment_UpperArmL][i]];
		if (abs(shoulderL.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(segments[Segment_UpperArmL][i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_shoulderL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_shoulderL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_shoulderL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_shoulderL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** elbow R ***/
	tmp.clear();
	tmpIdx.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	vector<int> combined;
	combined.insert(combined.end(), segments[Segment_UpperArmR].begin(), segments[Segment_UpperArmR].end());
	combined.insert(combined.end(), segments[Segment_LowerArmR].begin(), segments[Segment_LowerArmR].end());
	Vertex elbowR = joints[Joint_elbowR].getCoord();
	for (int i = 0; i < combined.size(); i++) {
		Vertex* v = &vertices[combined[i]];
		if (abs(elbowR.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(combined[i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_elbowR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_elbowR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_elbowR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_elbowR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** elbow L ***/
	tmp.clear();
	tmpIdx.clear();
	combined.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	combined.insert(combined.end(), segments[Segment_UpperArmL].begin(), segments[Segment_UpperArmL].end());
	combined.insert(combined.end(), segments[Segment_LowerArmL].begin(), segments[Segment_LowerArmL].end());
	Vertex elbowL = joints[Joint_elbowL].getCoord();
	for (int i = 0; i < combined.size(); i++) {
		Vertex* v = &vertices[combined[i]];
		if (abs(elbowL.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(combined[i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_elbowL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_elbowL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_elbowL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_elbowL].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** wrist R ***/
	tmp.clear();
	tmpIdx.clear();
	combined.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	combined.insert(combined.end(), segments[Segment_LowerArmR].begin(), segments[Segment_LowerArmR].end());
	combined.insert(combined.end(), segments[Segment_HandR].begin(), segments[Segment_HandR].end());
	Vertex wristR = joints[Joint_wristR].getCoord();
	for (int i = 0; i < combined.size(); i++) {
		Vertex* v = &vertices[combined[i]];
		if (abs(wristR.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(combined[i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_wristR].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_wristR].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_wristR].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_wristR].setRelatedVerts(2, tmpIdx[i]);
		}
	}
	/*** wrist L ***/
	tmp.clear();
	tmpIdx.clear();
	combined.clear();
	minZ = 1000; maxZ = -1000;
	minX = 1000; maxX = -1000;
	minY = 1000; maxY = -1000;
	combined.insert(combined.end(), segments[Segment_LowerArmL].begin(), segments[Segment_LowerArmL].end());
	combined.insert(combined.end(), segments[Segment_HandL].begin(), segments[Segment_HandL].end());
	Vertex wristL = joints[Joint_wristL].getCoord();
	for (int i = 0; i < combined.size(); i++) {
		Vertex* v = &vertices[combined[i]];
		if (abs(wristL.x - v->x) < 0.3) {
			tmp.push_back(v);
			tmpIdx.push_back(combined[i]);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->x < minX) {
			minX = tmp[i]->x;
			joints[Joint_wristL].setRelatedVerts(1, tmpIdx[i]);
		}
		if (tmp[i]->x > maxX) {
			maxX = tmp[i]->x;
			joints[Joint_wristL].setRelatedVerts(3, tmpIdx[i]);
		}
		if (tmp[i]->y < minY) {
			minY = tmp[i]->y;
			joints[Joint_wristL].setRelatedVerts(0, tmpIdx[i]);
		}

		if (tmp[i]->y > maxY) {
			maxY = tmp[i]->y;
			joints[Joint_wristL].setRelatedVerts(2, tmpIdx[i]);
		}
	}

	/*** Reverse re-definition ***/
	updateRigs(vertices, joints);
}

void Skinning::paintWeights(int part, vector<Vertex>& vertices, vector<Joint>& joints) {
	float weightRange = 0.1;

	vector<int> tmpGroups;

	vector<int> pelvisMid_pelvisR;
	vector<int> pelvisMid_pelvisL;

	switch (part) {
		case Segment_UpperArmR :

			for (int i = 0; i < armRSegment.size(); i++) {
				Vertex* v = &vertices[armRSegment[i]];

				v->jointsRelated.clear();
				v->jointWeights.clear();
				if (v->x > joints[Joint_shoulderR].getCoord().x - weightRange) {
					Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
					Vertex shoulderR = joints[Joint_shoulderR].getCoord();
					Vertex waist = joints[Joint_waist].getCoord();

					/*** Shoulder Mid weight ***/
					float dist = v->distance((shoulderMid + shoulderR) / 2);
					v->jointsRelated.push_back(Joint_shoulderMid);
					v->jointWeights.push_back(pow(1 / dist, 4));

					dist = v->distance((waist + shoulderR) / 2);
					v->jointsRelated.push_back(Joint_shoulderMid);
					v->jointWeights.push_back(pow(1 / dist, 4));

					/*** Shoulder R weight ***/
					dist = v->distance(Vertex(shoulderR.x - weightRange, shoulderR.y, shoulderR.z));
					v->jointsRelated.push_back(Joint_shoulderR);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_shoulderR);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < armRSegment.size(); i++) {
				Vertex* v = &vertices[armRSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_UpperArmL :
			for (int i = 0; i < armLSegment.size(); i++) {
				Vertex* v = &vertices[armLSegment[i]];

				v->jointsRelated.clear();
				v->jointWeights.clear();
				if (v->x < joints[Joint_shoulderL].getCoord().x + weightRange) {
					Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
					Vertex shoulderL = joints[Joint_shoulderL].getCoord();
					Vertex waist = joints[Joint_waist].getCoord();

					/*** Shoulder Mid weight ***/
					float dist = v->distance((shoulderMid + shoulderL) / 2);
					v->jointsRelated.push_back(Joint_shoulderMid);
					v->jointWeights.push_back(pow(1 / dist, 4));

					dist = v->distance((waist + shoulderL) / 2);
					v->jointsRelated.push_back(Joint_shoulderMid);
					v->jointWeights.push_back(pow(1 / dist, 4));

					/*** Shoulder R weight ***/
					dist = v->distance(Vertex(shoulderL.x + weightRange, shoulderL.y, shoulderL.z));
					v->jointsRelated.push_back(Joint_shoulderL);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_shoulderL);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < armLSegment.size(); i++) {
				Vertex* v = &vertices[armLSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_UpperLegR :
			tmpGroups.push_back(Joint_highLegR);
			tmpGroups.push_back(Joint_kneeR);
			tmpGroups.push_back(Joint_ankleR);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < weightSegment[tmpGroups[i]].size(); j++) {
					Vertex* v = &vertices[weightSegment[tmpGroups[i]][j]];

					v->jointsRelated.clear();
					v->jointWeights.clear();

					v->jointsRelated.push_back(Joint_pelvisR);
					v->jointWeights.push_back(1);
				}
			}

			pelvisMid_pelvisR.insert(pelvisMid_pelvisR.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
			pelvisMid_pelvisR.insert(pelvisMid_pelvisR.end(), weightSegment[Joint_pelvisR].begin(), weightSegment[Joint_pelvisR].end());

			for (int i = 0; i < pelvisMid_pelvisR.size(); i++) {
				Vertex* v = &vertices[pelvisMid_pelvisR[i]];
				Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();
				Vertex pelvisR = joints[Joint_pelvisR].getCoord();
				Vertex waist = joints[Joint_waist].getCoord();

				v->jointsRelated.clear();
				v->jointWeights.clear();

				float dist = v->distance(pelvisMid);
				v->jointsRelated.push_back(Joint_pelvisMid);
				v->jointWeights.push_back(pow(1 / dist, 4));

				dist = v->distance((waist + pelvisR * 3) / 4);
				v->jointsRelated.push_back(Joint_pelvisR);
				v->jointWeights.push_back(pow(1 / dist, 4));

				dist = v->distance(pelvisR);
				v->jointsRelated.push_back(Joint_pelvisR);
				v->jointWeights.push_back(pow(1 / dist, 4));
			}
			for (int i = 0; i < legRSegment.size(); i++) {
				Vertex* v = &vertices[legRSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_UpperLegL :
			tmpGroups.push_back(Joint_highLegL);
			tmpGroups.push_back(Joint_kneeL);
			tmpGroups.push_back(Joint_ankleL);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < weightSegment[tmpGroups[i]].size(); j++) {
					Vertex* v = &vertices[weightSegment[tmpGroups[i]][j]];
					v->jointsRelated.clear();
					v->jointWeights.clear();

					v->jointsRelated.push_back(Joint_pelvisL);
					v->jointWeights.push_back(1);
				}
			}
			pelvisMid_pelvisL.insert(pelvisMid_pelvisL.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
			pelvisMid_pelvisL.insert(pelvisMid_pelvisL.end(), weightSegment[Joint_pelvisL].begin(), weightSegment[Joint_pelvisL].end());

			for (int i = 0; i < pelvisMid_pelvisL.size(); i++) {
				Vertex* v = &vertices[pelvisMid_pelvisL[i]];
				Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();
				Vertex pelvisL = joints[Joint_pelvisL].getCoord();
				Vertex highLegL = joints[Joint_highLegL].getCoord();
				Vertex waist = joints[Joint_waist].getCoord();

				v->jointsRelated.clear();
				v->jointWeights.clear();

				float dist = v->distance(pelvisMid);
				v->jointsRelated.push_back(Joint_pelvisMid);
				v->jointWeights.push_back(pow(1 / dist, 4));

				dist = v->distance((waist + pelvisL * 3) / 4);
				v->jointsRelated.push_back(Joint_pelvisL);
				v->jointWeights.push_back(pow(1 / dist, 4));

				dist = v->distance(pelvisL);
				v->jointsRelated.push_back(Joint_pelvisL);
				v->jointWeights.push_back(pow(1 / dist, 4));
			}
			for (int i = 0; i < legLSegment.size(); i++) {
				Vertex* v = &vertices[legLSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_LowerArmR : 
			for (int i = 0; i < elbowRSegment.size(); i++) {
				Vertex shoulderR = joints[Joint_shoulderR].getCoord();
				Vertex elbowR = joints[Joint_elbowR].getCoord();
				Vertex wristR = joints[Joint_wristR].getCoord();
				Vertex* v = &vertices[elbowRSegment[i]];

				Vertex n = wristR - elbowR;
				Vertex dot = n.dot(v);

				v->jointsRelated.clear();
				v->jointWeights.clear();

				if ( (dot.x + dot.y + dot.z > 0 && v->distance(elbowR) < 0.1)){ //&& v->distance(elbowR) > 0.1 ) {
					float dist = v->distance(shoulderR);
					v->jointsRelated.push_back(Joint_shoulderR);
					v->jointWeights.push_back(pow(1 / dist, 4));

					dist = v->distanceToLine(elbowR, wristR);
					v->jointsRelated.push_back(Joint_elbowR);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_elbowR);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < elbowRSegment.size(); i++) {
				Vertex* v = &vertices[elbowRSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_LowerArmL : 
			for (int i = 0; i < elbowLSegment.size(); i++) {
				Vertex shoulderL = joints[Joint_shoulderL].getCoord();
				Vertex elbowL = joints[Joint_elbowL].getCoord();
				Vertex wristL = joints[Joint_wristL].getCoord();
				Vertex* v = &vertices[elbowRSegment[i]];

				Vertex n = wristL - elbowL;
				Vertex dot = n.dot(v);

				v->jointsRelated.clear();
				v->jointWeights.clear();

				if ( (dot.x + dot.y + dot.z > 0 && v->distance(elbowL) < 0.1)){ //&& v->distance(elbowR) > 0.1 ) {
					float dist = v->distance(shoulderL);
					v->jointsRelated.push_back(Joint_shoulderL);
					v->jointWeights.push_back(pow(1 / dist, 4));

					dist = v->distanceToLine(elbowL, wristL);
					v->jointsRelated.push_back(Joint_elbowL);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_elbowL);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < elbowLSegment.size(); i++) {
				Vertex* v = &vertices[elbowLSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_LowerLegR :
			for (int i = 0; i < kneeRSegment.size(); i++) {
				Vertex pelvisR = joints[Joint_pelvisR].getCoord();
				Vertex kneeR = joints[Joint_kneeR].getCoord();
				Vertex* v = &vertices[kneeRSegment[i]];

				v->jointsRelated.clear();
				v->jointWeights.clear();
				if (v->x > kneeR.x - weightRange) {
					float dist = v->distance(pelvisR);
					v->jointsRelated.push_back(Joint_pelvisR);
					v->jointWeights.push_back(pow(1 / dist, 4));
					
					dist = v->distance(kneeR);
					v->jointsRelated.push_back(Joint_kneeR);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_kneeR);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < kneeRSegment.size(); i++) {
				Vertex* v = &vertices[kneeRSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		case Segment_LowerLegL :
			for (int i = 0; i < kneeLSegment.size(); i++) {
				Vertex pelvisL = joints[Joint_pelvisL].getCoord();
				Vertex kneeL = joints[Joint_kneeL].getCoord();
				Vertex* v = &vertices[kneeLSegment[i]];

				v->jointsRelated.clear();
				v->jointWeights.clear();
				if (v->x < kneeL.x + weightRange) {
					float dist = v->distance(pelvisL);
					v->jointsRelated.push_back(Joint_pelvisL);
					v->jointWeights.push_back(pow(1 / dist, 4));
					
					dist = v->distance(kneeL);
					v->jointsRelated.push_back(Joint_kneeL);
					v->jointWeights.push_back(pow(1 / dist, 4));
				}
				else {
					v->jointsRelated.push_back(Joint_kneeL);
					v->jointWeights.push_back(1);
				}
			}
			for (int i = 0; i < kneeLSegment.size(); i++) {
				Vertex* v = &vertices[kneeLSegment[i]];

				float q = 0;
				for (int j = 0; j < v->jointWeights.size(); j++) {
					q += v->jointWeights[j];
				}
				for (int j = 0; j < v->jointWeights.size(); j++) {
					v->jointWeights[j] /= q;
				}
			}
			break;

		default:
			break;
	}
}

void Skinning::bendTorso(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	if ( part == Segment_Neck ) {
		pivotJoint = joints[Joint_shoulderMid].getCoord();

		vector<int> segments;
		segments.insert(segments.end(), bodySegment[Segment_Head].begin(), bodySegment[Segment_Head].end());
		segments.insert(segments.end(), bodySegment[Segment_Neck].begin(), bodySegment[Segment_Neck].end());

		for (int i = 0; i < segments.size(); i++) {
			Vertex* v = &vertices[segments[i]];

			float y = v->y;
			float z = v->z;

			v->y = cos(radian) * (y - pivotJoint.y) + sin(radian) * (z - pivotJoint.z) + pivotJoint.y;
			v->z = -sin(radian) * (y - pivotJoint.y) + cos(radian) * (z - pivotJoint.z) + pivotJoint.z;

		}
	}

	else if (part == Segment_UpperTorso) {
		pivotJoint = joints[Joint_waist].getCoord();

		vector<int> segments;
		segments.insert(segments.end(), bodySegment[Segment_Head].begin(), bodySegment[Segment_Head].end());
		segments.insert(segments.end(), bodySegment[Segment_Neck].begin(), bodySegment[Segment_Neck].end());
		segments.insert(segments.end(), bodySegment[Segment_UpperTorso].begin(), bodySegment[Segment_UpperTorso].end());
		segments.insert(segments.end(), bodySegment[Segment_UpperArmR].begin(), bodySegment[Segment_UpperArmR].end());
		segments.insert(segments.end(), bodySegment[Segment_LowerArmR].begin(), bodySegment[Segment_LowerArmR].end());
		segments.insert(segments.end(), bodySegment[Segment_HandR].begin(), bodySegment[Segment_HandR].end());
		segments.insert(segments.end(), bodySegment[Segment_UpperArmL].begin(), bodySegment[Segment_UpperArmL].end());
		segments.insert(segments.end(), bodySegment[Segment_LowerArmL].begin(), bodySegment[Segment_LowerArmL].end());
		segments.insert(segments.end(), bodySegment[Segment_HandL].begin(), bodySegment[Segment_HandL].end());

		for (int i = 0; i < segments.size(); i++) {
			Vertex* v = &vertices[segments[i]];

			float y = v->y;
			float z = v->z;

			v->y = cos(radian) * (y - pivotJoint.y) + sin(radian) * (z - pivotJoint.z) + pivotJoint.y;
			v->z = -sin(radian) * (y - pivotJoint.y) + cos(radian) * (z - pivotJoint.z) + pivotJoint.z;
		}
	}

}

void Skinning::rotateArmR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_UpperArmR, vertices, joints);

	for (int i = 0; i < armRSegment.size(); i++) {
		Vertex* v = &vertices[armRSegment[i]];

		float x = 0, y = 0;
		float tmp_x = 0, tmp_y = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderMid) {
				pivotJoint = joints[Joint_shoulderMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
			}
			else if (v->jointsRelated[j] == Joint_shoulderR ) {
				pivotJoint = joints[Joint_shoulderR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
	}
}

void Skinning::rotateArmL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperArmL, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < armLSegment.size(); i++) {
		Vertex* v = &vertices[armLSegment[i]];

		float x = 0, y = 0;
		float tmp_x = 0, tmp_y = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderMid) {
				pivotJoint = joints[Joint_shoulderMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
			}
			else if (v->jointsRelated[j] == Joint_shoulderR ) {
				pivotJoint = joints[Joint_shoulderL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
	}
}

void Skinning::rotateElbowR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerArmR, vertices, joints);

	for (int i = 0; i < elbowRSegment.size(); i++) {
		Vertex* v = &vertices[elbowRSegment[i]];

		float x = 0, z = 0;
		float tmp_x = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderR) {
				pivotJoint = joints[Joint_shoulderR].getCoord();
				x = v->x - pivotJoint.x;
				z = v->z - pivotJoint.z;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
				tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad)  * z + pivotJoint.z);
			}
			else if ( v->jointsRelated[j] == Joint_elbowR) {
				pivotJoint = joints[Joint_elbowR].getCoord();
				x = v->x - pivotJoint.x;
				z = v->z - pivotJoint.z;
				tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
				tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
			}
		}

		v->x = tmp_x;
		v->z = tmp_z;
	}
}

void Skinning::rotateElbowL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerArmL, vertices, joints);

	for (int i = 0; i < elbowLSegment.size(); i++) {
		Vertex* v = &vertices[elbowLSegment[i]];

		float x = 0, z = 0;
		float tmp_x = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderL) {
				pivotJoint = joints[Joint_shoulderL].getCoord();
				x = v->x - pivotJoint.x;
				z = v->z - pivotJoint.z;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
				tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
			}
			else if (v->jointsRelated[j] == Joint_elbowL) {
				pivotJoint = joints[Joint_elbowL].getCoord();
				x = v->x - pivotJoint.x;
				z = v->z - pivotJoint.z;
				tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
				tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
			}
		}

		v->x = tmp_x;
		v->z = tmp_z;
	}
}

void Skinning::rotateLegR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperLegR, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < legRSegment.size(); i++) {
		Vertex* v = &vertices[legRSegment[i]];

		float x = 0, y = 0;
		float tmp_x = 0, tmp_y = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisMid) {
				pivotJoint = joints[Joint_pelvisMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
			}
			else if (v->jointsRelated[j] == Joint_pelvisR) {
				pivotJoint = joints[Joint_pelvisR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
	}
}

void Skinning::rotateLegL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperLegL, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < legLSegment.size(); i++) {
		Vertex* v = &vertices[legLSegment[i]];

		float x = 0, y = 0;
		float tmp_x = 0, tmp_y = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisMid) {
				pivotJoint = joints[Joint_pelvisMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
			}
			else if (v->jointsRelated[j] == Joint_pelvisL) {
				pivotJoint = joints[Joint_pelvisL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
				tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
	}
}

void Skinning::rotateKneeR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerLegR, vertices, joints);
	
	for (int i = 0; i < kneeRSegment.size(); i++) {
		Vertex* v = &vertices[kneeRSegment[i]];

		float y = 0, z = 0;
		float tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisR) {
				pivotJoint = joints[Joint_pelvisR].getCoord();
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				tmp_y += v->jointWeights[j] * (cos(thisRad) * y + sin(thisRad) * z + pivotJoint.y);
				tmp_z += v->jointWeights[j] * (-sin(thisRad) * y + cos(thisRad)  * z + pivotJoint.z);
			}
			else if (v->jointsRelated[j] == Joint_kneeR) {
				pivotJoint = joints[Joint_kneeR].getCoord();
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				tmp_y += v->jointWeights[j] * (cos(radian) * y + sin(radian) * z + pivotJoint.y);
				tmp_z += v->jointWeights[j] * (-sin(radian) * y + cos(radian)  * z + pivotJoint.z);
			}
		}

		v->y = tmp_y;
		v->z = tmp_z;
	}
}

void Skinning::rotateKneeL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerLegL, vertices, joints);

	for (int i = 0; i < kneeLSegment.size(); i++) {
		Vertex* v = &vertices[kneeLSegment[i]];

		float y = 0, z = 0;
		float tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisL) {
				pivotJoint = joints[Joint_pelvisL].getCoord();
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				tmp_y += v->jointWeights[j] * (cos(thisRad) * y + sin(thisRad) * z + pivotJoint.y);
				tmp_z += v->jointWeights[j] * (-sin(thisRad) * y + cos(thisRad)  * z + pivotJoint.z);
			}
			else if (v->jointsRelated[j] == Joint_kneeL) {
				pivotJoint = joints[Joint_kneeL].getCoord();
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				tmp_y += v->jointWeights[j] * (cos(radian) * y + sin(radian) * z + pivotJoint.y);
				tmp_z += v->jointWeights[j] * (-sin(radian) * y + cos(radian)  * z + pivotJoint.z);
			}
		}

		v->y = tmp_y;
		v->z = tmp_z;
	}
}

void Skinning::updateRigs(vector<Vertex>& vertices, vector<Joint>& joints) {
	for (int i = 0; i < joints.size(); i++) {
		Vertex *j = &joints[i].getCoord();
		vector<int>* rv = &joints[i].getRelatedVerts();

		if (i != Joint_shoulderR || i != Joint_shoulderL || i != Joint_elbowR || i != Joint_elbowL || i != Joint_wristR || i != Joint_wristL) {
			j->x = (vertices[(*rv)[1]].x + vertices[(*rv)[3]].x) / 2;
			j->z = (vertices[(*rv)[1]].z + vertices[(*rv)[3]].z) / 2;
		}
		else {
			j->x = (vertices[(*rv)[0]].x + vertices[(*rv)[2]].x) / 2;
			j->y = (vertices[(*rv)[0]].y + vertices[(*rv)[2]].y) / 2;
		}
	}
}
