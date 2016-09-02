// Perceptron.cpp : implementation file
//

#include "stdafx.h"
#include "NN.h"
#include "Perceptron.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerceptron dialog
void forward_propagation(int *input,double **Weight,double y[]);
void Back_Propagation(double **Weight,double y[],double label);
double Sigmoid(double a);

CPerceptron::CPerceptron(CWnd* pParent /*=NULL*/)
	: CDialog(CPerceptron::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPerceptron)
	m_px = 0;
	m_py = 0;
	m_result = 0;
	//}}AFX_DATA_INIT
}


void CPerceptron::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerceptron)
	DDX_Text(pDX, IDC_EDIT_X, m_px);
	DDX_Text(pDX, IDC_EDIT_Y, m_py);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_result);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerceptron, CDialog)
	//{{AFX_MSG_MAP(CPerceptron)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerceptron message handlers

BOOL CPerceptron::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_result = 0;
	data = new int *[4];
	for(int i=0;i<4;i++)
	{
		data[i] = new int [2];
	}
	data[0][0]=0;
	data[0][1]=0;
	data[1][0]=0;
	data[1][1]=1;
	data[2][0]=1;
	data[2][1]=0;
	data[3][0]=1;
	data[3][1]=1;
	labels = new int[4];
	labels[0] = 1;
	labels[1] = 0;
	labels[2] = 0;
	labels[3] = 1;
	OnXorTrain();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPerceptron::OnXorTrain() 
{
	// TODO: Add your control notification handler code here
//初始化权值
	int i,j;
	//if (Weight) delete[] Weight;
	Weight = new double *[2];
	Weight[0] = new double[2*3];
	Weight[1] = new double[1*3];
	bool same;
	double rand_w;
	i = 0;
	while (i<6)
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
	while (i<3)
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

	double y[5];
	double err;
	while(1)
	{
		for (i=0;i<4;i++)
			for(int j=0;j<2;j++)
		{
			// 前向传播
			y[0] = data[i][j]; y[1] = data[i][j];
			forward_propagation(data[i],Weight,y);
			// 反向传播
			Back_Propagation(Weight,y,labels[i]);
		}
		
		// err
		err = 0;
		for (i=0;i<4;i++)
		{
			forward_propagation(data[i],Weight,y);
			err += 0.5*pow(y[4]-labels[i],2);
		}
		if (err < 0.001)
		{
			break;
		}
	}
}

void CPerceptron::OnXorTest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char ch1[10],ch2[10];
	int datatest[2];
	datatest[0]=m_px;
	datatest[1]=m_py;
	double y[5];
	y[0] = m_px; y[1] = m_py;
	forward_propagation(datatest,Weight,y);
	if(y[4]>0.5)
	m_result = 1;
	else m_result = 0;
	CString str="";
	str.Format("%d",m_result);
    SetDlgItemText(IDC_EDIT_RESULT,str);
}

void forward_propagation(int *input,double **Weight,double y[])
{
	int i;
	for (i=0;i<2;i++)
	{
		y[i+2] = Sigmoid(input[0]*Weight[0][0+i*3] + input[1]*Weight[0][1+i*3] + Weight[0][2+i*3]);
	}
	y[4] = Sigmoid(y[2]*Weight[1][0] + y[3]*Weight[1][1] + Weight[1][2]);
}

void Back_Propagation(double **Weight,double y[],double label)
{
	// 学习效率
	double eta = 0.01;
	// 输出层反馈
	int i,j;
	double delta1;
	delta1 = y[4]*(1-y[4])*(label-y[4]);
	for (i=0;i<3;i++)
	{
		if (i==2)
			Weight[1][i] += eta*delta1;
		else
			Weight[1][i] += eta*delta1*y[2+i];
	}
	// 中间层反馈
	double delta2[2];
	delta2[0] = y[2]*(1-y[2])*delta1*Weight[1][0];
	delta2[1] = y[3]*(1-y[3])*delta1*Weight[1][1];
	for (j=0;j<2;j++)
	{
		for (i=0;i<3;i++)
		{
			if (i==2)
				Weight[0][i+3*j] += eta*delta2[j];
			else
				Weight[0][i+3*j] += eta*delta2[j]*y[i];
		}
		
	}
}

double Sigmoid(double a)
{
	double output;
	output = 1/(1 + exp(-a));
	return output;
}

void CPerceptron::OnOK() 
{
	// TODO: Add extra validation here
	OnXorTest();
}
