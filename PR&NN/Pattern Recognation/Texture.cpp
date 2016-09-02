// Texture.cpp : implementation file
//

#include "stdafx.h"
#include "Pattern Recognation.h"
#include "Texture.h"
#include "math.h"
#include "MainFrm.h"
#include "nrutil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTexture dialog


CTexture::CTexture(CWnd* pParent /*=NULL*/)
	: CDialog(CTexture::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTexture)
		// NOTE: the ClassWizard will add member initialization here
	m_dCorrelation = 0.0;
	m_dEnergy = 0.0;
	m_dEntropy = 0.0;
	m_dInertiaQuadrature = 0.0;
	m_dLocalCalm = 0.0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTexture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTexture)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT_CORRELATION, m_dCorrelation);
	DDX_Text(pDX, IDC_EDIT_ENERGY, m_dEnergy);
	DDX_Text(pDX, IDC_EDIT_ENTROPY, m_dEntropy);
	DDX_Text(pDX, IDC_EDIT_INERTIA_QUADRATURE, m_dInertiaQuadrature);
	DDX_Text(pDX, IDC_EDIT_LOCAL_CALM, m_dLocalCalm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTexture, CDialog)
	//{{AFX_MSG_MAP(CTexture)
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTexture message handlers
////////////////////////////////////////////////////////////////////
//���ܣ�װ��ͼ��
//������FilePathName��ͼ���ļ�·����
void CTexture::LoadImage(CDib* p_dib)
{
	PMatrixRD = NULL;	//45�ȷ����ϵĻҶȹ��־���
	PMatrixLD = NULL;	//135�ȷ����ϵĻҶȹ��־���
	PMatrixV = NULL;		//90�ȷ����ϵĻҶȹ��־���
	PMatrixH = NULL;		//0�ȷ����ϵĻҶȹ��־���
	ImageArray = NULL;	//ԭʼ��ͼ����������
	
	m_tOriPixelArray = NULL;//ԭʼλͼ����
	m_tResPixelArray = NULL;//�ο�λͼ����
	//	m_dib = new CDib();
	
	distance = 5;
	FilterWindowWidth = 16;
	GrayLayerNum = 8; //��ʼ����Ϊ8���ҶȲ㣬�����޸�
	//�������־����ΪGrayLayerNum��GrayLayerNum
	int i,j;
	PMatrixH = new int*[GrayLayerNum];
	PMatrixLD= new int*[GrayLayerNum];
	PMatrixRD= new int*[GrayLayerNum];
	PMatrixV = new int*[GrayLayerNum];
	for(i=0; i<GrayLayerNum; i++)
	{
		PMatrixH[i] = new int[GrayLayerNum];
		PMatrixLD[i]= new int[GrayLayerNum];
		PMatrixRD[i]= new int[GrayLayerNum];
		PMatrixV[i] = new int[GrayLayerNum];
	}
	//����Ƿ�Ϊ�գ���Ϊ����Ҫ�ͷ��ڴ�
	if(m_tOriPixelArray !=NULL)
	{
		for(i=0; i<ImageHeight; i++)
		{
			delete m_tOriPixelArray[i];
			delete m_tResPixelArray[i];
			delete ImageArray[i];
		}
	}

	ImageWidth = p_dib->m_imgWidth;
	ImageHeight = p_dib->m_imgHeight;
	
	BYTE	*colorTable;
	colorTable = (BYTE *)p_dib->m_lpColorTable;
	int byteBitCount  = p_dib->m_nBitCount;
	
	m_tOriPixelArray  = new RGBQUAD*[ImageHeight];
	m_tResPixelArray  = new RGBQUAD*[ImageHeight];
	ImageArray = new BYTE*[ImageHeight];
	for(int l=0 ; l<ImageHeight; l++)
	{
		m_tOriPixelArray[l] = new RGBQUAD[ImageWidth];
		m_tResPixelArray[l] = new RGBQUAD[ImageWidth];
		ImageArray[l] = new BYTE[ImageWidth];
	}
	
	int count = 0;
	for(i=ImageHeight-1; i>=0; i--)
	{
		for(j=0; j<ImageWidth; j++)
		{
			m_tOriPixelArray[i][j].rgbBlue =colorTable[count++];
			m_tOriPixelArray[i][j].rgbGreen=colorTable[count++];
			m_tOriPixelArray[i][j].rgbRed  =colorTable[count++];
			m_tOriPixelArray[i][j].rgbReserved = 0;
			m_tResPixelArray[i][j]=m_tOriPixelArray[i][j];
			ImageArray[i][j] = (BYTE)(((unsigned int)m_tOriPixelArray[i][j].rgbBlue
				+(unsigned int)m_tOriPixelArray[i][j].rgbGreen
				+(unsigned int)m_tOriPixelArray[i][j].rgbRed)/3);
			count += byteBitCount-3;
		}
		count += (4-(ImageWidth*byteBitCount)%4)%4;
	}
}
////////////////////////////////////////////////////////////////////////////////////
//�������ܣ�������������
//������FeatureEnergy������
//      FeatureEntropy����
//      FeatureInertiaQuadrature�����Ծ�
//      FeatureCorrelation�����
//      FeatureLocalCalm���ֲ�ƽ��
//      pMatrix�����־���
//      dim�����־����ά��
///////////////////////////////////////////////////////////////////////////////////
void CTexture::TextureFeture(double &FeatureEnergy, double &FeatureEntropy, 
							  double &FeatureInertiaQuadrature, double &FeatureCorrelation, 
							  double &FeatureLocalCalm, int** pMatrix, int dim)

{
	int i,j;
	double **pdMatrix;
	pdMatrix = new double*[dim];
	for(i=0; i<dim; i++)
		pdMatrix[i] = new double[dim];

	int total = 0;
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim; j++)
		{
			total += pMatrix[i][j];
		}
	}

	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim; j++)
		{
			pdMatrix[i][j] = (double)pMatrix[i][j]/(double)total;
		}
	}
	
	FeatureEnergy = 0.0;
	FeatureEntropy = 0.0;
	FeatureInertiaQuadrature = 0.0;
	FeatureLocalCalm = 0.0;


	//�����������ء����Ծء��ֲ�ƽ��
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim; j++)
		{
			//����
			FeatureEnergy += pdMatrix[i][j]*pdMatrix[i][j];

			//��
			if(pdMatrix[i][j]>1e-12)
			{
				FeatureEntropy -= pdMatrix[i][j]*log(pdMatrix[i][j]);
			}

			//���Ծ�
			FeatureInertiaQuadrature += (double)(i-j)*(double)(i-j)*pdMatrix[i][j];

			//�ֲ�ƽ��
			FeatureLocalCalm += pdMatrix[i][j]/(1+(double)(i-j)*(double)(i-j));
		}
	}

	//����ux
	double ux = 0.0;
	double localtotal = 0.0;
	for(i=0; i<dim; i++)
	{
		localtotal = 0.0;
		for(j=0; j<dim; j++)
		{
			localtotal += pdMatrix[i][j];
		}
		ux += (double)i * localtotal;
	}

	//����uy
	double uy = 0.0;
	for(j=0; j<dim; j++)
	{
		localtotal = 0.0;
		for(i=0; i<dim; i++)
		{
			localtotal += pdMatrix[i][j];
		}
		uy += (double)j * localtotal;
	}

	//����sigmax
	double sigmax = 0.0;
	for(i=0; i<dim; i++)
	{
		localtotal = 0.0;
		for(j=0; j<dim; j++)
		{
			localtotal += pdMatrix[i][j];
		}
		sigmax += (double)(i-ux) * (double)(i-ux) * localtotal;
	}

	//����sigmay
	double sigmay = 0.0;
	for(j=0; j<dim; j++)
	{
		localtotal = 0.0;
		for(i=0; i<dim; i++)
		{
			localtotal += pdMatrix[i][j];
		}
		sigmay += (double)(j-uy) * (double)(j-uy) * localtotal;
	}

	//�������
	FeatureCorrelation = 0.0;
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim; j++)
		{
			FeatureCorrelation += (double)(i-ux) * (double)(j-uy) * pdMatrix[i][j];
		}
	}
	FeatureCorrelation /= sigmax;
	FeatureCorrelation /= sigmay;
}

/////////////////////////////////////////////////////////////////////////////////////
//���ܣ����㹲�־���
//������LocalImage����������ľֲ���������ͼ��
//      LocalImageWidth���ֲ�����������
////////////////////////////////////////////////////////////////////////////////////
void CTexture::ComputeMatrix(BYTE **LocalImage, int LocalImageWidth)
{
	BYTE **NewImage;
	NewImage = new BYTE*[LocalImageWidth];
	
	int i,j;
	for(i=0; i<LocalImageWidth; i++)
		NewImage[i] = new BYTE[LocalImageWidth];
	
	for(i=0; i<LocalImageWidth; i++)
	{
		for(j=0; j<LocalImageWidth; j++)
		{
			//�ֳ�GrayLayerNum���Ҷȼ�
			NewImage[i][j] = LocalImage[i][j] / (256/GrayLayerNum);
		}
	}
	
	for(i=0; i<GrayLayerNum; i++)
	{
		//
		for(j=0; j<GrayLayerNum; j++)
		{
			PMatrixH[i][j]  = 0;
			PMatrixLD[i][j] = 0;
			PMatrixRD[i][j] = 0;
			PMatrixV[i][j]  = 0;
		}
	}
	
	//����0�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth; i++)
	{
		for(j=0; j<LocalImageWidth-distance; j++)
		{
			PMatrixH[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i][j+distance]] += 1;
			PMatrixH[(unsigned int)NewImage[i][j+distance]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//����90�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth-distance; i++)
	{
		for(j=0; j<LocalImageWidth; j++)
		{
			PMatrixV[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i+distance][j]] += 1;
			PMatrixV[(unsigned int)NewImage[i+distance][j]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//����135�ȵĻҶȹ�����
	for(i=0; i<LocalImageWidth-distance; i++)
	{
		for(j=0; j<LocalImageWidth-distance; j++)
		{
			int newi, newj;
			newi = i+distance;
			newj = j+distance;
			PMatrixLD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixLD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//����45�ȵĻҶȹ�����
	for(i=distance; i<LocalImageWidth; i++)
	{
		for(j=0; j<LocalImageWidth-distance; j++)
		{
			int newi, newj;
			newi = i-distance;
			newj = j+distance;
			PMatrixRD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixRD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
}

void CTexture::OnOK() 
{
	double dEnergy			  = 0.0;
	double dEntropy			  = 0.0;
	double dInertiaQuadrature = 0.0;
	double dLocalCalm		  = 0.0;
	double dCorrelation		  = 0.0;
	double dEnergy1			  = 0.0;
	double dEntropy1		  = 0.0;
	double dInertiaQuadrature1= 0.0;
	double dLocalCalm1		  = 0.0;
	double dCorrelation1	  = 0.0;
	unsigned char** arLocalImage;
	arLocalImage = cmatrix(0, FilterWindowWidth-1, 0, FilterWindowWidth-1); 
	int rolltimeH = ImageHeight/FilterWindowWidth;
	int rolltimeW = ImageWidth /FilterWindowWidth;
	int i,j;
	int p,q;
	//��ͼ��ֳ����ɸ����ڣ������������ֵ
	for(i=0; i< rolltimeH; i++)
	{
		for(j=0; j<rolltimeW; j++)
			
		{			//���ȸ�ֵ���Ӵ���
			for(p=0; p<FilterWindowWidth; p++)
			{
				for(q=0; q<FilterWindowWidth; q++)
				{
					arLocalImage[p][q] = ImageArray[i*FilterWindowWidth+p][j*FilterWindowWidth+q];
				}
			}
			ComputeMatrix(arLocalImage, FilterWindowWidth);
			TextureFeture(dEnergy1, dEntropy1, dInertiaQuadrature1, dCorrelation1, dLocalCalm1, PMatrixH, GrayLayerNum);
			dEnergy              += dEnergy1;
			dEntropy             += dEntropy1;
			dInertiaQuadrature   += dInertiaQuadrature1;
			dCorrelation         += dCorrelation1;
			dLocalCalm           += dLocalCalm1;
		}
	}
	dEnergy              /= (rolltimeH*rolltimeW);
	dEntropy             /= (rolltimeH*rolltimeW);
	dInertiaQuadrature   /= (rolltimeH*rolltimeW);
	dCorrelation         /= (rolltimeH*rolltimeW);
	dLocalCalm           /= (rolltimeH*rolltimeW);
	m_dEnergy			 =  dEnergy;
	m_dEntropy			 =  dEntropy;
	m_dInertiaQuadrature =  dInertiaQuadrature;
	m_dCorrelation		 =  dCorrelation;
	m_dLocalCalm		 =  dLocalCalm;
	UpdateData(FALSE);
}

BOOL CTexture::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
