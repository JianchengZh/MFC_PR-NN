#if !defined(AFX_FUZZY_H__CBCA8142_AD11_462F_8733_F12D319C2987__INCLUDED_)
#define AFX_FUZZY_H__CBCA8142_AD11_462F_8733_F12D319C2987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fuzzy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFuzzy dialog

class CFuzzy : public CDialog
{
// Construction
public:
	//members
	CRect picrect;
	double **data;
	double acc;
	int *labels;
	double **means;
	int *Nsample;
	int iscluster;
	CPen *pen;
	int showC;

public:
	CFuzzy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFuzzy)
	enum { IDD = IDD_DIALOG_FUZZY };
	int		m_Cval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFuzzy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFuzzy)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUZZY_H__CBCA8142_AD11_462F_8733_F12D319C2987__INCLUDED_)
