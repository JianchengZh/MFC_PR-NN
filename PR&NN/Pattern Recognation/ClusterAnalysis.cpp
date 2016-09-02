// ClusterAnalysis.cpp : implementation file
//

#include "stdafx.h"
#include "Pattern Recognation.h"
#include "ClusterAnalysis.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis dialog
/*
#define m_k	 3	// Ԥ�ڵõ��ľ�����
		
#define m_thetaN 15		// һ�������е�����������
#define m_I  1000		// ��������Ĵ���
#define m_thetaS  5		// ��׼ƫ����������Ѳ�����
#define m_thetaD  50		// �ϲ�����
	
*/
#define m_L  4// ÿ�ε�������ϲ������������
#define m_Nc 10// ��ʼ�����
CClusterAnalysis::CClusterAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CClusterAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClusterAnalysis)
	m_cvalue = 0;
	m_jadd = 0.0;
	m_k = 0;
	m_thetaN = 0;
	m_thetaD = 0;
	m_thetaS = 0;
	m_I = 0;
	//}}AFX_DATA_INIT
}


void CClusterAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClusterAnalysis)
	DDX_Text(pDX, IDC_EDIT_C, m_cvalue);
	DDX_Text(pDX, IDC_EDIT_ERRORX_ADD, m_jadd);
	DDX_Text(pDX, IDC_EDIT_k, m_k);
	DDX_Text(pDX, IDC_EDIT_thetaN, m_thetaN);
	DDX_Text(pDX, IDC_EDIT_thetaD, m_thetaD);
	DDX_Text(pDX, IDC_EDIT_thetaS, m_thetaS);
	DDX_Text(pDX, IDC_EDIT_I, m_I);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClusterAnalysis, CDialog)
	//{{AFX_MSG_MAP(CClusterAnalysis)
	ON_BN_CLICKED(IDC_BUTTON_C_MEANS, OnButtonCMeans)
	ON_BN_CLICKED(IDC_BUTTON_ISODATA, OnButtonIsodata)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis message handlers
#define dataRange 100
#define Len 60
#define radius 2
#define eps 0.00000000000000001
#define x_len 5

BOOL CClusterAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	data = NULL;
	labels = NULL;
	Nsample = NULL;
	means = NULL;
	GetDlgItem(IDC_DRAW_CLUSTER)->GetWindowRect(&picrect);
	ScreenToClient(picrect);

	m_cvalue=5;
	m_jadd=0;
	iscluster = 0;


	m_k = 5;
	m_thetaN = 20;
	m_thetaD = 40;
	m_thetaS = 10;
	m_I = 2000;

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
//data
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClusterAnalysis::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CPen pen1(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&pen1);
	dc.MoveTo(picrect.left,picrect.top);
	dc.LineTo(picrect.right,picrect.top);
	
	dc.MoveTo(picrect.right-1,picrect.bottom);
	dc.LineTo(picrect.right-1,picrect.top);
	
	// ����һ�����ʵ�����
	CPen pen2(PS_SOLID,2,RGB(0,0,0));
	//������ѡ���豸
	dc.SelectObject(&pen2);
	// ��x��
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.right+30,picrect.bottom);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom-10);
	
	dc.MoveTo(picrect.right+30,picrect.bottom);
	dc.LineTo(picrect.right+20,picrect.bottom+10);
	// ��y��
	dc.MoveTo(picrect.left,picrect.bottom);
	dc.LineTo(picrect.left,picrect.top-30);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left-10,picrect.top-20);
	
	dc.MoveTo(picrect.left,picrect.top-30);
	dc.LineTo(picrect.left+10,picrect.top-20);
	
	// ��x��label
	dc.TextOut(picrect.right+40,picrect.bottom,"x1");
	// ��y��label
	dc.TextOut(picrect.left+15,picrect.top-25,"x2");
	// ��ԭ��
	dc.TextOut(picrect.left-20,picrect.bottom+5,"(0,0)");
	CString numstr = "";
	numstr.Format("%d",dataRange);
	CString str = "(" + numstr + ",0)"; 
	dc.TextOut(picrect.right-20,picrect.bottom+5,str);
	str = "(0," + numstr + ")";
	dc.TextOut(picrect.left-20,picrect.top+5,str);
	
	// �����ݵ�
	int i,j;
	int x,y;
	CPen pen3(PS_SOLID,2,RGB(0,0,0));
	if(data)
	{
		if (iscluster == 0)
		{
			for (i=0;i<Len;i++)
			{
				// ����ת��
				x = int(data[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - data[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				//������ѡ���豸
				dc.SelectObject(&pen3);
				dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
			}
		}
		else
		{
			// ���ݵ�
			for (i=0;i<Len;i++)
			{
				// ����ת��
				x = int(data[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - data[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				for (j=0;j<showC;j++)
				{
					if (labels[i]==j)
						dc.SelectObject(&pen[j]);	//������ѡ���豸
					dc.Ellipse(x-radius,y-radius,x+radius,y+radius);
				}	
			}
			// �����ĵ�
			for (i=0;i<showC;i++)
			{
				// ����ת��
				x = int(means[i][0]*(double(picrect.Width())/dataRange) + picrect.left);
				y = int(picrect.Height() - means[i][1]*(double(picrect.Height())/dataRange) + picrect.top);
				dc.SelectObject(&pen[i]);
/*
				CBrush brush,*oldbrush;
				brush.CreateSolidBrush(RGB(100,100,100));
				oldbrush=dc.SelectObject(&brush);
				dc.Ellipse(x-radius+2,y-radius+2,x+radius+2,y+radius+2);
				dc.SelectObject(oldbrush);*/

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
			font.CreatePointFont(150, "����");//����ɸĳ��Լ���Ҫ�ģ�
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

void CClusterAnalysis::OnButtonCMeans() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString str;
	// ���������c
	UpdateData(TRUE);
	showC = m_cvalue;
	// ��ֵ����
	means = new double*[m_cvalue];
	for(i=0;i<m_cvalue;i++)
		means[i]=new double[2];
	// ���ѡȡc ����������
	int index;
	for (i=0;i<m_cvalue;i++)
	{
		index = rand()*(Len/m_cvalue-1)/RAND_MAX + i*(Len/m_cvalue);
		means[i] = data[index];
	}
	// �õ�ÿ�����ݵ�����
	if (labels) delete[] labels;
	labels = new int[Len];
	double *dist = new double[m_cvalue];
	for (i=0;i<Len;i++)
	{
		for (j=0;j<m_cvalue;j++)
		{
			dist[j] = sqrt(pow(data[i][0]-means[j][0],2)+pow(data[i][1]-means[j][1],2));
		}	
		labels[i] = MinDist(dist,m_cvalue);
	}

	if (Nsample) delete[] Nsample;
	Nsample = new int [m_cvalue];
	GetNsample(labels,m_cvalue,Nsample);
	// ����means
	GetMean(data,labels,means,Nsample,m_cvalue);

	// ����Je�����ƽ���ͣ��������������J
	double Je = 0;
	double *J = new double[m_cvalue];
	GetJ(data,labels,means,m_cvalue,J);
	Je = GetJe(J,m_cvalue);
	
	// ����Ѱ��
	int rn;		// �����
	double *y=new double[2];int y_i;	// �������
	int k;
	double Nj,Ni,Nk;
	double rho_i,rho_k;
	double rho_j;
	double Jetmp;
	for(j=0;j<1000;j++)
	{
		srand((unsigned) time(NULL));
		rn = rand()%(Len-1);
		y_i = labels[rn];
		y = data[rn];
		Ni = double(Nsample[y_i]);
		if (Ni == 1) 
			continue;
		rho_i = (Ni/(Ni - 1)) * sqrt(pow(y[0]-means[y_i][0],2)+pow(y[1]-means[y_i][1],2));
		rho_k = 1000000;
		for (i=0;i<m_cvalue;i++)
		{
			if (i==y_i) continue;
			Nj = double(Nsample[i]);
			rho_j = (Nj/(Nj + 1)) * sqrt(pow(y[0]-means[i][0],2)+pow(y[1]-means[i][1],2));
			if (rho_j < rho_k)
			{
				rho_k = rho_j;
				k = i;
				Nk = double(Nsample[i]);
			}
		}
		if (rho_k < rho_i)
		{
			labels[rn] = k;
			// ���¼���mean Je
			for(i=0;i<2;i++)
			{
				means[y_i][i] = means[y_i][i] + (means[y_i][i]-y[i]) * (1/(Ni-1));
				means[k][i] = means[k][i] + (y[i]-means[k][i]) * (1/(Nk+1));
			}

			J[y_i] += -rho_i;
			J[k] += rho_k;
			Jetmp = GetJe(J,m_cvalue);
			GetNsample(labels,m_cvalue,Nsample);
			if (fabs(Jetmp-Je) < 1) 
				break;
			else 
				Je = Jetmp;
		}
	}
	// ���������ȷ��
	acc = GetAcc(labels,m_cvalue);
	//	str.Format("%.4f",acc/Len);
	//	SetDlgItemText(IDC_Acc,str);
	
	// ��ʾ
	str.Format("%.5f",Je);
	SetDlgItemText(IDC_EDIT_ERRORX_ADD,str);
	iscluster = 1;
	Invalidate();
	
	// �ͷ���ʱ�ڴ�
	delete[] dist;
	delete[] J;
}

void CClusterAnalysis::OnButtonIsodata() 
{
	// TODO: Add your control notification handler code here
	int iteration = 1;
	// ���ݱ�ǩ
	if (labels) delete[] labels;
	labels = new int[Len];
	int i,j;
	// �������
	UpdateData(TRUE);
	int Nc = m_Nc;
	int K = m_k;
	int thetaN = m_thetaN;
	double thetaS = m_thetaS;
	double thetaD = m_thetaD;
	
	// ���������ֵ����
	if (means) delete[] means;
	means = new double *[Nc];
	for(i=0;i<Nc;i++)
	{
		means[i] = new double [2];
	}
	// ����
	double *dist = NULL;
	int *tmpLabels = NULL;
	int ci,record;
	double distSum;
	int ltmp;
	double Ntmp;
	double **tmpMeans = NULL;
	// ���ѡȡc����������
	int index;
	bool same;
	i=0;
	while(i<Nc)
	{
		index = rand()*(Len-1)/RAND_MAX;
		same = false;
		for (j=0;j<i;j++)
		{
			if (means[j][0]==data[index][0] && means[j][1]==data[index][1])
			{
				same = true;
				break;
			}
		}
		if (!same)
		{
			means[i] = data[index];
			i++;
		}
		//	index++;
		
	}
	while (1)
	{
		// �ɵ㵽�����ֵ�����С��ֵԭ�򣬵õ�ÿ�����ݵ�����
		classification(means,data,labels,Nc);
		
		// �ж��Ƿ�ȡ��ĳЩ��(���г�Ա����һ����ֵ)
		if (Nsample) delete[] Nsample;
		Nsample = new int[Nc];
		GetNsample(labels,Nc,Nsample);
		// ���ÿ�����������Ŀ
		for (ci=0;ci<Nc;ci++)	
		{
			// ci�����ĿС����ֵ(�������������еĶ�������С����ԭ����䵽������������)
			if (Nsample[ci] < thetaN)	
			{
				if (dist) delete[] dist;
				dist = new double[Nc-1];
				if (tmpLabels) delete[] tmpLabels;
				tmpLabels = new int[Nc-1];
				if (tmpMeans) delete[] tmpMeans;
				tmpMeans = new double*[Nc];
				for(i=0;i<Nc;i++)
				{
					tmpMeans[i]=new double[2];
					for(j=0;j<2;j++)
						tmpMeans[i][j]=means[i][j];
				}

				// ���Ҹ���������
				for (i=0;i<Len;i++)		
				{
					if (labels[i]==ci)	// iΪ���ҵ��������������
					{
						for (j=0,record=0;j<Nc;j++)	// ���������ݾ������������ĵľ���
						{
							if (j==ci) continue;
							dist[record] = sqrt(pow(data[i][0]-tmpMeans[j][0],2)+pow(data[i][1]-tmpMeans[j][1],2));
							tmpLabels[record] = j;
							record++;
						}	
						// �õ������ݵ��������
						labels[i] = MinDistLabel(dist,Nc-1,tmpLabels);
						// �������ֵ
						double *tmp=new double[2];
						for(int m=0;m<2;m++)
						{
							tmp[m]=(data[i][m]-tmpMeans[labels[i]][m])*(1/double(Nsample[labels[i]]));
						}
						tmpMeans[labels[i]][m] = tmpMeans[labels[i]][m] + tmp[m];
						// �������Ա��
						Nsample[labels[i]]++;
						Nsample[ci]--;
					}
				}
			// ��������ֵ
			if (means) delete[] means;
			means = new double*[Nc];
			for(int n=0;n<Nc;n++)
			{
				means[n]=new double[2];
			}
			for (i=0,j=0;i<Nc;i++)
			{
				if (i==ci) continue;
				means[j] = tmpMeans[i];
				j++;
			}
			// �������1
			Nc--;
			// �����������ݵ�����ǩlabels
			classification(means,data,labels,Nc);
			// �����������ݵ������Nsample
			if (Nsample) delete[] Nsample;
			Nsample = new int[Nc];
			GetNsample(labels,Nc,Nsample);
			// ���¿�ʼɸ��
			ci = -1;		
		}
	}
	
	// ��������������ĵ�ƽ������ ��ƽ������
	if (dist) delete[] dist;
	dist = new double[Nc];
	memset(dist,0,sizeof(double)*Nc);
	for (i=0;i<Len;i++)
	{
		ltmp = labels[i];
		Ntmp = double(Nsample[ltmp]);
		dist[ltmp] += sqrt(pow(data[i][0]-means[ltmp][0],2)+pow(data[i][1]-means[ltmp][1],2)) / Ntmp;	
	}
	distSum = 0;
	for (i=0;i<Nc;i++)
	{
		Ntmp = double(Nsample[i]);
		distSum += dist[i]*Ntmp/Len;
	}
	
	// �жϷ��ѣ��ϲ������
	if (iteration==m_I)
		break;
	else if (Nc<=double(K)/2)
		seperate(Nc,dist,distSum);
	else if (Nc>=K*2)
		consolidation(Nc);
	else
	{ 
		if (Nc%2 == 0)	// ż��
			consolidation(Nc);
		else			// ����
			seperate(Nc,dist,distSum);
	}
	iteration++;
	}

	// �����������ݵ�����ǩlabels
	classification(means,data,labels,Nc);
	// �����������ݵ������Nsample
	if (Nsample) delete[] Nsample;
	Nsample = new int[Nc];
	GetNsample(labels,Nc,Nsample);
	// �����պϲ������������c
	showC = Nc;
	acc = GetAcc(labels,Nc);
	iscluster = 2;
	Invalidate();
}

void CClusterAnalysis::seperate(int &Nc,double *dist,double distSum)
{
	// �������
	UpdateData(TRUE);
	int K = m_k;
	int thetaN = m_thetaN;
	double thetaS = m_thetaS;
	// ������׼ƫ������
	double **sigma = new double*[Nc];
	for(int i=0;i<Nc;i++)
	{
		sigma[i]=new double [2];
		for(int j=0;j<2;j++)
		{
			sigma[i][j]=0;
		}
	}
	int c = Nc;
	int ltmp;
	double Ntmp;
	// ��ƫ���
	for (i=0;i<Len;i++)
	{
		ltmp = labels[i];
		Ntmp = double(Nsample[ltmp]);
		sigma[ltmp][0] += pow(data[i][0] - means[ltmp][0], 2) / Ntmp;
		sigma[ltmp][1] += pow(data[i][1] - means[ltmp][1], 2) / Ntmp;
	}
	// ��׼ƫ��
	for (i=0;i<c;i++)
	{
		sigma[i][0] = sqrt(sigma[i][0]);
		sigma[i][1] = sqrt(sigma[i][1]);
	}
	// ��sigma_jmax
	double *sigma_jmax = new double[c];
	int *sigma_jmax_index = new int[c];
	// ����ÿ���࣬�����׼ƫ�����ķ���
	for (i=0;i<c;i++)
	{
		sigma_jmax[i] = sigma[i][0] > sigma[i][1] ? sigma[i][0] : sigma[i][1];
		sigma_jmax_index[i] = sigma[i][0] > sigma[i][1] ? 1 : 2;
	}
	// �Ƿ����
	double **tmpMeans=new double*[Nc];
	for(i=0;i<Nc;i++)
		tmpMeans[i]=new double[2];
	for (i=0;i<c;i++)
	{
		if (sigma_jmax[i]>thetaS && dist[i]>distSum && Nsample[i]>2*(thetaN+1) || c<=(double(K)/2))
		{
			// tmpMeans��Ϊmeans����չ���洢�µĸ����ֵ
			if (tmpMeans) delete[] tmpMeans;
			tmpMeans = new double*[Nc];
			for(int p=0;p<Nc;p++)
			{
				tmpMeans[p]=new double [2];
				for(int q=0;q<2;q++)
				{
					tmpMeans[p][q]=means[p][q];
				}
			}
			// ���Ѻ���¾�ֵ
			if (sigma_jmax_index[i]==1)
			{
				tmpMeans[i][0] += 0.5 * sigma_jmax[i];
				tmpMeans[Nc][0] = tmpMeans[i][0] - 0.5 * sigma_jmax[i];
				tmpMeans[Nc][1] = tmpMeans[i][1];
			}
			else
			{
				tmpMeans[i][1] += 0.5 * sigma_jmax[i];
				tmpMeans[Nc][1] = tmpMeans[i][1] - 0.5 * sigma_jmax[i];
				tmpMeans[Nc][0] = tmpMeans[i][0];
			}
			// ��tmpMeans������means
			if (means) delete[] means;
			means = new double*[Nc+1];
			for(p=0;p<Nc+1;p++)
			{
				means[p]=new double [2];
				for(int q=0;q<2;q++)
				{
					means[p][q]=tmpMeans[p][q];
				}
			}
			// �����+1
			Nc++;
		}
	}
	// �ͷ��ڴ�
	delete[] tmpMeans;
	delete[] sigma;
	delete[] sigma_jmax;
	delete[] sigma_jmax_index;
}

void CClusterAnalysis::consolidation(int &Nc)
{
	int i,j;
	// �������
	UpdateData(TRUE);
	int L = m_L;
	int NumSigma = 0;
	double thetaD = m_thetaD;
	double *sigma = NULL;
	double *sigma_sort = NULL;
	double  **Index = NULL;
	int k;
	double tmp1;
	double *tmp2;
	bool *isconsolidation = NULL;
	double **tmpMeans = NULL;
	int tmpNc;
	int li,lj;
	double Ni,Nj;

	// ���������������֮��ľ���
	if (sigma) delete[] sigma;
	sigma = new double[Nc*Nc];
	for (i=1;i<Nc;i++)
	{
		for (j=i+1;j<Nc;j++)
		{
			sigma[i*Nc+j] = sqrt(pow(means[i][0]-means[j][0],2)+pow(means[i][1]-means[j][1],2));
			if (sigma[i*Nc+j] < thetaD) NumSigma++;
		}
	}
	if (NumSigma < 1) 
		return;
	// �Ƚ�sigma��thetaD��ȡ��С��thetaD��
	if (sigma_sort) delete[] sigma_sort;
	sigma_sort = new double[NumSigma];
	if (Index) delete[] Index;
	Index = new double*[NumSigma];
	for(i=0;i<2;i++)
		Index[i]=new double[2];
	k = 0;
	for (i=1;i<Nc;i++)
	{
		for (j=i+1;j<Nc;j++)
		{
			if (sigma[i*Nc+j] < thetaD)
			{
				sigma_sort[k] = sigma[i*Nc+j];
				Index[k][0] = i;
				Index[k][1] = j;
				k++;
			}
		}
	}
	// ��С��thetaD�߽�������
	for(i=0;i<NumSigma;i++) 
	{
		for(j=0;j<NumSigma-i-1;j++)
		{
			if(sigma_sort[j]>sigma_sort[j+1])
			{
				// ��������
				tmp1 = sigma_sort[j];
				sigma_sort[j] = sigma_sort[j+1];
				sigma_sort[j+1] = tmp1;
				// ��ǩ����
				tmp2 = Index[j];
				Index[j] = Index[j+1];
				Index[j+1] = tmp2;
			}		
		}
	}
	// ���ºϲ�������ֵ
	if (isconsolidation) delete[] isconsolidation;
	isconsolidation = new bool[Nc];
	memset(isconsolidation,TRUE,sizeof(bool)*Nc);
	tmpNc = Nc;
	for (i=0;i< min(L,NumSigma);i++)
	{
		// ��ϲ���������
		li = int(Index[i][0]);
		lj = int(Index[i][1]);
		// �ж���ε��������Ƿ�ϲ���
		if (isconsolidation[li] && isconsolidation[lj])
		{
			Ni = double(Nsample[li]);
			Nj = double(Nsample[lj]);
			for(int j=0;j<2;j++)
			{
				means[li][j] = (means[li][j]*Ni + means[lj][j]*Nj) * (1/(Nj + Ni));
				means[lj][0] = -1;
				means[lj][1] = -1;
			}

			isconsolidation[li] = false;
			isconsolidation[lj] = false;
			tmpNc--;
		}
	}
	// �������ֵ����
	if (tmpMeans) delete[] tmpMeans;
	tmpMeans = new double*[Nc];
	for(i=0;i<Nc;i++)
	{
		tmpMeans[i]=new double[2];
		for(int j=0;j<2;j++)
		{
			tmpMeans[i][j]=means[i][j];
		}
	}
	if (means) delete[] means;
	means = new double*[tmpNc];
	for (i=0,j=0;i<Nc;i++)
	{
		if (tmpMeans[i][0]!=-1)
		{
			means[j] = tmpMeans[i];
			j++;
		}
	}
	Nc = tmpNc;
	// �ͷ��ڴ�
	delete[] sigma;
	delete[] sigma_sort;
	delete[] Index;
	delete[] isconsolidation;
	delete[] tmpMeans;
	
}

int CClusterAnalysis::MinDistLabel(double *dist,int k,int *Labels)
{
	int i,c;
	double min_value;
	for (i=0;i<k;i++)
	{
		if (i==0) 
		{
			min_value = dist[i];
			c = Labels[i];
		}
		else if (dist[i] < min_value)
		{
			min_value = dist[i];
			c = Labels[i];
		}
	}
	return c;
}

void CClusterAnalysis::classification(double **means,double **data,int *labels,int c)
{
	double *distance = new double[c];
	for (int i=0;i<Len;i++)
	{
		for (int j=0;j<c;j++)
		{
			distance[j] = sqrt(pow(data[i][0]-means[j][0],2)+pow(data[i][1]-means[j][1],2));
		}	
		labels[i] = MinDist(distance,c);
	}
	delete[] distance;
}

int CClusterAnalysis::MinDist(double *input,int k)
{
	int i,c;
	double min_value;
	for (i=0;i<k;i++)
	{
		if (i==0) 
		{
			min_value = input[i];
			c = 0;
		}
		else if (input[i] < min_value)
		{
			min_value = input[i];
			c = i;
		}
	}
	return c;
}

void CClusterAnalysis::GetNsample(int *labels,int k,int *Nsample)
{
	memset(Nsample,0,sizeof(int)*k);
	int i,j;
	for (i=0;i<Len;i++)
	{
		for (j=0;j<k;j++)
		{
			if (labels[i]==j)
			{
				Nsample[j] += 1;
				break;
			}
		}
	}
}

void CClusterAnalysis::GetJ(double **data,int *labels,double **means,int k,double *J)
{
	memset(J,0,sizeof(double)*k);
	int i,j;
	for (i=0;i<Len;i++)
	{
		for (j=0;j<k;j++)
		{
			if (labels[i]==j)
			{
				J[j] += sqrt(pow(data[i][0]-means[j][0],2)+pow(data[i][1]-means[j][1],2));
			}
		}
	}
}

double CClusterAnalysis::GetJe(double *J,int k)
{
	double Je = 0;
	for (int i=0;i<k;i++)
		Je += J[i];
	return Je;
}

void CClusterAnalysis::GetMean(double **data,int *labels,double **means,int *Nsample,int k)
{
/*	memset(means,0,sizeof(double)*k);*/

	for(int m=0;m<k;m++)
		for(int n=0;n<2;n++)
			means[m][n]=0;
	for (int i=0;i<Len;i++)
		for(int j=0;j<2;j++)
	{
		means[labels[i]][j] +=  data[i][j]/double(Nsample[labels[i]]);
	}
}

int CClusterAnalysis::MaxIndex(int *input,int k)
{
	int maxvalue = 0;
	int index=0;;
	for (int i=0;i<k;i++)
	{
		if (input[i]>maxvalue)
		{
			maxvalue = input[i];
			index = i;
		}
	}
	return index;
}

double CClusterAnalysis::GetAcc(int *labels,int c)
{
	double Acc = 0;
	int i,j,k;
	int index;
	int *labelsNum = new int[c];
	int *labelsRecord = new int[3];
	bool same;
	for (j=0;j<3;j++)
	{
		memset(labelsNum,0,sizeof(int)*c);
		for (i=j*(Len/3);i<(Len/3)*(j+1);i++)
		{
			same = false;
			for (k=0;k<j;k++)
			{
				if (labels[i]==labelsRecord[k])
				{
					same = true;
					break;
				}
			}
			if (!same)
			{
				labelsNum[labels[i]]++;
			}
			
		}
		index = MaxIndex(labelsNum,c);
		Acc += labelsNum[index];
		labelsRecord[j] = index;
	}
	delete[] labelsNum;
	delete[] labelsRecord;
	return Acc;
}

