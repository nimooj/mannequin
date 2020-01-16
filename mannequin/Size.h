#pragma once

#include "BodyProxies.h"
#include "HumanOBJ.h"

class Size {
public:
	Size();
	Size(BodyProxies*);
	Size(HumanOBJ*);
	~Size();

	void setSize(int, float); // BodyLayer, circumference
	float getSize(int);  // BodyLayer

private:
	BodyProxies* body;
	HumanOBJ* human;

	float bust, waist, hip;
	void update();
};
