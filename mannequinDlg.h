
// mannequinDlg.h : header file
//

#pragma once

#include "Camera.h"
//#include "Body.h"
#include "BodyProxies.h"

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
private:
	HGLRC m_hRC;
	CDC* m_pDC;

	/*** OPENGL 3.3 ***/
	GLuint vao, light_vao;
	GLuint ebo;
	GLuint mannequinShaderProgram, lightShaderProgram;
	void defineMannequinVAO(GLuint&);
	void defineLightVAO(GLuint&);
	GLuint loadShaders(const char*, const char*);
	/*****************/

	int width;
	int height;

	vector<Vertex> vertices;
	vector<int> indices;
	vector<Vertex> normals;

	Camera camera;
	BodyProxies bodyProxies;
	LayerTree bodyLayers;
	JointTree jointTree;

	BOOL GetRenderingContext();
	virtual BOOL GetOldStyleRenderingContext();
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
};
