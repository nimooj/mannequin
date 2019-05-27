
// mannequinDlg.h : header file
//

#pragma once

#include "Camera.h"
#include "BodyProxies.h"
#include "HumanOBJ.h"
#include "Pose.h"
#include "Size.h"
#include "Skinning.h"
//#include "iglBody.h"
#include <random>

#include "./include/GL/glew.h"
#include "./include/GL/wglew.h"
#include "./include/GL/glut.h"
#include "./include/glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "./include/glm/gtx/transform.hpp"
#include "./include/glm/gtc/type_ptr.hpp"
#include "./include/glm/gtc/matrix_transform.hpp"

using namespace glm;


#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "./lib/glew32.lib")

// CmannequinDlg dialog
class CmannequinDlg : public CDialogEx
{
// Construction
public:
	CmannequinDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANNEQUIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic paintField;
//	CStatic jointField;
private:
	HGLRC m_hRC; // rendering context -- OpenGL
	CDC* m_pDC; // device context 0 -- windows

	GLint viewport[4];
	GLdouble modelview[16] = { 0 };
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;

	/*** OPENGL 3.3 ***/
	GLuint loadShaders(const char*, const char*);
	GLuint vao, light_vao, joint_vao;
	GLuint ebo;
	GLuint mannequinShaderProgram, lightShaderProgram, jointShaderProgram;

	vector<vec3> colorArray;
	void defineMannequinVAO(GLuint&);
	void defineLightVAO(GLuint&);
	void defineJointVAO(GLuint&);
	/*****************/

	void drawBody();
	void drawJoint();

	float currARPos, currALPos;
	float currLRPos, currLLPos;

	int width;
	int height;

	BodyProxies *bodyProxies;
	HumanOBJ *human;

	Skinning *skinning;

	Pose *pose;
	Size *size;
	LayerTree* bodyLayers;
	JointTree* jointTree;

	vector<Vertex>* vertices;
	vector<int>* indices;
	vector<Vertex>* normals;

	vector<Vertex>* humanVertices;
	vector<Joint>* humanJoints;

	vec3 humanScaleFactor;
	vec3 humanTranslateFactor;

	Camera camera;

	BOOL GetRenderingContext();
	virtual BOOL GetOldStyleRenderingContext();

	BOOL makeCurrent();
	BOOL makeOldStyleCurrent();

public:
	afx_msg void OnBnClickedFront();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedMoveleft();
	afx_msg void OnBnClickedMoveright();
	afx_msg void OnBnClickedZoomin();
	afx_msg void OnBnClickedZoomout();
	afx_msg void OnStnClickedPicture2();
	CSliderCtrl armRSlider;
	CSliderCtrl armLSlider;
	afx_msg void OnNMReleasedcaptureArml(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit armLEdit;
	CEdit armREdit;
	afx_msg void OnNMReleasedcaptureArmr(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl legRSlider;
	CSliderCtrl legLSlider;
	afx_msg void OnNMReleasedcaptureLegr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureLegl(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl posNeckSlider;
	CSliderCtrl posWaistSlider;
	CSliderCtrl posHipSlider;
	afx_msg void OnNMReleasedcapturePos0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturePos1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturePos2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnEnChangeBustsize();
//	afx_msg void OnEnChangeWaistsize();
//	afx_msg void OnEnChangeHipsize();
	CEdit bustSizeEdit;
	CEdit waistSizeEdit;
	CEdit hipSizeEdit;
	afx_msg void OnBnClickedSizeset();
	afx_msg void OnBnClickedJointexport();
	CEdit heightEdit;
	CSliderCtrl elbowLSlider;
	CSliderCtrl elbowRSlider;
	CSliderCtrl kneeLSlider;
	CSliderCtrl kneeRSlider;
};
