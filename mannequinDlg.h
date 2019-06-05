
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
#include "./include/FreeImage.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "./include/glm/gtx/transform.hpp"
#include "./include/glm/gtc/type_ptr.hpp"
#include "./include/glm/gtc/matrix_transform.hpp"

using namespace glm;


#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "./lib/glew32.lib")
#pragma comment(lib, "./lib/FreeImage.lib")

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

	int jointDefineMode = 0;

	static UINT loadThread(LPVOID);
	CString pathName;
	HGLRC m_hRC; // rendering context -- OpenGL
	CDC* m_pDC; // device context 0 -- windows

	void InitEditField();
	void EnableDeformation();

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
	GLuint ebo, joint_ebo;
	GLuint mannequinShaderProgram, lightShaderProgram, jointShaderProgram;

	int defineMannequinVAO(GLuint&);
	void defineLightVAO(GLuint&);
	void defineJointVAO(GLuint&);
	/*****************/

	void drawBody();
	void drawJoint();

	float currArmRPos, currArmLPos;
	float currElbowRPos, currElbowLPos;
	float currLegRPos, currLegLPos;
	float currKneeRPos, currKneeLPos;
	float currBentPos, currBentPos2;

	vector<vec3> colorArray;

	int width;
	int height;
	float aspectRatio;

	Camera camera;
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
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedMoveleft();
	afx_msg void OnBnClickedMoveright();
	afx_msg void OnBnClickedZoomin();
	afx_msg void OnBnClickedZoomout();
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
	CEdit bustSizeEdit;
	CEdit waistSizeEdit;
	CEdit hipSizeEdit;
	afx_msg void OnBnClickedSizeset();
	CEdit heightEdit;
	CSliderCtrl elbowLSlider;
	CSliderCtrl elbowRSlider;
	CSliderCtrl kneeLSlider;
	CSliderCtrl kneeRSlider;
	CSliderCtrl posBentSlider;
	afx_msg void OnNMReleasedcaptureBentslider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureElbowr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureElbowl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureKneer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureKneel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureBentslider2(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl posBentSlider2;
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
	CEdit kneeWidthEdit;
	CEdit neck2waistEdit;
	CEdit waist2hipEdit;
	CEdit armLengthEdit;
	afx_msg void OnFileOpen();
	CProgressCtrl progressBar;
	afx_msg void OnStnClickedPicture();
	afx_msg void OnDefineJoints();
	afx_msg void OnJointsRemoveall();
	afx_msg void OnFileExport();
	afx_msg void OnJointsSave();
	afx_msg void OnJointsLoad();
};
