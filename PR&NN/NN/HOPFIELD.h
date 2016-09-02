#if !defined(AFX_HOPFIELD_H__EC445A0F_F884_4526_A625_EB84A679915A__INCLUDED_)
#define AFX_HOPFIELD_H__EC445A0F_F884_4526_A625_EB84A679915A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HOPFIELD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHOPFIELD dialog

class CHOPFIELD : public CDialog
{
// Construction
public:
	//members
		int *Weight;
public:
	CHOPFIELD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHOPFIELD)
	enum { IDD = IDD_DIALOG_HOPFIELD };
	int		m_test0;
	int		m_test1;
	int		m_test2;
	int		m_train00;
	int		m_train01;
	int		m_train02;
	int		m_train10;
	int		m_train11;
	int		m_train12;
	int		m_train20;
	int		m_train21;
	int		m_train22;
	int		m_result0;
	int		m_result1;
	int		m_result2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHOPFIELD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHOPFIELD)
	virtual BOOL OnInitDialog();
	afx_msg void OnMemory();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOPFIELD_H__EC445A0F_F884_4526_A625_EB84A679915A__INCLUDED_)
