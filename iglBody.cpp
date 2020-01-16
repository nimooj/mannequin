#include "stdafx.h"
#include "iglBody.h"

iglBody::iglBody() {

}

iglBody::iglBody(string dir) {
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;

	igl::readOBJ(dir, V, F);
}

iglBody::~iglBody() {

}
