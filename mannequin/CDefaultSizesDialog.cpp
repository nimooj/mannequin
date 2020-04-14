#include "stdafx.h"
#include "CDefaultSizesDialog.h"


CDefaultSizesDialog::CDefaultSizesDialog()
{
}

CDefaultSizesDialog::CDefaultSizesDialog(CWnd* pParent) 
	: CDialogEx(IDD_DEFAULT_DIALOG, pParent) 
{
}

CDefaultSizesDialog::~CDefaultSizesDialog()
{
}
BEGIN_MESSAGE_MAP(CDefaultSizesDialog, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CDefaultSizesDialog::OnBnClickedOk)
END_MESSAGE_MAP()


void CDefaultSizesDialog::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CDefaultSizesDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString ctr;
	// showHeightName.SetWindowTextW(heightName);
	showHeightName.SetWindowTextA(heightName);
	ctr.Format(_T("%.3f"), heightVal);
	// showHeightValue.SetWindowTextW(ctr);
	showHeightValue.SetWindowTextA(ctr);

	// showBustName.SetWindowTextW(bustName);
	showBustName.SetWindowTextA(bustName);
	ctr.Format(_T("%.3f"), bustVal);
	// showBustValue.SetWindowTextW(ctr);
	showBustValue.SetWindowTextA(ctr);

	// showWaistName.SetWindowTextW(waistName);
	showWaistName.SetWindowTextA(waistName);
	ctr.Format(_T("%.3f"), waistVal);
	// showWaistValue.SetWindowTextW(ctr);
	showWaistValue.SetWindowTextA(ctr);

	// showHipName.SetWindowTextW(hipName);
	showHipName.SetWindowTextA(hipName);
	ctr.Format(_T("%.3f"), hipVal);
	// showHipValue.SetWindowTextW(ctr);
	showHipValue.SetWindowTextA(ctr);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDefaultSizesDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VALUE_HEIGHT, showHeightValue);
	DDX_Control(pDX, IDC_EDIT_VALUE_BUST, showBustValue);
	DDX_Control(pDX, IDC_EDIT_VALUE_WAIST, showWaistValue);
	DDX_Control(pDX, IDC_EDIT_VALUE_HIP, showHipValue);
	DDX_Control(pDX, IDC_STATIC_HEIGHT, showHeightName);
	DDX_Control(pDX, IDC_STATIC_BUST, showBustName);
	DDX_Control(pDX, IDC_STATIC_WAIST, showWaistName);
	DDX_Control(pDX, IDC_STATIC_HIP, showHipName);
}

void CDefaultSizesDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	CString ctr;
	// showHeightValue.GetWindowTextW(ctr);
	showHeightValue.GetWindowTextA(ctr);
	heightVal = _ttof(ctr);

	// showBustValue.GetWindowTextW(ctr);
	showBustValue.GetWindowTextA(ctr);
	bustVal = _ttof(ctr);

	// showWaistValue.GetWindowTextW(ctr);
	showWaistValue.GetWindowTextA(ctr);
	waistVal = _ttof(ctr);

	// showHipValue.GetWindowTextW(ctr);
	showHipValue.GetWindowTextA(ctr);
	hipVal = _ttof(ctr);
}
