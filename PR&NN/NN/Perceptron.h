#if !defined(AFX_PERCEPTRON_H__09E4F7BA_D136_4AEC_AA6A_D902DDEE5CF2__INCLUDED_)
#define AFX_PERCEPTRON_H__09E4F7BA_D136_4AEC_AA6A_D902DDEE5CF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Perceptron.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPerceptron dialog

class CPerceptron : public CDialog
{
// Construction
public:
//variable
	int **data;
	int *labels;
	double **Weight;
	bool w_draw;
	double output;
	bool islabel;
public:
//functions
	 void OnXorTrain();
	 void OnXorTest();
public:
	CPerceptron(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPerceptron)
	enum { IDD = IDD_DIALOG_XOR };
	int		m_px;
	int		m_py;
	int		m_result;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerceptron)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPerceptron)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERCEPTRON_H__09E4F7BA_D136_4AEC_AA6A_D902DDEE5CF2__INCLUDED_)
