#pragma once

#include "resource.h"
#include "Landmark.h"

#include <afxdialogex.h>
class CEditLandmarkDialog :
	public CDialogEx
{
public:
	CEditLandmarkDialog();
	CEditLandmarkDialog(CWnd* pParent);
	~CEditLandmarkDialog();
	enum { IDD = IDD_EDIT_LANDMARK };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	CEdit nameEdit;
	CEdit valueEdit;

public: 
	CString name;
	float value;
};

