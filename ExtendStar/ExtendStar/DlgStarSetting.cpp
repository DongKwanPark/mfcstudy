// DlgStarSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendStar.h"
#include "DlgStarSetting.h"
#include "afxdialogex.h"


// CDlgStarSetting dialog

IMPLEMENT_DYNAMIC(CDlgStarSetting, CDialogEx)

CDlgStarSetting::CDlgStarSetting(const int& nCount, CWnd* pParent /*=NULL*/)
	: m_nCount( nCount ), CDialogEx(CDlgStarSetting::IDD, pParent)
{
}

CDlgStarSetting::~CDlgStarSetting()
{
}

void CDlgStarSetting::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT_STARCOUNT, m_editStarCount);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStarSetting, CDialogEx)
END_MESSAGE_MAP()


// CDlgStarSetting message handlers


BOOL CDlgStarSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strCount;
	strCount.Format( _T("%d"), m_nCount );
	m_editStarCount.SetWindowText( strCount );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgStarSetting::OnOK()
{
	CString strCount;
	m_editStarCount.GetWindowText( strCount );
	int nCount = _ttoi( strCount );
	if( nCount < 1 || nCount > 100 )
	{
		AfxMessageBox( _T("입력값의 범위는 1 ~ 100 사이 입니다.") );
		return ;
	}
	m_nCount = nCount;

	CDialogEx::OnOK();
}

