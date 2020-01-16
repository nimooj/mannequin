#pragma once

#include "resource.h"

#include "./include/GL/glew.h"
#include "./include/GL/wglew.h"
#include "./include/GL/glut.h"
#include "./include/glm/glm.hpp"
#include "./include/FreeImage.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "./include/glm/gtx/transform.hpp"
#include "./include/glm/gtc/type_ptr.hpp"
#include "./include/glm/gtc/matrix_transform.hpp"

using namespace glm;

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

#include "Camera.h"
#include "Vertex.h"
#include "Joint.h"
#include "BodySegments.h"
#include "JointDefinition.h"
#include "Landmark.h"


class CLandmarkDialog : public CDialogEx {
// Construction
public:
	CLandmarkDialog();
	~CLandmarkDialog();
	CLandmarkDialog(CWnd* pParent);
	enum { IDD = IDD_LANDMARKDIALOG };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnDestroy();

	CStatic landmarkField;
	CListBox landmarkList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	HICON m_hIcon;

public: 
	HGLRC m_hRC; // rendering context -- OpenGL
	CDC* m_pDC; // device context 0 -- windows

	Camera camera;

	float topMostLevel = 0, bottomMostLevel = 0, leftMostLevel = 0, rightMostLevel = 0, leftMostOffset = 0, rightMostOffset = 0;

	vector<Vertex>* vertices;
	vector<int>* indices;
	vector<Joint>* joints;

	vector<Landmark>* variables;
	vector<vec3> varPos;

	vector<vec3> verts;
	vector<int> inds;

	vector<int> bodySegment[SegmentNum];

	float scaleF = 1;
	mat4 scaleMatrix = mat4(1.0f);

	virtual BOOL OnInitDialog();
	BOOL GetRenderingContext();
	virtual BOOL GetOldStyleRenderingContext();
	CButton girthType;
	CButton lengthType;
	afx_msg void OnBnClickedLength();
	afx_msg void OnBnClickedGirth();

	GLuint vao, line_vao, landmark_vao;

	GLuint position_vbo, color_vbo;
	GLuint line_position_vbo, line_color_vbo;
	GLuint landmark_position_vbo, landmark_color_vbo;

	GLuint position_attribute, color_attribute;
	GLuint line_position_attribute, line_color_attribute;
	GLuint landmark_position_attribute, landmark_color_attribute;

	GLuint ebo;
	GLuint shaderProgram, lineShaderProgram, landmarkShaderProgram;

	int selItem = -1;

	void defineVAO(GLuint&);
	void defineLineVAO(GLuint&);
	void defineLandmarkVAO(int, GLuint&);

	GLuint loadShaders(const char*, const char*);
	afx_msg void OnBnClickedButton1();
	CEdit variableEdit;

private :
	float screenWidth, screenHeight;

	vector<vec3> colorArray;
	vector<vec2> area;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	GLint viewport[4];
	GLdouble modelview[16] = { 0 };
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	void SetGirthVariable(CString, vector<int>, float);
	void SetLengthVariable(CString, vector<int>, vector<Joint>);
public:
	CButton showAllBodySegment;
	CButton showHeadBodySegment;
	CButton showNeckBodySegment;
	CButton showUpperTorsoBodySegment;
	CButton showLowerTorsoBodySegment;
	CButton showUpperArmRBodySegment;
	CButton showLowerArmRBodySegment;
	CButton showHandRBodySegment;
	CButton showUpperArmLBodySegment;
	CButton showLowerArmLBodySegment;
	CButton showHandLBodySegment;
	CButton showUpperLegRBodySegment;
	CButton showLowerLegRBodySegment;
	CButton showFootRBodySegment;
	CButton showUpperLegLBodySegment;
	CButton showLowerLegLBodySegment;
	CButton showFootLBodySegment;
	CSliderCtrl landmarkSlider;
	afx_msg void OnNMReleasedcaptureLandmarkslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFront();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnLbnSelchangeLandmarklist();
	afx_msg void OnBnClickedRemoveButton();
};
