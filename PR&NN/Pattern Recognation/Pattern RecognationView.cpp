// Pattern RecognationView.cpp : implementation of the CPatternRecognationView class
//

#include "stdafx.h"
#include "Pattern Recognation.h"

#include "Pattern RecognationDoc.h"
#include "Pattern RecognationView.h"
#include "MainFrm.h"
#include "Texture.h"
#include "nrutil.h"
#include "LinearFisher.h"
#include "Nonlinear.h"
#include "ClusterAnalysis.h"
#include "Fuzzy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView

IMPLEMENT_DYNCREATE(CPatternRecognationView, CScrollView)

BEGIN_MESSAGE_MAP(CPatternRecognationView, CScrollView)
	//{{AFX_MSG_MAP(CPatternRecognationView)
	ON_COMMAND(ID_FEATUREEXTRACT_TEXTURE, OnFeatureextractTexture)
	ON_COMMAND(ID_LINEAR_FISHER_DISCRIMINTIVE, OnLinearFisherDiscrimintive)
//	ON_COMMAND(ID_LBP, OnLbp)
	ON_COMMAND(ID_NONLINEAR, OnNonlinear)
	ON_COMMAND(ID_CLUSTER_ANALYSIS, OnClusterAnalysis)
	ON_COMMAND(ID_FUZZY_CLUSTER_C_MEANS, OnFuzzyClusterCMeans)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView construction/destruction

CPatternRecognationView::CPatternRecognationView()
{
	// TODO: add construction code here

}

CPatternRecognationView::~CPatternRecognationView()
{
}

BOOL CPatternRecognationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView drawing

void CPatternRecognationView::OnDraw(CDC* pDC)
{
	CPatternRecognationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDib* pDib = pDoc->m_dib;					//返回m_dib的指针
	
	pDib->Draw(pDC, CPoint(0, 0), pDib->GetDimensions()); 	//显示DIB

}

void CPatternRecognationView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView printing

BOOL CPatternRecognationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternRecognationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternRecognationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView diagnostics

#ifdef _DEBUG
void CPatternRecognationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPatternRecognationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPatternRecognationDoc* CPatternRecognationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternRecognationDoc)));
	return (CPatternRecognationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationView message handlers

void CPatternRecognationView::OnFeatureextractTexture() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPatternRecognationDoc *pDoc=GetDocument();
	CDib* pDib = pDoc->m_dib;
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24)
	{
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	CTexture t1;//定义一个灰度共现矩阵类
	t1.LoadImage(pDib);
	t1.DoModal();
}


void CPatternRecognationView::OnLbp() 
{
	// TODO: Add your command handler code here
	CPatternRecognationDoc *pDoc=GetDocument();
	CDib* pDib = pDoc->m_dib;
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24)
	{
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
}

void CPatternRecognationView::OnLinearFisherDiscrimintive() 
{
	// TODO: Add your command handler code here
	CLinearFisher t1;
	t1.DoModal();
}

void CPatternRecognationView::OnNonlinear() 
{
	// TODO: Add your command handler code here
	CNonlinear t1;
	t1.DoModal();
}


void CPatternRecognationView::OnClusterAnalysis() 
{
	// TODO: Add your command handler code here
	CClusterAnalysis t1;
	t1.DoModal();
}

void CPatternRecognationView::OnFuzzyClusterCMeans() 
{
	// TODO: Add your command handler code here
	CFuzzy t1;
	t1.DoModal();
}
