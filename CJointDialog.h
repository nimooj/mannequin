#pragma once
#include "resource.h"
#include <afxdialogex.h>

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

#include "HumanOBJ.h"
#include "Camera.h"
#include "Vertex.h"
#include "Joint.h"
#include "JointDefinition.h"

class CJointDialog :
	public CDialogEx
{
public:
	CJointDialog();
	CJointDialog(CWnd* pParent);
	enum { IDD = IDD_JOINTDIALOG };
	~CJointDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedJointdelete();
	afx_msg void OnBnClickedJointsave();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();

public:
	CListBox jointList;
	Joint currJoint;

	HGLRC m_hRC; // rendering context -- OpenGL
	CDC* m_pDC; // device context 0 -- windows
	Camera camera;

	float screenWidth, screenHeight;

	GLuint vao, joint_vao;
	GLuint position_vbo, color_vbo;
	GLuint joint_position_vbo, joint_color_vbo;
	GLuint position_attribute, color_attribute;
	GLuint joint_position_attribute, joint_color_attribute;

	GLuint ebo;
	GLuint shaderProgram, jointShaderProgram;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	GLint viewport[4];
	GLdouble modelview[16] = { 0 };
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	GLuint loadShaders(const char*, const char*);
	void defineVAO(GLuint&);
	void defineJointVAO(GLuint&);
	BOOL GetRenderingContext();
	virtual BOOL GetOldStyleRenderingContext();

	float scaleF = 1;
	mat4 scaleMatrix = mat4(1.0f);


	HumanOBJ* human;
	vector<Vertex>* vertices;
	vector<int>* indices;
	vector<Joint>* joints;

	vector<vec3> verts, color;
	vector<int> inds;

	afx_msg void OnStnClickedJointfield();
	CStatic jointField;
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedFront();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedJointUndo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	HACCEL AccelTable;
};

