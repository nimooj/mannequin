#include "stdafx.h"
#include "CJointDialog.h"


CJointDialog::CJointDialog()
{
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
}


BOOL CJointDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_MESSAGE_MAP(CJointDialog, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CJointDialog::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CJointDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
}
