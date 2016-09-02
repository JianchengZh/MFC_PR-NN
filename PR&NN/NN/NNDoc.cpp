// NNDoc.cpp : implementation of the CNNDoc class
//

#include "stdafx.h"
#include "NN.h"

#include "NNDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNNDoc

IMPLEMENT_DYNCREATE(CNNDoc, CDocument)

BEGIN_MESSAGE_MAP(CNNDoc, CDocument)
	//{{AFX_MSG_MAP(CNNDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNNDoc construction/destruction

CNNDoc::CNNDoc()
{
	// TODO: add one-time construction code here

}

CNNDoc::~CNNDoc()
{
}

BOOL CNNDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNNDoc serialization

void CNNDoc::Serialize(CArchive& ar)
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
// CNNDoc diagnostics

#ifdef _DEBUG
void CNNDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNNDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNNDoc commands
