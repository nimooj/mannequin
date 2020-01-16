#pragma once
#include "resource.h"
#include <afxdialogex.h>

class CDefaultSizesDialog :
	public CDialogEx
{
public:
	CDefaultSizesDialog();
	~CDefaultSizesDialog();
	CDefaultSizesDialog(CWnd* pParent);
	enum { IDD = IDD_DEFAULT_DIALOG };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();


	virtual void DoDataExchange(CDataExchange* pDX);
	CEdit showHeightValue;
	CEdit showBustValue;
	CEdit showWaistValue;
	CEdit showHipValue;
	CStatic showHeightName;
	CStatic showBustName;
	CStatic showWaistName;
	CStatic showHipName;

public :
	CString heightName, bustName, waistName, hipName;
	float heightVal, bustVal, waistVal, hipVal;
	afx_msg void OnBnClickedOk();
};

