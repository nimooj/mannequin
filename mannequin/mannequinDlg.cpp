
// mannequinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mannequin.h"
#include "mannequinDlg.h"
#include "afxdialogex.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./include/stb_image.h"


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
	DDX_Control(pDX, IDC_ELBOWL, elbowLSlider);
	DDX_Control(pDX, IDC_ELBOWR, elbowRSlider);
	DDX_Control(pDX, IDC_KNEEL, kneeLSlider);
	DDX_Control(pDX, IDC_KNEER, kneeRSlider);
	DDX_Control(pDX, IDC_BENTSLIDER, posBentSlider);
	DDX_Control(pDX, IDC_BENTSLIDER2, posBentSlider2);
	DDX_Control(pDX, IDC_CHECK1, showAllBodySegment);
	DDX_Control(pDX, IDC_CHECK2, showHeadBodySegment);
	DDX_Control(pDX, IDC_CHECK16, showNeckBodySegment);
	DDX_Control(pDX, IDC_CHECK15, showUpperTorsoBodySegment);
	DDX_Control(pDX, IDC_CHECK17, showLowerTorsoBodySegment);
	DDX_Control(pDX, IDC_CHECK13, showUpperArmRBodySegment);
	DDX_Control(pDX, IDC_CHECK14, showLowerArmRBodySegment);
	DDX_Control(pDX, IDC_CHECK12, showHandRBodySegment);
	DDX_Control(pDX, IDC_CHECK19, showUpperArmLBodySegment);
	DDX_Control(pDX, IDC_CHECK20, showLowerArmLBodySegment);
	DDX_Control(pDX, IDC_CHECK18, showHandLBodySegment);
	DDX_Control(pDX, IDC_CHECK22, showUpperLegRBodySegment);
	DDX_Control(pDX, IDC_CHECK23, showLowerLegRBodySegment);
	DDX_Control(pDX, IDC_CHECK21, showFootRBodySegment);
	DDX_Control(pDX, IDC_CHECK25, showUpperLegLBodySegment);
	DDX_Control(pDX, IDC_CHECK26, showLowerLegLBodySegment);
	DDX_Control(pDX, IDC_CHECK24, showFootLBodySegment);
	DDX_Control(pDX, IDC_PROGRESS1, progressBar);
	DDX_Control(pDX, IDC_SIZELIST, sizeControl);
	DDX_Control(pDX, IDC_CHECK_LANDMARKS, showLandmarks);
	DDX_Control(pDX, IDC_CHECK_JOINTS, showJoints);
	DDX_Control(pDX, IDC_CHECK_WIREFRAME, showWireframe);
	DDX_Control(pDX, IDC_CHECK_ARM_WEIGHT, showArmWeight);
	DDX_Control(pDX, IDC_CHECK_ELBOW_WEIGHT, showElbowWeight);
	DDX_Control(pDX, IDC_CHECK_LEG_WEIGHT, showUpperLegWeight);
	DDX_Control(pDX, IDC_CHECK_KNEE_WEIGHT, showLowerLegWeight);
	DDX_Control(pDX, IDC_AXIS_X, axisXradio);
	DDX_Control(pDX, IDC_AXIS_Y, axisYradio);
	DDX_Control(pDX, IDC_AXIS_Z, axisZradio);
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
//	ON_STN_CLICKED(IDC_PICTURE, &CmannequinDlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_MOVEUP, &CmannequinDlg::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, &CmannequinDlg::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_MOVELEFT, &CmannequinDlg::OnBnClickedMoveleft)
	ON_BN_CLICKED(IDC_MOVERIGHT, &CmannequinDlg::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_ZOOMIN, &CmannequinDlg::OnBnClickedZoomin)
	ON_BN_CLICKED(IDC_ZOOMOUT, &CmannequinDlg::OnBnClickedZoomout)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ARML, &CmannequinDlg::OnNMReleasedcaptureArml)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ARMR, &CmannequinDlg::OnNMReleasedcaptureArmr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LEGR, &CmannequinDlg::OnNMReleasedcaptureLegr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LEGL, &CmannequinDlg::OnNMReleasedcaptureLegl)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_BENTSLIDER, &CmannequinDlg::OnNMReleasedcaptureBentslider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ELBOWR, &CmannequinDlg::OnNMReleasedcaptureElbowr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ELBOWL, &CmannequinDlg::OnNMReleasedcaptureElbowl)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_KNEER, &CmannequinDlg::OnNMReleasedcaptureKneer)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_KNEEL, &CmannequinDlg::OnNMReleasedcaptureKneel)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_BENTSLIDER2, &CmannequinDlg::OnNMReleasedcaptureBentslider2)
//	ON_COMMAND(IDR_MENU1, &CmannequinDlg::OnIdrMenu1)
ON_COMMAND(ID_FILE_OPEN, &CmannequinDlg::OnFileOpen)
ON_STN_CLICKED(IDC_PICTURE, &CmannequinDlg::OnStnClickedPicture)
ON_COMMAND(ID_DEFINE_JOINTS, &CmannequinDlg::OnDefineJoints)
ON_COMMAND(ID_JOINTS_REMOVEALL, &CmannequinDlg::OnJointsRemoveall)
ON_COMMAND(ID_FILE_EXPORT, &CmannequinDlg::OnFileExport)
ON_COMMAND(ID_JOINTS_SAVE, &CmannequinDlg::OnJointsSave)
ON_COMMAND(ID_JOINTS_LOAD, &CmannequinDlg::OnJointsLoad)
ON_COMMAND(ID_LANDMARKS_DEFINE, &CmannequinDlg::OnLandmarksDefine)
ON_UPDATE_COMMAND_UI(ID_MODE_ADVANCED32785, &CmannequinDlg::OnUpdateModeAdvanced)
ON_COMMAND(ID_SCALEOUT, &CmannequinDlg::OnScaleout)
ON_COMMAND(ID_SCALEIN, &CmannequinDlg::OnScalein)
ON_COMMAND(ID_VIEW_ZOOMIN, &CmannequinDlg::OnViewZoomin)
ON_COMMAND(ID_VIEW_ZOOMOUT, &CmannequinDlg::OnViewZoomout)
ON_COMMAND(ID_JOINT_UNDO, &CmannequinDlg::OnJointUndo)
ON_COMMAND(ID_LANDMARKS_SAVE, &CmannequinDlg::OnLandmarksSave)
ON_COMMAND(ID_LANDMARKS_LOAD, &CmannequinDlg::OnLandmarksLoad)
ON_BN_CLICKED(IDC_CHECK_LANDMARKS, &CmannequinDlg::OnBnClickedCheckLandmarks)
ON_BN_CLICKED(IDC_CHECK_JOINTS, &CmannequinDlg::OnBnClickedCheckJoints)
ON_NOTIFY(NM_DBLCLK, IDC_SIZELIST, &CmannequinDlg::OnNMDblclkSizelist)
ON_NOTIFY(NM_CLICK, IDC_SIZELIST, &CmannequinDlg::OnNMClickSizelist)
ON_BN_CLICKED(IDC_CHECK_WIREFRAME, &CmannequinDlg::OnBnClickedCheckWireframe)
ON_COMMAND(ID_MODIFY_SETTHREESIZE, &CmannequinDlg::OnModifySetthreesize)
ON_BN_CLICKED(IDC_CHECK_ARM_WEIGHT, &CmannequinDlg::OnBnClickedCheckArmWeight)
ON_BN_CLICKED(IDC_CHECK_ELBOW_WEIGHT, &CmannequinDlg::OnBnClickedCheckElbowWeight)
ON_BN_CLICKED(IDC_CHECK_LEG_WEIGHT, &CmannequinDlg::OnBnClickedCheckLegWeight)
ON_BN_CLICKED(IDC_CHECK_KNEE_WEIGHT, &CmannequinDlg::OnBnClickedCheckKneeWeight)
ON_COMMAND(ID_VIEW_INITIALIZE, &CmannequinDlg::OnViewInitialize)
ON_COMMAND(ID_VIEW_FITTO, &CmannequinDlg::OnViewFitto)
ON_COMMAND(ID_DRESSFORM_WHOLETIGHTS, &CmannequinDlg::OnDressformWholetights)
ON_COMMAND(ID_DRESSFORM_DRESS, &CmannequinDlg::OnDressformDress)
ON_COMMAND(ID_DRESSFORM_TOP, &CmannequinDlg::OnDressformTop)
ON_COMMAND(ID_DRESSFORM_PANTS, &CmannequinDlg::OnDressformPants)
ON_COMMAND(ID_DRESSFORM_SKIRT, &CmannequinDlg::OnDressformSkirt)
ON_COMMAND(ID_JOINTS_POSEEXPORT, &CmannequinDlg::OnJointsPoseexport)
ON_COMMAND(ID_POSE_POSELOAD, &CmannequinDlg::OnPosePoseload)
ON_COMMAND(ID_JOINTS_MIRROR, &CmannequinDlg::OnJointsMirror)
ON_COMMAND(ID_JOINTS_EXPAND, &CmannequinDlg::OnJointsExpand)
ON_COMMAND(ID_FILE_EXPORTHUMAN, &CmannequinDlg::OnFileExporthuman)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_SIZELIST, &CmannequinDlg::OnLvnItemchangedSizelist)
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_TEXTURE_SELECTAREA, &CmannequinDlg::OnTextureSelectarea)
ON_BN_CLICKED(IDC_SHOWCROTCH, &CmannequinDlg::OnBnClickedShowcrotch)
ON_COMMAND(ID_TEXTURE_SETBRA, &CmannequinDlg::OnTextureSetbra)
ON_COMMAND(ID_TEXTURE_SETUNDERPANTS, &CmannequinDlg::OnTextureSetunderpants)
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

	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect);
	width = rect.Width();
	height = rect.Height();
	glViewport(0, 0, width, height);
//	aspectRatio = width / height;
	aspectRatio = 1;

	progressBar.SetRange(0, 100);
	progressBar.SetPos(0);

	if (!GetRenderingContext()) {
		AfxMessageBox(CString("Error in joint OpenGL initialization."));
		return FALSE;
	}

	/* Initiate Size Edit */
	sizeControl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	sizeControl.GetWindowRect(rect);

	sizeControl.InsertColumn(0, _T("Name"), LVCFMT_LEFT, rect.Width()/2, -1);
	sizeControl.InsertColumn(1, _T("Value (cm)"), LVCFMT_LEFT, rect.Width()/2, -1);

	for (int i = 0; i < SegmentNum; i++) {
		float r = rand() / double(RAND_MAX);
		float g = rand() / double(RAND_MAX);
		float b = rand() / double(RAND_MAX);
		colorArray.push_back(vec3(r, g, b));
	}

	AccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	/*** Texture ***/
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int twidth, theight, channels;
	unsigned char* data = stbi_load("skin.jpg", &twidth, &theight, &channels, 0);
	if (data == NULL)
		cout << "Cannot load texture." << endl;

	if (data) {
		cout << "Texture loaded." << endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmannequinDlg::InitEditField() {
	progressBar.SetPos(10);
	camera = Camera();

	progressBar.SetPos(20);

	CT2CA convertedString(pathName);
	string s(convertedString);
	human = new HumanOBJ(s);

	progressBar.SetPos(70);

	vertices = &human->getVerts();
	indices = &human->getIndices();
	normals = &human->getNormals();

	progressBar.SetPos(80);

	currArmRPos = 50;
	currArmLPos = 50;
	currElbowRPos = 50;
	currElbowLPos = 50;

	currLegRPos = 50;
	currLegLPos = 50;
	currKneeRPos = 50;
	currKneeLPos = 50;

	currBentPos = 5;
	currBentPos2 = 5;

	/* Initiate Arm Slider */
	armRSlider.SetRange(0, 100);
	armRSlider.SetPos(currArmRPos);
	armRSlider.SetTicFreq(1);
	armRSlider.SetLineSize(1);

	elbowRSlider.SetRange(0, 100);
	elbowRSlider.SetPos(currElbowRPos);
	elbowRSlider.SetTicFreq(1);
	elbowRSlider.SetLineSize(1);

	armLSlider.SetRange(0, 100);
	armLSlider.SetPos(currArmLPos);
	armLSlider.SetTicFreq(1);
	armLSlider.SetLineSize(1);

	elbowLSlider.SetRange(0, 100);
	elbowLSlider.SetPos(currElbowLPos);
	elbowLSlider.SetTicFreq(1);
	elbowLSlider.SetLineSize(1);

	/* Initiate Leg Slider */
	legRSlider.SetRange(0, 50);
	legRSlider.SetPos(currLegRPos);
	legRSlider.SetTicFreq(1);
	legRSlider.SetLineSize(1);

	kneeRSlider.SetRange(0, 90);
	kneeRSlider.SetPos(currKneeRPos);
	kneeRSlider.SetTicFreq(1);
	kneeRSlider.SetLineSize(1);

	legLSlider.SetRange(0, 50);
	legLSlider.SetPos(currLegLPos);
	legLSlider.SetTicFreq(1);
	legLSlider.SetLineSize(1);

	kneeLSlider.SetRange(0, 90);
	kneeLSlider.SetPos(currKneeLPos);
	kneeLSlider.SetTicFreq(1);
	kneeLSlider.SetLineSize(1);

	/* Initiate Pos Slider */
	//posBentSlider.SetRange(0, 10);
	posBentSlider.SetRange(4, 6);
	posBentSlider.SetPos(currBentPos);
	posBentSlider.SetTicFreq(1);
	posBentSlider.SetLineSize(1);

	posBentSlider2.SetRange(0, 10);
	posBentSlider2.SetPos(currBentPos2);
	posBentSlider2.SetTicFreq(1);
	posBentSlider2.SetLineSize(1);

	progressBar.SetPos(90);

	progressBar.SetPos(100);

	axisXradio.SetCheck(false);
	axisYradio.SetCheck(false);
	axisZradio.SetCheck(true);

	SetTimer(0, 300, NULL);
}

void CmannequinDlg::EnableDeformation() {
	float humanheight = 0, bust = 0, waist = 0, hip = 0;
	progressBar.SetPos(0);

	humanJoints = &human->joints;
	progressBar.SetPos(5);
	human->setRigs(scaleF); // Set hierarchy and segment
	human->scaleFactor = scaleF;

	progressBar.SetPos(40);

	pose = new Pose(human); // Enable posing
	progressBar.SetPos(70);

	size = new Size(human); // Enable sizing
	progressBar.SetPos(100);

	landmarkVariables = &human->landmarks;

	sizeControl.DeleteAllItems();
	for (int i = 0; i < landmarkVariables->size(); i++) {
		sizeControl.InsertItem(i, (*landmarkVariables)[i].name);
		CString ctr;
		ctr.Format(_T("%.3f"), (*landmarkVariables)[i].value);
		sizeControl.SetItem(i, 1, LVIF_TEXT, ctr, 0, 0, 0, NULL);
	}

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

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &position_vbo);
	glDeleteBuffers(1, &color_vbo);
	glDeleteBuffers(1, &normal_vbo);
	glDeleteBuffers(1, &texture_vbo);
	glDeleteProgram(mannequinShaderProgram);

	glDeleteVertexArrays(1, &joint_vao);
	glDeleteBuffers(1, &joint_ebo);
	glDeleteBuffers(1, &joint_position_vbo);
	glDeleteProgram(jointShaderProgram);

	glDeleteVertexArrays(1, &landmark_vao);
	glDeleteBuffers(1, &landmark_position_vbo);
	glDeleteBuffers(1, &landmark_color_vbo);
	glDeleteProgram(landmarkShaderProgram);

	if (FALSE == ::wglDeleteContext(m_hRC)) {
		AfxMessageBox(CString("wglDeleteContext failed"));
	}
}

void CmannequinDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 0) {

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

	vec3 cameraPos = pos;
	//vec3 color = vec3(1.0f, 1.0f, 1.0f);
	/*
	float r = (float)85 / 255;
	float g = (float)79 / 255;
	float b = (float)72 / 255;
	*/
	float r = 1, g = 1, b = 1;
	vec3 lightColor = vec3(r, g, b);
	vec3 lightPos = vec3(pos.x, 3.0f, pos.z);

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

	//mat4 projectionMatrix = perspective((float)radians(45.0f), width / (float)height, 0.1f, 300.0f);
	projectionMatrix = ortho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f * aspectRatio, 10.f * aspectRatio, 0.0f, 100.0f);
	viewMatrix = lookAt(pos, dir, up);
	modelMatrix = scaleMatrix * mat4(1.0f);

	GLuint projectionID = glGetUniformLocation(mannequinShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	GLuint viewID = glGetUniformLocation(mannequinShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	GLuint modelID = glGetUniformLocation(mannequinShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	if (showWireframeMode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUniform1i(glGetUniformLocation(mannequinShaderProgram, "texture"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(position_attribute);
	glDisableVertexAttribArray(color_attribute);
	glDisableVertexAttribArray(normal_attribute);
	glDisableVertexAttribArray(texture_attribute);
	/*****************/

	if (isBra) {
		defineUnderwearVAO(underwear_vao, *human->bra);
		glBindVertexArray(underwear_vao);
		glDrawArrays(GL_POINTS, 0, human->bra->size());
	// 	glDrawElements(GL_TRIANGLES, human->braEBO->size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	if (isUnderpants) {
		defineUnderwearVAO(underwear_vao, *human->underpants);
		glBindVertexArray(underwear_vao);
		glDrawArrays(GL_POINTS, 0, human->underpants->size());
		glBindVertexArray(0);
	}

	if (humanJoints && showJointsMode) {
		defineJointVAO(joint_vao);

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
		//glDrawElements(GL_LINES, (JointNum - 1)*2, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(joint_position_attribute);
		glBindVertexArray(0);
	}

	if (landmarkVariables && showLandmarksMode) {
		for (int i = 1; i < landmarkVariables->size(); i++) {
			defineLandmarkVAO(i, landmark_vao);
			glUseProgram(landmarkShaderProgram);

			projectionID = glGetUniformLocation(landmarkShaderProgram, "projection");
			glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
			viewID = glGetUniformLocation(landmarkShaderProgram, "view");
			glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
			modelID = glGetUniformLocation(landmarkShaderProgram, "model");
			glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

			glBindVertexArray(landmark_vao);
			if (i == selItem)
				glLineWidth(3);
			else
				glLineWidth(1);
			glDrawArrays(GL_LINE_LOOP, 0, (*landmarkVariables)[i].vertIdx.size());
			//glDrawArrays(GL_POINTS, 0, (*landmarkVariables)[i].vertIdx.size());

			glDisableVertexAttribArray(landmark_position_attribute);
			glDisableVertexAttribArray(landmark_color_attribute);
			glBindVertexArray(0);
		}
	}
}

void CmannequinDlg::drawJoint() {
	defineJointVAO(joint_vao);

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
	vector<vec2> texture;
	vector<int> indexing;

	vector<vec3> color;

	for (int i = 0; i < vertices->size(); i++) {
		Vertex bv = (*vertices)[i];
		position.push_back(vec3(bv.x, bv.y, bv.z));
		float r = (float) 85 / 255;
		float g = (float) 79 / 255;
		float b = (float) 72 / 255;
		color.push_back(vec3(r, g, b));
	}

	for (int i = 0; i < normals->size(); i++) {
		Vertex nv = (*normals)[i];
		normal.push_back(vec3(nv.x, nv.y, nv.z));
	}

	float vt[3] = { 0.0f, 0.5f, 1.0f };
	for (int i = 0; i < human->textures.size(); i++) {
		Vertex t = human->textures[i];
		// texture.push_back(vec2(t.x, t.y));
		texture.push_back(vec2(vt[i%3]));
	}
	
	for (int i = 0; i < indices->size(); i++) {
		indexing.push_back((*indices)[i] - 1);
	}

	if (showAllBodySegment.GetCheck()) {
		for ( int i = 0; i < SegmentNum; i++ ) {
			for (int j = 0; j < human->bodySegment[i].size(); j++) {
				color[human->bodySegment[i][j]] = colorArray[i];
			}
		}
	}
	else {
		if (showHeadBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_Head].size(); i++) {
				color[human->bodySegment[Segment_Head][i]] = colorArray[Segment_Head];
			}
		}

		if (showNeckBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_Neck].size(); i++) {
				color[human->bodySegment[Segment_Neck][i]] = colorArray[Segment_Neck];
			}
		}

		if (showUpperTorsoBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_UpperTorso].size(); i++) {
				color[human->bodySegment[Segment_UpperTorso][i]] = colorArray[Segment_UpperTorso];
			}
		}

		if (showLowerTorsoBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_LowerTorso].size(); i++) {
				color[human->bodySegment[Segment_LowerTorso][i]] = colorArray[Segment_LowerTorso];
			}
		}

		if (showUpperLegRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_UpperLegR].size(); i++) {
				color[human->bodySegment[Segment_UpperLegR][i]] = colorArray[Segment_UpperLegR];
			}
		}

		if (showLowerLegRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_LowerLegR].size(); i++) {
				color[human->bodySegment[Segment_LowerLegR][i]] = colorArray[Segment_LowerLegR];
			}
		}

		if (showFootRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_FootR].size(); i++) {
				color[human->bodySegment[Segment_FootR][i]] = colorArray[Segment_FootR];
			}
		}

		if (showUpperLegLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_UpperLegL].size(); i++) {
				color[human->bodySegment[Segment_UpperLegL][i]] = colorArray[Segment_UpperLegL];
			}
		}

		if (showLowerLegLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_LowerLegL].size(); i++) {
				color[human->bodySegment[Segment_LowerLegL][i]] = colorArray[Segment_LowerLegL];
			}
		}

		if (showFootLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_FootL].size(); i++) {
				color[human->bodySegment[Segment_FootL][i]] = colorArray[Segment_FootL];
			}
		}

		if (showUpperArmRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_UpperArmR].size(); i++) {
				color[human->bodySegment[Segment_UpperArmR][i]] = colorArray[Segment_UpperArmR];
			}
		}

		if (showLowerArmRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_LowerArmR].size(); i++) {
				color[human->bodySegment[Segment_LowerArmR][i]] = colorArray[Segment_LowerArmR];
			}
		}

		if (showHandRBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_HandR].size(); i++) {
				color[human->bodySegment[Segment_HandR][i]] = colorArray[Segment_HandR];
			}
		}

		if (showUpperArmLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_UpperArmL].size(); i++) {
				color[human->bodySegment[Segment_UpperArmL][i]] = colorArray[Segment_UpperArmL];
			}
		}

		if (showLowerArmLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_LowerArmL].size(); i++) {
				color[human->bodySegment[Segment_LowerArmL][i]] = colorArray[Segment_LowerArmL];
			}
		}

		if (showHandLBodySegment.GetCheck()) {
			for (int i = 0; i < human->bodySegment[Segment_HandL].size(); i++) {
				color[human->bodySegment[Segment_HandL][i]] = colorArray[Segment_HandL];
			}
		}
	}

	Skinning skinning = human->skinning;
	if (showArmWeightMode == 1) {
		for (int i = 0; i < skinning.armRSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.armRSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_shoulderR) {
					if (v.jointWeights[j] == 1) {
						color[skinning.armRSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.armRSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.armRSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
		for (int i = 0; i < skinning.armLSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.armLSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_shoulderL) {
					if (v.jointWeights[j] == 1) {
						color[skinning.armLSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.armLSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.armLSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
	}
	if (showElbowWeightMode == 1) {
		for (int i = 0; i < skinning.elbowRSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.elbowRSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_elbowR) {
					if (v.jointWeights[j] == 1) {
						color[skinning.elbowRSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.elbowRSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.elbowRSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
		for (int i = 0; i < skinning.elbowLSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.elbowLSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_elbowL) {
					if (v.jointWeights[j] == 1) {
						color[skinning.elbowLSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.elbowLSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.elbowLSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
	}
	if (showLegWeightMode == 1) {
		for (int i = 0; i < skinning.legRSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.legRSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_pelvisR) {
					if (v.jointWeights[j] == 1) {
						color[skinning.legRSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.legRSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.legRSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
		for (int i = 0; i < skinning.legLSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.legLSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_pelvisL) {
					if (v.jointWeights[j] == 1) {
						color[skinning.legLSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.legLSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.legLSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
	}
	if (showKneeWeightMode == 1) {
		for (int i = 0; i < skinning.kneeRSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.kneeRSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_kneeR) {
					if (v.jointWeights[j] == 1) {
						color[skinning.kneeRSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.kneeRSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.kneeRSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
		for (int i = 0; i < skinning.kneeLSegment.size(); i++) {
			Vertex v = (*vertices)[skinning.kneeLSegment[i]];
			for (int j = 0; j < v.jointsRelated.size(); j++) {
				if (v.jointsRelated[j] == Joint_kneeL) {
					if (v.jointWeights[j] == 1) {
						color[skinning.kneeLSegment[i]] = vec3(1, 0, 0);
					}
					else if (v.jointWeights[j] >= 0.5) {
						color[skinning.kneeLSegment[i]] = vec3(1, 1, 0);
					}
					else if (v.jointWeights[j] < 0.5) {
						color[skinning.kneeLSegment[i]] = vec3(0, 0, 1);
					}
				}
			}
		}
	}

	// Position
	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), &position[0], GL_STATIC_DRAW);

	position_attribute = glGetAttribLocation(mannequinShaderProgram, "position");
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	// Color for different segment parts
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), &color[0], GL_STATIC_DRAW);

	color_attribute = glGetAttribLocation(mannequinShaderProgram, "color");
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	// Normal
	glGenBuffers(1, &normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(vec3), &normal[0], GL_STATIC_DRAW);

	normal_attribute = glGetAttribLocation(mannequinShaderProgram, "normal");
	glVertexAttribPointer(normal_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normal_attribute);

	
	// Indexing
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexing.size() * sizeof(int), &indexing[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Texture
	glGenBuffers(1, &texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, texture.size() * sizeof(vec2), &texture[0], GL_STATIC_DRAW);

	texture_attribute = glGetAttribLocation(mannequinShaderProgram, "TexCoord");
	glVertexAttribPointer(texture_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texture_attribute);

}

void CmannequinDlg::defineJointVAO(GLuint& joint_vao) {
	glGenVertexArrays(1, &joint_vao);
	glBindVertexArray(joint_vao);

	jointShaderProgram = loadShaders("shaders/JointVertexShader.vertexshader", "shaders/JointFragmentShader.fragmentshader");

	vector<vec3> joints; 
	vector<int> joint_indices;

	for ( int i = 0; i < humanJoints->size(); i++ ) {
		Vertex v = (*humanJoints)[i].getCoord();
		joints.push_back(vec3(v.x, v.y, v.z));
	}

	joint_indices.push_back(0);
	joint_indices.push_back(1);

	joint_indices.push_back(1);
	joint_indices.push_back(2);

	joint_indices.push_back(2);
	joint_indices.push_back(3);

	joint_indices.push_back(3);
	joint_indices.push_back(4);

	joint_indices.push_back(1);
	joint_indices.push_back(5);

	joint_indices.push_back(5);
	joint_indices.push_back(6);

	joint_indices.push_back(6);
	joint_indices.push_back(7);

	joint_indices.push_back(7);
	joint_indices.push_back(8);

	joint_indices.push_back(8);
	joint_indices.push_back(9);

	joint_indices.push_back(9);
	joint_indices.push_back(10);

	joint_indices.push_back(6);
	joint_indices.push_back(11);

	joint_indices.push_back(11);
	joint_indices.push_back(12);

	joint_indices.push_back(12);
	joint_indices.push_back(13);

	joint_indices.push_back(13);
	joint_indices.push_back(14);

	joint_indices.push_back(1);
	joint_indices.push_back(15);

	joint_indices.push_back(15);
	joint_indices.push_back(16);

	joint_indices.push_back(16);
	joint_indices.push_back(17);

	if (!joints.empty()) {
		glGenBuffers(1, &joint_position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, joint_position_vbo);
		glBufferData(GL_ARRAY_BUFFER, joints.size() * sizeof(vec3), &joints[0], GL_STATIC_DRAW);

		joint_position_attribute = glGetAttribLocation(jointShaderProgram, "position");
		glVertexAttribPointer(joint_position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(joint_position_attribute);

		glGenBuffers(1, &joint_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, joint_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, joint_indices.size() * sizeof(int), &joint_indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}
}

void CmannequinDlg::defineLandmarkVAO(int idx, GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	landmarkShaderProgram = loadShaders("shaders/GirthVertexShader.vertexshader", "shaders/GirthFragmentShader.fragmentshader");

	vector<vec3> position;
	vector<vec3> color;

	for (int i = 0; i < (*landmarkVariables)[idx].vertIdx.size(); i++) {
		Vertex v;
		if ((*landmarkVariables)[idx].type == Girth) {
			v = (*vertices)[(*landmarkVariables)[idx].vertIdx[i] - 1];

			position.push_back(vec3(v.x, (*landmarkVariables)[idx].level, v.z));
		}
		else if ((*landmarkVariables)[idx].type == Length) {
			v = (*humanJoints)[(*landmarkVariables)[idx].vertIdx[i]].getCoord();
			position.push_back(vec3(v.x, v.y, v.z));
		}

		//position.push_back(vec3(v.x, v.y, v.z));

		color.push_back(vec3(1, 0, 0));
	}

	glGenBuffers(1, &landmark_position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, landmark_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), &position[0], GL_STATIC_DRAW);

	landmark_position_attribute = glGetAttribLocation(landmarkShaderProgram, "position");
	glVertexAttribPointer(landmark_position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(landmark_position_attribute);

	glGenBuffers(1, &landmark_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, landmark_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), &color[0], GL_STATIC_DRAW);

	landmark_color_attribute = glGetAttribLocation(landmarkShaderProgram, "color");
	glVertexAttribPointer(landmark_color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(landmark_color_attribute);

	glBindVertexArray(0);
}

void CmannequinDlg::defineUnderwearVAO(GLuint& vao, vector<float> undieData) {
	underwearShaderProgram = loadShaders("shaders/JointVertexShader.vertexShader", "shaders/JointFragmentShader.fragmentShader");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &underwear_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, underwear_vbo);
	glBufferData(GL_ARRAY_BUFFER, undieData.size() * sizeof(float), &undieData[0], GL_STATIC_DRAW);

	int undiePositionAttrib = glGetAttribLocation(underwearShaderProgram, "position");
	glVertexAttribPointer(undiePositionAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(undiePositionAttrib);

	int undieColorAttrib = glGetAttribLocation(underwearShaderProgram, "color");
	glVertexAttribPointer(undieColorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(undieColorAttrib);

	glGenBuffers(1, &underwear_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, underwear_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, human->braEBO->size() * sizeof(int), &human->braEBO[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
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

void CmannequinDlg::OnNMReleasedcaptureArmr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = armRSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = -(pos - currArmRPos) * M_PI / 180;

		pose[0] = Joint_shoulderR;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;
			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}

		// human->skinning.rotateArmR(Joint_shoulderR, -(pos - currArmRPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_collarboneR); // Added for DQS
		boneIndices.push_back(Bone_ribR); // Added for DQS
		boneIndices.push_back(Bone_shoulderR);
		boneIndices.push_back(Bone_upperArmR);
		boneIndices.push_back(Bone_upperArm1R);
		boneIndices.push_back(Bone_lowerArmR);
		boneIndices.push_back(Bone_lowerArm1R);
		boneIndices.push_back(Bone_lowerArm2R);

		human->skinning.deformDQS(Joint_shoulderR, -(pos - currArmRPos), boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_shoulderR;
		his.value = -(pos - currArmRPos);
		human->skinning.history.push_back(his);

		currArmRPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureArml(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = armLSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = (pos - currArmLPos) * M_PI / 180;

		pose[0] = Joint_shoulderL;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		// human->skinning.rotateArmL(Joint_shoulderL, pos - currArmLPos, *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_collarboneL);
		boneIndices.push_back(Bone_ribL);
		boneIndices.push_back(Bone_shoulderL);
		boneIndices.push_back(Bone_upperArmL);
		boneIndices.push_back(Bone_upperArm1L);
		boneIndices.push_back(Bone_lowerArmL);
		boneIndices.push_back(Bone_lowerArm1L);
		boneIndices.push_back(Bone_lowerArm2L);

		// human->skinning.deform(Joint_shoulderL, pos - currArmLPos, boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;
		human->skinning.deformDQS(Joint_shoulderL, pos - currArmLPos, boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_shoulderL;
		his.value = (pos - currArmLPos);
		human->skinning.history.push_back(his);

		currArmLPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureLegr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = legRSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = -(pos - currLegRPos) * M_PI / 180;

		pose[0] = Joint_pelvisR;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		// human->skinning.rotateLegR(Joint_pelvisR, -(pos - currLegRPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_pelvisR);
		boneIndices.push_back(Bone_hipR);
		boneIndices.push_back(Bone_upperLegR);
		boneIndices.push_back(Bone_upperLeg1R);
		boneIndices.push_back(Bone_lowerLegR);
		human->skinning.deform(Joint_pelvisR, -(pos - currLegRPos), boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_pelvisR;
		his.value = -(pos - currLegRPos);
		human->skinning.history.push_back(his);

		currLegRPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureLegl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = legLSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = (pos - currLegLPos) * M_PI / 180;

		pose[0] = Joint_pelvisL;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		//human->skinning.rotateLegL(Joint_pelvisL, (pos - currLegLPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_pelvisL);
		boneIndices.push_back(Bone_hipL);
		boneIndices.push_back(Bone_upperLegL);
		boneIndices.push_back(Bone_upperLeg1L);
		boneIndices.push_back(Bone_lowerLegL);
		human->skinning.deform(Joint_pelvisL, pos - currLegLPos, boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_pelvisL;
		his.value = (pos - currLegLPos);
		human->skinning.history.push_back(his);

		currLegLPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureElbowr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = elbowRSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = -(pos - currElbowRPos) * M_PI / 180;

		pose[0] = Joint_elbowR;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		//human->skinning.rotateElbowR(Joint_elbowR, -(pos - currElbowRPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_lowerArmR);
		boneIndices.push_back(Bone_lowerArm1R);
		boneIndices.push_back(Bone_lowerArm2R);

		human->skinning.deform(Joint_elbowR, -(pos - currElbowRPos), boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_elbowR;
		his.value = -(pos - currElbowRPos);
		human->skinning.history.push_back(his);

		currElbowRPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureElbowl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = elbowLSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = (pos - currElbowLPos) * M_PI / 180;

		pose[0] = Joint_elbowL;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		// human->skinning.rotateElbowL(Joint_elbowL, (pos - currElbowLPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_lowerArmL);
		boneIndices.push_back(Bone_lowerArm1L);
		boneIndices.push_back(Bone_lowerArm2L);

		human->skinning.deform(Joint_elbowL, pos - currElbowLPos, boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_elbowL;
		his.value = (pos - currElbowLPos);
		human->skinning.history.push_back(his);
		
		currElbowLPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureKneer(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = kneeRSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = -(pos - currKneeRPos) * M_PI / 180;

		pose[0] = Joint_kneeR;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		// human->skinning.rotateKneeR(Joint_kneeR, -(pos - currKneeRPos), *vertices, *humanJoints);;
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_lowerLegR);
		human->skinning.deform(Joint_kneeR, -(pos - currKneeRPos), boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_kneeR;
		his.value = -(pos - currKneeRPos);
		human->skinning.history.push_back(his);

		currKneeRPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureKneel(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = kneeLSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = (pos - currKneeLPos) * M_PI / 180;

		pose[0] = Joint_kneeL;
		if (axisXradio.GetCheck()) {
			human->skinning.axis = Axis_X;

			pose[1] = 1;
			pose[2] = 0;
			pose[3] = 0;

			pose[4] = 0;
			pose[5] = cos(radian);
			pose[6] = -sin(radian);

			pose[7] = 0;
			pose[8] = sin(radian);
			pose[9] = cos(radian);
		}
		if (axisYradio.GetCheck()) {
			human->skinning.axis = Axis_Y;

			pose[1] = cos(radian);
			pose[2] = 0;
			pose[3] = sin(radian);

			pose[4] = 0;
			pose[5] = 1;
			pose[6] = 0;

			pose[7] = -sin(radian);
			pose[8] = 0;
			pose[9] = cos(radian);
		}
		if (axisZradio.GetCheck()) {
			human->skinning.axis = Axis_Z;

			pose[1] = cos(radian);
			pose[2] = -sin(radian);
			pose[3] = 0;

			pose[4] = sin(radian);
			pose[5] = cos(radian);
			pose[6] = 0;

			pose[7] = 0;
			pose[8] = 0;
			pose[9] = 1;
		}
		//human->poseHistory.push_back(pose);

		// human->skinning.rotateKneeL(Joint_kneeL, (pos - currKneeLPos), *vertices, *humanJoints);
		vector<Bone>* bones = &human->bones;
		vector<int> boneIndices;
		boneIndices.push_back(Bone_lowerLegL);
		human->skinning.deform(Joint_kneeL, pos - currKneeLPos, boneIndices, *bones, human->boneSegment, human->boneWeight, *vertices, *humanJoints);;

		poseHistory his;
		his.axis = human->skinning.axis;
		his.part = Joint_kneeL;
		his.value = (pos - currKneeLPos);
		human->skinning.history.push_back(his);

		currKneeLPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureBentslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = posBentSlider.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];

		pose[0] = Segment_Neck;

		for (int i = 1; i < 10; i++) {
			pose[i] = 0;
		}
		pose[9] = pos - currBentPos;

		//human->poseHistory.push_back(pose);

		human->skinning.bendTorso(Segment_Neck, pos - currBentPos, *vertices, *humanJoints);
		currBentPos = pos;
	}
}

void CmannequinDlg::OnNMReleasedcaptureBentslider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (humanJoints) {
		*pResult = 0;
		int pos = posBentSlider2.GetPos();

		CString ctr;
		ctr.Format(_T("%d"), pos);

		float pose[10];
		float radian = (pos - currBentPos2) * M_PI / 180;

		pose[0] = Segment_UpperTorso;

		pose[1] = 1;
		pose[2] = 0;
		pose[3] = 0;

		pose[4] = 0;
		pose[5] = cos(radian);
		pose[6] = sin(radian);

		pose[7] = 0;
		pose[8] = -sin(radian);
		pose[9] = cos(radian);

		//human->poseHistory.push_back(pose);

		human->skinning.bendTorso(Segment_UpperTorso, pos - currBentPos2, *vertices, *humanJoints);
		currBentPos2 = pos;
	}
}

void CmannequinDlg::OnBnClickedFront()
{
	// TODO: Add your control notification handler code here
	camera.ViewFront();
}

void CmannequinDlg::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	camera.ViewBack();
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
}

void CmannequinDlg::OnBnClickedLeft()
{
	// TODO: Add your control notification handler code here
	camera.ViewLeft();
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

void CmannequinDlg::OnFileOpen()
{
	// TODO: Add your command handler code here

	static TCHAR BASED_CODE szFilter[] = _T("OBJ 파일(*.OBJ) | *.obj; *.OBJ |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.obj"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())

	{
		pathName = dlg.GetPathName();
		AfxExtractSubString(filepath_filename, pathName, 0, '.');

		InitEditField();
		dlg.DestroyWindow();
	}
}

void CmannequinDlg::OnDefineJoints()
{
	// TODO: Add your command handler code here

	jointDefineMode = 1;

	/*
	if (human) {
		if (jointDlg == NULL) {
			CWnd *pWnd;
			jointDlg = new CJointDialog(CWnd::FromHandle(this->m_hWnd));
		}

		jointDlg->human = human;
		jointDlg->vertices = vertices;
		jointDlg->indices = indices;

		if (humanJoints)
			jointDlg->joints = humanJoints;
		else
			jointDlg->joints = 0;

		jointDlg->scaleF = scaleF;
		jointDlg->scaleMatrix = scaleMatrix;


		if (jointDlg->DoModal() == IDOK) {
			makeCurrent();
		}
	}
	*/

	//jointDefineMode = 0;
}

void CmannequinDlg::OnJointsMirror()
{
	// TODO: Add your command handler code here
	if (human && humanJoints->size() == JointNum) {
		Vertex j = (*humanJoints)[Joint_shoulderR].getCoord();
		(*humanJoints)[Joint_shoulderL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_elbowR].getCoord();
		(*humanJoints)[Joint_elbowL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_wristR].getCoord();
		(*humanJoints)[Joint_wristL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_pelvisR].getCoord();
		(*humanJoints)[Joint_pelvisL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_kneeR].getCoord();
		(*humanJoints)[Joint_kneeL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_ankleR].getCoord();
		(*humanJoints)[Joint_ankleL].setCoord(Vertex(-j.x, j.y, j.z));
	}
	else if (human && humanJoints->size() == ExpandedJointNum) {
		Vertex j = (*humanJoints)[Joint_shoulderR].getCoord();
		(*humanJoints)[Joint_shoulderL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_elbowR].getCoord();
		(*humanJoints)[Joint_elbowL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_wristR].getCoord();
		(*humanJoints)[Joint_wristL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_pelvisR].getCoord();
		(*humanJoints)[Joint_pelvisL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_kneeR].getCoord();
		(*humanJoints)[Joint_kneeL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_ankleR].getCoord();
		(*humanJoints)[Joint_ankleL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_collarboneR].getCoord();
		(*humanJoints)[Joint_collarboneL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_shoulderTwistR].getCoord();
		(*humanJoints)[Joint_shoulderTwistL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_shoulderTwistR].getCoord();
		(*humanJoints)[Joint_shoulderTwistL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_elbowTwistR].getCoord();
		(*humanJoints)[Joint_elbowTwistL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_elbowTwist1R].getCoord();
		(*humanJoints)[Joint_elbowTwist1L].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_hipR].getCoord();
		(*humanJoints)[Joint_hipL].setCoord(Vertex(-j.x, j.y, j.z));

		j = (*humanJoints)[Joint_hipTwistR].getCoord();
		(*humanJoints)[Joint_hipTwistL].setCoord(Vertex(-j.x, j.y, j.z));
	}
	else if (humanJoints->size() < 18) {
		AfxMessageBox(_T("Define all the joints before mirroring."));
	}
}

void CmannequinDlg::OnJointsRemoveall()
{
	// TODO: Add your command handler code here
	if (human) {
		jointDefineMode = 0;
		humanJoints->clear();
	}
}

void CmannequinDlg::OnFileExport()
{
	// TODO: Add your command handler code here
	if (human) {
		human->writeToOBJ(filepath_filename);
	}
}

void CmannequinDlg::OnJointsSave()
{
	// TODO: Add your command handler code here
	if (human) {
		human->jointExport(filepath_filename);
		jointDefineMode = 0;
		EnableDeformation();
	}
}

void CmannequinDlg::OnJointsLoad()
{
	// TODO: Add your command handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Joint 파일(*.Joint) | *.JOINT; *.Joint |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.Joint"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())

	{
		jpathName = dlg.GetPathName();

		CT2CA convertedString(jpathName);
		string s(convertedString);
		human->getJoints(s);
		jointDefineMode = 0;
		progressBar.SetPos(5);

		showJoints.SetCheck(true);
		showJointsMode = 1;

		showLandmarks.SetCheck(true);
		showLandmarksMode = 1;

		EnableDeformation();
		dlg.DestroyWindow();
	}
}

void CmannequinDlg::OnPosePoseload()
{
	// TODO: Add your command handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Pose 파일(*.Pose) | *.POSE; *.pose |모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.Pose"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal()) {
		pathName = dlg.GetPathName();
		CT2CA convertedString(pathName);
		string s(convertedString);

		human->skinning.setPose(s);

		for (int i = 0; i < human->skinning.history.size(); i++) {
			poseHistory his = human->skinning.history[i];
			if (his.part == Joint_shoulderR) {
				human->skinning.axis = his.axis;
				human->skinning.rotateArmR(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_shoulderL) {
				human->skinning.axis = his.axis;
				human->skinning.rotateArmL(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_elbowR) {
				human->skinning.axis = his.axis;
				human->skinning.rotateElbowR(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_elbowL) {
				human->skinning.axis = his.axis;
				human->skinning.rotateElbowL(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_elbowL) {
				human->skinning.axis = his.axis;
				human->skinning.rotateElbowL(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_pelvisR) {
				human->skinning.axis = his.axis;
				human->skinning.rotateLegR(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_pelvisL) {
				human->skinning.axis = his.axis;
				human->skinning.rotateLegL(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_kneeR) {
				human->skinning.axis = his.axis;
				human->skinning.rotateKneeR(his.part, his.value, *vertices, *humanJoints);
			}
			else if (his.part == Joint_kneeL) {
				human->skinning.axis = his.axis;
				human->skinning.rotateKneeL(his.part, his.value, *vertices, *humanJoints);
			}
		}
		dlg.DestroyWindow();
	}
}

void CmannequinDlg::OnJointsPoseexport()
{
	// TODO: Add your command handler code here

	if (human->skinning.history.size() > 0) {
		ofstream outfile(filepath_filename + _T("_pose.Pose"));

		for (int i = 0; i < human->skinning.history.size(); i++) {
			poseHistory his = human->skinning.history[i];
			outfile << his.part << " " << his.axis << " " << his.value << endl;
		}

		outfile.close();

		AfxMessageBox(_T("Pose exported."));
	}
	else {
		AfxMessageBox(_T("No pose to export."));
	}
}

void CmannequinDlg::OnLandmarksDefine()
{
	// TODO: Add your command handler code here
	landmarkDefineMode = 1;

	if (human && humanJoints) {
		if (landmarkDlg == NULL) {
			CWnd *pWnd;
			landmarkDlg = new CLandmarkDialog(CWnd::FromHandle(this->m_hWnd));
		}

		landmarkDlg->vertices = vertices;
		landmarkDlg->indices = indices;
		landmarkDlg->scaleF = scaleF;
		landmarkDlg->scaleMatrix = scaleMatrix;

		landmarkDlg->joints = humanJoints;

		landmarkDlg->topMostLevel = human->topMostLevel;
		landmarkDlg->bottomMostLevel = human->bottomMostLevel;
		landmarkDlg->leftMostOffset = human->leftMostOffset;
		landmarkDlg->leftMostLevel = human->leftMostLevel;
		landmarkDlg->rightMostOffset = human->rightMostOffset;
		landmarkDlg->rightMostLevel = human->rightMostLevel;

		landmarkDlg->variables = landmarkVariables;

		Skinning skinning = human->skinning;
		for (int i = 0; i < SegmentNum; i++) {
			landmarkDlg->bodySegment[i].insert(landmarkDlg->bodySegment[i].end(), skinning.bodySegment[i].begin(), skinning.bodySegment[i].end());
		}

		if (landmarkDlg->DoModal() == IDOK) {
			// After modal 
			//landmarkVariables;
			makeCurrent();

			human->crotch = landmarkDlg->crotch;
			// human->crotch->print();

			sizeControl.DeleteAllItems();
			for (int i = 0; i < landmarkVariables->size(); i++) {
				sizeControl.InsertItem(i, (*landmarkVariables)[i].name);
				CString ctr;
				ctr.Format(_T("%.3f"), (*landmarkVariables)[i].value);
				sizeControl.SetItem(i, 1, LVIF_TEXT, ctr, 0, 0, 0, NULL);
			}
			landmarkDlg->DestroyWindow();
		}
	}
	else {
		AfxMessageBox(_T("Define joints first!"));
	}

	landmarkDefineMode = 0;
}

void CmannequinDlg::OnLandmarksLoad()
{
	// TODO: Add your command handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Landmark 파일(*.Landmark) | *.LANDMARK; *.landmark |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.Landmark"), _T(""), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal()) {
		pathName = dlg.GetPathName();
		CT2CA convertedString(pathName);
		string s(convertedString);

		landmarkVariables = &human->setLandmarks(s);

		sizeControl.DeleteAllItems();
		for (int i = 0; i < landmarkVariables->size(); i++) {
			sizeControl.InsertItem(i, (*landmarkVariables)[i].name);
			CString ctr;
			ctr.Format(_T("%.3f"), (*landmarkVariables)[i].value);
			sizeControl.SetItem(i, 1, LVIF_TEXT, ctr, 0, 0, 0, NULL);
		}
		showLandmarks.SetCheck(true);
		showLandmarksMode = 1;

		dlg.DestroyWindow();
	}
}

void CmannequinDlg::OnLandmarksSave()
{
	// TODO: Add your command handler code here
	ofstream outfile(filepath_filename + _T("_landmarks.Landmark"));

	for (int i = 0; i < landmarkVariables->size(); i++) {
		Landmark l = (*landmarkVariables)[i];

		CT2CA pszConvertedAnsiString(l.name);
		string name(pszConvertedAnsiString);

		outfile << name << endl;
		outfile << l.type << endl;
		outfile << l.level << endl;
		outfile << l.value << endl;

		for (int j = 0; j < l.region.size(); j++) {
			outfile << l.region[j] << " ";
		}
		outfile << endl;

		for (int j = 0; j < l.vertIdx.size(); j++) {
			outfile << l.vertIdx[j] << " ";
		}
		outfile << endl << endl;
	}
	outfile.close();

	AfxMessageBox(_T("Landmarks exported."));
}

void CmannequinDlg::OnUpdateModeAdvanced(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	/*
	pCmdUI->SetCheck(TRUE);
	CWnd* pWnd = AfxGetMainWnd();
	CMenu *pMenu = pWnd->GetMenu();
	*/
}

BOOL CmannequinDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (AccelTable != NULL) {
		if (TranslateAccelerator(m_hWnd, AccelTable, pMsg))
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CmannequinDlg::OnScaleout()
{
	// TODO: Add your command handler code here
	scaleFactor.x -= 0.1f;
	scaleFactor.y -= 0.1f;
	scaleFactor.z -= 0.1f;
	scaleMatrix = scale(scaleFactor);

	scaleF -= 0.1f;
	human->scaleFactor = scaleF;
}

void CmannequinDlg::OnScalein()
{
	// TODO: Add your command handler code here
	//scaleMatrix = scale(vec3(1.1f, 1.1f, 1.1f));
	scaleFactor.x += 0.1f;
	scaleFactor.y += 0.1f;
	scaleFactor.z += 0.1f;
	scaleMatrix = scale(scaleFactor);

	scaleF += 0.1f;
	human->scaleFactor = scaleF;
}

void CmannequinDlg::OnViewZoomin()
{
	// TODO: Add your command handler code here
	OnScalein();
}

void CmannequinDlg::OnViewZoomout()
{
	// TODO: Add your command handler code here
	OnScaleout();
}

void CmannequinDlg::OnJointUndo()
{
	// TODO: Add your command handler code here
	if (jointDefineMode == 1 && humanJoints) {
		if (humanJoints->size() > 0)
			humanJoints->pop_back();
	}
}

void CmannequinDlg::OnBnClickedCheckLandmarks()
{
	// TODO: Add your control notification handler code here
	if (showLandmarks.GetCheck()) {
		showLandmarksMode = 1;
	}
	else {
		showLandmarksMode = 0;
	}
}

void CmannequinDlg::OnBnClickedCheckJoints()
{
	// TODO: Add your control notification handler code here
	if (showJoints.GetCheck()) {
		showJointsMode = 1;
	}
	else {
		showJointsMode = 0;
	}
}

void CmannequinDlg::OnNMDblclkSizelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	/*** Retrieve selected item ***/
	LPNMITEMACTIVATE pNMItemActive = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int index = pNMItemActivate->iItem;

	if (humanJoints && landmarkVariables && index >= 0 && index < landmarkVariables->size()) {
		if (editLandmarkDlg == NULL) {
			CWnd *pWnd;
			editLandmarkDlg = new CEditLandmarkDialog(CWnd::FromHandle(this->m_hWnd));
		}
		editLandmarkDlg->name = (*landmarkVariables)[index].name;
		editLandmarkDlg->value = (*landmarkVariables)[index].value;

		if (editLandmarkDlg->DoModal() == IDOK) {
			float oldVal = (*landmarkVariables)[index].value;


			CString ctr;
			ctr.Format(_T("%.3f"), (*landmarkVariables)[index].value);
			sizeControl.SetItem(index, 1, LVIF_TEXT, ctr, 0, 0, 0, NULL);

			// (*landmarkVariables)[index].name = editLandmarkDlg->name;
			// (*landmarkVariables)[index].value = editLandmarkDlg->value;

			// 0: height, 1: bust, 2: waist, 3: hip, 4: arm right, 5: arm left, 6: leg right, 7: leg left, 8: shoulder
			if (index == 0) {
				human->setHeight((*landmarkVariables)[0].value);
			}
			else if (index == 1) {
				human->setBustSize(scaleF, (*landmarkVariables)[1].value);
			}
			else if (index == 2) {
				human->setWaistSize(scaleF, (*landmarkVariables)[2].value);
			}
			else if (index == 3) {
				human->setHipSize(scaleF, (*landmarkVariables)[3].value);
			}
			else if (index == 4) {
				// human->setArmLength(index, (*landmarkVariables)[4].value);
				human->setArmLength(index, editLandmarkDlg->value);
			}
			else if (index == 5) {
				// human->setArmLength(index, (*landmarkVariables)[5].value);
				human->setArmLength(index, editLandmarkDlg->value);
			}
			else if (index == 6) {

			}
			else if (index == 7) {

			}
			else if (index == 8) {
				human->setShoulderLength(index, editLandmarkDlg->value);
			}
			else {
				human->setSize(scaleF, (*landmarkVariables)[index].type, index, oldVal, (*landmarkVariables)[index].value);
			}

			editLandmarkDlg->DestroyWindow();
		}
	}

	*pResult = 0;
}

void CmannequinDlg::OnNMClickSizelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActive = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int index = pNMItemActivate->iItem;

	if (humanJoints && landmarkVariables && index >= 0 && index < landmarkVariables->size()) {
		selItem = index;
	}

	*pResult = 0;
}

void CmannequinDlg::OnBnClickedCheckWireframe()
{
	// TODO: Add your control notification handler code here
	if (showWireframe.GetCheck()) {
		showWireframeMode = 1;
	}
	else {
		showWireframeMode = 0;
	}
}

void CmannequinDlg::OnModifySetthreesize()
{
	// TODO: Add your command handler code here

	if (humanJoints) {
		if (defaultSizesDlg == NULL) {
			CWnd *pWnd;
			defaultSizesDlg = new CDefaultSizesDialog(CWnd::FromHandle(this->m_hWnd));
		}

		for (int i = 0; i < landmarkVariables->size(); i++) {
			if (i == 0) {
				defaultSizesDlg->heightName = (*landmarkVariables)[i].name;
				defaultSizesDlg->heightVal = (*landmarkVariables)[i].value;
			}
			else if (i == 1) {
				defaultSizesDlg->bustName = (*landmarkVariables)[i].name;
				defaultSizesDlg->bustVal = (*landmarkVariables)[i].value;
			}
			else if (i == 2) {
				defaultSizesDlg->waistName = (*landmarkVariables)[i].name;
				defaultSizesDlg->waistVal = (*landmarkVariables)[i].value;
			}
			else if (i == 3) {
				defaultSizesDlg->hipName = (*landmarkVariables)[i].name;
				defaultSizesDlg->hipVal = (*landmarkVariables)[i].value;
			}
		}

		if (defaultSizesDlg->DoModal() == IDOK) {

			for (int i = 0; i < landmarkVariables->size(); i++) {
				if (i == 0) {
					(*landmarkVariables)[i].value = defaultSizesDlg->heightVal;
				}
				else if (i == 1) {
					(*landmarkVariables)[i].value = defaultSizesDlg->bustVal;
				}
				else if (i == 2) {
					(*landmarkVariables)[i].value = defaultSizesDlg->waistVal;
				}
				else if (i == 3) {
					(*landmarkVariables)[i].value = defaultSizesDlg->hipVal;
				}

				CString ctr;
				ctr.Format(_T("%.3f"), (*landmarkVariables)[i].value);
				sizeControl.SetItem(i, 1, LVIF_TEXT, ctr, 0, 0, 0, NULL);
			}

			human->setSize(scaleF, (*landmarkVariables)[0].value, (*landmarkVariables)[1].value, (*landmarkVariables)[2].value, (*landmarkVariables)[3].value);
			defaultSizesDlg->DestroyWindow();
		}
	}
}

void CmannequinDlg::OnBnClickedCheckArmWeight()
{
	// TODO: Add your control notification handler code here
	if (showArmWeight.GetCheck()) {
		showArmWeightMode = 1;
		skinning = &human->skinning;

		//skinning->paintWeights(Segment_UpperArmR, *vertices, *humanJoints);
		//skinning->paintWeights(Segment_UpperArmL, *vertices, *humanJoints);
	}
	else {
		showArmWeightMode = 0;
	}
}

void CmannequinDlg::OnBnClickedCheckElbowWeight()
{
	// TODO: Add your control notification handler code here
	if (showElbowWeight.GetCheck()) {
		showElbowWeightMode = 1;
		skinning = &human->skinning;
		//skinning->paintWeights(Segment_LowerArmR, *vertices, *humanJoints);
		//skinning->paintWeights(Segment_LowerArmL, *vertices, *humanJoints);
	}
	else {
		showElbowWeightMode = 0;
	}
}

void CmannequinDlg::OnBnClickedCheckLegWeight()
{
	// TODO: Add your control notification handler code here
	if (showUpperLegWeight.GetCheck()) {
		showLegWeightMode = 1;
		skinning = &human->skinning;
		//skinning->paintWeights(Segment_UpperLegR, *vertices, *humanJoints);
		//skinning->paintWeights(Segment_UpperLegL, *vertices, *humanJoints);
	}
	else {
		showLegWeightMode = 0;
	}
}

void CmannequinDlg::OnBnClickedCheckKneeWeight()
{
	// TODO: Add your control notification handler code here
	if (showLowerLegWeight.GetCheck()) {
		showKneeWeightMode = 1;
		skinning = &human->skinning;
		//skinning->paintWeights(Segment_LowerLegR, *vertices, *humanJoints);
		//skinning->paintWeights(Segment_LowerLegL, *vertices, *humanJoints);
	}
	else {
		showKneeWeightMode = 0;
	}
}

void CmannequinDlg::OnViewInitialize()
{
	// TODO: Add your command handler code here
	if (human) {
		scaleFactor = vec3(1, 1, 1);
		scaleMatrix = scale(scaleFactor);

		scaleF = 1;
		human->scaleFactor = scaleF;
	}
}

void CmannequinDlg::OnViewFitto()
{
	// TODO: Add your command handler code here
	if (human) {
		float human_width = abs(human->leftMostOffset);
		float human_height = abs(human->topMostLevel);

		scaleF = 1;
		if (human_width >= 10 || human_height >= 10)
			scaleF = 0.1;
		if (human_width >= 100 || human_height >= 100)
			scaleF = 0.01;
		if (human_width >= 1000 || human_height >= 1000)
			scaleF = 0.001;
		if (human_width >= 10000 || human_height >= 10000)
			scaleF = 0.0001;
		if (human_width >= 100000 || human_height >= 100000)
			scaleF = 0.00001;

		scaleFactor = vec3(scaleF);
		human->scaleFactor = scaleF;
		scaleMatrix = scale(scaleFactor);
	}
}

void CmannequinDlg::OnDressformWholetights()
{
	// TODO: Add your command handler code here
	if (human) {
		vector<int> parts;
		parts.push_back(Segment_Neck);
		parts.push_back(Segment_UpperTorso);
		parts.push_back(Segment_LowerTorso);
		parts.push_back(Segment_UpperArmR);
		parts.push_back(Segment_LowerArmR);
		parts.push_back(Segment_UpperArmL);
		parts.push_back(Segment_LowerArmL);
		parts.push_back(Segment_UpperLegR);
		parts.push_back(Segment_LowerLegR);
		parts.push_back(Segment_UpperLegL);
		parts.push_back(Segment_LowerLegL);

		human->writeDressForm(TIGHTS, filepath_filename, parts);
	}
}

void CmannequinDlg::OnDressformDress()
{
	// TODO: Add your command handler code here
	if (human) {
		vector<int> parts;
		parts.push_back(Segment_Neck);
		parts.push_back(Segment_UpperTorso);
		parts.push_back(Segment_LowerTorso);
		parts.push_back(Segment_UpperArmR);
		parts.push_back(Segment_LowerArmR);
		parts.push_back(Segment_UpperArmL);
		parts.push_back(Segment_LowerArmL);
		parts.push_back(Segment_UpperLegR);
		parts.push_back(Segment_LowerLegR);
		parts.push_back(Segment_UpperLegL);
		parts.push_back(Segment_LowerLegL);

		// Make dress
		// TODO :: Handle cleavage
		human->writeDressForm(DRESS, filepath_filename, parts);
	}
}

void CmannequinDlg::OnDressformTop()
{
	// TODO: Add your command handler code here
	if (human) {
		vector<int> parts;
		parts.push_back(Segment_Neck);
		parts.push_back(Segment_UpperTorso);
		parts.push_back(Segment_LowerTorso);
		parts.push_back(Segment_UpperArmR);
		parts.push_back(Segment_LowerArmR);
		parts.push_back(Segment_UpperArmL);
		parts.push_back(Segment_LowerArmL);

		// TODO :: Handle cleavage
		human->writeDressForm(TOP, filepath_filename, parts);
	}
}

void CmannequinDlg::OnDressformPants()
{
	// TODO: Add your command handler code here
	if (human) {
		vector<int> parts;
		parts.push_back(Segment_LowerTorso);
		parts.push_back(Segment_UpperLegR);
		parts.push_back(Segment_LowerLegR);
		parts.push_back(Segment_UpperLegL);
		parts.push_back(Segment_LowerLegL);

		// TODO :: Handle cleavage
		human->writeDressForm(PANTS, filepath_filename, parts);
	}
}

void CmannequinDlg::OnDressformSkirt()
{
	// TODO: Add your command handler code here
	if (human) {
		vector<int> parts;
		parts.push_back(Segment_UpperLegR);
		parts.push_back(Segment_LowerLegR);
		parts.push_back(Segment_UpperLegL);
		parts.push_back(Segment_LowerLegL);

		// TODO :: Make Skirt
		// TODO :: Handle cleavage
		human->writeDressForm(SKIRT, filepath_filename, parts);
	}
}

void CmannequinDlg::OnJointsExpand()
{
	// TODO: Add your command handler code here
	if (humanJoints->size() < ExpandedJointNum) {
		human->expandJoint();
	}
}


void CmannequinDlg::OnFileExporthuman()
{
	// TODO: Add your command handler code here
	if (human) {
		human->writeToHuman(filepath_filename);
	}
}


void CmannequinDlg::OnLvnItemchangedSizelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CmannequinDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CmannequinDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}



void CmannequinDlg::OnTextureSelectarea()
{
	// TODO: Add your command handler code here
	drawMode = 1;
}

void CmannequinDlg::OnStnClickedPicture()
{
	// TODO: Add your control notification handler code here
	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect);

	float width = rect.Width();
	float height = rect.Height();

	//ScreenToClient(&rect2); // For mouse event
	CPoint point;

	if (human && jointDefineMode) {
		if (rect.PtInRect(point)) {
			GetCursorPos(&point);
			GetDlgItem(IDC_PICTURE)->ScreenToClient(&point);

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
			int jointIdx = 0;
			if (humanJoints)
				jointIdx = humanJoints->size();
			human->setJoint(scaleF, jointIdx, newPos[0], newPos[1]);

			humanJoints = &human->joints;
			showJoints.SetCheck(true);
			showJointsMode = 1;
		}
	}

	if (human && drawMode) {
		if (rect.PtInRect(point)) {
			GetCursorPos(&point);
			GetDlgItem(IDC_PICTURE)->ScreenToClient(&point);

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
			/*
			int jointIdx = 0;
			if (humanJoints)
				jointIdx = humanJoints->size();
			human->setJoint(scaleF, jointIdx, newPos[0], newPos[1]);

			humanJoints = &human->joints;
			showJoints.SetCheck(true);
			showJointsMode = 1;
			*/
		}
	}
}


void CmannequinDlg::OnBnClickedShowcrotch()
{
	// TODO: Add your control notification handler code here
	if (showCrotch) {
		showCrotch = 0;
	}
	else {
		showCrotch = 1;
	}
}


void CmannequinDlg::OnTextureSetbra()
{
	// TODO: Add your command handler code here
	isBra = 1;
	human->setBra();
}


void CmannequinDlg::OnTextureSetunderpants()
{
	// TODO: Add your command handler code here
	isUnderpants = 1;
	human->setUnderpants();
}
