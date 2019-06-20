#pragma once
#include "resource.h"
#include <afxdialogex.h>

class CJointDialog :
	public CDialogEx
{
public:
	CJointDialog();
	CJointDialog(CWnd* pParent);
	enum { IDD = IDD_JOINTDIALOG };
	~CJointDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

