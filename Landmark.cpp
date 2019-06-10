#include "stdafx.h"

#include "Landmark.h"

Landmark::Landmark() {

}

Landmark::Landmark(CString ctr, float t) {
	name = ctr;
	type = t;
}

Landmark::Landmark(CString ctr, float t, float val) {
	name = ctr;
	type = t;
	value = val;
}

Landmark::Landmark(CString ctr, float t, float val, vector<int> inds) {
	name = ctr;
	type = t;
	value = val;
	vertIdx.insert(vertIdx.end(), inds.begin(), inds.end());
}

Landmark::Landmark(CString ctr, float t, float val, float h, vector<int> inds) {
	name = ctr;
	type = t;
	value = val;
	level = h;
	vertIdx.insert(vertIdx.end(), inds.begin(), inds.end());
}

Landmark::~Landmark() {

}

void Landmark::SetGirthFeature(vector<int>& inds, vector<Vertex>& verts, float h) {
	float ys = 0;
	float dist = 0;
	vector<Vertex> girth;
	GrahamScan g;
	
	/*** Limit relevants ***/
	int trial = 0;
	float range = 0.5;
	while (trial <= 10) {
		if ( girth.size() >= 10 )
			break;

		girth.clear();

		for (int i = 0; i < inds.size(); i++) {
			if (abs(verts[inds[i] - 1].y - h) <= range) {
				Vertex v = verts[inds[i] - 1];
				girth.push_back(v);
				ys += v.y;
			}
		}

		trial++;
		range += 0.5;
	}

	/*** Unify offset ***/
	for (int i = 0; i < girth.size(); i++) {
		girth[i].y = ys / girth.size();
	}

	level = girth[0].y;

	/*** Get Convex Hull  ***/
	g = GrahamScan(girth);
	vector<Vertex> convex = g.GenerateConvexHull();

	for (int i = 1; i < convex.size(); i++) {
		dist += convex[i].distance(convex[i - 1]);
		vertIdx.push_back(convex[i].idx);
	}
	dist += convex[convex.size() - 1].distance(convex[0]);

	value = dist;
}