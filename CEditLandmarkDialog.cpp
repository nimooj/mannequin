#include "stdafx.h"

#include "CEditLandmarkDialog.h"

BEGIN_MESSAGE_MAP(CEditLandmarkDialog, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CEditLandmarkDialog::OnBnClickedOk)
END_MESSAGE_MAP()


CEditLandmarkDialog::CEditLandmarkDialog()
{
}


CEditLandmarkDialog::~CEditLandmarkDialog()
{
}

CEditLandmarkDialog::CEditLandmarkDialog(CWnd* pParent) 
	: CDialogEx(IDD_EDIT_LANDMARK, pParent) 
{
}

void CEditLandmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, nameEdit);
	DDX_Control(pDX, IDC_EDIT_VALUE, valueEdit);
}

void CEditLandmarkDialog::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CEditLandmarkDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	nameEdit.SetWindowTextW(name);

	CString ctr;
	ctr.Format(_T("%.3f"), value);
	valueEdit.SetWindowTextW(ctr);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CEditLandmarkDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	nameEdit.GetWindowTextW(name);

	CString ctr;
	valueEdit.GetWindowTextW(ctr);
	value = _ttof(ctr);
}
