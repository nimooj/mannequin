#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Eigen/Core"
#include "igl/readOBJ.h"

using namespace std;

/*
Eigen::PlainObjectBase<Eigen::MatrixXd> vertices;
Eigen::PlainObjectBase<Eigen::MatrixXi> faces;
*/

class iglBody {
public:
	iglBody();
	iglBody(string);
	~iglBody();

private:

};
