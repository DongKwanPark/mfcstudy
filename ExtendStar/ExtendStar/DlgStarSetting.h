#pragma once


// CDlgStarSetting dialog

class CDlgStarSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStarSetting)

public:
	CDlgStarSetting(const int& nCount, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStarSetting();

// Dialog Data
	enum { IDD = IDD_DLG_SETTINGSTAR };

	CEdit m_editStarCount;

private:
	int m_nCount;

public:
	int GetCount() { return m_nCount; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

