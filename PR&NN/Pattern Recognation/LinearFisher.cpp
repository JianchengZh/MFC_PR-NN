// LinearFisher.cpp : implementation file
//

#include "stdafx.h"
#include "Pattern Recognation.h"
#include "LinearFisher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearFisher dialog
#define radius 2
#define eps 0.00000000000000001
#define m_iter 10
double *mean(double **p,int len);
void var( double **p,double *m,int len,double S[2][2]);
CLinearFisher::CLinearFisher(CWnd* pParent /*=NULL*/)
	: CDialog(CLinearFisher::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinearFisher)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLinearFisher::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinearFisher)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinearFisher, CDialog)
	//{{AFX_MSG_MAP(CLinearFisher)
	ON_BN_CLICKED(IDC_BUTTON_FISHER, OnButtonFisher)
	ON_BN_CLICKED(IDC_BUTTON_PERCEPTRON, OnButtonPerceptron)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL CLinearFisher::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//获取picture控件大小
	GetDlgItem(IDC_COORD1)->GetWindowRect(&picrect);
	//转化为对话框上的相对位置
	ScreenToClient(picrect);
	// TODO: Add extra initialization here
	P = NULL;
	N = NULL;
	line = false;
	k = 0;
	b = 0;
	PosLen = 0;
	NegLen = 0;
	dataRange = 0;
	ch = false;
	OnRandomData() ;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLinearFisher::OnRandomData() 
{
	// TODO: Add your control notification handler code here
//	if(P) delete[] P;
//	if(N) delete[] N;
	PosLen		= 40; 
	NegLen		= 40;
	dataRange	= 100;
	P = new double*[PosLen];
	N = new double*[NegLen];
	// 生成线性可分样本
	int i;

	for (i=0;i<PosLen;i++)
	{
		P[i]=new double[2];
		//		srand((unsigned)time(NULL)+i);
		P[i][0] = rand()%(dataRange*6/10);
		P[i][1] = rand()%(dataRange*6/10);
	}
	for (i=0;i<NegLen;i++)
	{
		N[i]=new double[2];
		//		srand((unsigned)time(NULL)+i);
		N[i][0] = rand()*50/RAND_MAX + 50;
		N[i][1] = rand()*50/RAND_MAX + 50;
	}
	//线性不可分样本
/*
	dataRange	= 40;
	for (i=0;i<PosLen;i++)
	{
		P[i]=new double[2];
		P[i][0] = rand()%(dataRange*5/10);
		P[i][1] = rand()%(dataRange*5/10);
	}

	for (i=0;i<NegLen;i++)
	{
		N[i]=new double[2];
		N[i][0] = rand()%(dataRange*6/10)+10;
		N[i][1] = rand()%(dataRange*6/10)+10;
	}*/
	line = false;
	Invalidate();
}

void CLinearFisher::OnButtonFisher() 
{
	// TODO: Add your control notification handler code here
//	OnRandomData() ;
	Invalidate();
	// 均值
	double *PMean =new double [2];
	double *NMean =new double [2];
	NMean= mean(N,NegLen);
	PMean= mean(P,PosLen);
	// 方差
	double PosVar[2][2] = {0},NegVar[2][2] = {0};
	var(P,PMean,PosLen,PosVar);
	var(N,NMean,NegLen,NegVar);
	// 类间离散度
	double Sw[2][2] = {0};
	Sw[0][0] = PosVar[0][0] + NegVar[0][0];
	Sw[1][0] = PosVar[1][0] + NegVar[1][0];
	Sw[0][1] = PosVar[0][1] + NegVar[0][1];
	Sw[1][1] = PosVar[1][1] + NegVar[1][1];
	// 类内离散度
	double invSw[2][2] = {0};
	double coef = 1 / (Sw[0][0]*Sw[1][1] - Sw[0][1]*Sw[1][0] + eps);
	invSw[0][0] = coef*Sw[1][1];
	invSw[1][0] = -coef*Sw[0][1];
	invSw[0][1] = -coef*Sw[1][0];
	invSw[1][1] = coef*Sw[0][0];
	// 阈值
	double *W=new double [2];
	W[0] = invSw[0][0]*(PMean[0]-NMean[0]) + invSw[0][1]*(PMean[1]-NMean[1]);
	W[1] = invSw[1][0]*(PMean[0]-NMean[0]) + invSw[1][1]*(PMean[2]-NMean[1]);
	// m1 m2
	double m1,m2;
	m1 = W[0]*PMean[0] + W[1]*PMean[1];
	m2 = W[0]*NMean[0] + W[1]*NMean[1];
	// y0
	double y0 = (m1 + m2)/2;
	
	// 分类线
	GetDiscLine(-y0,W[0],W[1]);

	
	// 统计错误率
	int i;
	double y;
	int mis_class = 0;
	for (i=0;i<PosLen;i++)
	{
		y = W[0]*P[i][0] + W[1]*P[i][1] - y0;
		if(y<0) 
		{
			mis_class += 1;
		}
	}
	for (i=0;i<NegLen;i++)
	{
		y = W[0]*N[i][0] + W[1]*N[i][1] - y0;
		if(y>0) 
		{
			mis_class += 1;
		}
	}
	line = true;
	Invalidate();

}

void CLinearFisher::OnButtonPerceptron() 
{
	// TODO: Add your control notification handler code here
//	OnRandomData() ;
	UpdateData(TRUE);
	int iter		= 0;
	int maxiter		= m_iter * 1000;
	int mis_class	= 0;
	double w[3];
	for(int i=0;i<3;i++)
	{
		w[i]=((rand()-RAND_MAX)/2)*0.01;
	}
	double delta	= 0.1;
	double y;
	double w_tmp[3];
	while (iter < maxiter)
	{
		iter += 1;
		mis_class = 0;
		memset(w_tmp,0,sizeof(double)*3);
		for (i=0;i<PosLen;i++)
		{
			y = w[1]*P[i][0] + w[2]*P[i][1] + w[0];
			if(y<0) 
			{
				mis_class += 1;
				w_tmp[1] += P[i][0] * delta;
				w_tmp[2] += P[i][1] * delta;
				w_tmp[0] += 1 * delta;
			}
		}
		for (i=0;i<NegLen;i++)
		{
			y = w[1]*N[i][0] + w[2]*N[i][1] + w[0];
			if(y>0) 
			{
				mis_class += 1;
				w_tmp[1] += -N[i][0] * delta;
				w_tmp[2] += -N[i][1] * delta;
				w_tmp[0] += -1 * delta;
			}
		}
		w[0] += w_tmp[0];w[1] += w_tmp[1];w[2] += w_tmp[2];
		if (mis_class == 0)
			break;
	}
	CString str;
	str.Format("%.4f",double(mis_class)/double(PosLen+NegLen));

	GetDiscLine(w[0],w[1],w[2]);
	line = true;
	Invalidate();
}

void CLinearFisher::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
		//画picture控件边框
	CPen pen1(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&pen1);
	dc.MoveTo(picrect.left,picrect.top);
	dc.LineTo(picrect.right,picrect.top);
	
	dc.MoveTo(picrect.right-1,picrect.bottom);
	dc.LineTo(picrect.right-1,picrect.top);
	
	//设置一个画笔的属性
	CPen pen2(PS_SOLID,2,RGB(0,0,0));
	//将画笔选入设备
	dc.SelectObject(&pen2);
	//画x轴
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.right+30,picrect.bottom);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom-10);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom+10);
	//画y轴
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.left,picrect.top-30);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left-10,picrect.top-20);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left+10,picrect.top-20);

	//画x轴label
	dc.TextOut(picrect.right+40,picrect.bottom,"x1");
	//画y轴label
	dc.TextOut(picrect.left+15,picrect.top-25,"x2");
	//画原点
	dc.TextOut(picrect.left-20,picrect.bottom+5,"(0,0)");
	CString numstr = "";
	numstr.Format("%d",dataRange);
	CString str = "(" + numstr + ",0)"; 
	dc.TextOut(picrect.right-20,picrect.bottom+5,str);
	str = "(0," + numstr + ")";
	dc.TextOut(picrect.left-20,picrect.top+5,str);

	// 画数据点(规定随机生成的前dataRange/2个数据为一类，后dataRange/2个为另一类)
	int i;
	int x,y;
	CPen pen3(PS_SOLID,2,RGB(150,255,0));
	CPen pen4(PS_SOLID,2,RGB(0,150,255));
	if(P)
	{
		for (i=0;i<PosLen;i++)
		{
			// 坐标转换
			x = int(P[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
			y = int(picrect.Height() - P[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
//			CPen pen3(PS_SOLID,2,RGB(255,0,0));
			//将画笔选入设备
			dc.SelectObject(&pen3);
			dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
		}
	}
	if(N)
	{
		for (i=0;i<NegLen;i++)
		{
			// 坐标转换
			x = int(N[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
			y = int(picrect.Height() - N[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
	//		CPen pen4(PS_SOLID,2,RGB(0,0,255));
			//将画笔选入设备
			dc.SelectObject(&pen4);
			dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
		}
	}
	if (line)
	{
		//将画笔选入设备
		dc.SelectObject(&pen4);
		double  mp[4][2];
		mp[0][0] = 0;			mp[0][1] = k*mp[0][0] + b;
		mp[1][0] = dataRange;	mp[1][1] = k*mp[1][0] + b;
		mp[2][1] = 0;			mp[2][0] = (mp[2][1] - b)/(k + eps);
		mp[3][1] = dataRange;	mp[3][0] = (mp[3][1] - b)/(k + eps);
		bool np = false;
		int x,y;
		for (int i=0;i<4;i++)
		{
			if (mp[i][0] < dataRange && mp[i][0] >0 || mp[i][1] < dataRange && mp[i][1] >0)
			{
				x = int(mp[i][0]*picrect.Width()/dataRange + picrect.left);
				y = int(picrect.top + picrect.Height() - mp[i][1]*picrect.Height()/dataRange);
				if (!np)
				{
					dc.MoveTo(x,y);
					np = true;
				}
				else
					dc.LineTo(x,y);
			}
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

// 求样本均值矩阵
 double *mean(double **p,int len)
{
	double *m;
	m=new double [2];
	m[0]=0;	m[1]=0;
	for (int i=0;i<len;i++)
	{
		m[0] += p[i][0]/len;
		m[1] += p[i][1]/len;
	}
	return m;
}

// 求样本方差矩阵
void var( double **p,double *m,int len,double S[2][2])
{
	for (int i=0;i<len;i++)
	{
		S[0][0] += (p[i][0] - m[0])*(p[i][0] - m[0]);
		S[1][0] += (p[i][1] - m[1])*(p[i][0] - m[0]);
		S[0][1] += (p[i][0] - m[0])*(p[i][1] - m[1]);
		S[1][1] += (p[i][1] - m[1])*(p[i][1] - m[1]);
	}
}

void CLinearFisher::GetDiscLine(double w0,double w1,double w2)
{
	k = - w1 / (w2 + eps);
	b = - w0 / (w2 + eps);
}
