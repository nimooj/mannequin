#include "stdafx.h"
#include "CJointDialog.h"


CJointDialog::CJointDialog()
{
	vertices = NULL;
	indices = NULL;
	joints = NULL;
}

CJointDialog::CJointDialog(CWnd* pParent) 
	: CDialogEx(IDD_JOINTDIALOG, pParent) {

}

CJointDialog::~CJointDialog()
{
}

void CJointDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JOINTLIST, jointList);
	DDX_Control(pDX, IDC_JOINTFIELD, jointField);
}

BOOL CJointDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	GetDlgItem(IDC_JOINTFIELD)->GetClientRect(&rect);
	screenWidth = rect.Width();
	screenHeight = rect.Height();
	glViewport(0, 0, screenWidth, screenHeight);

	if (!GetRenderingContext()) {
		AfxMessageBox(CString("Error in joint OpenGL initialization."));
		return FALSE;
	}

	if (joints) {
		for (int i = 0; i < joints->size(); i++) {
			//jointList.InsertString(i, (*joints)[i].id);
		}
	}

	Camera camera = Camera();

	SetTimer(0, 300, NULL);

	AccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR2));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CJointDialog, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_JOINTDELETE, &CJointDialog::OnBnClickedJointdelete)
	ON_BN_CLICKED(IDC_JOINTSET, &CJointDialog::OnBnClickedJointsave)
	ON_BN_CLICKED(IDC_MOVEUP, &CJointDialog::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, &CJointDialog::OnBnClickedMovedown)
	ON_STN_CLICKED(IDC_JOINTFIELD, &CJointDialog::OnStnClickedJointfield)
	ON_BN_CLICKED(IDC_RIGHT, &CJointDialog::OnBnClickedRight)
	ON_BN_CLICKED(IDC_FRONT, &CJointDialog::OnBnClickedFront)
	ON_BN_CLICKED(IDC_BACK, &CJointDialog::OnBnClickedBack)
	ON_BN_CLICKED(IDC_LEFT, &CJointDialog::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_UP, &CJointDialog::OnBnClickedUp)
	ON_BN_CLICKED(IDC_JOINTUNDO, &CJointDialog::OnBnClickedJointUndo)
END_MESSAGE_MAP()

void CJointDialog::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

void CJointDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0) {
		defineVAO(vao);

		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT); // || GL_DEPTH_BUFFER_BIT);

		projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.f, 0.0f, 100.0f);
		viewMatrix = lookAt(camera.cameraPosition, camera.cameraFront, camera.cameraUp);
		modelMatrix = scaleMatrix * mat4(1.0f);

		glUseProgram(shaderProgram);
		GLuint projectionID = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
		GLuint viewID = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
		GLuint modelID = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(position_attribute);
		glDisableVertexAttribArray(color_attribute);
		glBindVertexArray(0);

		if (joints) {
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
			glDrawArrays(GL_POINTS, 0, joints->size());

			glDisableVertexAttribArray(joint_position_attribute);
			glDisableVertexAttribArray(joint_color_attribute);
			glBindVertexArray(0);
		}

		glDeleteProgram(shaderProgram);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &position_vbo);
		glDeleteBuffers(1, &color_vbo);
		glDeleteBuffers(1, &ebo);

		glDeleteProgram(jointShaderProgram);
		glDeleteVertexArrays(1, &joint_vao);
		glDeleteBuffers(1, &joint_position_vbo);
		glDeleteBuffers(1, &joint_color_vbo);

		SwapBuffers(m_pDC->GetSafeHdc());
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CJointDialog::OnBnClickedJointdelete()
{
	// TODO: Add your control notification handler code here

}

void CJointDialog::OnBnClickedJointsave()
{
	// TODO: Add your control notification handler code here

}

void CJointDialog::OnBnClickedMoveup()
{
	// TODO: Add your control notification handler code here
}

void CJointDialog::OnBnClickedMovedown()
{
	// TODO: Add your control notification handler code here
}

void CJointDialog::defineVAO(GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	verts.clear();
	inds.clear();
	color.clear();

	shaderProgram = loadShaders("shaders/LandmarkVertexShader.vertexshader", "shaders/LandmarkFragmentShader.fragmentshader");

	for (int i = 0; i < vertices->size(); i++) {
		verts.push_back(vec3((*vertices)[i].x, (*vertices)[i].y, (*vertices)[i].z));
		color.push_back(vec3(0, 0, 0));
	}

	for (int i = 0; i < indices->size(); i++) {
		inds.push_back((*indices)[i] - 1);
	}
	/*
	*/

	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(vec3), &verts[0], GL_STATIC_DRAW);

	position_attribute = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	// Color for different segment parts
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), &color[0], GL_STATIC_DRAW);

	color_attribute = glGetAttribLocation(shaderProgram, "color");
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(int), &inds[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void CJointDialog::defineJointVAO(GLuint& joint_vao) {
	glGenVertexArrays(1, &joint_vao);
	glBindVertexArray(joint_vao);

	jointShaderProgram = loadShaders("shaders/JointVertexShader.vertexshader", "shaders/JointFragmentShader.fragmentshader");

	vector<vec3> njoints; 
	vector<vec3> joint_colors;

	for ( int i = 0; i < joints->size(); i++ ) {
		Vertex v = (*joints)[i].getCoord();
		njoints.push_back(vec3(v.x, v.y, v.z));
		joint_colors.push_back(vec3(1, 0, 0));
	}

	/*
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
	*/

	if (!njoints.empty()) {
		glGenBuffers(1, &joint_position_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, joint_position_vbo);
		glBufferData(GL_ARRAY_BUFFER, njoints.size() * sizeof(vec3), &njoints[0], GL_STATIC_DRAW);

		joint_position_attribute = glGetAttribLocation(jointShaderProgram, "position");
		glVertexAttribPointer(joint_position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(joint_position_attribute);

		glGenBuffers(1, &joint_color_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, joint_color_vbo);
		glBufferData(GL_ARRAY_BUFFER, joint_colors.size() * sizeof(vec3), &joint_colors[0], GL_STATIC_DRAW);

		joint_color_attribute = glGetAttribLocation(jointShaderProgram, "color");
		glVertexAttribPointer(joint_color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(joint_color_attribute);

		glBindVertexArray(0);
	}
}

GLuint CJointDialog::loadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
	// Create shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader from file
	string vertexShaderSource;
	ifstream vertexShaderStream(vertexFilePath, ios::in);
	if (vertexShaderStream.is_open()) {
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
	if (fragmentShaderStream.is_open()) {
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

BOOL CJointDialog::GetRenderingContext()
{
	CWnd* pImage = GetDlgItem(IDC_JOINTFIELD);
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

BOOL CJointDialog::GetOldStyleRenderingContext() {
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

void CJointDialog::OnStnClickedJointfield()
{
	// TODO: Add your control notification handler code here
	CRect rect;
	GetDlgItem(IDC_JOINTFIELD)->GetClientRect(&rect);

	float width = rect.Width();
	float height = rect.Height();

	//ScreenToClient(&rect2); // For mouse event
	CPoint point;

	if (rect.PtInRect(point)) {
		GetCursorPos(&point);
		GetDlgItem(IDC_JOINTFIELD)->ScreenToClient(&point);

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
		if (joints)
			jointIdx = joints->size();

		human->setJoint(scaleF, jointIdx, newPos[0], newPos[1]);

		joints = &human->joints;
	}
}

void CJointDialog::OnBnClickedRight()
{
	// TODO: Add your control notification handler code here
	camera.ViewRight();
}

void CJointDialog::OnBnClickedFront()
{
	// TODO: Add your control notification handler code here
	camera.ViewFront();
}

void CJointDialog::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	camera.ViewBack();
}

void CJointDialog::OnBnClickedLeft()
{
	// TODO: Add your control notification handler code here
	camera.ViewLeft();
}

void CJointDialog::OnBnClickedUp()
{
	// TODO: Add your control notification handler code here
	camera.ViewUp();
}

void CJointDialog::OnBnClickedJointUndo()
{
	// TODO: Add your control notification handler code here
	cout << "!!!!!!!!!!!!" << endl;
	AfxMessageBox(_T("!!!!!!!!"));

	/*
	if (joints) {
		cout << "fddd" << endl;
		human->undoJoint();
		joints = &human->joints;
	}
	*/
}

BOOL CJointDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (AccelTable != NULL) {
		if (TranslateAccelerator(m_hWnd, AccelTable, pMsg))
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
