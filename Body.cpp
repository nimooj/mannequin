#include "stdafx.h"
#include "Body.h"

Body::Body() {
	bodyproxies = BodyProxies();

	/* SURFACE GENERATION */
	layerSize = 9;
	bustRadius = 90 / (2 * M_PI);
	waistRadius = 70 / (2 * M_PI);
	hipRadius = 94 / (2 * M_PI);

	idx = 0;

	int layerNum = 0;
	int startAngle = 0;

	makeBody();

	/* LAYERS */
	/*
	// Apex
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, headIdx++) {
		float radian = degree * M_PI / 180;
		headGroup.push_back(Vertex(headIdx, 10*cos(radian), 72, 10*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 10*cos(radian), 72, 10*sin(radian)));
	}
	layerNum++;
	// Top head
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, headIdx++) {
		float radian = degree * M_PI / 180;
		headGroup.push_back(Vertex(headIdx, 10*cos(radian), 70, 10*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 10*cos(radian), 70, 10*sin(radian)));
	}
	layerNum++;
	// Jaw
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, headIdx++) {
		float radian = degree * M_PI / 180;
		headGroup.push_back(Vertex(headIdx, 10*cos(radian), 50, 10*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 10*cos(radian), 50, 10*sin(radian)));
	}
	// high neck
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, neckIdx++) {
		float radian = degree * M_PI / 180;
		neckGroup.push_back(Vertex(neckIdx, 6*cos(radian), 48, 6*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 6*cos(radian), 48, 6*sin(radian)));
	}
	//low neck
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, neckIdx++) {
		float radian = degree * M_PI / 180;
		neckGroup.push_back(Vertex(neckIdx, 7*cos(radian), 43, 7*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 7*cos(radian), 43, 7*sin(radian)));
	}
	// shoulder
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoUpperIdx++) {
		float radian = degree * M_PI / 180;
		torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 16*cos(radian), 40, 13*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 16*cos(radian), 40, 13*sin(radian)));
	}
	//  armpit
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoUpperIdx++) {
		float radian = degree * M_PI / 180;
		torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 15*cos(radian), 25, 15*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 15*cos(radian), 25, 15*sin(radian)));
	}
	// under arm
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoUpperIdx++) {
		float radian = degree * M_PI / 180;
		torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 13*cos(radian), 23, 13*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 13*cos(radian), 23, 13*sin(radian)));
	}
	// waist
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoUpperIdx++) {
		float radian = degree * M_PI / 180;
		torsoUpperGroup.push_back(Vertex(idx, waistRadius*cos(radian), 10, waistRadius*sin(radian)));
		wholeGroup.push_back(Vertex(idx, waistRadius*cos(radian), 10, waistRadius*sin(radian)));
	}
	// pelvis
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoLowerIdx++) {
		float radian = degree * M_PI / 180;
		torsoLowerGroup.push_back(Vertex(torsoLowerIdx, hipRadius*cos(radian), 7, hipRadius*sin(radian)));
		wholeGroup.push_back(Vertex(idx, hipRadius*cos(radian), 7, hipRadius*sin(radian)));
	}
	// hip
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoLowerIdx++) {
		float radian = degree * M_PI / 180;
		torsoLowerGroup.push_back(Vertex(torsoLowerIdx, hipRadius*cos(radian), 5, hipRadius*sin(radian)));
		wholeGroup.push_back(Vertex(idx, hipRadius*cos(radian), 5, hipRadius*sin(radian)));
	}
	// crotch
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, torsoLowerIdx++) {
		float radian = degree * M_PI / 180;
		torsoLowerGroup.push_back(Vertex(torsoLowerIdx, 3*cos(radian), 2, 3*sin(radian)));
		wholeGroup.push_back(Vertex(idx, 3*cos(radian), 3, 3*sin(radian)));
	}

	// arm right upper
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, armRightIdx++) {
		float radian = degree * M_PI / 180;
		armRightUpperGroup.push_back(Vertex(armRightIdx, -45, 5*sin(radian) + 33, 5*cos(radian)));
		wholeGroup.push_back(Vertex(idx, -45, 5*sin(radian) + 33, 5*cos(radian)));
	}
	// arm right lower
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, armRightIdx++) {
		float radian = degree * M_PI / 180;
		armRightLowerGroup.push_back(Vertex(armRightIdx, -70, 3*sin(radian) + 31, 3*cos(radian)));
		wholeGroup.push_back(Vertex(idx, -70, 3*sin(radian) + 31, 3*cos(radian)));
	}
	// arm left upper
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, armLeftIdx++) {
		float radian = degree * M_PI / 180;
		armLeftUpperGroup.push_back(Vertex(armLeftIdx, 45, 5*sin(radian) + 33, -5*cos(radian)));
		wholeGroup.push_back(Vertex(idx, 45, 5*sin(radian) + 33, -5*cos(radian)));
	}
	// arm left lower
	for (int degree = startAngle; degree < 360; degree += 360 / layerSize, idx++, armLeftIdx++) {
		float radian = degree * M_PI / 180;
		armLeftLowerGroup.push_back(Vertex(armLeftIdx, 70, 3*sin(radian) + 31, -3*cos(radian)));
		wholeGroup.push_back(Vertex(idx, 70, 3*sin(radian) + 31, -3*cos(radian)));
	}
	*/

	/* JOINTS */
	/* JOINTS GENERATION
	for (int i = 0; i < 16; i++) {
		joints.push_back(Vertex(i, 0, 0, 0));
	}

	joints[NeckUpper].y = 55;
	joints[NeckLower].y = 45;

	joints[ShoulderR].y = 40;
	joints[ShoulderL].y = 40;
	joints[ShoulderR].x = -20;
	joints[ShoulderL].x = 20;

	joints[ElbowR].y = 40;
	joints[ElbowL].y = 40;
	joints[ElbowR].x = -45;
	joints[ElbowL].x = 45;

	joints[WristR].y = 40;
	joints[WristL].y = 40;
	joints[WristR].x = -70;
	joints[WristL].x = 70;

	joints[Waist].y = 10;

	joints[PelvisM].y = -10;
	joints[PelvisR].y = -10;
	joints[PelvisL].y = -10;
	joints[PelvisR].x = -20;
	joints[PelvisL].x = 20;

	joints[KneeR].y = -45;
	joints[KneeL].y = -45;
	joints[KneeR].x = -22;
	joints[KneeL].x = 22;

	joints[AnkleR].y = -80;
	joints[AnkleL].y = -80;
	joints[AnkleR].x = -25;
	joints[AnkleL].x = 25;
	*/
}

Body::Body(string dir) {
	bodyproxies = BodyProxies(dir);

	/* SURFACE GENERATION */
	layerSize = 9;
	bustRadius = 90 / (2 * M_PI);
	waistRadius = 70 / (2 * M_PI);
	hipRadius = 94 / (2 * M_PI);

	idx = 0;

	int layerNum = 0;
	int startAngle = 0;

	//makeBody();
}

Body::~Body() {

}

void Body::makeBody() {
	/*
	makeHead();
	makeNeck();
	makeTorso();
	makeArms();
	makeLegs();
	*/
}


void Body::makeHead() {

}
void Body::makeNeck() {
	int neckIdx = 0;

	neckGroup.push_back(Vertex(neckIdx, 0, 55, 0)); // 1
	wholeGroup.push_back(Vertex(idx, 0, 55, 0));
	neckIdx++;
	idx++;

	neckGroup.push_back(Vertex(neckIdx, -7, 55, 0)); // 2
	wholeGroup.push_back(Vertex(idx, -7, 55, 0));
	neckIdx++;
	idx++;

	neckGroup.push_back(Vertex(neckIdx, 0, 53, 0)); // 3
	wholeGroup.push_back(Vertex(idx, 0, 53, 0));
	neckIdx++;
	idx++;

	neckGroup.push_back(Vertex(neckIdx, -7, 53, 0)); // 4
	wholeGroup.push_back(Vertex(idx, -7, 53, 0));
	neckIdx++;
	idx++;

	neckGroup.push_back(Vertex(neckIdx, -7, 50, 0)); // 5
	wholeGroup.push_back(Vertex(idx, -7, 50, 0));
	neckIdx++;
	idx++;

	neckGroup.push_back(Vertex(neckIdx, 0, 50, 0)); // 6
	wholeGroup.push_back(Vertex(idx, 0, 50, 0));
	neckIdx++;
	idx++;
}
void Body::makeTorso() {
	int torsoUpperIdx = 0;
	int torsoLowerIdx = 0;

	// RIGHT TORSO
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 0, 50, 0)); // 1
	wholeGroup.push_back(Vertex(idx, 0, 50, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, -7, 50, 0)); //2
	wholeGroup.push_back(Vertex(idx, -7, 50, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, -20, 45, 0)); //3
	wholeGroup.push_back(Vertex(idx, -20, 45, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 0, 45, 0)); //4
	wholeGroup.push_back(Vertex(idx, 0, 45, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, -20, 35, 0)); //5
	wholeGroup.push_back(Vertex(idx, -20, 35, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 0, 35, 0)); //6
	wholeGroup.push_back(Vertex(idx, 0, 35, 0));
	torsoUpperIdx++;
	idx++;

	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, -18, 31, 0)); //7
	wholeGroup.push_back(Vertex(idx, -18, 31, 0));
	torsoUpperIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 0, 31, 0)); //8
	wholeGroup.push_back(Vertex(idx, 0, 31, 0));
	torsoUpperIdx++;
	idx++;

	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, -16, 15, 0)); //9
	torsoLowerGroup.push_back(Vertex(torsoLowerIdx, -16, 15, 0)); //1
	wholeGroup.push_back(Vertex(idx, -16, 15, 0));
	torsoUpperIdx++;
	torsoLowerIdx++;
	idx++;
	torsoUpperGroup.push_back(Vertex(torsoUpperIdx, 0, 15, 0)); //10
	torsoLowerGroup.push_back(Vertex(torsoLowerIdx, 0, 15, 0)); //2
	wholeGroup.push_back(Vertex(idx, 0, 15, 0));
	torsoUpperIdx++;
	torsoLowerIdx++;
	idx++;

	torsoLowerGroup.push_back(Vertex(torsoLowerIdx, -15, 0, 0)); //3
	wholeGroup.push_back(Vertex(idx, -15, 0, 0));
	torsoLowerIdx++;
	idx++;
	torsoLowerGroup.push_back(Vertex(torsoLowerIdx, 0, 0, 0)); //4
	wholeGroup.push_back(Vertex(idx, 0, 0, 0));
	torsoLowerIdx++;
	idx++;
}
void Body::makeArms() {
	int armRightUpperIdx = 0;
	int armRightLowerIdx = 0;

	// RIGHT ARM
	armRightUpperGroup.push_back(Vertex(armRightUpperIdx, -20, 45, 0)); // 1
	wholeGroup.push_back(Vertex(idx, -20, 45, 0));
	armRightUpperIdx++;
	idx++;

	armRightUpperGroup.push_back(Vertex(armRightUpperIdx, -20, 35, 0)); // 2
	wholeGroup.push_back(Vertex(idx, -20, 35, 0));
	armRightUpperIdx++;
	idx++;

	armRightUpperGroup.push_back(Vertex(armRightUpperIdx, -45, 43, 0)); // 3
	armRightLowerGroup.push_back(Vertex(armRightLowerIdx, -45, 43, 0)); // 1
	wholeGroup.push_back(Vertex(idx, -45, 43, 0));
	armRightUpperIdx++;
	armRightLowerIdx++;
	idx++;

	armRightUpperGroup.push_back(Vertex(armRightUpperIdx, -45, 34, 0)); //4
	armRightLowerGroup.push_back(Vertex(armRightLowerIdx, -45, 34, 0)); //2
	wholeGroup.push_back(Vertex(idx, -45, 34, 0));
	armRightUpperIdx++;
	armRightLowerIdx++;
	idx++;

	armRightLowerGroup.push_back(Vertex(armRightLowerIdx, -70, 40, 0)); // 3
	wholeGroup.push_back(Vertex(idx, -70, 40, 0));
	armRightLowerIdx++;
	idx++;

	armRightLowerGroup.push_back(Vertex(armRightLowerIdx, -70, 33, 0)); // 4
	wholeGroup.push_back(Vertex(idx, -70, 33, 0));
	armRightLowerIdx++;
	idx++;
}
void Body::makeLegs() {
	int legRightUpperIdx = 0;
	int legRightLowerIdx = 0;

	// RIGHT LEG
	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, 0, 0, 0)); // 1
	wholeGroup.push_back(Vertex(idx, 0, 0, 0));
	legRightUpperIdx++;
	idx++;
	
	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -15, 0, 0)); // 2
	wholeGroup.push_back(Vertex(idx, -15, 0, 0));
	legRightUpperIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, 0, -10, 0)); // 3
	wholeGroup.push_back(Vertex(idx, 0, -10, 0));
	legRightUpperIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -3, -10, 0)); // 4
	wholeGroup.push_back(Vertex(idx, -3, -10, 0));
	legRightUpperIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -3.5, -12, 0)); // 5
	wholeGroup.push_back(Vertex(idx, -3.5, -12, 0));
	legRightUpperIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -17, -8, 0)); // 6
	wholeGroup.push_back(Vertex(idx, -17, -8, 0));
	legRightUpperIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -5, -42, 0)); // 7
	legRightLowerGroup.push_back(Vertex(legRightLowerIdx, -5, -42, 0)); // 1
	wholeGroup.push_back(Vertex(idx, -5, -42, 0));
	legRightUpperIdx++;
	legRightLowerIdx++;
	idx++;

	legRightUpperGroup.push_back(Vertex(legRightUpperIdx, -17, -42, 0)); // 8
	legRightLowerGroup.push_back(Vertex(legRightLowerIdx, -17, -42, 0)); // 2
	wholeGroup.push_back(Vertex(idx, -17, -42, 0));
	legRightUpperIdx++;
	legRightLowerIdx++;
	idx++;

	legRightLowerGroup.push_back(Vertex(legRightLowerIdx, -16, -72, 0)); // 3
	wholeGroup.push_back(Vertex(idx, -16, -72, 0));
	legRightLowerIdx++;
	idx++;

	legRightLowerGroup.push_back(Vertex(legRightLowerIdx, -6, -72, 0)); // 4
	wholeGroup.push_back(Vertex(idx, -6, -72, 0));
	legRightLowerIdx++;
	idx++;
}

void Body::update(int groupName, float nx, float ny, float nz) {

}

void Body::writeToOBJ() {
	int accumSize = 0;
	ofstream outfile("Body.obj");
	outfile << "# Written by Minjoo Kang" << endl;
	outfile << endl << endl;

	/*
	for (int i = 0; i < bodyproxies.baseVert.size(); i++) {
		Vertex v = bodyproxies.baseVert[i];
		outfile << "v " << v.x << " " << v.y << " " << v.z << endl;
	}

	for (int i = 0; i < bodyproxies.baseMesh.size(); i++) {
		Mesh m = bodyproxies.baseMesh[i];
		outfile << "f  " << m.index1 << " " << m.index2 << " " << m.index3 << " " << m.index4 << endl;
	}
	*/

	outfile.close();

	cout << "OBJ exported." << endl;
}

