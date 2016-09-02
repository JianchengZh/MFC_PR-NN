#if !defined(AFX_TEXTURE_H__9B4BCDE7_FCA3_4F6F_992B_BCE02535F47F__INCLUDED_)
#define AFX_TEXTURE_H__9B4BCDE7_FCA3_4F6F_992B_BCE02535F47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Texture.h : header file
//
#include "Dib.h"
/////////////////////////////////////////////////////////////////////////////
// CTexture dialog

class CTexture : public CDialog
{
// Construction
public:
	CTexture(CWnd* pParent = NULL);   // standard constructor
	
//�Ҷ����ֹ�������
public:
	void ComputeMatrix(BYTE** LocalImage, int LocalImageWidth);
	void TextureFeture(double& FeatureEnergy, double& FeatureEntropy, double& FeatureInertiaQuadrature, double& FeatureCorrelation, double& FeatureLocalCalm, int** pMatrix, int dim);
	//����
//	CDib* m_dib;
	double FeatureLocalCalmRD;	//�ֲ�ƽ���ԣ�45�ȷ���
	double FeatureLocalCalmLD;	//�ֲ�ƽ���ԣ�135�ȷ���
	double FeatureLocalCalmV;	//�ֲ�ƽ���ԣ�90�ȷ���ȷ���
	double FeatureLocalCalmH;	//�ֲ�ƽ���ԣ�0�ȷ���
	double FeatureCorrelationRD;	//����ԣ�45�ȷ���
	double FeatureCorrelationLD;	//����ԣ�135�ȷ���
	double FeatureCorrelationV;		//����ԣ�90�ȷ���
	double FeatureCorrelationH;		//����ԣ�0�ȷ���
	double FeatureInertiaQuadratureRD;	//���Ծأ�45�ȷ���
	double FeatureInertiaQuadratureLD;	//���Ծأ�135�ȷ���
	double FeatureInertiaQuadratureV;	//���Ծأ�90�ȷ���
	double FeatureInertiaQuadratureH;	//���Ծأ�0�ȷ���
	double FeatureEntropyRD;	//�أ�45�ȷ���
	double FeatureEntropyLD;	//�أ�135�ȷ���
	double FeatureEntropyV;		//�أ�90�ȷ���
	double FeatureEntropyH;		//�أ�0�ȷ���
	double FeatureEnergyRD;		//������45�ȷ���
	double FeatureEnergyLD;		//������135�ȷ���
	double FeatureEnergyV;		//������90�ȷ���
	double FeatureEnergyH;		//������0�ȷ���
	int FilterWindowWidth;	//���������Ĵ�С��ͨ����ͼ�񻮷ֳ����ɸ���������
	long ImageHeight;	//ԭͼ��ĸ߶�
	long ImageWidth;		//ԭͼ��Ŀ��
	int distance;	//���룬���ݲ�ͬ��Ӧ��ѡȡ	
	int GrayLayerNum;	//�Ҷȷּ�
	int** PMatrixRD;	//45�ȷ����ϵĻҶȹ��־���
	int** PMatrixLD;	//135�ȷ����ϵĻҶȹ��־���
	int** PMatrixV;		//90�ȷ����ϵĻҶȹ��־���
	int** PMatrixH;		//0�ȷ����ϵĻҶȹ��־���
	BYTE** ImageArray;	//ԭʼ��ͼ���������飭�Ҷ�
	
	RGBQUAD** m_tOriPixelArray;//ԭʼλͼ����
	RGBQUAD** m_tResPixelArray;//�ο�λͼ����
	
	void LoadImage(CDib* p_dib);

//����غ���




// Dialog Data
	//{{AFX_DATA(CTexture)
	enum { IDD = IDD_DIALOG_TEXTURE_GRAYSHOW };
	double	m_dCorrelation;
	double	m_dEnergy;
	double	m_dEntropy;
	double	m_dInertiaQuadrature;
	double	m_dLocalCalm;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTexture)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CTexture)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTURE_H__9B4BCDE7_FCA3_4F6F_992B_BCE02535F47F__INCLUDED_)
