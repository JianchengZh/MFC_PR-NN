// NNView.h : interface of the CNNView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NNVIEW_H__DA85DDB0_1757_4040_9B5E_3195F3013782__INCLUDED_)
#define AFX_NNVIEW_H__DA85DDB0_1757_4040_9B5E_3195F3013782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNNView : public CView
{
protected: // create from serialization only
	CNNView();
	DECLARE_DYNCREATE(CNNView)

// Attributes
public:
	CNNDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNNView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNNView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNNView)
	afx_msg void OnXor();
	afx_msg void OnNonlinear();
	afx_msg void OnAssociateMemory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NNView.cpp
inline CNNDoc* CNNView::GetDocument()
   { return (CNNDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NNVIEW_H__DA85DDB0_1757_4040_9B5E_3195F3013782__INCLUDED_)
