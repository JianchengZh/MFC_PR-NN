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
	CDib();//���캯��
	CDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);//�������Ĺ��캯��
	virtual ~CDib();	//��������
//��Ա����
public:	
	unsigned char * m_pImgData; 				//ͼ������ָ��
	LPRGBQUAD m_lpColorTable; 				//ͼ����ɫ��ָ��
	int m_nBitCount;						//ÿ����ռ��λ��
private:
	LPBYTE m_lpDib;						//ָ��DIB��ָ��
	HPALETTE m_hPalette;					//�߼���ɫ����
	int m_nColorTableLength; 					//��ɫ���ȣ����ٸ����
public:
	int m_imgWidth;							//ͼ��Ŀ�����Ϊ��λ
	int m_imgHeight; 						//ͼ��ĸߣ�����Ϊ��λ
	LPBITMAPINFOHEADER m_lpBmpInfoHead; 	//ͼ����Ϣͷָ��
	//��Ա����
public:          					
	BOOL Read(LPCTSTR lpszPathName); 		//DIB������
	BOOL Write(LPCTSTR lpszPathName);       //DIBд����
	int ComputeColorTabalLength(int nBitCount);	//������ɫ��ĳ���
	BOOL Draw(CDC* pDC, CPoint origin, CSize size); //ͼ�����
	CSize GetDimensions();					//��ȡͼ��ά��
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);              	//���µ������滻DIB
private:
	void MakePalette();						//�����߼���ɫ��
	void Empty();                         	//����ռ�

};

#endif // !defined(AFX_DIB_H__67EF903D_15C2_463A_9588_70C20ABA32FD__INCLUDED_)
