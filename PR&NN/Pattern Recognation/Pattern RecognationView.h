// Pattern RecognationView.h : interface of the CPatternRecognationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATTERNRECOGNATIONVIEW_H__50C334D8_F21B_42F7_861A_198316DCA804__INCLUDED_)
#define AFX_PATTERNRECOGNATIONVIEW_H__50C334D8_F21B_42F7_861A_198316DCA804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//第五章  非线性判别函数
//随机产生多类二维样本，编写程序用最小距离分类器和K近邻分类器对其进行分类。
//第七章  聚类分析
//随机产生多类二维样本，编写程序用C--均值聚类和ISODATA聚类算法对其进行分类。
//第八章  模糊模式识别
//随机产生多类二维样本，编写程序用模糊C--均值聚类算法对其进行分类。


class CPatternRecognationView : public CScrollView
{
protected: // create from serialization only
	CPatternRecognationView();
	DECLARE_DYNCREATE(CPatternRecognationView)

// Attributes
public:
	CPatternRecognationDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternRecognationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPatternRecognationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPatternRecognationView)
	afx_msg void OnFeatureextractTexture();
	afx_msg void OnLinearFisherDiscrimintive();
	afx_msg void OnLbp();
	afx_msg void OnNonlinear();
	afx_msg void OnClusterAnalysis();
	afx_msg void OnFuzzyClusterCMeans();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Pattern RecognationView.cpp
inline CPatternRecognationDoc* CPatternRecognationView::GetDocument()
   { return (CPatternRecognationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNRECOGNATIONVIEW_H__50C334D8_F21B_42F7_861A_198316DCA804__INCLUDED_)
