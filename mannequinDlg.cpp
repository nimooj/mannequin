
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
	//Create OpenGL Context
	if (!GetRenderingContext()) {
		AfxMessageBox(CString("Error in OpenGL initialization."));
		return -1;
	}

	// Get Rect size
	CRect rect;
	GetClientRect(&rect);
	width = rect.Width();
	height = rect.Height();

	camera = Camera();

	bodyProxies = BodyProxies();
	bodyLayers = bodyProxies.getBodyLayers();
	jointTree = bodyProxies.getJointTree();

	vertices = bodyProxies.getVerts();
	indices = bodyProxies.getIndices();
	normals = bodyProxies.getNormals();

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);

	/*** OPENGL 3.3 ***/
	defineMannequinVAO(vao);
	defineLightVAO(light_vao);
	/*****************/

	SetTimer(1000, 30, NULL);

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
	/*****************/

	if (FALSE == ::wglDeleteContext(m_hRC)) {
		AfxMessageBox(CString("wglDeleteContext failed"));
	}

}

void CmannequinDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	// TODO: Add your message handler code here and/or call default
	vec3 pos = camera.cameraPosition;
	vec3 dir = camera.cameraFront;
	vec3 up = camera.cameraUp;

	vec3 color = vec3(1.0f,1.0f, 1.0f);
	vec3 lightColor = vec3(0.8f, 0.8f, 0.8f);
	vec3 lightPos = vec3(0.0f, 10.0f, 15.0f);
	vec3 cameraPos = pos;

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(mannequinShaderProgram);
	GLint color_attribute = glGetUniformLocation(mannequinShaderProgram, "objColor");
	glUniform3fv(color_attribute, 1, &color[0]);
	GLint lightColor_attribute = glGetUniformLocation(mannequinShaderProgram, "lightColor");
	glUniform3fv(lightColor_attribute, 1, &lightColor[0]);
	GLint lightPos_attribute = glGetUniformLocation(mannequinShaderProgram, "lightPos");
	glUniform3fv(lightPos_attribute, 1, &lightPos[0]);
	GLint cameraPos_attribute = glGetUniformLocation(mannequinShaderProgram, "cameraPos");
	glUniform3fv(cameraPos_attribute, 1, &cameraPos[0]);

	/*** Handling View Matrix ***/
	//mat4 projectionMatrix = perspective((float)radians(45.0f), width / (float)height, 0.1f, 100.0f);
	mat4 projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.f, 0.0f, 100.0f);
	mat4 viewMatrix = lookAt(pos, dir, up);
	mat4 scaleMatrix = scale(vec3(0.8f, 0.8f, 0.8f));
	mat4 modelMatrix =  scaleMatrix * mat4(1.0f);

	GLuint projectionID = glGetUniformLocation(mannequinShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	GLuint viewID = glGetUniformLocation(mannequinShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	GLuint modelID = glGetUniformLocation(mannequinShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);
	/***************************/

	/*** OPENGL 3.3 ***/
	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 580);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(lightShaderProgram);
	projectionID = glGetUniformLocation(lightShaderProgram, "projection");
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
	viewID = glGetUniformLocation(lightShaderProgram, "view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);

	modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, lightPos);
	modelMatrix = scale(modelMatrix, vec3(4.0f));
	modelID = glGetUniformLocation(lightShaderProgram, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(light_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	/******************/

	/*
	glPointSize(3);
	glColor4f(1, 1, 1, 0.5);
	glPushMatrix();
	for (int i = 0; i < bodyLayers.getSize(); i++) {
		Layer l = bodyLayers.getLayer(i);
		vector<Vertex> lv = l.getVerts();
		glBufferData(GL_ARRAY_BUFFER, lv.size() * sizeof(glm::vec3), &lv[0], GL_STATIC_DRAW);
		//for (int j = 0; j < lv.size(); j++) {
			//glBegin(GL_POINTS);
			//glVertex3f(lv[j].x, lv[j].y, lv[j].z);
			//glEnd();
		//}
	}


	glPointSize(5);
	glColor3f(1, 0, 0);

	vector<Joint> jt = jointTree.getJointTree();
	int i = 0;
	while (i < jointTree.getSize()) {
		Vertex jv = jt[i].getCoord();
		glBegin(GL_POINTS);
		glVertex3f(jv.x, jv.y, jv.z);
		//while (jt[i].hasChildren) {
			//glVertex3f();
		//}

		i++;
		glEnd();
	}

	glPopMatrix();
	glFlush();
	*/

	SwapBuffers(m_pDC->GetSafeHdc());
}

void CmannequinDlg::defineMannequinVAO(GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	mannequinShaderProgram = loadShaders("shaders/MannequinVertexShader.vertexshader", "shaders/MannequinFragmentShader.fragmentshader");

	vector<vec3> position, normal;
	vector<int> indexing;
	//position.assign(vertices.size(), vec3(0, 0, 0));

	/*
	position.push_back(vec3(0, 0.5, 0));
	position.push_back(vec3(0.5, -0.5, 0));
	position.push_back(vec3(-0.5, -0.5, 0));
	color.push_back(vec3(1, 0, 0));
	color.push_back(vec3(0, 1, 0));
	color.push_back(vec3(0, 0, 1));
	*/

	for (int i = 0; i < vertices.size(); i++) {
		Vertex bv = vertices[i];
		//position[bv.idx - 1] = vec3(bv.x, bv.y, bv.z);
		position.push_back(vec3(bv.x, bv.y, bv.z));
	}

	for (int i = 0; i < normals.size(); i++) {
		Vertex nv = normals[i];
		normal.push_back(vec3(nv.x, nv.y, nv.z));
	}
	
	for (int i = 0; i < indices.size(); i++) {
		indexing.push_back(indices[i] - 1);
	}

	// Position
	GLuint position_vbo;
	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), &position[0], GL_STATIC_DRAW);

	GLint position_attribute = glGetAttribLocation(mannequinShaderProgram, "position");
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

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

	//glBindVertexArray(0);
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

void CmannequinDlg::OnStnClickedPicture()
{
	// TODO: Add your control notification handler code here
}

void CmannequinDlg::OnBnClickedExport()
{
	// TODO: Add your control notification handler code here
	bodyProxies.writeToOBJ(vertices, indices, normals);
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
