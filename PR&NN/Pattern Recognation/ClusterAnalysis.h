#if !defined(AFX_CLUSTERANALYSIS_H__3B9B01E6_CCFD_48EA_AB11_C27833A74183__INCLUDED_)
#define AFX_CLUSTERANALYSIS_H__3B9B01E6_CCFD_48EA_AB11_C27833A74183__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClusterAnalysis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis dialog

class CClusterAnalysis : public CDialog
{
// Construction
public:
	//members
	CRect picrect;
	double **data;
	int *labels;
	double **means;
	int *Nsample;
	int iscluster;
	CPen *pen;
	int showC;
	double acc;
	int m_Nc,m_L;
public:
	//functions
	int MaxIndex(int *input,int k);
	void GetMean(double **data,int *labels,double **means,int *Nsample,int k);
	double GetJe(double *J,int k);
	void GetJ(double **data,int *labels,double **means,int k,double *J);
	void GetNsample(int *labels,int k,int *Nsample);
	int MinDist(double *input,int k);
	void classification(double **data,double **means,int *labels,int c);
	int MinDistLabel(double *dist,int k,int *Labels);
    double GetAcc(int *labels,int c);

public:
	//functions
	void seperate(int &Nc,double *dist,double distSum);
	void consolidation(int &Nc);

public:
	CClusterAnalysis(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClusterAnalysis)
	enum { IDD = IDD_DIALOG_CLUSTER };
	int		m_cvalue;
	double	m_jadd;
	int		m_k;
	int		m_thetaN;
	int		m_thetaD;
	int		m_thetaS;
	int		m_I;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClusterAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClusterAnalysis)
	afx_msg void OnButtonCMeans();
	afx_msg void OnButtonIsodata();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLUSTERANALYSIS_H__3B9B01E6_CCFD_48EA_AB11_C27833A74183__INCLUDED_)
