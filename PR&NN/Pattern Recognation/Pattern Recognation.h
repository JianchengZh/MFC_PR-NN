// Pattern Recognation.h : main header file for the PATTERN RECOGNATION application
//

#if !defined(AFX_PATTERNRECOGNATION_H__3A759799_0795_4B9D_93D7_C31B84E627D6__INCLUDED_)
#define AFX_PATTERNRECOGNATION_H__3A759799_0795_4B9D_93D7_C31B84E627D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPatternRecognationApp:
// See Pattern Recognation.cpp for the implementation of this class
//

class CPatternRecognationApp : public CWinApp
{
public:
	CPatternRecognationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternRecognationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPatternRecognationApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNRECOGNATION_H__3A759799_0795_4B9D_93D7_C31B84E627D6__INCLUDED_)
