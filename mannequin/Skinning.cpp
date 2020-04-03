#include "stdafx.h"
#include "Skinning.h"

Skinning::Skinning() {
}

Skinning::~Skinning() {

}

void Skinning::setPose(string dir) {
	history.clear();

	ifstream infile(dir);
	string s;

	while (getline(infile, s)) {
		istringstream iss(s);
		int part, i_axis;
		float val;
		iss >> part >> i_axis >> val;

		poseHistory his;
		his.part = part;
		his.axis = i_axis;
		his.value = val;
		history.push_back(his);
	}
	infile.close();
}

void Skinning::setSegments(vector<Vertex>& vertices, vector<Joint>& joints, vector<int>& segmentResult, vector<int> weightResult[], vector<float> weightValues[]) {
	vector<Vertex> jointGroup;
	for (int j = 0; j < JointNum; j++) {
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
	j = joints[Joint_kneeR].getCoord();
	Vertex n = joints[Joint_pelvisR].getCoord() - j;

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

	j = joints[Joint_kneeL].getCoord();
	n = joints[Joint_pelvisL].getCoord() - j;

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

	for (int i = 0; i < SegmentNum; i++) {
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
		Vertex shoulderR = joints[Joint_shoulderR].getCoord();
		Vertex elbowR = joints[Joint_elbowR].getCoord();

		Vertex n = joints[Joint_wristR].getCoord() - joints[Joint_elbowR].getCoord();
		Vertex dot = n.dot(v - elbowR);
		float sum = dot.x + dot.y + dot.z;

		float elbow2shoulder = elbowR.distance(shoulderR);

		if (sum < 0 && v.distance(elbowR) < elbow2shoulder / 4) {
			tmpElbowR.push_back(weightSegment[Joint_elbowR][i]);
		}
		else if (sum >= 0) { // Forearm
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
		Vertex shoulderL = joints[Joint_shoulderL].getCoord();
		Vertex elbowL = joints[Joint_elbowL].getCoord();

		Vertex n = joints[Joint_wristL].getCoord() - joints[Joint_elbowL].getCoord();
		Vertex dot = n.dot(v - elbowL);
		float sum = dot.x + dot.y + dot.z;

		float elbow2shoulder = elbowL.distance(shoulderL);

		if (sum < 0 && v.distance(elbowL) < elbow2shoulder / 4) {
			tmpElbowL.push_back(weightSegment[Joint_elbowL][i]);
		}
		else if (sum >= 0) {
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

		if (v.y < (pelvisMid.y * 2 + waist.y) / 3) {
			tmpPelvisR.push_back(weightSegment[Joint_pelvisR][i]);
		}
	}

	weightSegment[Joint_pelvisR].clear();
	weightSegment[Joint_pelvisR].insert(weightSegment[Joint_pelvisR].end(), tmpPelvisR.begin(), tmpPelvisR.end());

	legRSegment.insert(legRSegment.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_pelvisR].begin(), weightSegment[Joint_pelvisR].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_kneeR].begin(), weightSegment[Joint_kneeR].end());
	legRSegment.insert(legRSegment.end(), weightSegment[Joint_ankleR].begin(), weightSegment[Joint_ankleR].end());

	vector<int> tmpKneeR;
	for (int i = 0; i < weightSegment[Joint_kneeR].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeR][i]];
		Vertex pelvisR = joints[Joint_pelvisR].getCoord();
		Vertex kneeR = joints[Joint_kneeR].getCoord();
		Vertex ankleR = joints[Joint_ankleR].getCoord();

		Vertex n = (ankleR - kneeR);
		Vertex dot = n.dot(v - kneeR);
		float sum = dot.x + dot.y + dot.z;
		float knee2pelvis = kneeR.distance(pelvisR);

		if (sum < 0 && v.distance(kneeR) < knee2pelvis / 4) { // Thigh
		//if (sum < 0) { // Thigh
			tmpKneeR.push_back(weightSegment[Joint_kneeR][i]);
		}
		else if (sum >= 0) { // Calf
			tmpKneeR.push_back(weightSegment[Joint_kneeR][i]);
		}
	}

	//weightSegment[Joint_kneeR].clear();
	//weightSegment[Joint_kneeR].insert(weightSegment[Joint_kneeR].end(), tmpKneeR.begin(), tmpKneeR.end());

	//kneeRSegment.insert(kneeRSegment.end(), weightSegment[Joint_kneeR].begin(), weightSegment[Joint_kneeR].end());
	kneeRSegment.insert(kneeRSegment.end(), tmpKneeR.begin(), tmpKneeR.end());
	kneeRSegment.insert(kneeRSegment.end(), weightSegment[Joint_ankleR].begin(), weightSegment[Joint_ankleR].end());

	/*** NEW WEIGHT SEGMENT FOR LEG LEFT ***/
	vector<int> tmpPelvisL;
	for (int i = 0; i < weightSegment[Joint_pelvisL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_pelvisL][i]];
		Vertex waist = joints[Joint_waist].getCoord();
		Vertex pelvisMid = joints[Joint_pelvisMid].getCoord();

		if (v.y < (pelvisMid.y * 2 + waist.y) / 3) {
			tmpPelvisL.push_back(weightSegment[Joint_pelvisL][i]);
		}
	}

	weightSegment[Joint_pelvisL].clear();
	weightSegment[Joint_pelvisL].insert(weightSegment[Joint_pelvisL].end(), tmpPelvisL.begin(), tmpPelvisL.end());

	legLSegment.insert(legLSegment.end(), weightSegment[Joint_pelvisMid].begin(), weightSegment[Joint_pelvisMid].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_pelvisL].begin(), weightSegment[Joint_pelvisL].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_kneeL].begin(), weightSegment[Joint_kneeL].end());
	legLSegment.insert(legLSegment.end(), weightSegment[Joint_ankleL].begin(), weightSegment[Joint_ankleL].end());

	vector<int> tmpKneeL;
	for (int i = 0; i < weightSegment[Joint_kneeL].size(); i++) {
		Vertex v = vertices[weightSegment[Joint_kneeL][i]];
		Vertex pelvisL = joints[Joint_pelvisL].getCoord();
		Vertex kneeL = joints[Joint_kneeL].getCoord();
		Vertex ankleL = joints[Joint_ankleL].getCoord();

		Vertex n = (ankleL - kneeL);
		Vertex dot = n.dot(v - kneeL);
		float sum = dot.x + dot.y + dot.z;
		float knee2pelvis = kneeL.distance(pelvisL);

		if (sum < 0 && v.distance(kneeL) < knee2pelvis / 4) { // Thigh
		//if (sum < 0) { // Thigh
			tmpKneeL.push_back(weightSegment[Joint_kneeL][i]);
		}
		else if (sum >= 0) { // Calf
			tmpKneeL.push_back(weightSegment[Joint_kneeL][i]);
		}
	}

	//weightSegment[Joint_kneeL].clear();
	//weightSegment[Joint_kneeL].insert(weightSegment[Joint_kneeL].end(), tmpKneeL.begin(), tmpKneeL.end());

	//kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_kneeL].begin(), weightSegment[Joint_kneeL].end());
	kneeLSegment.insert(kneeLSegment.end(), tmpKneeL.begin(), tmpKneeL.end());
	kneeLSegment.insert(kneeLSegment.end(), weightSegment[Joint_ankleL].begin(), weightSegment[Joint_ankleL].end());

	for (int i = 0; i < WeightNum; i++) {
		weightResult[i].insert(weightResult[i].end(), weightSegment[i].begin(), weightSegment[i].end());
	}
}

void Skinning::refineSegments(vector<Vertex>& vertices, vector<Joint>& joints, vector<int> bs[]) {
	// Body Segment in trouble ... upper torso and upper arms
	Vertex shoulderR = joints[Joint_shoulderR].getCoord();
	Vertex shoulderL = joints[Joint_shoulderL].getCoord();

	vector<int> newUpperTorso, newUpperArmR, newUpperArmL;
	newUpperTorso.insert(newUpperTorso.end(), bs[Segment_UpperTorso].begin(), bs[Segment_UpperTorso].end());

	for (int i = 0; i < bs[Segment_UpperArmR].size(); i++) {
		int index = bs[Segment_UpperArmR][i];

		if (vertices[index].x > shoulderR.x) {
			newUpperTorso.push_back(index);
		}
		else {
			newUpperArmR.push_back(index);
		}
	}

	for (int i = 0; i < bs[Segment_UpperArmL].size(); i++) {
		int index = bs[Segment_UpperArmL][i];

		if (vertices[index].x < shoulderL.x) {
			newUpperTorso.push_back(index);
		}
		else {
			newUpperArmL.push_back(index);
		}
	}


	bs[Segment_UpperTorso].clear();
	bs[Segment_UpperTorso].insert(bs[Segment_UpperTorso].end(), newUpperTorso.begin(), newUpperTorso.end());

	bs[Segment_UpperArmR].clear();
	bs[Segment_UpperArmR].insert(bs[Segment_UpperArmR].end(), newUpperArmR.begin(), newUpperArmR.end());

	bs[Segment_UpperArmL].clear();
	bs[Segment_UpperArmL].insert(bs[Segment_UpperArmL].end(), newUpperArmL.begin(), newUpperArmL.end());
}

void Skinning::setBindings(vector<Vertex>& vertices, vector<Joint>& joints) {
}

void Skinning::paintWeights(int part, vector<Vertex>& vertices, vector<Joint>& joints) {
	float weightRange = 0.1;

	vector<int> tmpGroups;

	vector<int> pelvisMid_pelvisR;
	vector<int> pelvisMid_pelvisL;

	switch (part) {
	case Segment_UpperArmR:
		for (int i = 0; i < armRSegment.size(); i++) {
			Vertex* v = &vertices[armRSegment[i]];

			v->jointsRelated.clear();
			v->jointWeights.clear();
			if (v->x > joints[Joint_shoulderR].getCoord().x - weightRange) {
				Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
				Vertex shoulderR = joints[Joint_shoulderR].getCoord();
				Vertex waist = joints[Joint_waist].getCoord();

				/*** Shoulder Mid weight ***/
				float dist = v->distance((shoulderMid + shoulderR * 2) / 3);
				v->jointsRelated.push_back(Joint_shoulderMid);
				v->jointWeights.push_back(pow(1 / dist, 4));
				//v->jointWeights.push_back(1);

				/*** Shoulder R weight ***/
				dist = v->distance(Vertex(shoulderR.x, shoulderR.y, shoulderR.z));
				v->jointsRelated.push_back(Joint_shoulderR);
				v->jointWeights.push_back(pow(1 / dist, 4));
				//v->jointWeights.push_back(1);
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

	case Segment_UpperArmL:
		for (int i = 0; i < armLSegment.size(); i++) {
			Vertex* v = &vertices[armLSegment[i]];

			v->jointsRelated.clear();
			v->jointWeights.clear();
			if (v->x < joints[Joint_shoulderL].getCoord().x + weightRange) {
				Vertex shoulderMid = joints[Joint_shoulderMid].getCoord();
				Vertex shoulderL = joints[Joint_shoulderL].getCoord();
				Vertex waist = joints[Joint_waist].getCoord();

				/*** Shoulder Mid weight ***/
				float dist = v->distance((shoulderMid + shoulderL * 2) / 3);
				v->jointsRelated.push_back(Joint_shoulderMid);
				v->jointWeights.push_back(pow(1 / dist, 4));

				/*** Shoulder R weight ***/
				dist = v->distance(Vertex(shoulderL.x, shoulderL.y, shoulderL.z));
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

	case Segment_LowerArmR:
		for (int i = 0; i < elbowRSegment.size(); i++) {
			Vertex shoulderR = joints[Joint_shoulderR].getCoord();
			Vertex elbowR = joints[Joint_elbowR].getCoord();
			Vertex wristR = joints[Joint_wristR].getCoord();
			Vertex* v = &vertices[elbowRSegment[i]];

			Vertex n = wristR - elbowR;
			Vertex dot = n.dot(*v - elbowR);
			float sum = dot.x + dot.y + dot.z;

			v->jointsRelated.clear();
			v->jointWeights.clear();

			if (sum <= 0) {
				float dist = v->distance((shoulderR + elbowR * 3) / 4);
				v->jointsRelated.push_back(Joint_shoulderR);
				v->jointWeights.push_back(pow(1 / dist, 4));

				dist = v->distance(elbowR);
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

	case Segment_LowerArmL:
		for (int i = 0; i < elbowLSegment.size(); i++) {
			Vertex shoulderL = joints[Joint_shoulderL].getCoord();
			Vertex elbowL = joints[Joint_elbowL].getCoord();
			Vertex wristL = joints[Joint_wristL].getCoord();
			Vertex* v = &vertices[elbowLSegment[i]];

			Vertex n = wristL - elbowL;
			Vertex dot = n.dot(*v - elbowL);
			float sum = dot.x + dot.y + dot.z;

			v->jointsRelated.clear();
			v->jointWeights.clear();

			if (sum <= 0) {
				float dist = v->distance((shoulderL + elbowL * 3) / 4);
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

	case Segment_UpperLegR:
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

	case Segment_UpperLegL:
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

	case Segment_LowerLegR:
		for (int i = 0; i < kneeRSegment.size(); i++) {
			Vertex pelvisR = joints[Joint_pelvisR].getCoord();
			Vertex kneeR = joints[Joint_kneeR].getCoord();
			Vertex ankleR = joints[Joint_ankleR].getCoord();
			Vertex* v = &vertices[kneeRSegment[i]];

			Vertex n = ankleR - kneeR;
			Vertex dot = n.dot(*v - kneeR);
			float sum = dot.x + dot.y + dot.z;

			v->jointsRelated.clear();
			v->jointWeights.clear();
			if (sum < 0) {
				float dist = v->distance((pelvisR + kneeR * 2) / 3);
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


	case Segment_LowerLegL:
		for (int i = 0; i < kneeLSegment.size(); i++) {
			Vertex pelvisL = joints[Joint_pelvisL].getCoord();
			Vertex kneeL = joints[Joint_kneeL].getCoord();
			Vertex ankleL = joints[Joint_ankleL].getCoord();
			Vertex* v = &vertices[kneeLSegment[i]];

			Vertex n = ankleL - kneeL;
			Vertex dot = n.dot(*v - kneeL);
			float sum = dot.x + dot.y + dot.z;

			v->jointsRelated.clear();
			v->jointWeights.clear();
			if (sum < 0) {
				float dist = v->distance((pelvisL + kneeL * 2) / 3);
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

	if (part == Segment_Neck) {
		pivotJoint = joints[Joint_shoulderMid].getCoord();

		vector<int> segments;
		segments.insert(segments.end(), bodySegment[Segment_Head].begin(), bodySegment[Segment_Head].end());
		segments.insert(segments.end(), bodySegment[Segment_Neck].begin(), bodySegment[Segment_Neck].end());

		for (int i = 0; i < segments.size(); i++) {
			Vertex* v = &vertices[segments[i]];

			float y = v->y;
			float z = v->z;

			//v->y = cos(radian) * (y - pivotJoint.y) + sin(radian) * (z - pivotJoint.z) + pivotJoint.y;
			//v->z = -sin(radian) * (y - pivotJoint.y) + cos(radian) * (z - pivotJoint.z) + pivotJoint.z;

			//v->y -= degree;
			v->z -= degree;
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

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderMid) {
				pivotJoint = joints[Joint_shoulderMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * (y)-sin(thisRad) * (z)+pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * (y)+cos(thisRad)  * (z)+pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_shoulderR) {
				pivotJoint = joints[Joint_shoulderR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * (y)-sin(radian) * (z)+pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * (y)+cos(radian)  * (z)+pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex shoulderR = joints[Joint_shoulderR].getCoord();
	Vertex* elbowR = &joints[Joint_elbowR].getCoord();
	Vertex* wristR = &joints[Joint_wristR].getCoord();

	if (axis == Axis_X) {
		float y = elbowR->y - shoulderR.y;
		float z = elbowR->z - shoulderR.z;
		elbowR->y = cos(radian) * y - sin(radian) * z + shoulderR.y;
		elbowR->z = sin(radian) * y + cos(radian) * z + shoulderR.z;

		y = wristR->y - shoulderR.y;
		z = wristR->z - shoulderR.z;
		wristR->y = cos(radian) * y - sin(radian) * z + shoulderR.y;
		wristR->z = sin(radian) * y + cos(radian) * z + shoulderR.z;
	}
	else if (axis == Axis_Y) {
		float x = elbowR->x - shoulderR.x;
		float z = elbowR->x - shoulderR.z;
		elbowR->x = cos(radian) * x + sin(radian) * z + shoulderR.x;
		elbowR->z = -sin(radian) * x + cos(radian) * z + shoulderR.z;

		x = wristR->x - shoulderR.x;
		z = wristR->z - shoulderR.z;
		wristR->x = cos(radian) * x + sin(radian) * z + shoulderR.x;
		wristR->z = -sin(radian) * x + cos(radian) * z + shoulderR.z;
	}
	else if (axis == Axis_Z) {
		float x = elbowR->x - shoulderR.x;
		float y = elbowR->y - shoulderR.y;
		elbowR->x = cos(radian) * x - sin(radian) * y + shoulderR.x;
		elbowR->y = sin(radian) * x + cos(radian) * y + shoulderR.y;

		x = wristR->x - shoulderR.x;
		y = wristR->y - shoulderR.y;
		wristR->x = cos(radian) * x - sin(radian) * y + shoulderR.x;
		wristR->y = sin(radian) * x + cos(radian) * y + shoulderR.y;
	}
}

void Skinning::rotateArmL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperArmL, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < armLSegment.size(); i++) {
		Vertex* v = &vertices[armLSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderMid) {
				pivotJoint = joints[Joint_shoulderMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * (y)-sin(thisRad) * (z)+pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * (y)+cos(thisRad)  * (z)+pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {

					tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_shoulderL) {
				pivotJoint = joints[Joint_shoulderL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * (y)-sin(radian) * (z)+pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * (y)+cos(radian)  * (z)+pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex shoulderL = joints[Joint_shoulderL].getCoord();
	Vertex* elbowL = &joints[Joint_elbowL].getCoord();
	Vertex* wristL = &joints[Joint_wristL].getCoord();

	if (axis == Axis_X) {
		float y = elbowL->y - shoulderL.y;
		float z = elbowL->z - shoulderL.z;
		elbowL->y = cos(radian) * y - sin(radian) * z + shoulderL.y;
		elbowL->z = sin(radian) * y + cos(radian) * z + shoulderL.z;

		y = wristL->y - shoulderL.y;
		z = wristL->z - shoulderL.z;
		wristL->y = cos(radian) * y - sin(radian) * z + shoulderL.y;
		wristL->z = sin(radian) * y + cos(radian) * z + shoulderL.z;
	}
	else if (axis == Axis_Y) {
		float x = elbowL->x - shoulderL.x;
		float z = elbowL->x - shoulderL.z;
		elbowL->x = cos(radian) * x + sin(radian) * z + shoulderL.x;
		elbowL->z = -sin(radian) * x + cos(radian) * z + shoulderL.z;

		x = wristL->x - shoulderL.x;
		z = wristL->z - shoulderL.z;
		wristL->x = cos(radian) * x + sin(radian) * z + shoulderL.x;
		wristL->z = -sin(radian) * x + cos(radian) * z + shoulderL.z;
	}
	else if (axis == Axis_Z) {
		float x = elbowL->x - shoulderL.x;
		float y = elbowL->y - shoulderL.y;
		elbowL->x = cos(radian) * x - sin(radian) * y + shoulderL.x;
		elbowL->y = sin(radian) * x + cos(radian) * y + shoulderL.y;

		x = wristL->x - shoulderL.x;
		y = wristL->y - shoulderL.y;
		wristL->x = cos(radian) * x - sin(radian) * y + shoulderL.x;
		wristL->y = sin(radian) * x + cos(radian) * y + shoulderL.y;
	}
}

void Skinning::rotateElbowR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerArmR, vertices, joints);

	for (int i = 0; i < elbowRSegment.size(); i++) {
		Vertex* v = &vertices[elbowRSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderR) {
				pivotJoint = joints[Joint_shoulderR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y - sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * y + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad)  * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_elbowR) {
				pivotJoint = joints[Joint_elbowR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y - sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * y + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * x + cos(radian) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex elbowR = joints[Joint_elbowR].getCoord();
	Vertex* wristR = &joints[Joint_wristR].getCoord();

	if (axis == Axis_X) {
		float y = wristR->y - elbowR.y;
		float z = wristR->z - elbowR.z;
		wristR->y = cos(radian) * y - sin(radian) * z + elbowR.y;
		wristR->z = sin(radian) * y + cos(radian) * z + elbowR.z;
	}
	else if (axis == Axis_Y) {
		float x = wristR->x - elbowR.x;
		float z = wristR->z - elbowR.z;
		wristR->x = cos(radian) * x + sin(radian) * z + elbowR.x;
		wristR->z = -sin(radian) * x + cos(radian) * z + elbowR.z;
	}
	else if (axis == Axis_Z) {
		float x = wristR->x - elbowR.x;
		float y = wristR->y - elbowR.y;
		wristR->x = cos(radian) * x - sin(radian) * y + elbowR.x;
		wristR->y = sin(radian) * x + cos(radian) * y + elbowR.y;
	}
}

void Skinning::rotateElbowL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerArmL, vertices, joints);

	for (int i = 0; i < elbowLSegment.size(); i++) {
		Vertex* v = &vertices[elbowLSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_shoulderL) {
				pivotJoint = joints[Joint_shoulderL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y - sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * y + cos(thisRad) * z + pivotJoint.z);

				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {

					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_elbowL) {
				pivotJoint = joints[Joint_elbowL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y - sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * y + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * x + cos(radian) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex elbowL = joints[Joint_elbowL].getCoord();
	Vertex* wristL = &joints[Joint_wristL].getCoord();

	if (axis == Axis_X) {
		float y = wristL->y - elbowL.y;
		float z = wristL->z - elbowL.z;
		wristL->y = cos(radian) * y - sin(radian) * z + elbowL.y;
		wristL->z = sin(radian) * y + cos(radian) * z + elbowL.z;
	}
	else if (axis == Axis_Y) {
		float x = wristL->x - elbowL.x;
		float z = wristL->z - elbowL.z;
		wristL->x = cos(radian) * x + sin(radian) * z + elbowL.x;
		wristL->z = -sin(radian) * x + cos(radian) * z + elbowL.z;
	}
	else if (axis == Axis_Z) {
		float x = wristL->x - elbowL.x;
		float y = wristL->y - elbowL.y;
		wristL->x = cos(radian) * x - sin(radian) * y + elbowL.x;
		wristL->y = sin(radian) * x + cos(radian) * y + elbowL.y;
	}
}

void Skinning::rotateLegR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperLegR, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < legRSegment.size(); i++) {
		Vertex* v = &vertices[legRSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisMid) {
				pivotJoint = joints[Joint_pelvisMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y - sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * y + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_pelvisR) {
				pivotJoint = joints[Joint_pelvisR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y - sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * y + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex pelvisR = joints[Joint_pelvisR].getCoord();
	Vertex* kneeR = &joints[Joint_kneeR].getCoord();
	Vertex* ankleR = &joints[Joint_ankleR].getCoord();

	if (axis == Axis_X) {
		float y = kneeR->y - pelvisR.y;
		float z = kneeR->z - pelvisR.z;
		kneeR->y = cos(radian) * y - sin(radian) * z + pelvisR.y;
		kneeR->z = -sin(radian) * y + cos(radian) * z + pelvisR.z;

		y = ankleR->y - pelvisR.y;
		z = ankleR->z - pelvisR.z;
		ankleR->y = cos(radian) * y - sin(radian) * z + pelvisR.y;
		ankleR->z = -sin(radian) * y + cos(radian) * z + pelvisR.z;
	}
	else if (axis == Axis_Y) {
		float x = kneeR->x - pelvisR.x;
		float z = kneeR->z - pelvisR.z;
		kneeR->x = cos(radian) * x + sin(radian) * z + pelvisR.x;
		kneeR->z = -sin(radian) * x + cos(radian) * z + pelvisR.z;

		x = ankleR->x - pelvisR.x;
		z = ankleR->z - pelvisR.z;
		ankleR->x = cos(radian) * x + sin(radian) * z + pelvisR.x;
		ankleR->z = -sin(radian) * x + cos(radian) * z + pelvisR.z;
	}
	else if (axis == Axis_Z) {
		float x = kneeR->x - pelvisR.x;
		float y = kneeR->y - pelvisR.y;
		kneeR->x = cos(radian) * x - sin(radian) * y + pelvisR.x;
		kneeR->y = sin(radian) * x + cos(radian) * y + pelvisR.y;

		x = ankleR->x - pelvisR.x;
		y = ankleR->y - pelvisR.y;
		ankleR->x = cos(radian) * x - sin(radian) * y + pelvisR.x;
		ankleR->y = sin(radian) * x + cos(radian) * y + pelvisR.y;
	}
}

void Skinning::rotateLegL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;

	paintWeights(Segment_UpperLegL, vertices, joints);

	Vertex pivotJoint;
	for (int i = 0; i < legLSegment.size(); i++) {
		Vertex* v = &vertices[legLSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisMid) {
				pivotJoint = joints[Joint_pelvisMid].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y - sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(thisRad) * y + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x + sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * (x)-sin(thisRad) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * (x)+cos(thisRad)  * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_pelvisL) {
				pivotJoint = joints[Joint_pelvisL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y - sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (sin(radian) * y + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x + sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (-sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * (x)-sin(radian) * (y)+pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * (x)+cos(radian) * (y)+pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex pelvisL = joints[Joint_pelvisL].getCoord();
	Vertex* kneeL = &joints[Joint_kneeL].getCoord();
	Vertex* ankleL = &joints[Joint_ankleL].getCoord();

	if (axis == Axis_X) {
		float y = kneeL->y - pelvisL.y;
		float z = kneeL->z - pelvisL.z; kneeL->z = -sin(radian) * y + cos(radian) * z + pelvisL.z;

		y = ankleL->y - pelvisL.y;
		z = ankleL->z - pelvisL.z;
		ankleL->y = cos(radian) * y - sin(radian) * z + pelvisL.y;
		ankleL->z = -sin(radian) * y + cos(radian) * z + pelvisL.z;
	}
	else if (axis == Axis_Y) {
		float x = kneeL->x - pelvisL.x;
		float z = kneeL->z - pelvisL.z;
		kneeL->x = cos(radian) * x + sin(radian) * z + pelvisL.x;
		kneeL->z = -sin(radian) * x + cos(radian) * z + pelvisL.z;

		x = ankleL->x - pelvisL.x;
		z = ankleL->z - pelvisL.z;
		ankleL->x = cos(radian) * x + sin(radian) * z + pelvisL.x;
		ankleL->z = -sin(radian) * x + cos(radian) * z + pelvisL.z;
	}
	else if (axis == Axis_Z) {
		float x = kneeL->x - pelvisL.x;
		float y = kneeL->y - pelvisL.y;
		kneeL->x = cos(radian) * x - sin(radian) * y + pelvisL.x;
		kneeL->y = sin(radian) * x + cos(radian) * y + pelvisL.y;

		x = ankleL->x - pelvisL.x;
		y = ankleL->y - pelvisL.y;
		ankleL->x = cos(radian) * x - sin(radian) * y + pelvisL.x;
		ankleL->y = sin(radian) * x + cos(radian) * y + pelvisL.y;
	}
}

void Skinning::rotateKneeR(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerLegR, vertices, joints);

	for (int i = 0; i < kneeRSegment.size(); i++) {
		Vertex* v = &vertices[kneeRSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisR) {
				pivotJoint = joints[Joint_pelvisR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y + sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * y + cos(thisRad)  * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_kneeR) {
				pivotJoint = joints[Joint_kneeR].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y + sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (-sin(radian) * y + cos(radian)  * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * x + cos(radian) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex kneeR = joints[Joint_kneeR].getCoord();
	Vertex* ankleR = &joints[Joint_ankleR].getCoord();

	if (axis == Axis_X) {
		float y = ankleR->y - kneeR.y;
		float z = ankleR->z - kneeR.z;
		ankleR->y = cos(radian) * y - sin(radian) * z + kneeR.y;
		ankleR->z = sin(radian) * y + cos(radian) * z + kneeR.z;
	}
	else if (axis == Axis_Y) {
		float x = ankleR->x - kneeR.x;
		float z = ankleR->z - kneeR.z;
		ankleR->x = cos(radian) * x + sin(radian) * z + kneeR.x;
		ankleR->z = -sin(radian) * x + cos(radian) * z + kneeR.z;
	}
	else if (axis == Axis_Z) {
		float x = ankleR->x - kneeR.x;
		float y = ankleR->y - kneeR.y;
		ankleR->x = cos(radian) * x - sin(radian) * y + kneeR.x;
		ankleR->y = sin(radian) * x + cos(radian) * y + kneeR.y;
	}
}

void Skinning::rotateKneeL(int part, float degree, vector<Vertex>& vertices, vector<Joint>& joints) {
	float thisRad = (0) * M_PI / 180;
	float radian = degree * M_PI / 180;
	Vertex pivotJoint;

	paintWeights(Segment_LowerLegL, vertices, joints);

	for (int i = 0; i < kneeLSegment.size(); i++) {
		Vertex* v = &vertices[kneeLSegment[i]];

		float x = 0, y = 0, z = 0;
		float tmp_x = 0, tmp_y = 0, tmp_z = 0;
		for (int j = 0; j < v->jointsRelated.size(); j++) {
			if (v->jointsRelated[j] == Joint_pelvisL) {
				pivotJoint = joints[Joint_pelvisL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;

				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(thisRad) * y + sin(thisRad) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (-sin(thisRad) * y + cos(thisRad)  * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(thisRad) * x - sin(thisRad) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(thisRad) * x + cos(thisRad) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
			else if (v->jointsRelated[j] == Joint_kneeL) {
				pivotJoint = joints[Joint_kneeL].getCoord();
				x = v->x - pivotJoint.x;
				y = v->y - pivotJoint.y;
				z = v->z - pivotJoint.z;
				if (axis == Axis_X) {
					tmp_x = v->x;
					tmp_y += v->jointWeights[j] * (cos(radian) * y + sin(radian) * z + pivotJoint.y);
					tmp_z += v->jointWeights[j] * (-sin(radian) * y + cos(radian)  * z + pivotJoint.z);
				}
				else if (axis == Axis_Y) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * z + pivotJoint.x);
					tmp_y = v->y;
					tmp_z += v->jointWeights[j] * (sin(radian) * x + cos(radian) * z + pivotJoint.z);
				}
				else if (axis == Axis_Z) {
					tmp_x += v->jointWeights[j] * (cos(radian) * x - sin(radian) * y + pivotJoint.x);
					tmp_y += v->jointWeights[j] * (sin(radian) * x + cos(radian) * y + pivotJoint.y);
					tmp_z = v->z;
				}
			}
		}

		v->x = tmp_x;
		v->y = tmp_y;
		v->z = tmp_z;
	}

	Vertex kneeL = joints[Joint_kneeL].getCoord();
	Vertex* ankleL = &joints[Joint_ankleL].getCoord();

	if (axis == Axis_X) {
		float y = ankleL->y - kneeL.y;
		float z = ankleL->z - kneeL.z;
		ankleL->y = cos(radian) * y - sin(radian) * z + kneeL.y;
		ankleL->z = sin(radian) * y + cos(radian) * z + kneeL.z;
	}
	else if (axis == Axis_Y) {
		float x = ankleL->x - kneeL.x;
		float z = ankleL->z - kneeL.z;
		ankleL->x = cos(radian) * x + sin(radian) * z + kneeL.x;
		ankleL->z = -sin(radian) * x + cos(radian) * z + kneeL.z;
	}
	else if (axis == Axis_Z) {
		float x = ankleL->x - kneeL.x;
		float y = ankleL->y - kneeL.y;
		ankleL->x = cos(radian) * x - sin(radian) * y + kneeL.x;
		ankleL->y = sin(radian) * x + cos(radian) * y + kneeL.y;
	}
}

void Skinning::deform(int pivotIndex, float degree, vector<int>& currBones, vector<Bone>& bones,  vector<int> boneSegment[], vector<float> boneWeight[], vector<Vertex>& vertices, vector<Joint>& joints) {
	float radian = degree * M_PI / 180;

	/*** SORT OUT duplicates ***/
	vector<int> vertIndices;
	vector<int> copyVertIndices;
	for (int i = 0; i < currBones.size(); i++) {
		for (int j = 0; j < boneSegment[currBones[i]].size(); j++) {
			vertIndices.push_back(boneSegment[currBones[i]][j]);
		}
	}
	
	sort(vertIndices.begin(), vertIndices.end());

	for (int i = 0; i < vertIndices.size(); i++) {
		if (copyVertIndices.size() > 1) {
			if (copyVertIndices[copyVertIndices.size() - 1] == vertIndices[i])
				continue;
		}
		copyVertIndices.push_back(vertIndices[i]);
	}

	vertIndices.clear();
	vertIndices.insert(vertIndices.end(), copyVertIndices.begin(), copyVertIndices.end());

	/*** Perform deformation ***/
	Vertex pivotJoint = joints[pivotIndex].getCoord();
	for (int i = 0; i < vertIndices.size(); i++) {
		int vertIdx = vertIndices[i];
		Vertex* currVert = &vertices[vertIdx];

		float weight = 0;
		float new_x = 0, new_y = 0, new_z = 0;
		float x = currVert->x - pivotJoint.x;
		float y = currVert->y - pivotJoint.y;
		float z = currVert->z - pivotJoint.z;
		
		for (int j = 0; j < vertices[vertIdx].refBone.size(); j++) {
			int currBone = vertices[vertIdx].refBone[j];
			float currWeight = vertices[vertIdx].refWeight[j];

			if (currBone == -1)
				continue;

			//Vertex pivotJoint = joints[bones[currBone].upperJoint].getCoord();
			for (int k = 0; k < currBones.size(); k++) {
				if (currBones[k] == currBone) { // Effected only by those participating in deformation

					if (axis == Axis_Z) {
						new_x += currWeight * (cos(radian) * x - sin(radian) * y + pivotJoint.x);
						new_y += currWeight * (sin(radian) * x + cos(radian) * y + pivotJoint.y);
					}
					weight += currWeight;
				}
			}
		}

		if (axis == Axis_Z) {
			new_x += (1 - weight) * (x + pivotJoint.x);
			new_y += (1 - weight) * (y + pivotJoint.y);
		}

		if (axis == Axis_Z) {
			currVert->x = new_x;
			currVert->y = new_y;
		}
	}

	for (int i = 0; i < currBones.size(); i++) {
		int currBone = currBones[i];
		//Vertex pivotJoint = joints[bones[currBone].upperJoint].getCoord();
		Vertex* lowerJoint = &joints[bones[currBone].lowerJoint].getCoord();
		float x = lowerJoint->x - pivotJoint.x;
		float y = lowerJoint->y - pivotJoint.y;

		if (axis == Axis_Z) {
			lowerJoint->x = cos(radian) * x - sin(radian) * y + pivotJoint.x;
			lowerJoint->y = sin(radian) * x + cos(radian) * y + pivotJoint.y;
		}
	}
}

void Skinning::deformDQS(int pivotIndex, float degree, vector<int>& currBones, vector<Bone>& bones, vector<int> boneSegment[], vector<float> boneWeight[], vector<Vertex>& vertices, vector<Joint>& joints) {
	float radian = degree * M_PI / 180;
	/*** Copyright GAIA : from gmath.cpp SetFromMatrix(double *mat, bool isGL) ***/
	double q[4];
	double tr, s;
	int i, j, k;
	int nxt[3] = { 1, 2, 0 };

	double mat[16]; // 4x4 matrix
	float x, y, z, w;

	if (axis == Axis_Z) {
		mat[0] = cos(radian);
		mat[1] = -sin(radian);
		mat[2] = 0;
		mat[3] = 0;

		mat[4] = sin(radian);
		mat[5] = cos(radian);
		mat[6] = 0;
		mat[7] = 0;

		mat[8] = 0;
		mat[9] = 0;
		mat[10] = 1;
		mat[11] = 0;

		mat[12] = 0;
		mat[13] = 0;
		mat[14] = 0;
		mat[15] = 1;
	}
	
	tr = mat[0] + mat[5] + mat[10];
	if (tr > 0.0) {
		s = sqrt(tr + 1.0);
		w = s * 0.5; 
		s = 0.5 / s; 
		x = (mat[9] - mat[6]) * s; 
		y = (mat[2] - mat[8]) * s; 
		z = (mat[4] - mat[1]) * s; 
	}
	else {
		i = 0;
		if (mat[5] > mat[0]) {
			i = 1;
		}
		if (mat[10] > mat[i * 4 + i]) {
			i = 2;
		}
		j = nxt[i];
		k = nxt[j];
		s = sqrt((mat[i * 4 + i] - (mat[j * 4 + j] + mat[k * 4 + k])) + 1.0);
		q[i] = s * 0.5;
		s = 0.5 / s;
		w = (mat[k * 4 + j] - mat[j * 4 + k]) * s;
		q[j] = (mat[j * 4 + i] + mat[i * 4 + j]) * s;
		q[k] = (mat[k * 4 + i] + mat[i * 4 + k]) * s;
		x = q[0];
		y = q[1];
		z = q[2];
	}

	double bq[4];
	double btr, bs;
	int bi, bj, bk;
	nxt[0] = 1; nxt[1] = 2; nxt[2] = 0;
	double bmat[16];
	float bx, by, bz, bw;
	if (axis == Axis_Z) {
		bmat[0] = 1;
		bmat[1] = 0;
		bmat[2] = 0;
		bmat[3] = 0;

		bmat[4] = 0;
		bmat[5] = 1;
		bmat[6] = 0;
		bmat[7] = 0;

		bmat[8] = 0;
		bmat[9] = 0;
		bmat[10] = 1;
		bmat[11] = 0;

		bmat[12] = 0;
		bmat[13] = 0;
		bmat[14] = 0;
		bmat[15] = 1;
	}
	
	btr = bmat[0] + bmat[5] + bmat[10];
	if (btr > 0.0) {
		bs = sqrt(btr + 1.0);
		bw = bs * 0.5; 
		bs = 0.5 / bs; 
		bx = (bmat[9] - bmat[6]) * bs; 
		by = (bmat[2] - bmat[8]) * bs; 
		bz = (bmat[4] - bmat[1]) * bs; 
	}
	else {
		bi = 0;
		if (bmat[5] > bmat[0]) {
			bi = 1;
		}
		if (bmat[10] > bmat[bi * 4 + bi]) {
			bi = 2;
		}
		bj = nxt[bi];
		bk = nxt[bj];
		bs = sqrt((bmat[bi * 4 + bi] - (bmat[bj * 4 + bj] + bmat[bk * 4 + bk])) + 1.0);
		bq[i] = bs * 0.5;
		bs = 0.5 / bs;
		bw = (bmat[bk * 4 + bj] - mat[bj * 4 + bk]) * bs;
		bq[bj] = (bmat[bj * 4 + bi] + bmat[bi * 4 + bj]) * bs;
		bq[bk] = (bmat[bk * 4 + bi] + bmat[bi * 4 + bk]) * bs;
		bx = bq[0];
		by = bq[1];
		bz = bq[2];
	}

	// conjugate

	/*** SORT OUT duplicates ***/
	vector<int> vertIndices; vector<int> copyVertIndices;
	for (int i = 0; i < currBones.size(); i++) {
		for (int j = 0; j < boneSegment[currBones[i]].size(); j++) {
			vertIndices.push_back(boneSegment[currBones[i]][j]);
		}
	}
	sort(vertIndices.begin(), vertIndices.end());
	for (int i = 0; i < vertIndices.size(); i++) {
		if (copyVertIndices.size() > 1) {
			if (copyVertIndices[copyVertIndices.size() - 1] == vertIndices[i])
				continue;
		}
		copyVertIndices.push_back(vertIndices[i]);
	}
	vertIndices.clear(); vertIndices.insert(vertIndices.end(), copyVertIndices.begin(), copyVertIndices.end());

	/*** Perform deformation ***/
	Vertex pivotJoint = joints[pivotIndex].getCoord();
	for (int i = 0; i < vertIndices.size(); i++) {
		int vertIdx = vertIndices[i];
		Vertex* currVert = &vertices[vertIdx];

		float weight = 0; 
		float new_x = 0, new_y = 0, new_z = 0;
		float vx = currVert->x - pivotJoint.x; 
		float vy = currVert->y - pivotJoint.y; 
		float vz = currVert->z - pivotJoint.z;
		float q_hat[4] = { 0, 0, 0, 0 }; float cq_hat[4] = { 0, 0, 0, 0 }; // q = (w, x, y, z)
		
		for (int j = 0; j < vertices[vertIdx].refBone.size(); j++) {
			int currBone = vertices[vertIdx].refBone[j];
			float currWeight = vertices[vertIdx].refWeight[j];
			if (currBone == -1) continue;
			for (int k = 0; k < currBones.size(); k++) {
				if (currBones[k] == currBone) { // Effected only by those participating in deformation
					if (axis == Axis_Z) {
						if (currBone == currBones[0] || currBone == Bone_ribR || currBone == Bone_ribL) {
							q_hat[0] += currWeight * bw;
							q_hat[1] += currWeight * bx;
							q_hat[2] += currWeight * by;
							q_hat[3] += currWeight * bz;

							continue;
						}
						q_hat[0] += currWeight * w; 
						q_hat[1] += currWeight * x; 
						q_hat[2] += currWeight * y; 
						q_hat[3] += currWeight * z;
					}
					weight += currWeight;
				}
			}
		}

		float qsize = sqrt(pow(q_hat[0], 2) + pow(q_hat[1], 2) + pow(q_hat[2], 2) + pow(q_hat[3], 2));
		q_hat[0] /= qsize;
		q_hat[1] /= qsize;
		q_hat[2] /= qsize;
		q_hat[3] /= qsize;

		/*
		cq_hat[0] = (1 - weight) * w;
		cq_hat[1] = (1 - weight) * x;
		cq_hat[2] = (1 - weight) * y;
		cq_hat[3] = (1 - weight) * z;
		*/
		float cqsize = sqrt(pow(cq_hat[0], 2) + pow(cq_hat[1], 2) + pow(cq_hat[2], 2) + pow(cq_hat[3], 2));
		cq_hat[0] /= cqsize;
		cq_hat[1] /= cqsize;
		cq_hat[2] /= cqsize;
		cq_hat[3] /= cqsize;

		// float cqsize = sqrt(pow(cq_hat[0], 2) + pow(cq_hat[1], 2) + pow(cq_hat[2], 2) + pow(cq_hat[3], 2));
		// cq_hat[0] /= cqsize; cq_hat[1] /= cqsize; cq_hat[2] /= cqsize; cq_hat[3] /= cqsize;

		if (axis == Axis_Z) {
			currVert->x = (pow(q_hat[1], 2) + pow(q_hat[0], 2) - pow(q_hat[2], 2) - pow(q_hat[3], 2)) * vx + (2 * q_hat[1] * q_hat[2] - 2 * q_hat[0] * q_hat[3]) * vy + (2 * q_hat[1] * q_hat[3] + 2 * q_hat[0] * q_hat[2]) * vz + pivotJoint.x;
			currVert->y = (2 * q_hat[1] * q_hat[2] + 2 * q_hat[0] * q_hat[3]) * vx + (pow(q_hat[2], 2) + pow(q_hat[0], 2) - pow(q_hat[1], 2) - pow(q_hat[3], 2)) * vy + (2 * q_hat[2] * q_hat[3] - 2 * q_hat[0] * q_hat[1]) * vz + pivotJoint.y;
			currVert->z = (2 * q_hat[1] * q_hat[3] - 2 * q_hat[0] * q_hat[2]) * vx + (2 * q_hat[2] * q_hat[3] + 2 * q_hat[0] * q_hat[1]) * vy + (pow(q_hat[0], 2) + pow(q_hat[3], 2) - pow(q_hat[1], 2) - pow(q_hat[2], 2)) * vz + pivotJoint.z;
		}
	}
}

void Skinning::updateRigs(vector<Vertex>& vertices, vector<Joint>& joints) {
	for (int i = 0; i < joints.size(); i++) {
		int jointId = joints[i].id;
		Vertex *j = &joints[i].getCoord();

		/*
		vector<int> rv = joints[i].getRelatedVerts();

		j->y = (vertices[rv[2]].y + vertices[rv[3]].y) / 2;
		j->z = (vertices[rv[4]].z + vertices[rv[5]].z) / 2;

		if (jointId == Joint_neck || jointId == Joint_shoulderMid || jointId == Joint_waist || jointId == Joint_pelvisMid)
			j->x = 0;
		else
			j->x = (vertices[rv[0]].x + vertices[rv[1]].x) / 2;
			*/
	}
}
