// NN.h : main header file for the NN application
//

#if !defined(AFX_NN_H__3F98DE99_1C4D_4FFF_A63D_618519DE639F__INCLUDED_)
#define AFX_NN_H__3F98DE99_1C4D_4FFF_A63D_618519DE639F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNNApp:
// See NN.cpp for the implementation of this class
//

class CNNApp : public CWinApp
{
public:
	CNNApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNNApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNNApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NN_H__3F98DE99_1C4D_4FFF_A63D_618519DE639F__INCLUDED_)
