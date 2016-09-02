// Nonlinear.cpp : implementation file
//

#include "stdafx.h"
#include "Pattern Recognation.h"
#include "Nonlinear.h"
#include "math.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNonlinear dialog
#define m_K 8
#define m_x1 50
#define m_x2 50
#define Len 20
#define dataRange 100
#define radius 2
#define eps 0.00000000000000001
void mysort(double data[],int label[]);
double *mean1(double **p,int len);
int MinIndex(double d1,double d2,double d3);

CNonlinear::CNonlinear(CWnd* pParent /*=NULL*/)
	: CDialog(CNonlinear::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNonlinear)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNonlinear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNonlinear)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNonlinear, CDialog)
	//{{AFX_MSG_MAP(CNonlinear)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_NEAREST, OnButtonNearest)
	ON_BN_CLICKED(IDC_BUTTON_K_NEAREST, OnButtonKNearest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNonlinear message handlers

BOOL CNonlinear::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//获取picture控件大小
	GetDlgItem(IDC_CORAD_NON)->GetWindowRect(&picrect);
	//转化为对话框上的相对位置
	ScreenToClient(picrect);
	
	w1 = NULL; w2 = NULL; w3 = NULL;
	UpdateData(FALSE);
	w1 = new double*[Len];
	w2 = new double*[Len];
	w3 = new double*[Len];
	// 生成正负样本
	int i;
	for (i=0;i<Len;i++)
	{
//		srand((unsigned)time(NULL)); 
		w1[i] = new double[2];
		w2[i] = new double[2];
	    w3[i] = new double[2];
		w1[i][0] = rand()%(dataRange*4/10);
		w1[i][1] = rand()%(dataRange);
		
		w2[i][0] = dataRange*4/10+rand()%(dataRange*6/10);
		w2[i][1] = dataRange*3/10+rand()%(dataRange*6/10);
		
		w3[i][0] = dataRange*4/10+rand()%(dataRange*6/10);
		w3[i][1] = rand()%(dataRange*3/10);
	}

	line = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNonlinear::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
		CPen pen1(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&pen1);
	dc.MoveTo(picrect.left,picrect.top);
	dc.LineTo(picrect.right,picrect.top);
	
	dc.MoveTo(picrect.right-1,picrect.bottom);
	dc.LineTo(picrect.right-1,picrect.top);
	
	// 设置一个画笔的属性
	CPen pen2(PS_SOLID,2,RGB(0,0,0));
	//将画笔选入设备
	dc.SelectObject(&pen2);
	// 画x轴
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.right+30,picrect.bottom);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom-10);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom+10);
	// 画y轴
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.left,picrect.top-30);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left-10,picrect.top-20);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left+10,picrect.top-20);
	
	// 画x轴label
	dc.TextOut(picrect.right+40,picrect.bottom,"x1");
	// 画y轴label
	dc.TextOut(picrect.left+15,picrect.top-25,"x2");
	// 画原点
	dc.TextOut(picrect.left-20,picrect.bottom+5,"(0,0)");
	CString numstr = "";
	numstr.Format("%d",dataRange);
	CString str = "(" + numstr + ",0)"; 
	dc.TextOut(picrect.right-20,picrect.bottom+5,str);
	str = "(0," + numstr + ")";
	dc.TextOut(picrect.left-20,picrect.top+5,str);

	// 画数据点
	int i;
	int x1,y1,x2,y2,x3,y3;
	CPen pen3(PS_SOLID,2,RGB(255,0,0));
	CPen pen4(PS_SOLID,2,RGB(0,0,255));
	CPen pen5(PS_SOLID,2,RGB(0,255,0));
	CPen pen6(PS_SOLID,4,RGB(160,0,160));
	if(w1 && w2 && w3)
	{
		for (i=0;i<Len;i++)
		{
			// 坐标转换
			x1 = int(w1[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
			y1 = int(picrect.Height() - w1[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
			x2 = int(w2[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
			y2 = int(picrect.Height() - w2[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
			x3 = int(w3[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
			y3 = int(picrect.Height() - w3[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
			//将画笔选入设备
			dc.SelectObject(&pen3);
			dc.Ellipse(x1-radius,y1-radius,x1+radius,y1+radius);
			dc.SelectObject(&pen4);
			dc.Ellipse(x2-radius,y2-radius,x2+radius,y2+radius);
			dc.SelectObject(&pen5);
			dc.Ellipse(x3-radius,y3-radius,x3+radius,y3+radius);
		}

		// 测试点
		UpdateData(TRUE);
		x1 = int(m_x1*(double(picrect.Width())/dataRange) + picrect.left);
		y1 = int(picrect.Height() - m_x2*(double(picrect.Height())/dataRange) + picrect.top);
		dc.SelectObject(&pen6);
		dc.Ellipse(x1-radius,y1-radius,x1+radius,y1+radius);

		// legend
		x1 = picrect.right-30;
		y1 = picrect.top+10;
		x2 = picrect.right-30;
		y2 = picrect.top+25;
		x3 = picrect.right-30;
		y3 = picrect.top+40;
		dc.SelectObject(&pen3);
		dc.Ellipse(x1-radius-1,y1-radius-1,x1+radius-1,y1+radius-1);
		dc.SelectObject(&pen4);
		dc.Ellipse(x2-radius-1,y2-radius-1,x2+radius-1,y2+radius-1);
		dc.SelectObject(&pen5);
		dc.Ellipse(x3-radius-1,y3-radius-1,x3+radius-1,y3+radius-1);
		dc.TextOut(picrect.right-20,picrect.top,"w1");
		dc.TextOut(picrect.right-20,picrect.top+15,"w2");
		dc.TextOut(picrect.right-20,picrect.top+30,"w3");
	}

	// 画分类线
	if (line)
	{
		//将画笔选入设备
		dc.SelectObject(&pen4);
		double mp[4][2];
		int x,y;
		int c = 0;
		for (c=0;c<3;c++)
		{
			mp[0][0] = 0;			mp[0][1] = k[c]*mp[0][0] + b[c];
			mp[1][0] = dataRange;	mp[1][1] = k[c]*mp[1][0] + b[c];
			mp[2][1] = 0;			mp[2][0] = (mp[2][1] - b[c])/k[c];
			mp[3][1] = dataRange;	mp[3][0] = (mp[3][1] - b[c])/k[c];
			dc.MoveTo(int(picrect.left + pc[0]*picrect.Width()/dataRange),
				int(picrect.top + picrect.Height() - pc[1]*picrect.Height()/dataRange));
			for (int i=0;i<4;i++)
			{
				if (mp[i][0] < dataRange && mp[i][0] >0 || mp[i][1] < dataRange && mp[i][1] >0)
				{
					if (c==0 && mp[i][0] < pc[0] || c==1 && mp[i][0] > pc[0] || c==2 && mp[i][0] < pc[0])
					{
						x = int(mp[i][0]*picrect.Width()/dataRange + picrect.left);
						y = int(picrect.top + picrect.Height() - mp[i][1]*picrect.Height()/dataRange);
						dc.LineTo(x,y);						
					}					
				}
			}
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CNonlinear::OnButtonNearest() 
{
	// TODO: Add your control notification handler code here
	double *w1mean = mean1(w1,Len);
	double *w2mean = mean1(w2,Len);
	double *w3mean = mean1(w3,Len);
	
	// 三均值点连线
	double k1,k2,k3;
	k1 = (w1mean[1] - w2mean[1]) / (w1mean[0] - w2mean[0] + eps);
	k2 = (w2mean[1] - w3mean[1]) / (w2mean[0] - w3mean[0] + eps);
	k3 = (w1mean[1] - w3mean[1]) / (w1mean[0] - w3mean[0] + eps);
	double **p=new double *[3];
	for(int i=0;i<3;i++)
		p[i]=new double[2];
	p[0][0]=(w1mean[0]+w2mean[0])/2;
	p[0][1]=(w1mean[1]+w2mean[1])/2;//p12
	p[1][0]=(w2mean[0]+w3mean[0])/2;
	p[1][1]=(w2mean[1]+w3mean[1])/2;//p23
	p[2][0]=(w1mean[0]+w3mean[0])/2;
	p[2][1]=(w1mean[1]+w3mean[1])/2;//p13

	// 三中垂线l1 l2 l3	
	k[0] = -1 / (k1 + eps);
	k[1] = -1 / (k2 + eps);
	k[2] = -1 / (k3 + eps);
	b[0] = p[0][1] - k[0] * p[0][0];
	b[1] = p[1][1] - k[1] * p[1][0];
	b[2] = p[2][1] - k[2] * p[2][0];
	
	// l1 l2 l3交点
	double tmp[2];
	pc=new double[2];
	pc[0] = (b[1] - b[0])/(k[0] - k[1] + eps);
	pc[1] = k[0] * pc[0] + b[0];
	
	tmp[0] = (b[2] - b[0])/(k[0] - k[2] + eps);
	tmp[1] = k[0] * tmp[0] + b[0];
	
	// 分类结果
	UpdateData(TRUE);
	double d1,d2,d3;
	d1 = sqrt(pow(double(m_x1)-w1mean[0],2)+pow(double(m_x2)-w1mean[1],2));
	d2 = sqrt(pow(double(m_x1)-w2mean[0],2)+pow(double(m_x2)-w2mean[1],2));
	d3 = sqrt(pow(double(m_x1)-w3mean[0],2)+pow(double(m_x2)-w3mean[1],2));
	int c = MinIndex(d1,d2,d3);
	
	// 画图
	line = true;
	Invalidate();
}

void CNonlinear::OnButtonKNearest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int c1n=0,c2n=0,c3n=0;
	int i;
	// 距离数组 标签数组
	double D[3*Len];
	int L[3*Len];
	for (i=0;i<Len;i++)
	{
		D[i*3]		= sqrt(pow(m_x1-w1[i][0],2)+pow(m_x2-w1[i][1],2)); 
		L[i*3]		= 1;
		D[i*3+1]	= sqrt(pow(m_x1-w2[i][0],2)+pow(m_x2-w2[i][1],2)); 
		L[i*3+1]	= 2;
		D[i*3+2]	= sqrt(pow(m_x1-w3[i][0],2)+pow(m_x2-w3[i][1],2)); 
		L[i*3+2]	= 3;
	}
	// 排序
	mysort(D,L);
	// 统计Knn类别
	for (i=0;i<m_K;i++)
	{
		switch(L[i])
		{
		case 1:c1n++;break;
		case 2:c2n++;break;
		case 3:c3n++;break;
		}
	}
	
	line = true;
	Invalidate();
}

void mysort(double data[],int label[])
{
	int i,j;
	double tmp1;
	int tmp2;
	for(i=0;i<3*Len;i++) 
	{
		for(j=0;j<3*Len-i-1;j++)
		{
			if(data[j]>data[j+1])
			{
				// 数据排序
				tmp1 = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp1;
				// 标签排序
				tmp2 = label[j];
				label[j] = label[j+1];
				label[j+1] = tmp2;
			}		
		}
	}
}

// 求样本均值矩阵
double *mean1(double **p,int len)
{
	double *m;
	m=new double[2];
	m[0]=0;m[1]=0;
	for (int i=0;i<len;i++)
	{
		m[0] += p[i][0]/len;
		m[1] += p[i][1]/len;
	}
	return m;
}
//最小距离
int MinIndex(double d1,double d2,double d3)
{
	if (d1 <= d2 && d1 <= d3) return 1;
	else if (d2 <= d1 && d2 <= d3) return 2;
	else return 3;
}
