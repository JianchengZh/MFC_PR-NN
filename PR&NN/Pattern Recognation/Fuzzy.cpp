// Fuzzy.cpp : implementation file
//

#include "stdafx.h"
#include "Pattern Recognation.h"
#include "Fuzzy.h"
#include "math.h"
#include "ClusterAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFuzzy dialog


CFuzzy::CFuzzy(CWnd* pParent /*=NULL*/)
	: CDialog(CFuzzy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFuzzy)
	m_Cval = 0;
	//}}AFX_DATA_INIT
}


void CFuzzy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFuzzy)
	DDX_Text(pDX, IDC_EDIT_Cval, m_Cval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFuzzy, CDialog)
	//{{AFX_MSG_MAP(CFuzzy)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFuzzy message handlers
#define dataRange 100
#define Len 60
#define radius 2
#define eps 0.00000000000000001
#define x_len 5
#define m_b 2

BOOL CFuzzy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_DRAW_FUZZY)->GetWindowRect(&picrect);
	ScreenToClient(picrect);
	data = NULL;
	labels = NULL;
	Nsample = NULL;
	means = NULL;
	m_Cval = 5;
	if (data) delete[] data;
	data = new double*[Len];
	int i;
	for (i=0;i<Len/3;i++)
	{
		data[i] = new double[2];
		data[i][0]= rand()%(dataRange*4/10);
		data[i][1] = rand()%(dataRange*4/10);
	}
	for (i=Len/3;i<Len*2/3;i++)
	{
		data[i] = new double[2];
		data[i][0]= rand()*40/RAND_MAX + 60;
		data[i][1] = rand()*60/RAND_MAX + 0;
	}
	
	for (i=Len*2/3;i<Len;i++)
	{	
		data[i] = new double[2];
		data[i][0] = rand()*50/RAND_MAX + 20;
		data[i][1] = rand()*40/RAND_MAX + 60;
	}
	UpdateData(FALSE);
	pen = new CPen[10];
	pen[0].CreatePen(PS_SOLID,2,RGB(0,255,0));
	pen[1].CreatePen(PS_SOLID,2,RGB(255,0,0));
	pen[2].CreatePen(PS_SOLID,2,RGB(255,210,0));
	pen[3].CreatePen(PS_SOLID,2,RGB(0,0,255));
	pen[4].CreatePen(PS_SOLID,2,RGB(0,255,255));
	pen[5].CreatePen(PS_SOLID,2,RGB(255,0,255));
	pen[6].CreatePen(PS_SOLID,2,RGB(160,0,160));
	pen[7].CreatePen(PS_SOLID,2,RGB(0,0,128));
	pen[8].CreatePen(PS_SOLID,2,RGB(128,0,0));
	pen[9].CreatePen(PS_SOLID,2,RGB(0,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFuzzy::OnPaint() 
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
	int i,j;
	int x,y;
	CPen pen3(PS_SOLID,2,RGB(0,0,0));
	if(data)
	{
		if (iscluster == 0)
		{
			for (i=0;i<Len;i++)
			{
				// 坐标转换
				x = int(data[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - data[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				//将画笔选入设备
				dc.SelectObject(&pen3);
				dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
			}
		}
		else
		{
			// 数据点
			for (i=0;i<Len;i++)
			{
				// 坐标转换
				x = int(data[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - data[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				for (j=0;j<showC;j++)
				{
					if (labels[i]==j)
						dc.SelectObject(&pen[j]);	//将画笔选入设备
					dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
				}	
			}
			// 类中心点
			for (i=0;i<showC;i++)
			{
				// 坐标转换
				x = int(means[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - means[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				dc.SelectObject(&pen[i]);
				dc.MoveTo(x-x_len,y);
				dc.LineTo(x+x_len,y);
				dc.MoveTo(x,y-x_len);
				dc.LineTo(x,y+x_len);
			}
			// legend
			for (i=0;i<showC;i++)
			{
				dc.SelectObject(&pen[i]);
				x = picrect.right-30;
				y = picrect.top + 10 + 15*i;
				dc.Ellipse(x-radius-1,y-radius-1,x+radius-1,y+radius-1);
				str.Format("%d",i+1);
				dc.TextOut(picrect.right-20,picrect.top+15*i,"w"+str);
				// N sample
				str.Format("%d",Nsample[i]);
				dc.TextOut(picrect.right-60,picrect.top+15*i,str);
			}

			// title
			CFont font; 
			font.CreatePointFont(150, "黑体");//字体可改成自己需要的，
			dc.SelectObject(&font);
			switch (iscluster)
			{
			case 1:dc.TextOut(300,10,"C - Means");break;
			case 2:dc.TextOut(300,10,"ISODATA");break;
			case 3:dc.TextOut(300,10,"Fuzzy C-Means");break;
			}
			
		}
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CFuzzy::OnOK() 
{
	// TODO: Add extra validation here
		int i,j;
	// 读入类别数c
	UpdateData(TRUE);
	int Nc = m_Cval;
	double M = m_b;
	double epsm = 0.000001;

	// 初始化隶属度函数(归一化)
	double *U0 = new double[Nc*Len];
	for (i=0;i<Nc;i++)
	{
		for (j=0;j<Len;j++)
		{
			U0[i*Len+j] = (rand()%100+1);
		}
	}
	double sum;
	for (j=0;j<Len;j++)
	{
		sum = 0;
		for (i=0;i<Nc;i++)
		{
			sum += U0[i*Len+j];
		}
		for (i=0;i<Nc;i++)
		{
			U0[i*Len+j] /= sum;
		}
	}

	//FCM 迭代算法
	double *Um = NULL;
	double *dist = NULL;
	double *U = NULL;
	double *distSum = NULL;
	double *Ubias = NULL;
	double m = 1/(M-1);
	double *max_bias = NULL;
	double max_value;
	while(1)
	{
		if (Um) delete[] Um;
		Um = new double[Nc*Len];
		for (i=0;i<Nc;i++)
		{
			for (j=0;j<Len;j++)
		{
				Um[i*Len+j] = pow(U0[i*Len+j],M);
			}
		}
		if (means) delete[] means;
		means = new double*[Nc];
		for(i=0;i<Nc;i++)
		{
			means[i]=new double[2];
			for(j=0;j<2;j++)
			{
				means[i][j]=0;
			}
		}
		for (i=0;i<Nc;i++)
		{
			sum = 0;
			for (j=0;j<Len;j++)
			{
				means[i][0] += Um[i*Len+j] * data[j][0];
				means[i][1] += Um[i*Len+j] * data[j][1];
				sum += Um[i*Len+j];
			}
			means[i][0] /= sum;
			means[i][1] /= sum;
		}

		if (dist) delete[] dist;
		dist = new double[Nc*Len];
		for (i=0;i<Nc;i++)
		{
			for (j=0;j<Len;j++)
			{
				dist[i*Len+j] = sqrt(pow(means[i][0]-data[j][0],2)+pow(means[i][1]-data[j][1],2));
			}
		}
		if (distSum) delete[] distSum;
		distSum = new double[Len];
		memset(distSum,0,sizeof(double)*Len);
		for (j=0;j<Len;j++)
		{
			for (i=0;i<Nc;i++)
			{
				distSum[j] += pow(1/(dist[i*Len+j]+eps),m);
			}
			distSum[j] = 1/(distSum[j]+eps);
		}
		if (U) delete[] U;
		U = new double[Nc*Len];
		for (i=0;i<Nc;i++)
		{
			for (j=0;j<Len;j++)
			{
				U[i*Len+j] = pow(1/(dist[i*Len+j]+eps),m) * distSum[j];
			}
		}
		
		if (Ubias) delete[] Ubias;
		Ubias = new double[Nc];
		memset(Ubias,0,sizeof(double)*Nc);
		for (i=0;i<Nc;i++)
		{
			for (j=0;j<Len;j++)
			{
				Ubias[i] += fabs(U[i*Len+j]-U0[i*Len+j]);
			}
		}
		max_value = -1;
		for (i=0;i<Nc;i++)
		{
			if (Ubias[i]>max_value)
				max_value = Ubias[i];
		}
		if (max_value < epsm)
			break;

		if (U0) delete[] U0;
		U0 = new double[Nc*Len];
		memcpy(U0,U,sizeof(double)*Nc*Len);

	}

	if (labels) delete[] labels;
	labels = new int[Len];
	int ltmp;
	for (j=0;j<Len;j++)
	{
		max_value = -1;
		for (i=0;i<Nc;i++)
		{
			if (U[i*Len+j]>max_value)
			{
				max_value = U[i*Len+j];
				ltmp = i;
			}
		}
		labels[j] = ltmp;
	}
	if (Nsample) delete[] Nsample;
	Nsample = new int[m_Cval];
	CClusterAnalysis t1;
	t1.GetNsample(labels,Nc,Nsample);


	acc = t1.GetAcc(labels,Nc);

	showC = m_Cval;
	iscluster = 3;
	Invalidate();
//	CDialog::OnOK();
}
