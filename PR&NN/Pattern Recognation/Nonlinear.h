#if !defined(AFX_NONLINEAR_H__CA407ADA_6BB0_4478_88CE_372418296BF2__INCLUDED_)
#define AFX_NONLINEAR_H__CA407ADA_6BB0_4478_88CE_372418296BF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Nonlinear.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNonlinear dialog

class CNonlinear : public CDialog
{
// Construction
public:
	//members
		CRect picrect;//image region
		double **w1,**w2,**w3;//samples
		double k[3];//lines
	    double b[3];//
		double  *pc;//the point
		bool line;
public:
	CNonlinear(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNonlinear)
	enum { IDD = IDD_DIALOG_NONLINEAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNonlinear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNonlinear)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonNearest();
	afx_msg void OnButtonKNearest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NONLINEAR_H__CA407ADA_6BB0_4478_88CE_372418296BF2__INCLUDED_)
