// HOPFIELD.cpp : implementation file
//

#include "stdafx.h"
#include "NN.h"
#include "HOPFIELD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHOPFIELD dialog
#define m_Ns 3
int sgn(int x);
CHOPFIELD::CHOPFIELD(CWnd* pParent /*=NULL*/)
	: CDialog(CHOPFIELD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHOPFIELD)
	m_test0 = 0;
	m_test1 = 0;
	m_test2 = 0;
	m_train00 = 0;
	m_train01 = 0;
	m_train02 = 0;
	m_train10 = 0;
	m_train11 = 0;
	m_train12 = 0;
	m_train20 = 0;
	m_train21 = 0;
	m_train22 = 0;
	m_result0 = 0;
	m_result1 = 0;
	m_result2 = 0;
	//}}AFX_DATA_INIT
}


void CHOPFIELD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHOPFIELD)
	DDX_Text(pDX, IDC_EDIT_TEST0, m_test0);
	DDV_MinMaxInt(pDX, m_test0, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TEST1, m_test1);
	DDV_MinMaxInt(pDX, m_test1, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TEST2, m_test2);
	DDV_MinMaxInt(pDX, m_test2, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN00, m_train00);
	DDV_MinMaxInt(pDX, m_train00, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN01, m_train01);
	DDV_MinMaxInt(pDX, m_train01, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN02, m_train02);
	DDV_MinMaxInt(pDX, m_train02, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN10, m_train10);
	DDV_MinMaxInt(pDX, m_train10, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN11, m_train11);
	DDV_MinMaxInt(pDX, m_train11, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN12, m_train12);
	DDV_MinMaxInt(pDX, m_train12, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN20, m_train20);
	DDV_MinMaxInt(pDX, m_train20, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN21, m_train21);
	DDV_MinMaxInt(pDX, m_train21, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRAIN22, m_train22);
	DDV_MinMaxInt(pDX, m_train22, 0, 1);
	DDX_Text(pDX, IDC_EDIT_RESULT0, m_result0);
	DDV_MinMaxInt(pDX, m_result0, 0, 1);
	DDX_Text(pDX, IDC_EDIT_RESULT1, m_result1);
	DDV_MinMaxInt(pDX, m_result1, 0, 1);
	DDX_Text(pDX, IDC_EDIT_RESULT2, m_result2);
	DDV_MinMaxInt(pDX, m_result2, 0, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHOPFIELD, CDialog)
	//{{AFX_MSG_MAP(CHOPFIELD)
	ON_BN_CLICKED(IDC_MEMORY, OnMemory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHOPFIELD message handlers

BOOL CHOPFIELD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Weight=NULL;
	m_test0 = 1;
	m_test1 = 0;
	m_test2 = 1;
	m_train00 = 1;
	m_train01 = 1;
	m_train02 = 0;
	m_train10 = 0;
	m_train11 = 1;
	m_train12 = 1;
	m_train20 = 0;
	m_train21 = 0;
	m_train22 = 1;
	m_result0 = 0;
	m_result1 = 0;
	m_result2 = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHOPFIELD::OnMemory() 
{
	// TODO: Add your control notification handler code here
	// 获取输入的要求记忆的样本
	UpdateData(TRUE);
	int input[9] = {m_train00,m_train01,m_train02,m_train10,m_train11,m_train12,m_train20,m_train21,m_train22};
	for(int i=0;i<9;i++)
	{
		if(!input[i])
			input[i]=-1;
	}
	
	// Hebb学习规则
	if (Weight) delete[] Weight;
	Weight = new int[3*3];
	memset(Weight,0,sizeof(int)*3*3);
	int j,k;
	int x[3];
	for (k=0;k<m_Ns;k++)
	{
		x[0] = input[3*k]; x[1] = input[3*k+1]; x[2] = input[3*k+2];
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				Weight[i*3+j] += x[i]*x[j];
				if (i==j)
				{
					Weight[i*3+j] -= 1;
				}
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDC_EDIT_RESULT0,"0");
	SetDlgItemText(IDC_EDIT_RESULT1,"0");
	SetDlgItemText(IDC_EDIT_RESULT2,"0");
}

void CHOPFIELD::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int V[3] = {m_test0,m_test1,m_test2};
	int loop = 1;
	int i,j,k;
	int Vx;
	bool isStable;
	while(loop < 1000)
	{
		loop++;
		isStable = true;
		for (i=0;i<3;i++)
		{
			Vx = 0;
			for (j=0;j<3;j++)
			{
				for (k=j+1;k<3;k++)
				{
					if (j==i)
					{
						Vx += Weight[j*3+k]*V[k]; 
					}
					else if(k==i)
					{
						Vx += Weight[j*3+k]*V[j]; 
					}
				}
			}
			Vx = sgn(Vx);
			if (Vx!=V[i])
			{
				V[i] = Vx;
				isStable = false;
				break;
			}
		}
		if (isStable)
		{
			break;
		}
	}
	// 显示
	for(i=0;i<3;i++)
	{
		if(V[i]<0)
			V[i]=0;
	}
	if (loop==1000) MessageBox(_T("找不到稳定状态！"),_T("警告！"),MB_OK);
	else
	{
		CString str;
		str.Format("%d",V[0]);
		SetDlgItemText(IDC_EDIT_RESULT0,str);
		str.Format("%d",V[1]);
		SetDlgItemText(IDC_EDIT_RESULT1,str);
		str.Format("%d",V[2]);
		SetDlgItemText(IDC_EDIT_RESULT2,str);
	}
//	CDialog::OnOK();
}

int sgn(int x)
{
	int output;
	output = x > 0? 1:-1;
	return output;
}
