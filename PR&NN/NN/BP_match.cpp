// BP_match.cpp : implementation file
//

#include "stdafx.h"
#include "NN.h"
#include "BP_match.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBP_match dialog
#define len 14
#define x_len 5
void Re_Back_Propagation(double **Weight,double y[],double label);
void Re_forward_propagation(double input,double **Weight,double y[]);

CBP_match::CBP_match(CWnd* pParent /*=NULL*/)
	: CDialog(CBP_match::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBP_match)
	m_iter = 0;
	m_see = 0.0;
	//}}AFX_DATA_INIT
}


void CBP_match::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBP_match)
	DDX_Text(pDX, IDC_EDIT_ITER, m_iter);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_see);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBP_match, CDialog)
	//{{AFX_MSG_MAP(CBP_match)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, OnButtonInitial)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBP_match message handlers


void CBP_match::OnButtonInitial() 
{
	// TODO: Add your control notification handler code here
	if (data) delete[] data;
	data = new double[len];
	if (label) delete label;
	label = new double[len];
	int i;
	for (i=0;i<len;i++)
		data[i] = 0.1*double(i)-1;
	label[0] = 11.86;	label[1] = 15.67;	label[2] = 20.60;	label[3] = 26.69;	label[4] = 33.71;
	label[5] = 41.93;	label[6] = 51.13;	label[7] = 61.49;	label[8] = 72.90;	label[9] = 85.44;
	label[10] = 99.08;	label[11] = 113.77;	label[12] = 129.54;label[13] = 146.48;	
	for (i=0;i<len;i++)
		label[i] = (label[i]+1)/2;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	istest = false;
	Invalidate();
}

void CBP_match::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int i,j;
	// 用小(+-0.3)随机数进行权值初始化，各权值不能为0，也不能相同
	double **Weight = new double *[2];
	Weight[0] = new double[6*2];
	Weight[1] = new double[1*6];
	bool same;
	double rand_w;
	i = 0;
	while (i<12)
	{
		same = false;
		rand_w = double(rand())*0.1/RAND_MAX - 0.05;
		for (j=0;j<i;j++)
		{
			if (Weight[0][j]==rand_w)
			{
				same = true;
				break;
			}
		}
		if (!same)
		{
			Weight[0][i] = rand_w;
			i++;
		}
	}
	i = 0;
	while (i<6)
	{
		same = false;
		rand_w = double(rand())*0.1/RAND_MAX - 0.05;
		for (j=0;j<i;j++)
		{
			if (Weight[1][j]==rand_w)
			{
				same = true;
				break;
			}
		}
		if (!same)
		{
			Weight[1][i] = rand_w;
			i++;
		}
	}
	
	double y[7];
	for (j=0;j<m_iter;j++)
	{
		for (i=0;i<len;i++)
		{
			// 前向传播
			Re_forward_propagation(data[i],Weight,y);
			// 反向传播
			Re_Back_Propagation(Weight,y,label[i]);
		}
		
		
	}
	
	// err
	SEE = 0;
	for (i=0;i<len;i++)
	{
		Re_forward_propagation(data[i],Weight,y);
		SEE += 0.5*pow(y[6]-label[i],2);
	}
	epoch = m_iter;
	
	// test
	if (test_data) delete[] test_data;
	test_data = new double[201];
	if (test_label) delete[] test_label;
	test_label = new double[201];
	for (i=0;i<201;i++)
	{
		test_data[i] = 0.01*double(i)-1;
		Re_forward_propagation(test_data[i],Weight,y);
		test_label[i] = y[6];
	}
	m_see=SEE;
	UpdateData(FALSE);
	delete[] Weight;
	Weight = NULL;
	istest = true;
	Invalidate();
//	CDialog::OnOK();
}
double tansig(double a)
{
	double output;
	output = 1/(1 + exp(-a));
	return output;
}

double purelin(double a)
{
	return a;
}

void Re_forward_propagation(double input,double **Weight,double y[])
{
	int i;
	y[0] = input;
	for (i=0;i<5;i++)
	{
		y[i+1] = tansig(input*Weight[0][0+i*2] + Weight[0][1+i*2]);
	}
	y[6] = purelin(y[1]*Weight[1][0] + y[2]*Weight[1][1] + y[3]*Weight[1][2] + y[4]*Weight[1][3] + y[5]*Weight[1][4] + Weight[1][5]);
}

void Re_Back_Propagation(double **Weight,double y[],double label)
{
	// 学习效率
	double eta = 0.01;
	// 输出层反馈
	int i,j;
	double delta1;
	delta1 = label-y[6];
	for (i=0;i<6;i++)
	{
		if (i==5)
			Weight[1][i] += eta*delta1;
		else
			Weight[1][i] += eta*delta1*y[1+i];
	}
	// 中间层反馈
	double delta2[5];
	delta2[0] = y[1]*(1-y[1])*delta1*Weight[1][0];
	delta2[1] = y[2]*(1-y[2])*delta1*Weight[1][1];
	delta2[2] = y[3]*(1-y[3])*delta1*Weight[1][2];
	delta2[3] = y[4]*(1-y[4])*delta1*Weight[1][3];
	delta2[4] = y[5]*(1-y[5])*delta1*Weight[1][4];
	for (j=0;j<5;j++)
	{
		for (i=0;i<2;i++)
		{
			if (i==1)
				Weight[0][i+2*j] += eta*delta2[j];
			else
				Weight[0][i+2*j] += eta*delta2[j]*y[i];
		}
		
	}
}

void CBP_match::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int i;
	CString str;
	// 画picture控件边框
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
	dc.TextOut(picrect.left,picrect.bottom,"0");
	//dc.TextOut(picrect.left-15,picrect.bottom-10,"0");
//	dc.TextOut(picrect.left+picrect.Width()/2,picrect.bottom,"0");
//	dc.TextOut(picrect.left-15,picrect.bottom-10-picrect.Height()/2,"0.5");
	dc.TextOut(picrect.right,picrect.bottom,"1");
	dc.TextOut(picrect.left-30,picrect.top,"140");
	dc.TextOut(picrect.right,picrect.bottom,"X");
	dc.TextOut(picrect.left,picrect.top-15,"Y");
	
	CPen pen3(PS_SOLID,2,RGB(0,100,150));
	CPen pen4(PS_SOLID,2,RGB(50,180,80));
	int x,y;
	int x_new,y_new;
	if (data)
	{
		dc.SelectObject(&pen3);
		for (i=0;i<len;i++)
		{
			x = int((data[i]+1)*double(picrect.Width())/1.5 + picrect.left);
			y = int(picrect.Height() - label[i]*double(picrect.Height())/140 + picrect.top);
			
			dc.MoveTo(x-x_len,y);
			dc.LineTo(x+x_len,y);
			dc.MoveTo(x,y-x_len);
			dc.LineTo(x,y+x_len);
		}
		if (istest)
		{
			dc.SelectObject(&pen4);
			x = int((test_data[0]+1)*double(picrect.Width())/1.5 + picrect.left);
			y = int(picrect.Height() - test_label[0]*double(picrect.Height()) /140+ picrect.top);
			for (i=1;i<140;i++)
			{
				x_new = int((test_data[i]+1)*double(picrect.Width())/1.5 + picrect.left);
				y_new = int(picrect.Height() - test_label[i]*double(picrect.Height())/140 + picrect.top);
				dc.MoveTo(x,y);
				dc.LineTo(x_new,y_new);
				x = x_new; y = y_new;
			}
		}
	}	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CBP_match::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_DRAW)->GetWindowRect(&picrect);
	//转化为对话框上的相对位置
	ScreenToClient(picrect);
	
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	m_iter=400;
	data = NULL;
	label = NULL;
	test_data = NULL;
	test_label = NULL;
	istest = false;
	m_see=0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}