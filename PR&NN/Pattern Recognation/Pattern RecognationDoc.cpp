// Pattern RecognationDoc.cpp : implementation of the CPatternRecognationDoc class
//

#include "stdafx.h"
#include "Pattern Recognation.h"

#include "Pattern RecognationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationDoc

IMPLEMENT_DYNCREATE(CPatternRecognationDoc, CDocument)

BEGIN_MESSAGE_MAP(CPatternRecognationDoc, CDocument)
	//{{AFX_MSG_MAP(CPatternRecognationDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationDoc construction/destruction

CPatternRecognationDoc::CPatternRecognationDoc()
{
	// TODO: add one-time construction code here
	m_dib = new CDib;
}

CPatternRecognationDoc::~CPatternRecognationDoc()
{
	if (m_dib != NULL)
	{
		delete m_dib;
		m_dib = 0;
	}
}

BOOL CPatternRecognationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationDoc serialization

void CPatternRecognationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationDoc diagnostics

#ifdef _DEBUG
void CPatternRecognationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPatternRecognationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationDoc commands

BOOL CPatternRecognationDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_dib->Read(lpszPathName) == TRUE)
	{	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return 0;
}

BOOL CPatternRecognationDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_dib->Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return 0;	
	//return CDocument::OnSaveDocument(lpszPathName);
}
