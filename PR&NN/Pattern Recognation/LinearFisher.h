#if !defined(AFX_LINEARFISHER_H__77961BF2_7D2D_44AB_B932_3903DEDE2A63__INCLUDED_)
#define AFX_LINEARFISHER_H__77961BF2_7D2D_44AB_B932_3903DEDE2A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinearFisher.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinearFisher dialog

class CLinearFisher : public CDialog
{
// Construction
public:
	// 图像区域矩形
	CRect picrect;
	// 二维数据
	double **P;
	double **N;
	int PosLen;
	int NegLen;
	int dataRange;
	bool ch;
	// 分类线参数
	bool line;
	double k,b;
	void OnRandomData(); 
	void GetDiscLine(double w0,double w1,double w2);
public:
	CLinearFisher(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinearFisher)
	enum { IDD = IDD_DIALOG_LINEAR_FISHER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinearFisher)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
// members
public:
//functions
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinearFisher)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFisher();
	afx_msg void OnButtonPerceptron();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARFISHER_H__77961BF2_7D2D_44AB_B932_3903DEDE2A63__INCLUDED_)
