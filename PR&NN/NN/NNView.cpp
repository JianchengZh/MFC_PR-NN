// NNView.cpp : implementation of the CNNView class
//

#include "stdafx.h"
#include "NN.h"

#include "NNDoc.h"
#include "NNView.h"
#include "Perceptron.h"
#include "BP_match.h"
#include "HOPFIELD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNNView

IMPLEMENT_DYNCREATE(CNNView, CView)

BEGIN_MESSAGE_MAP(CNNView, CView)
	//{{AFX_MSG_MAP(CNNView)
	ON_COMMAND(ID_XOR, OnXor)
	ON_COMMAND(ID_NONLINEAR, OnNonlinear)
	ON_COMMAND(ID_ASSOCIATE_MEMORY, OnAssociateMemory)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNNView construction/destruction

CNNView::CNNView()
{
	// TODO: add construction code here

}

CNNView::~CNNView()
{
}

BOOL CNNView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNNView drawing

void CNNView::OnDraw(CDC* pDC)
{
	CNNDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CNNView printing

BOOL CNNView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNNView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNNView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNNView diagnostics

#ifdef _DEBUG
void CNNView::AssertValid() const
{
	CView::AssertValid();
}

void CNNView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNNDoc* CNNView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNNDoc)));
	return (CNNDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNNView message handlers

//三层感知器网络解决异或问题
void CNNView::OnXor() 
{
	// TODO: Add your command handler code here
	CPerceptron t1;
	t1.DoModal();
}

//三层BP神经网络实现非线性函数拟合
void CNNView::OnNonlinear() 
{
	// TODO: Add your command handler code here
	CBP_match t1;
	t1.DoModal();
}

void CNNView::OnAssociateMemory() 
{
	// TODO: Add your command handler code here
	CHOPFIELD t1;
	t1.DoModal();
}
