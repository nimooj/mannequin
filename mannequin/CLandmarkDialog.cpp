#include "stdafx.h"
#include "afxdialogex.h"

#include "CLandmarkDialog.h"

BEGIN_MESSAGE_MAP(CLandmarkDialog, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LENGTH, &CLandmarkDialog::OnBnClickedLength)
	ON_BN_CLICKED(IDC_GIRTH, &CLandmarkDialog::OnBnClickedGirth)
	ON_BN_CLICKED(IDC_BUTTON1, &CLandmarkDialog::OnBnClickedButton1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LANDMARKSLIDER, &CLandmarkDialog::OnNMReleasedcaptureLandmarkslider)
	ON_BN_CLICKED(IDC_FRONT, &CLandmarkDialog::OnBnClickedFront)
	ON_BN_CLICKED(IDC_BACK, &CLandmarkDialog::OnBnClickedBack)
	ON_BN_CLICKED(IDC_RIGHT, &CLandmarkDialog::OnBnClickedRight)
	ON_BN_CLICKED(IDC_LEFT, &CLandmarkDialog::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_UP, &CLandmarkDialog::OnBnClickedUp)
	ON_BN_CLICKED(IDC_MOVEUP, &CLandmarkDialog::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, &CLandmarkDialog::OnBnClickedMovedown)
	ON_LBN_SELCHANGE(IDC_LANDMARKLIST, &CLandmarkDialog::OnLbnSelchangeLandmarklist)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, &CLandmarkDialog::OnBnClickedRemoveButton)
END_MESSAGE_MAP()

CLandmarkDialog::CLandmarkDialog() {

}

CLandmarkDialog::~CLandmarkDialog() {

}

CLandmarkDialog::CLandmarkDialog(CWnd* pParent) 
	: CDialogEx(IDD_LANDMARKDIALOG, pParent) 
{
}

void CLandmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LANDMARKFIELD, landmarkField);
	DDX_Control(pDX, IDC_LANDMARKLIST, landmarkList);
	DDX_Control(pDX, IDC_GIRTH, girthType);
	DDX_Control(pDX, IDC_LENGTH, lengthType);
	DDX_Control(pDX, IDC_VARNAME, variableEdit);
	DDX_Control(pDX, IDC_CHECK_ALL, showAllBodySegment);
	DDX_Control(pDX, IDC_CHECK_HEAD, showHeadBodySegment);
	DDX_Control(pDX, IDC_CHECK_NECK, showNeckBodySegment);
	DDX_Control(pDX, IDC_CHECK_UPPERTORSO, showUpperTorsoBodySegment);
	DDX_Control(pDX, IDC_CHECK_LOWERTORSO, showLowerTorsoBodySegment);
	DDX_Control(pDX, IDC_CHECK_UPPERARMR, showUpperArmRBodySegment);
	DDX_Control(pDX, IDC_CHECK_LOWERARMR, showLowerArmRBodySegment);
	DDX_Control(pDX, IDC_CHECK_HANDR, showHandRBodySegment);
	DDX_Control(pDX, IDC_CHECK_UPPERARML, showUpperArmLBodySegment);
	DDX_Control(pDX, IDC_CHECK_LOWERARML, showLowerArmLBodySegment);
	DDX_Control(pDX, IDC_CHECK_HANDL, showHandLBodySegment);
	DDX_Control(pDX, IDC_CHECK_UPPERLEGR, showUpperLegRBodySegment);
	DDX_Control(pDX, IDC_CHECK_LOWERLEGR, showLowerLegRBodySegment);
	DDX_Control(pDX, IDC_CHECK_FOOTR, showFootRBodySegment);
	DDX_Control(pDX, IDC_CHECK_UPPERLEGL, showUpperLegLBodySegment);
	DDX_Control(pDX, IDC_CHECK_LOWERLEGL, showLowerLegLBodySegment);
	DDX_Control(pDX, IDC_CHECK_FOOTL, showFootLBodySegment);
	DDX_Control(pDX, IDC_LANDMARKSLIDER, landmarkSlider);
}

void CLandmarkDialog::OnDestroy()
{
	CDialogEx::OnDestroy();

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &position_vbo);
	glDeleteBuffers(1, &color_vbo);
	glDeleteBuffers(1, &ebo);

	glDeleteProgram(lineShaderProgram);
	glDeleteVertexArrays(1, &line_vao);
	glDeleteBuffers(1, &line_position_vbo);
	glDeleteBuffers(1, &line_color_vbo);

	glDeleteProgram(landmarkShaderProgram);
	glDeleteVertexArrays(1, &landmark_vao);
	glDeleteBuffers(1, &landmark_position_vbo);
	glDeleteBuffers(1, &landmark_color_vbo);

	// TODO: Add your message handler code here
	if (FALSE == ::wglDeleteContext(m_hRC)) {
		AfxMessageBox(CString("wglDeleteContext failed"));
	}
}

BOOL CLandmarkDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	GetDlgItem(IDC_LANDMARKFIELD)->GetClientRect(&rect);
	screenWidth = rect.Width();
	screenHeight = rect.Height();
	glViewport(0, 0, screenWidth, screenHeight);

	if (!GetRenderingContext()) {
		AfxMessageBox(CString("Error in joint OpenGL initialization."));
		return FALSE;
	}

	girthType.SetCheck(true);
	lengthType.SetCheck(false);

	for (int i = 0; i < variables->size(); i++) {
		landmarkList.InsertString(i, (*variables)[i].name);
	}

	for (int i = 0; i < SegmentNum; i++) {
		float r = rand() / double(RAND_MAX);
		float g = rand() / double(RAND_MAX);
		float b = rand() / double(RAND_MAX);
		colorArray.push_back(vec3(r, g, b));
	}

	Camera camera = Camera();

	area.push_back(vec2(-100, 0));
	area.push_back(vec2(100, 0));

	landmarkSlider.SetRange(0, screenHeight);
	landmarkSlider.SetPos(screenHeight/2);
	landmarkSlider.SetTicFreq(1);
	landmarkSlider.SetLineSize(1);

	SetTimer(0, 300, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CLandmarkDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == 0) {
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

		defineVAO(vao);

		projectionMatrix = ortho(-10.0f , 10.0f , -10.0f , 10.f , 0.0f, 100.0f);
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

		for (int i = 0; i < variables->size(); i++) {
			defineLandmarkVAO(i, landmark_vao);
			glUseProgram(landmarkShaderProgram);

			projectionID = glGetUniformLocation(landmarkShaderProgram, "projection");
			glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
			viewID = glGetUniformLocation(landmarkShaderProgram, "view");
			glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
			modelID = glGetUniformLocation(landmarkShaderProgram, "model");
			glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

			if (i == selItem)
				glLineWidth(3);
			else
				glLineWidth(1);

			glBindVertexArray(landmark_vao);
			glDrawArrays(GL_LINE_LOOP, 0, varPos.size());

			glDisableVertexAttribArray(landmark_position_attribute);
			glDisableVertexAttribArray(landmark_color_attribute);
			glBindVertexArray(0);
		}

		/**/
		defineLineVAO(line_vao);
		glUseProgram(lineShaderProgram);

		projectionID = glGetUniformLocation(lineShaderProgram, "projection");
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
		viewID = glGetUniformLocation(lineShaderProgram, "view");
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
		modelID = glGetUniformLocation(lineShaderProgram, "model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

		glBindVertexArray(line_vao);
		if (area.size() == 2) {
			glLineWidth(1);
			glDrawArrays(GL_LINES, 0, area.size());
		}
		else if (area.size() == 1) {
			glPointSize(3);
			glDrawArrays(GL_POINTS, 0, area.size());

		}
		glDisableVertexAttribArray(line_position_attribute);
		glDisableVertexAttribArray(line_color_attribute);
		glBindVertexArray(0);

		SwapBuffers(m_pDC->GetSafeHdc());
	}
}

void CLandmarkDialog::OnBnClickedLength()
{
	// TODO: Add your control notification handler code here
	girthType.SetCheck(false);
	lengthType.SetCheck(true);
}

void CLandmarkDialog::OnBnClickedGirth()
{
	// TODO: Add your control notification handler code here
	girthType.SetCheck(true);
	lengthType.SetCheck(false);
}

void CLandmarkDialog::defineVAO(GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	shaderProgram = loadShaders("shaders/LandmarkVertexShader.vertexshader", "shaders/LandmarkFragmentShader.fragmentshader");

	verts.clear();
	inds.clear();
	vector<vec3> color;

	for (int i = 0; i < vertices->size(); i++) {
		verts.push_back(vec3((*vertices)[i].x, (*vertices)[i].y, (*vertices)[i].z));
		color.push_back(vec3(0, 0, 0));
	}

	for (int i = 0; i < indices->size(); i++) {
		inds.push_back((*indices)[i] - 1);
	}

	if (showAllBodySegment.GetCheck()) {
		for ( int i = 0; i < SegmentNum; i++ ) {
			for (int j = 0; j < bodySegment[i].size(); j++) {
				color[bodySegment[i][j] - 1] = colorArray[i];
			}
		}
	}
	else {
		if (showHeadBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_Head].size(); i++) {
				color[bodySegment[Segment_Head][i] - 1] = colorArray[Segment_Head];
			}
		}

		if (showNeckBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_Neck].size(); i++) {
				color[bodySegment[Segment_Neck][i] - 1] = colorArray[Segment_Neck];
			}
		}

		if (showUpperTorsoBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_UpperTorso].size(); i++) {
				color[bodySegment[Segment_UpperTorso][i] - 1] = colorArray[Segment_UpperTorso];
			}
		}

		if (showLowerTorsoBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_LowerTorso].size(); i++) {
				color[bodySegment[Segment_LowerTorso][i] - 1] = colorArray[Segment_LowerTorso];
			}
		}

		if (showUpperLegRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_UpperLegR].size(); i++) {
				color[bodySegment[Segment_UpperLegR][i] - 1] = colorArray[Segment_UpperLegR];
			}
		}

		if (showLowerLegRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_LowerLegR].size(); i++) {
				color[bodySegment[Segment_LowerLegR][i] - 1] = colorArray[Segment_LowerLegR];
			}
		}

		if (showFootRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_FootR].size(); i++) {
				color[bodySegment[Segment_FootR][i] - 1] = colorArray[Segment_FootR];
			}
		}

		if (showUpperLegLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_UpperLegL].size(); i++) {
				color[bodySegment[Segment_UpperLegL][i] - 1] = colorArray[Segment_UpperLegL];
			}
		}

		if (showLowerLegLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_LowerLegL].size(); i++) {
				color[bodySegment[Segment_LowerLegL][i] - 1] = colorArray[Segment_LowerLegL];
			}
		}

		if (showFootLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_FootL].size(); i++) {
				color[bodySegment[Segment_FootL][i] - 1] = colorArray[Segment_FootL];
			}
		}

		if (showUpperArmRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_UpperArmR].size(); i++) {
				color[bodySegment[Segment_UpperArmR][i] - 1] = colorArray[Segment_UpperArmR];
			}
		}

		if (showLowerArmRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_LowerArmR].size(); i++) {
				color[bodySegment[Segment_LowerArmR][i] - 1] = colorArray[Segment_LowerArmR];
			}
		}

		if (showHandRBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_HandR].size(); i++) {
				color[bodySegment[Segment_HandR][i] - 1] = colorArray[Segment_HandR];
			}
		}

		if (showUpperArmLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_UpperArmL].size(); i++) {
				color[bodySegment[Segment_UpperArmL][i] - 1] = colorArray[Segment_UpperArmL];
			}
		}

		if (showLowerArmLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_LowerArmL].size(); i++) {
				color[bodySegment[Segment_LowerArmL][i] - 1] = colorArray[Segment_LowerArmL];
			}
		}

		if (showHandLBodySegment.GetCheck()) {
			for (int i = 0; i < bodySegment[Segment_HandL].size(); i++) {
				color[bodySegment[Segment_HandL][i] - 1] = colorArray[Segment_HandL];
			}
		}
	}

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

void CLandmarkDialog::defineLandmarkVAO(int idx, GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	landmarkShaderProgram = loadShaders("shaders/GirthVertexShader.vertexshader", "shaders/GirthFragmentShader.fragmentshader");

	varPos.clear();
	vector<vec3> color;

	for (int i = 0; i < (*variables)[idx].vertIdx.size(); i++) {
		Vertex v;
		if (idx == 0 || (*variables)[idx].type == Girth) // Height is Length type but has to go here
			v = (*vertices)[(*variables)[idx].vertIdx[i] - 1];
		else
			v = (*joints)[(*variables)[idx].vertIdx[i]].getCoord();

		// When height
		if (idx == 0) {
			varPos.push_back(vec3(leftMostOffset - 0.5, v.y, 0));
		}
		else {
			if ((*variables)[idx].type == Girth) {
				varPos.push_back(vec3(v.x, (*variables)[idx].level, v.z));
			}
			else if ((*variables)[idx].type == Length) {
				varPos.push_back(vec3(v.x, v.y, v.z));
			}
		}

		color.push_back(vec3(1, 0, 0));
	}

	glGenBuffers(1, &landmark_position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, landmark_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, varPos.size() * sizeof(vec3), &varPos[0], GL_STATIC_DRAW);

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

void CLandmarkDialog::defineLineVAO(GLuint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	lineShaderProgram = loadShaders("shaders/LineVertexShader.vertexshader", "shaders/LineFragmentShader.fragmentshader");

	//area.clear();
	vector<vec3> color;
	for (int i = 0; i < area.size(); i++) {
		color.push_back(vec3(1, 0, 0));
	}

	glGenBuffers(1, &line_position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, line_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, area.size() * sizeof(vec2), &area[0], GL_STATIC_DRAW);

	line_position_attribute = glGetAttribLocation(lineShaderProgram, "position");
	glVertexAttribPointer(line_position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(line_position_attribute);

	glGenBuffers(1, &line_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, line_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), &color[0], GL_STATIC_DRAW);

	line_color_attribute = glGetAttribLocation(lineShaderProgram, "color");
	glVertexAttribPointer(line_color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(line_color_attribute);

	glBindVertexArray(0);
}

void CLandmarkDialog::OnNMReleasedcaptureLandmarkslider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = landmarkSlider.GetPos();

	CPoint point;

	point.x = 0;
	point.y = pos;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)point.x;
	winY = (float)viewport[3] - (float)point.y;

	glReadPixels(point.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	vec4 npos = vec4(posX, posY, posZ, 1);
	vec4 newpos = inverse(modelMatrix) * inverse(viewMatrix) * inverse(projectionMatrix) * npos;

	for (int i = 0; i < area.size(); i++) {
		area[i].y = newpos[1];
	}
}

void CLandmarkDialog::SetGirthVariable(CString n, vector<int> segment, float h) {
	Landmark* l = new Landmark(n, Girth);

	vector<int> secs, cv;
	for (int i = 0; i < segment.size(); i++) {
		secs.push_back(segment[i]);
		cv.insert(cv.end(), bodySegment[segment[i]].begin(), bodySegment[segment[i]].end());
	}

	bool result = l->SetGirthFeature(scaleF, segment, cv, *vertices, h);
	if (result) {
		variables->push_back(*l);

		/*** Reset variable field ***/
		landmarkList.InsertString((*variables).size() - 1, (*variables)[(*variables).size() - 1].name);
	}
	else {
		AfxMessageBox(_T("Unable to define landmark."));
	}
}

void CLandmarkDialog::SetLengthVariable(CString n, vector<int> segment, vector<Joint> relatedJoints) {
	Landmark* l = new Landmark(n, Length);

	bool result = l->SetLengthFeature(segment, relatedJoints);;
	if (result) {
		variables->push_back(*l);

		/*** Reset variable field ***/
		landmarkList.InsertString((*variables).size() - 1, (*variables)[(*variables).size() - 1].name);
	}
	else {
		AfxMessageBox(_T("Unable to define landmark."));
	}
}

void CLandmarkDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString ctr;
	variableEdit.GetWindowTextA(ctr);
	// variableEdit.GetWindowTextW(ctr);
	if (ctr == "") {
		AfxMessageBox(_T("Insert name."));
	}
	else {
		vector<int> secs;
		if (showAllBodySegment.GetCheck()) {
			if (girthType.GetCheck()) {
				for (int i = 0; i < SegmentNum; i++) {
					secs.push_back(i);
				}
				SetGirthVariable(ctr, secs, area[0].y);
			}
			else if (lengthType.GetCheck()) { // Set Every Length
				/*
				for (int i = 0; i < SegmentNum; i++) {
					secs.push_back(i);
				}
				SetLengthVariable(ctr, secs);
				*/
			}
			showAllBodySegment.SetCheck(false);
		}
		else {
			if (girthType.GetCheck()) {
				if (showHeadBodySegment.GetCheck()) {
					secs.push_back(Segment_Head);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showHeadBodySegment.SetCheck(false);
				}
				if (showNeckBodySegment.GetCheck()) {
					secs.push_back(Segment_Neck);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showNeckBodySegment.SetCheck(false);
				}
				if (showUpperTorsoBodySegment.GetCheck()) {
					secs.push_back(Segment_UpperTorso);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showUpperTorsoBodySegment.SetCheck(false);
				}
				if (showLowerTorsoBodySegment.GetCheck()) {
					secs.push_back(Segment_LowerTorso);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showLowerTorsoBodySegment.SetCheck(false);
				}
				if (showUpperLegRBodySegment.GetCheck()) {
					secs.push_back(Segment_UpperLegR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showUpperLegRBodySegment.SetCheck(false);
				}
				if (showLowerLegRBodySegment.GetCheck()) {
					secs.push_back(Segment_LowerLegR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showLowerLegRBodySegment.SetCheck(false);
				}
				if (showFootRBodySegment.GetCheck()) {
					secs.push_back(Segment_FootR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showFootRBodySegment.SetCheck(false);
				}
				if (showUpperLegLBodySegment.GetCheck()) {
					secs.push_back(Segment_UpperLegL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showUpperLegLBodySegment.SetCheck(false);
				}
				if (showLowerLegLBodySegment.GetCheck()) {
					secs.push_back(Segment_LowerLegL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showLowerLegLBodySegment.SetCheck(false);
				}
				if (showFootLBodySegment.GetCheck()) {
					secs.push_back(Segment_FootL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showFootLBodySegment.SetCheck(false);
				}
				if (showUpperArmRBodySegment.GetCheck()) {
					secs.push_back(Segment_UpperArmR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showUpperArmRBodySegment.SetCheck(false);
				}
				if (showLowerArmRBodySegment.GetCheck()) {
					secs.push_back(Segment_LowerArmR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showLowerArmRBodySegment.SetCheck(false);
				}
				if (showHandRBodySegment.GetCheck()) {
					secs.push_back(Segment_HandR);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showHandRBodySegment.SetCheck(false);
				}
				if (showUpperArmLBodySegment.GetCheck()) {
					secs.push_back(Segment_UpperArmL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showUpperArmLBodySegment.SetCheck(false);
				}
				if (showLowerArmLBodySegment.GetCheck()) {
					secs.push_back(Segment_LowerArmL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showLowerArmLBodySegment.SetCheck(false);
				}
				if (showHandLBodySegment.GetCheck()) {
					secs.push_back(Segment_HandL);
					SetGirthVariable(ctr, secs, area[0].y);
					secs.clear();
					showHandLBodySegment.SetCheck(false);
				}
			}
			else if (lengthType.GetCheck()) {
				vector<Joint> rjoints;
				if (showHeadBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_Head);
					rjoints.push_back(Joint(-1, Vertex(0, topMostLevel, 0)));
					rjoints.push_back((*joints)[Joint_neck]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showHeadBodySegment.SetCheck(false);
				}
				if (showNeckBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_Neck);
					rjoints.push_back((*joints)[Joint_neck]);
					rjoints.push_back((*joints)[Joint_shoulderMid]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showNeckBodySegment.SetCheck(false);
				}
				if (showUpperTorsoBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_UpperTorso);
					rjoints.push_back((*joints)[Joint_shoulderMid]);
					rjoints.push_back((*joints)[Joint_waist]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showUpperTorsoBodySegment.SetCheck(false);
				}
				if (showLowerTorsoBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_LowerTorso);
					rjoints.push_back((*joints)[Joint_waist]);
					rjoints.push_back((*joints)[Joint_pelvisMid]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showLowerTorsoBodySegment.SetCheck(false);
				}
				if (showUpperLegRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_UpperLegR);
					rjoints.push_back((*joints)[Joint_pelvisR]);
					rjoints.push_back((*joints)[Joint_kneeR]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showUpperLegRBodySegment.SetCheck(false);
				}
				if (showLowerLegRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_LowerLegR);
					rjoints.push_back((*joints)[Joint_kneeR]);
					rjoints.push_back((*joints)[Joint_ankleR]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showLowerLegRBodySegment.SetCheck(false);
				}
				if (showFootRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_FootR);
					rjoints.push_back((*joints)[Joint_ankleR]);
					rjoints.push_back(Joint(-1, Vertex((*joints)[Joint_ankleR].getCoord().x, bottomMostLevel, 0)));
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showFootRBodySegment.SetCheck(false);
				}
				if (showUpperLegLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_UpperLegL);
					rjoints.push_back((*joints)[Joint_pelvisL]);
					rjoints.push_back((*joints)[Joint_kneeL]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showUpperLegLBodySegment.SetCheck(false);
				}
				if (showLowerLegLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_LowerLegL);
					rjoints.push_back((*joints)[Joint_kneeL]);
					rjoints.push_back((*joints)[Joint_ankleL]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showLowerLegLBodySegment.SetCheck(false);
				}
				if (showFootLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_FootL);
					rjoints.push_back((*joints)[Joint_ankleL]);
					rjoints.push_back(Joint(-1, Vertex((*joints)[Joint_ankleL].getCoord().x, bottomMostLevel, 0)));
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showFootLBodySegment.SetCheck(false);
				}
				if (showUpperArmRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_UpperArmR);
					rjoints.push_back((*joints)[Joint_shoulderR]);
					rjoints.push_back((*joints)[Joint_elbowR]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showUpperArmRBodySegment.SetCheck(false);
				}
				if (showLowerArmRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_LowerArmR);
					rjoints.push_back((*joints)[Joint_elbowR]);
					rjoints.push_back((*joints)[Joint_wristR]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showLowerArmRBodySegment.SetCheck(false);
				}
				if (showHandRBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_HandR);
					rjoints.push_back((*joints)[Joint_wristR]);
					rjoints.push_back(Joint(-1, Vertex(leftMostOffset, leftMostLevel, 0)));
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showHandRBodySegment.SetCheck(false);
				}
				if (showUpperArmLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_UpperArmL);
					rjoints.push_back((*joints)[Joint_shoulderL]);
					rjoints.push_back((*joints)[Joint_elbowL]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showUpperArmLBodySegment.SetCheck(false);
				}
				if (showLowerArmLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_LowerArmL);
					rjoints.push_back((*joints)[Joint_elbowL]);
					rjoints.push_back((*joints)[Joint_wristL]);
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showLowerArmLBodySegment.SetCheck(false);
				}
				if (showHandLBodySegment.GetCheck()) {
					rjoints.clear();
					secs.push_back(Segment_HandL);
					rjoints.push_back((*joints)[Joint_wristL]);
					rjoints.push_back(Joint(-1, Vertex(rightMostOffset, rightMostLevel, 0)));
					SetLengthVariable(ctr, secs, rjoints);
					secs.clear();
					showHandLBodySegment.SetCheck(false);
				}
			}
		}
	}
	// variableEdit.SetWindowTextW(_T(""));
	variableEdit.SetWindowTextA(_T(""));
}

GLuint CLandmarkDialog::loadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
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

BOOL CLandmarkDialog::GetRenderingContext()
{
	CWnd* pImage = GetDlgItem(IDC_LANDMARKFIELD);
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

BOOL CLandmarkDialog::GetOldStyleRenderingContext() {
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

void CLandmarkDialog::OnBnClickedFront()
{
	// TODO: Add your control notification handler code here
	camera.ViewFront();
}

void CLandmarkDialog::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	camera.ViewBack();
}

void CLandmarkDialog::OnBnClickedRight()
{
	camera.ViewRight();
	// TODO: Add your control notification handler code here
}

void CLandmarkDialog::OnBnClickedLeft()
{
	// TODO: Add your control notification handler code here
	camera.ViewLeft();
}

void CLandmarkDialog::OnBnClickedUp()
{
	// TODO: Add your control notification handler code here
	camera.ViewUp();
}

void CLandmarkDialog::OnBnClickedMoveup()
{
	// TODO: Add your control notification handler code here
	if ((*variables)[selItem].type == Girth) {
		vector<int> secs, inds;
		for (int i = 0; i < (*variables)[selItem].region.size(); i++) {
			secs.push_back((*variables)[selItem].region[i]);
		}
		for (int i = 0; i < secs.size(); i++) {
			inds.insert(inds.end(), bodySegment[secs[i]].begin(), bodySegment[secs[i]].end());
		}

		(*variables)[selItem].SetGirthFeature(scaleF, secs, inds, *vertices, (*variables)[selItem].level + 0.2);
	}
}

void CLandmarkDialog::OnBnClickedMovedown()
{
	// TODO: Add your control notification handler code here
	if ((*variables)[selItem].type == Girth) {
		vector<int> secs, inds;
		for (int i = 0; i < (*variables)[selItem].region.size(); i++) {
			secs.push_back((*variables)[selItem].region[i]);
		}
		for (int i = 0; i < secs.size(); i++) {
			inds.insert(inds.end(), bodySegment[secs[i]].begin(), bodySegment[secs[i]].end());
		}

		(*variables)[selItem].SetGirthFeature(scaleF, secs, inds, *vertices, (*variables)[selItem].level - 0.2);
	}
}

void CLandmarkDialog::OnLbnSelchangeLandmarklist()
{
	// TODO: Add your control notification handler code here

	CListBox * pList1 = (CListBox *)GetDlgItem(IDC_LANDMARKLIST);
	selItem = pList1->GetCurSel();
}

void CLandmarkDialog::OnBnClickedRemoveButton()
{
	// TODO: Add your control notification handler code here
	if (selItem < 4) {
		AfxMessageBox(_T("Cannot delete default landmark feaure!"));
	}
	else {
		variables->erase(variables->begin() + selItem);
		landmarkList.DeleteString(selItem);
	}
}
