
// mannequinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mannequin.h"
#include "mannequinDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmannequinDlg dialog

CmannequinDlg::CmannequinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANNEQUIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmannequinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, paintField);
	DDX_Control(pDX, IDC_ARMR, armRSlider);
	DDX_Control(pDX, IDC_ARML, armLSlider);
	DDX_Control(pDX, IDC_LEGR, legRSlider);
	DDX_Control(pDX, IDC_LEGL, legLSlider);
	DDX_Control(pDX, IDC_POS0, posNeckSlider);
	DDX_Control(pDX, IDC_POS1, posWaistSlider);
	DDX_Control(pDX, IDC_POS2, posHipSlider);
	DDX_Control(pDX, IDC_BUSTSIZE, bustSizeEdit);
	DDX_Control(pDX, IDC_WAISTSIZE, waistSizeEdit);
	DDX_Control(pDX, IDC_HIPSIZE, hipSizeEdit);
	DDX_Control(pDX, IDC_HEIGHT, heightEdit);
	DDX_Control(pDX, IDC_ELBOWL, elbowLSlider);
	DDX_Control(pDX, IDC_ELBOWR, elbowRSlider);
	DDX_Control(pDX, IDC_KNEEL, kneeLSlider);
	DDX_Control(pDX, IDC_KNEER, kneeRSlider);
}

BEGIN_MESSAGE_MAP(CmannequinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FRONT, &CmannequinDlg::OnBnClickedFront)
	ON_BN_CLICKED(IDC_BACK, &CmannequinDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_UP, &CmannequinDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_RIGHT, &CmannequinDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_LEFT, &CmannequinDlg::OnBnClickedLeft)
	ON_STN_CLICKED(IDC_PICTURE, &CmannequinDlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_EXPORT, &CmannequinDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDC_MOVEUP, &CmannequinDlg::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, &CmannequinDlg::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_MOVELEFT, &CmannequinDlg::OnBnClickedMoveleft)
	ON_BN_CLICKED(IDC_MOVERIGHT, &CmannequinDlg::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_ZOOMIN, &CmannequinDlg::OnBnClickedZoomin)
	ON_BN_CLICKED(IDC_ZOOMOUT, &CmannequinDlg::OnBnClickedZoomout)
	ON_STN_CLICKED(IDC_PICTURE2, &CmannequinDlg::OnStnClickedPicture2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ARML, &CmannequinDlg::OnNMReleasedcaptureArml)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ARMR, &CmannequinDlg::OnNMReleasedcaptureArmr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LEGR, &CmannequinDlg::OnNMReleasedcaptureLegr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LEGL, &CmannequinDlg::OnNMReleasedcaptureLegl)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_POS0, &CmannequinDlg::OnNMReleasedcapturePos0)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_POS1, &CmannequinDlg::OnNMReleasedcapturePos1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_POS2, &CmannequinDlg::OnNMReleasedcapturePos2)
//	ON_EN_CHANGE(IDC_BUSTSIZE, &CmannequinDlg::OnEnChangeBustsize)
//	ON_EN_CHANGE(IDC_WAISTSIZE, &CmannequinDlg::OnEnChangeWaistsize)
//	ON_EN_CHANGE(IDC_HIPSIZE, &CmannequinDlg::OnEnChangeHipsize)
	ON_BN_CLICKED(IDC_SIZESET, &CmannequinDlg::OnBnClickedSizeset)
	ON_BN_CLICKED(IDC_JOINTEXPORT, &CmannequinDlg::OnBnClickedJointexport)
END_MESSAGE_MAP()

// CmannequinDlg message handlers

BOOL CmannequinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//iglBody ib = iglBody("layers/Body.obj");

	camera = Camera();

	human = new HumanOBJ("layers/Alesia_body.obj");
	humanVertices = &human->getVerts();
	humanJoints = &human->getJoints(); // HumanJoints import

	human->setRigs(); // Set hierarchy and segment
	pose = new Pose(human); // Enable posing
	size = new Size(human); // Enable sizing

	float humanheight = human->height;
	float bust = human->getBustSize();
	float waist = human->getWaistSize();
	float hip = human->getHipSize();

	human->setThreeSize(height, bust + 10, waist + 20, hip + 10);
	bust = human->getBustSize();
	waist = human->getWaistSize();
	hip = human->getHipSize();

	humanScaleFactor = vec3(0.1f);
	humanTranslateFactor = vec3(0, -8, 0);

	vertices = &human->getVerts();
	indices = &human->getIndices();
	normals = &human->getNormals();

	for (int i = 0; i < 18; i++) {
		float r = rand() / double(RAND_MAX);
		float g = rand() / double(RAND_MAX);
		float b = rand() / double(RAND_MAX);
		colorArray.push_back(vec3(r * 10, g * 10, b * 10));
	}

	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect);
	width = rect.Width();
	height = rect.Height();
	glViewport(0, 0, width, height);

	if (!GetRenderingContext()) {
		AfxMessageBox(CString("Error in joint OpenGL initialization."));
		return FALSE;
	}

	defineLightVAO(light_vao);

	SetTimer(0, 300, NULL);

	/* Initiate Arm Slider */
	currARPos = 64;
	currALPos = 64;

	armRSlider.SetRange(55, 95);
	armLSlider.SetRange(55, 95);

	armRSlider.SetPos(currARPos);
	armLSlider.SetPos(currALPos);

	armRSlider.SetTicFreq(1);
	armLSlider.SetTicFreq(1);

	armRSlider.SetLineSize(1);
	armLSlider.SetLineSize(1);

	/* Initiate Leg Slider */
	currLRPos = 10;
	currLLPos = 10;

	legRSlider.SetRange(0, 15);
	legLSlider.SetRange(0, 15);

	legRSlider.SetPos(currLRPos);
	legLSlider.SetPos(currLLPos);

	legRSlider.SetTicFreq(1);
	legLSlider.SetTicFreq(1);

	legRSlider.SetLineSize(1);
	legLSlider.SetLineSize(1);

	/* Initiate Pos Slider */
	posNeckSlider.SetRange(-2, 2);
	posWaistSlider.SetRange(-3, 3);
	posHipSlider.SetRange(-3, 3);

	posNeckSlider.SetLineSize(1);
	posWaistSlider.SetLineSize(1);
	posHipSlider.SetLineSize(1);

	posNeckSlider.SetTicFreq(1);
	posWaistSlider.SetTicFreq(1);
	posHipSlider.SetTicFreq(1);

	/* Initiate Size Edit */
	CString ctr;
	ctr.Format(_T("%.3f"), humanheight);
	heightEdit.SetWindowTextW(ctr);

	ctr.Format(_T("%.3f"), bust);
	bustSizeEdit.SetWindowTextW(ctr);

	ctr.Format(_T("%.3f"), waist);
	waistSizeEdit.SetWindowTextW(ctr);

	ctr.Format(_T("%.3f"), hip);
	hipSizeEdit.SetWindowTextW(ctr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmannequinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmannequinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmannequinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmannequinDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	/*** OPENGL 3.3 ***/
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &light_vao);
	glDeleteVertexArrays(1, &joint_vao);
	glDeleteBuffers(1, &ebo);
	/*****************/

	if (FALSE == ::wglDeleteContext(m_hRC)) {
		AfxMessageBox(CString("wglDeleteContext failed"));
	}
}

void CmannequinDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 0) {
		makeCurrent();
		drawBody();
		SwapBuffers(m_pDC->GetSafeHdc());
	}
}

void CmannequinDlg::drawBody() {
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	defineMannequinVAO(vao);

	vec3 pos = camera.cameraPosition;
	vec3 dir = camera.cameraFront;
	vec3 up = camera.cameraUp;

	//vec3 color = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightColor = vec3(0.8f, 0.8f, 0.8f);
	vec3 lightPos = vec3(0.0f, 10.0f, 15.0f);
	vec3 cameraPos = pos;

	/*** Draw Body ***/
	glUseProgram(mannequinShaderProgram);
	//GLint color_attribute = glGetUniformLocation(mannequinShaderProgram, "objColor");
	//glUniform3fv(color_attribute, 1, &color[0]);
	GLint lightColor_attribute = glGetUniformLocation(mannequinShaderProgram, "lightColor");
	glUniform3fv(lightColor_attribute, 1, &lightColor[0]);
	GLint lightPos_attribute = glGetUniformLocation(mannequinShaderProgram, "lightPos");
	glUniform3fv(lightPos_attribute, 1, &lightPos[0]);
	GLint cameraPos_attribute = glGetUniformLocation(mannequinShaderProgram, "cameraPos");
	glUniform3fv(cameraPos_attribute, 1, &cameraPos[0]);

	//mat4 projectionMatrix = perspective((float)radians(45.0f), width2 / (float)height2, 0.1f, 300.0f);
	projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.f, 0.0f, 100.0f);
	viewMatrix = lookAt(pos, dir, up);
	modelMatrix = mat4(1.0f);

	/*
	mat4 scaleMatrix = scale(humanScaleFactor);
	mat4 translateMatrix = translate(humanTranslateFactor);
	mat4 modelMatrix =  translateMatrix * scaleMatrix * mat4(1.0f);
	*/
	GLuint projectionID = glGetUniformLocation(mannequinShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	GLuint viewID = glGetUniformLocation(mannequinShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	GLuint modelID = glGetUniformLocation(mannequinShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
	/*****************/

	/*** Draw Joints ***/
	defineJointVAO(joint_vao);

	glUseProgram(jointShaderProgram);
	projectionID = glGetUniformLocation(jointShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	viewID = glGetUniformLocation(jointShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	modelID = glGetUniformLocation(jointShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

	glPointSize(5);
	glBindVertexArray(joint_vao);
	glDrawArrays(GL_POINTS, 0, humanJoints->size());
	/*
	*/
	/*******************/
}

void CmannequinDlg::drawJoint() {
	defineJointVAO(joint_vao);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3 pos = camera.cameraPosition;
	vec3 dir = camera.cameraFront;
	vec3 up = camera.cameraUp;
	mat4 projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.f, 0.0f, 100.0f);
	mat4 viewMatrix = lookAt(pos, dir, up);
	mat4 modelMatrix =  mat4(1.0f);

	glUseProgram(jointShaderProgram);
	GLuint projectionID = glGetUniformLocation(jointShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	GLuint viewID = glGetUniformLocation(jointShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	GLuint modelID = glGetUniformLocation(jointShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

	glPointSize(5);
	glBindVertexArray(joint_vao);
	glDrawArrays(GL_POINTS, 0, humanJoints->size());
}

void CmannequinDlg::defineMannequinVAO(GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	mannequinShaderProgram = loadShaders("shaders/MannequinVertexShader.vertexshader", "shaders/MannequinFragmentShader.fragmentshader");

	vector<vec3> position, normal;
	vector<int> indexing;

	for (int i = 0; i < vertices->size(); i++) {
		Vertex bv = (*vertices)[i];
		position.push_back(vec3(bv.x, bv.y, bv.z));
	}

	for (int i = 0; i < normals->size(); i++) {
		Vertex nv = (*normals)[i];
		normal.push_back(vec3(nv.x, nv.y, nv.z));
	}
	
	for (int i = 0; i < indices->size(); i++) {
		indexing.push_back((*indices)[i] - 1);
	}

	vector<vec3> color;
	for (int i = 0; i < vertices->size(); i++) {

		if (abs((*vertices)[i].y - human->waistLevel) < 0.1)
			color.push_back(vec3(1, 0, 0));
		else if (abs((*vertices)[i].y - human->bustLevel) < 0.1)
			color.push_back(vec3(1, 0, 0));
		else if (abs((*vertices)[i].y - human->hipLevel) < 0.1)
			color.push_back(vec3(1, 0, 0));
		else 
			color.push_back(vec3(1, 1, 1));
	}

	/*
	Skinning skinning = human->skinning;
	for (int i = 0; i < skinning.armRSegment.size(); i++) {
		color[skinning.armRSegment[i]] = vec3(1, 0, 0);
		if (human->vertices[skinning.armRSegment[i]].jointsRelated.size() != 1) {
			for (int j = 0; j < human->vertices[skinning.armRSegment[i]].jointsRelated.size(); j++) {
				if (human->vertices[skinning.armRSegment[i]].jointsRelated[j] == Joint_shoulderR) { 
					if (human->vertices[skinning.armRSegment[i]].jointWeights[j] > 0.5)
						color[skinning.armRSegment[i]] = vec3(1, 1, 0);
					else if (human->vertices[skinning.armRSegment[i]].jointWeights[j] <= 0.5)
						color[skinning.armRSegment[i]] = vec3(0, 0, 1);
				}
			}
		}
	}

	for (int i = 0; i < skinning.armLSegment.size(); i++) {
		color[skinning.armLSegment[i]] = vec3(1, 0, 0);
		if (human->vertices[skinning.armLSegment[i]].jointsRelated.size() != 1) {
			for (int j = 0; j < human->vertices[skinning.armLSegment[i]].jointsRelated.size(); j++) {
				if (human->vertices[skinning.armLSegment[i]].jointsRelated[j] == Joint_shoulderL) { 
					if (human->vertices[skinning.armLSegment[i]].jointWeights[j] > 0.5)
						color[skinning.armLSegment[i]] = vec3(1, 1, 0);
					else if (human->vertices[skinning.armLSegment[i]].jointWeights[j] <= 0.5)
						color[skinning.armLSegment[i]] = vec3(0, 0, 1);
				}
			}
		}
	}

	for (int i = 0; i < skinning.legRSegment.size(); i++) {
		color[skinning.legRSegment[i]] = vec3(1, 0, 0);
		if (human->vertices[skinning.legRSegment[i]].jointsRelated.size() != 1) {
			for (int j = 0; j < human->vertices[skinning.legRSegment[i]].jointsRelated.size(); j++) {
				if (human->vertices[skinning.legRSegment[i]].jointsRelated[j] == Joint_pelvisR) { 
					if (human->vertices[skinning.legRSegment[i]].jointWeights[j] > 0.5)
						color[skinning.legRSegment[i]] = vec3(1, 1, 0);
					else if (human->vertices[skinning.legRSegment[i]].jointWeights[j] <= 0.5)
						color[skinning.legRSegment[i]] = vec3(0, 0, 1);
				}
			}
		}
	}

	for (int i = 0; i < skinning.legLSegment.size(); i++) {
		color[skinning.legLSegment[i]] = vec3(1, 0, 0);
		if (human->vertices[skinning.legLSegment[i]].jointsRelated.size() != 1) {
			for (int j = 0; j < human->vertices[skinning.legLSegment[i]].jointsRelated.size(); j++) {
				if (human->vertices[skinning.legLSegment[i]].jointsRelated[j] == Joint_pelvisL) { 
					if (human->vertices[skinning.legLSegment[i]].jointWeights[j] > 0.5)
						color[skinning.legLSegment[i]] = vec3(1, 1, 0);
					else if (human->vertices[skinning.legLSegment[i]].jointWeights[j] <= 0.5)
						color[skinning.legLSegment[i]] = vec3(0, 0, 1);
				}
			}
		}
	}
	*/

	// Position
	GLuint position_vbo;
	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), &position[0], GL_STATIC_DRAW);

	GLint position_attribute = glGetAttribLocation(mannequinShaderProgram, "position");
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	// Color for different segment parts
	GLuint color_vbo;
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), &color[0], GL_STATIC_DRAW);
	GLint color_attribute = glGetAttribLocation(mannequinShaderProgram, "color");
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	// Normal
	GLuint normal_vbo;
	glGenBuffers(1, &normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(vec3), &normal[0], GL_STATIC_DRAW);

	GLint normal_attribute = glGetAttribLocation(mannequinShaderProgram, "normal");
	glVertexAttribPointer(normal_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normal_attribute);
	
	// Indexing
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexing.size() * sizeof(int), &indexing[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void CmannequinDlg::defineLightVAO(GLuint& light_vao) {
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);

	lightShaderProgram = loadShaders("shaders/LightVertexShader.vertexshader", "shaders/LightFragmentShader.fragmentshader");

	vector<vec3> light_cube;

	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));

	light_cube.push_back(vec3(-0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, 0.5f));

	light_cube.push_back(vec3(-0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, 0.5f));

	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));

	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, -0.5f, -0.5f));

	light_cube.push_back(vec3(-0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, -0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, 0.5f));
	light_cube.push_back(vec3(-0.5f, 0.5f, -0.5f));

	GLuint position_vbo;
	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, light_cube.size() * sizeof(vec3), &light_cube[0], GL_STATIC_DRAW);

	GLint position_attribute = glGetAttribLocation(lightShaderProgram, "position");
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	glBindVertexArray(0);
}

void CmannequinDlg::defineJointVAO(GLuint& joint_vao) {
	glGenVertexArrays(1, &joint_vao);
	glBindVertexArray(joint_vao);

	jointShaderProgram = loadShaders("shaders/JointVertexShader.vertexshader", "shaders/JointFragmentShader.fragmentshader");

	vector<vec3> joints;

	for ( int i = 0; i < humanJoints->size(); i++ ) {
		Vertex v = (*humanJoints)[i].getCoord();
		joints.push_back(vec3(v.x, v.y, v.z));
	}

	/*
	for (int i = 0; i < jointTree->getSize(); i++) {
		Joint joint = jointTree->at(i);
		Vertex jv = joint.getCoord();

		joints.push_back(vec3(jv.x, jv.y, jv.z));
	}
	*/

	if (!joints.empty()) {
		GLuint position_vbo;
		glGenBuffers(1, &position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
		glBufferData(GL_ARRAY_BUFFER, joints.size() * sizeof(vec3), &joints[0], GL_STATIC_DRAW);

		GLint position_attribute = glGetAttribLocation(jointShaderProgram, "position");
		glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(position_attribute);

		glBindVertexArray(0);
	}
}

GLuint CmannequinDlg::loadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
	// Create shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader from file
	string vertexShaderSource;
	ifstream vertexShaderStream(vertexFilePath, ios::in);
	if (vertexShaderStream.is_open() ) {
		stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderSource = sstr.str();
		vertexShaderStream.close();
	}
	else {
		AfxMessageBox(CString("Unable to open " + *vertexFilePath));
		return -1;
	}

	string fragmentShaderSource;
	ifstream fragmentShaderStream(fragmentFilePath, ios::in);
	if (fragmentShaderStream.is_open() ) {
		stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderSource = sstr.str();
		fragmentShaderStream.close();
	}
	else {
		AfxMessageBox(CString("Unable to open " + *fragmentFilePath));
		return -1;
	}

	GLint success;
	GLchar infoLog[512];

	// Compile Vertex shader
	char const * vertexShaderPointer = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderPointer, NULL);
	glCompileShader(vertexShader);

	// Check vertex Shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: vertex shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
	}

	// Compile Fragment shader
	const char * fragmentShaderPointer = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderPointer, NULL);
	glCompileShader(fragmentShader);

	// Check fragment Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: fragment shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
	}

	// Linking to program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

		TRACE(CString("ERROR: shader program 연결 실패 ") + CString(infoLog) + CString("\n"));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void CmannequinDlg::OnStnClickedPicture2()
{
	/*** Convertsion to openGL coordinates ***/
	// TODO: Add your control notification handler code here
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect);

	float width = rect.Width();
	float height = rect.Height();

	//ScreenToClient(&rect2); // For mouse event
	CPoint point;

	if (rect.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_PICTURE2)->ScreenToClient(&point);

		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);

		winX = (float)point.x;
		winY = (float)viewport[3] - (float)point.y;

		glReadPixels(point.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

		// Conversion to Object coordinate
		//  model iverse * viewMatrix inverse * project inverse * cursor pos = new Pos in object coordinate
		vec4 npos = vec4(posX, posY, posZ, 1);
		vec4 newPos = inverse(modelMatrix) * inverse(viewMatrix) * inverse(projectionMatrix) * npos;

		// posX, posY, posZ ... World coordinates
		//human->setJoint(posX, posY);
		human->setJoint(humanJoints->size(), newPos[0], newPos[1]);
	}
}

void CmannequinDlg::OnNMReleasedcaptureArmr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = armRSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	human->skinning.rotateAR(Joint_shoulderR, -(pos - currARPos), *vertices, *humanJoints);;
	currARPos = pos;
}

void CmannequinDlg::OnNMReleasedcaptureArml(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = armLSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	//pose->rotate(Joint_shoulderL, axisZ, Left, (float) pos);
	human->skinning.rotateAL(Joint_shoulderR, pos - currALPos, *vertices, *humanJoints);;
	currALPos = pos;
}

void CmannequinDlg::OnNMReleasedcaptureLegr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int pos = legRSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	//pose->rotate(Joint_pelvisR, axisZ, Right, (float) pos);
	human->skinning.rotateLR(Joint_pelvisR, -(pos - currLRPos), *vertices, *humanJoints);;
	currLRPos = pos;
}

void CmannequinDlg::OnNMReleasedcaptureLegl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = legLSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	//pose->rotate(Joint_pelvisL, axisZ, Left, (float) pos);
	human->skinning.rotateLL(Joint_pelvisL, (pos - currLLPos), *vertices, *humanJoints);;
	currLLPos = pos;
}

void CmannequinDlg::OnNMReleasedcapturePos0(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int pos = posNeckSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	pose->translate(Joint_neck, 0, 0, -pos/(float)10);
}

void CmannequinDlg::OnNMReleasedcapturePos1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = posWaistSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	pose->translate(Joint_waist, 0, 0, -pos/(float)10);
}

void CmannequinDlg::OnNMReleasedcapturePos2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = posHipSlider.GetPos();

	CString ctr;
	ctr.Format(_T("%d"), pos);

	pose->translate(Joint_pelvisMid, 0, 0, -pos/(float)10);
}

void CmannequinDlg::OnBnClickedSizeset()
{
	// TODO: Add your control notification handler code here

	CString ctr;
	heightEdit.GetWindowTextW(ctr);
	float posHeight = _ttof(ctr);

	bustSizeEdit.GetWindowTextW(ctr);
	float posB = _ttof(ctr);

	waistSizeEdit.GetWindowTextW(ctr);
	float posW = _ttof(ctr);


	hipSizeEdit.GetWindowTextW(ctr);
	float posH = _ttof(ctr);

	//size->setSize(Bust, posB);
	//size->setSize(Waist, posW);
	//size->setSize(Hip, posH);
	human->setThreeSize(posHeight, posB, posW, posH);
}

void CmannequinDlg::OnBnClickedFront()
{
	// TODO: Add your control notification handler code here
	camera.ViewFront();
	drawBody();
}

void CmannequinDlg::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	camera.ViewBack();
	drawBody();
}

void CmannequinDlg::OnBnClickedUp()
{
	// TODO: Add your control notification handler code here
	camera.ViewUp();
}

void CmannequinDlg::OnBnClickedRight()
{
	// TODO: Add your control notification handler code here
	camera.ViewRight();
	drawBody();
}

void CmannequinDlg::OnBnClickedLeft()
{
	// TODO: Add your control notification handler code here
	camera.ViewLeft();
	drawBody();
}

void CmannequinDlg::OnStnClickedPicture()
{
	// TODO: Add your control notification handler code here
}

void CmannequinDlg::OnBnClickedExport()
{
	// TODO: Add your control notification handler code here
	//bodyProxies->writeToOBJ(vertices, indices, normals);
	human->writeToOBJ();
}

void CmannequinDlg::OnBnClickedMoveup()
{
	// TODO: Add your control notification handler code here
	camera.MoveUp();
}

void CmannequinDlg::OnBnClickedMovedown()
{
	// TODO: Add your control notification handler code here
	camera.MoveDown();
}

void CmannequinDlg::OnBnClickedMoveleft()
{
	// TODO: Add your control notification handler code here
	camera.MoveLeft();
}

void CmannequinDlg::OnBnClickedMoveright()
{
	// TODO: Add your control notification handler code here
	camera.MoveRight();
}

void CmannequinDlg::OnBnClickedZoomin()
{
	// TODO: Add your control notification handler code here
	camera.ZoomIn();
}

void CmannequinDlg::OnBnClickedZoomout()
{
	// TODO: Add your control notification handler code here
	camera.ZoomOut();
}

BOOL CmannequinDlg::GetRenderingContext()
{
	//픽처 컨트롤에만 그리도록 DC 생성
	//참고 https://goo.gl/CK36zE
	CWnd* pImage = GetDlgItem(IDC_PICTURE);
	CRect rc;
	pImage->GetWindowRect(rc);
	m_pDC = pImage->GetDC();


	if (NULL == m_pDC)
	{
		AfxMessageBox(CString("Unable to get a DC"));
		return FALSE;
	}

	if (!GetOldStyleRenderingContext())
	{
		return TRUE;
	}

	//Get access to modern OpenGL functionality from this old style context.
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		AfxMessageBox(CString("GLEW could not be initialized!"));
		return FALSE;
	}

	//참고 http://gamedev.stackexchange.com/a/30443
	GLint attribs[] =
	{
		//OpenGL 3.3 사용
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		// Uncomment this for forward compatibility mode
		//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		// Uncomment this for Compatibility profile
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		// We are using Core profile here
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};


	HGLRC CompHRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	if (CompHRC && wglMakeCurrent(m_pDC->GetSafeHdc(), CompHRC))
		m_hRC = CompHRC;

	return TRUE;
}

BOOL CmannequinDlg::GetOldStyleRenderingContext() {
	//A generic pixel format descriptor. This will be replaced with a more
	//specific and modern one later, so don't worry about it too much.
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		32,                             // 32-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		24,                        // 24-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	// Get the id number for the best match supported by the hardware device context
	// to what is described in pfd
	int pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	//If there's no match, report an error
	if (0 == pixelFormat)
	{
		AfxMessageBox(CString("ChoosePixelFormat failed"));
		return FALSE;
	}

	//If there is an acceptable match, set it as the current 
	if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	{
		AfxMessageBox(CString("SetPixelFormat failed"));
		return FALSE;
	}

	//Create a context with this pixel format
	if (0 == (m_hRC = wglCreateContext(m_pDC->GetSafeHdc())))
	{
		AfxMessageBox(CString("wglCreateContext failed"));
		return FALSE;
	}

	//Make it current. 
	if (FALSE == wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
	{
		AfxMessageBox(CString("wglMakeCurrent failed"));
		return FALSE;
	}

	return TRUE;
}

BOOL CmannequinDlg::makeCurrent() {
	if (!makeOldStyleCurrent())
	{
		AfxMessageBox(CString("wglMakeCurrent failed"));
		return FALSE;
	}

	GLint attribs[] =
	{
		//OpenGL 3.3 사용
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		// Uncomment this for forward compatibility mode
		//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		// Uncomment this for Compatibility profile
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		// We are using Core profile here
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};


	HGLRC CompHRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	if (CompHRC && wglMakeCurrent(m_pDC->GetSafeHdc(), CompHRC))
		m_hRC = CompHRC;

	return TRUE;
}

BOOL CmannequinDlg::makeOldStyleCurrent() {
	if (FALSE == wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
	{
		return FALSE;
	}
	return TRUE;
}

void CmannequinDlg::OnBnClickedJointexport()
{
	// TODO: Add your control notification handler code here
	human->jointExport();
}
