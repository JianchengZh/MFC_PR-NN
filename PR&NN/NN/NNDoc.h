// NNDoc.h : interface of the CNNDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NNDOC_H__4EE77515_5894_427B_9BF4_7C260AE8D3F8__INCLUDED_)
#define AFX_NNDOC_H__4EE77515_5894_427B_9BF4_7C260AE8D3F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNNDoc : public CDocument
{
protected: // create from serialization only
	CNNDoc();
	DECLARE_DYNCREATE(CNNDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNNDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNNDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNNDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NNDOC_H__4EE77515_5894_427B_9BF4_7C260AE8D3F8__INCLUDED_)
