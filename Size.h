#pragma once

#include "BodyProxies.h"

class Size {
public:
	Size();
	~Size();

	void setSize(int, float); // BodyLayer, circumference
	float getSize(int);  // BodyLayer
};
