// Pattern RecognationDoc.h : interface of the CPatternRecognationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATTERNRECOGNATIONDOC_H__052E655A_CDEA_4C78_8DAD_86D41511B701__INCLUDED_)
#define AFX_PATTERNRECOGNATIONDOC_H__052E655A_CDEA_4C78_8DAD_86D41511B701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dib.h"
class CPatternRecognationDoc : public CDocument
{
protected: // create from serialization only
	CPatternRecognationDoc();
	DECLARE_DYNCREATE(CPatternRecognationDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternRecognationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPatternRecognationDoc();
	//获取m_dib的指针
	CDib *GetPDib()
	{
		return m_dib;
	}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
	//private:
public:
	//ImgDib类的对象，从打开文件中读入的数据放在该对象中
	CDib * m_dib;
protected:
	//{{AFX_MSG(CPatternRecognationDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNRECOGNATIONDOC_H__052E655A_CDEA_4C78_8DAD_86D41511B701__INCLUDED_)
