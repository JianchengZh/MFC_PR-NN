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
	
//灰度再现共生矩阵
public:
	void ComputeMatrix(BYTE** LocalImage, int LocalImageWidth);
	void TextureFeture(double& FeatureEnergy, double& FeatureEntropy, double& FeatureInertiaQuadrature, double& FeatureCorrelation, double& FeatureLocalCalm, int** pMatrix, int dim);
	//变量
//	CDib* m_dib;
	double FeatureLocalCalmRD;	//局部平稳性－45度方向
	double FeatureLocalCalmLD;	//局部平稳性－135度方向
	double FeatureLocalCalmV;	//局部平稳性－90度方向度方向
	double FeatureLocalCalmH;	//局部平稳性－0度方向
	double FeatureCorrelationRD;	//相关性－45度方向
	double FeatureCorrelationLD;	//相关性－135度方向
	double FeatureCorrelationV;		//相关性－90度方向
	double FeatureCorrelationH;		//相关性－0度方向
	double FeatureInertiaQuadratureRD;	//惯性矩－45度方向
	double FeatureInertiaQuadratureLD;	//惯性矩－135度方向
	double FeatureInertiaQuadratureV;	//惯性矩－90度方向
	double FeatureInertiaQuadratureH;	//惯性矩－0度方向
	double FeatureEntropyRD;	//熵－45度方向
	double FeatureEntropyLD;	//熵－135度方向
	double FeatureEntropyV;		//熵－90度方向
	double FeatureEntropyH;		//熵－0度方向
	double FeatureEnergyRD;		//能量－45度方向
	double FeatureEnergyLD;		//能量－135度方向
	double FeatureEnergyV;		//能量－90度方向
	double FeatureEnergyH;		//能量－0度方向
	int FilterWindowWidth;	//纹理区域块的大小，通常将图像划分成若干个纹理块计算
	long ImageHeight;	//原图像的高度
	long ImageWidth;		//原图像的宽度
	int distance;	//距离，依据不同的应用选取	
	int GrayLayerNum;	//灰度分级
	int** PMatrixRD;	//45度方向上的灰度共现矩阵
	int** PMatrixLD;	//135度方向上的灰度共现矩阵
	int** PMatrixV;		//90度方向上的灰度共现矩阵
	int** PMatrixH;		//0度方向上的灰度共现矩阵
	BYTE** ImageArray;	//原始的图像数据数组－灰度
	
	RGBQUAD** m_tOriPixelArray;//原始位图数据
	RGBQUAD** m_tResPixelArray;//参考位图数据
	
	void LoadImage(CDib* p_dib);

//自相关函数




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
