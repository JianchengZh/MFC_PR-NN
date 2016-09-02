#if !defined(AFX_BP_MATCH_H__9ED011F7_3BFE_4AFC_BA89_DC467FB723E5__INCLUDED_)
#define AFX_BP_MATCH_H__9ED011F7_3BFE_4AFC_BA89_DC467FB723E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BP_match.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBP_match dialog

class CBP_match : public CDialog
{
// Construction
public:
	// 图像区域矩形
	CRect picrect;
	// 数据
	double *data;
	double *label;
	double *test_data;
	double *test_label;
	// 记录
	int epoch;
	double SEE;
	// 显示
	bool istest;
public:
	CBP_match(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBP_match)
	enum { IDD = IDD_DIALOG_BPNN };
	int		m_iter;
	double	m_see;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBP_match)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBP_match)
	afx_msg void OnButtonInitial();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BP_MATCH_H__9ED011F7_3BFE_4AFC_BA89_DC467FB723E5__INCLUDED_)
