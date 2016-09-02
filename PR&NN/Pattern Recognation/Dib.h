// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__67EF903D_15C2_463A_9588_70C20ABA32FD__INCLUDED_)
#define AFX_DIB_H__67EF903D_15C2_463A_9588_70C20ABA32FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <vfw.h>
//#pragma comment(lib,"vfw32.lib")

class CDib 
{
public:
	CDib();//构造函数
	CDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);//带参数的构造函数
	virtual ~CDib();	//析构函数
//成员变量
public:	
	unsigned char * m_pImgData; 				//图像数据指针
	LPRGBQUAD m_lpColorTable; 				//图像颜色表指针
	int m_nBitCount;						//每像素占的位数
private:
	LPBYTE m_lpDib;						//指向DIB的指针
	HPALETTE m_hPalette;					//逻辑调色板句柄
	int m_nColorTableLength; 					//颜色表长度（多少个表项）
public:
	int m_imgWidth;							//图像的宽，像素为单位
	int m_imgHeight; 						//图像的高，像素为单位
	LPBITMAPINFOHEADER m_lpBmpInfoHead; 	//图像信息头指针
	//成员函数
public:          					
	BOOL Read(LPCTSTR lpszPathName); 		//DIB读函数
	BOOL Write(LPCTSTR lpszPathName);       //DIB写函数
	int ComputeColorTabalLength(int nBitCount);	//计算颜色表的长度
	BOOL Draw(CDC* pDC, CPoint origin, CSize size); //图像绘制
	CSize GetDimensions();					//读取图像维数
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);              	//用新的数据替换DIB
private:
	void MakePalette();						//创建逻辑调色板
	void Empty();                         	//清理空间

};

#endif // !defined(AFX_DIB_H__67EF903D_15C2_463A_9588_70C20ABA32FD__INCLUDED_)
