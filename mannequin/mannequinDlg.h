#pragma once

#include "Camera.h"
#include "BodyProxies.h"
#include "HumanOBJ.h"
#include "Pose.h"
#include "Size.h"
#include "Skinning.h"
#include "Landmark.h"

#include "CJointDialog.h"
#include "CLandmarkDialog.h"
#include "CEditLandmarkDialog.h"
#include "CDefaultSizesDialog.h"

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
	CString pathName;
	CString jpathName;
	CString filepath_filename;

	CJointDialog* jointDlg;
	CLandmarkDialog* landmarkDlg;
	CEditLandmarkDialog* editLandmarkDlg;
	CDefaultSizesDialog* defaultSizesDlg;

	float scaleF = 1;

	int drawMode = 0;
	int jointDefineMode = 0;
	int landmarkDefineMode = 0;

	int showWireframeMode = 0;
	int showCrotch = 0;

	int showJointsMode = 0;
	int showLandmarksMode = 0;

	int showArmWeightMode = 0;
	int showElbowWeightMode = 0;

	int showLegWeightMode = 0;
	int showKneeWeightMode = 0;

	HGLRC m_hRC; // rendering context -- OpenGL
	CDC* m_pDC; // device context 0 -- windows

	void InitEditField();
	void EnableDeformation();

	GLint viewport[4];
	GLdouble modelview[16] = { 0 };
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	vec3 scaleFactor = vec3(1, 1, 1);
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 scaleMatrix = mat4(1.0f);
	mat4 modelMatrix;

	/*** OPENGL 3.3 ***/
	GLuint loadShaders(const char*, const char*);
	GLuint vao, joint_vao, landmark_vao;
	GLuint ebo, joint_ebo;
	GLuint mannequinShaderProgram, jointShaderProgram, landmarkShaderProgram;

	GLuint tex;

	GLuint underwear_vao, underwear_vbo, underwear_ebo;
	GLuint underwearShaderProgram;

	GLuint position_vbo, color_vbo, normal_vbo, texture_vbo;
	GLuint position_attribute, color_attribute, normal_attribute, texture_attribute;

	GLuint joint_position_vbo;
	GLuint joint_position_attribute;

	GLuint landmark_position_vbo;
	GLuint landmark_position_attribute;
	GLuint landmark_color_vbo;
	GLuint landmark_color_attribute;

	void defineMannequinVAO(GLuint&);
	void defineJointVAO(GLuint&);
	void defineLandmarkVAO(int, GLuint&);
	void defineUnderwearVAO(GLuint&, vector<float>);

	int isBra = 0;
	int isUnderpants = 0;
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

	vector<Landmark>* landmarkVariables;

	BOOL GetRenderingContext();
	virtual BOOL GetOldStyleRenderingContext();

	BOOL makeCurrent();
	BOOL makeOldStyleCurrent();

	int selItem = -1;

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
//	CEdit armLEdit;
//	CEdit armREdit;
	afx_msg void OnNMReleasedcaptureArmr(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl legRSlider;
	CSliderCtrl legLSlider;
	afx_msg void OnNMReleasedcaptureLegr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureLegl(NMHDR *pNMHDR, LRESULT *pResult);
//	CEdit bustSizeEdit;
//	CEdit waistSizeEdit;
//	CEdit hipSizeEdit;
//	afx_msg void OnBnClickedSizeset();
//	CEdit heightEdit;
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
//	CEdit kneeWidthEdit;
//	CEdit neck2waistEdit;
//	CEdit waist2hipEdit;
//	CEdit armLengthEdit;
	afx_msg void OnFileOpen();
	CProgressCtrl progressBar;
	afx_msg void OnStnClickedPicture();
	afx_msg void OnDefineJoints();
	afx_msg void OnJointsRemoveall();
	afx_msg void OnFileExport();
	afx_msg void OnJointsSave();
	afx_msg void OnJointsLoad();
	CListCtrl sizeControl;
	afx_msg void OnLandmarksDefine();
	afx_msg void OnUpdateModeAdvanced(CCmdUI *pCmdUI);
	HACCEL AccelTable;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnScaleout();
	afx_msg void OnScalein();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnJointUndo();
	CButton showLandmarks;
	afx_msg void OnLandmarksSave();
	afx_msg void OnLandmarksLoad();
	CButton showJoints;
	afx_msg void OnBnClickedCheckLandmarks();
	afx_msg void OnBnClickedCheckJoints();
	afx_msg void OnNMDblclkSizelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSizelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckWireframe();
	CButton showWireframe;
	afx_msg void OnModifySetthreesize();
	afx_msg void OnArmsShoulders();
	afx_msg void OnArmsElbos();
	afx_msg void OnLegsPelvis();
	afx_msg void OnLegsKnee();
	CButton showArmWeight;
	CButton showElbowWeight;
	CButton showUpperLegWeight;
	CButton showLowerLegWeight;
	afx_msg void OnBnClickedCheckArmWeight();
	afx_msg void OnBnClickedCheckElbowWeight();
	afx_msg void OnBnClickedCheckLegWeight();
	afx_msg void OnBnClickedCheckKneeWeight();
	afx_msg void OnViewInitialize();
	CButton axisXradio;
	CButton axisYradio;
	CButton axisZradio;
	afx_msg void OnViewFitto();
	afx_msg void OnDressformWholetights();
	afx_msg void OnDressformDress();
	afx_msg void OnDressformTop();
	afx_msg void OnDressformPants();
	afx_msg void OnDressformSkirt();
	afx_msg void OnJointsPoseexport();
	afx_msg void OnPosePoseload();
	afx_msg void OnJointsMirror();
	afx_msg void OnJointsExpand();
	afx_msg void OnFileExporthuman();
	afx_msg void OnLvnItemchangedSizelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTextureSelectarea();
	afx_msg void OnBnClickedShowcrotch();
	afx_msg void OnTextureSetbra();
	afx_msg void OnTextureSetunderpants();
};
