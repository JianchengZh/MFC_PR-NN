; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFuzzy
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Pattern Recognation.h"
LastPage=0

ClassCount=11
Class1=CPatternRecognationApp
Class2=CPatternRecognationDoc
Class3=CPatternRecognationView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_DIALOG_CLUSTER
Resource2=IDD_DIALOG_LINEAR_FISHER
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_DIALOG_NONLINEAR
Class7=CTexture
Resource4=IDD_ABOUTBOX
Class8=CLinearFisher
Resource5=IDR_MAINFRAME
Class9=CNonlinear
Resource6=IDR_PATTERTYPE
Class10=CClusterAnalysis
Resource7=IDD_DIALOG_TEXTURE_GRAYSHOW
Class11=CFuzzy
Resource8=IDD_DIALOG_FUZZY

[CLS:CPatternRecognationApp]
Type=0
HeaderFile=Pattern Recognation.h
ImplementationFile=Pattern Recognation.cpp
Filter=N
LastObject=CPatternRecognationApp

[CLS:CPatternRecognationDoc]
Type=0
HeaderFile=Pattern RecognationDoc.h
ImplementationFile=Pattern RecognationDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPatternRecognationDoc

[CLS:CPatternRecognationView]
Type=0
HeaderFile=Pattern RecognationView.h
ImplementationFile=Pattern RecognationView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CPatternRecognationView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=Pattern Recognation.cpp
ImplementationFile=Pattern Recognation.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_PATTERTYPE]
Type=1
Class=CPatternRecognationView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_FEATUREEXTRACT_TEXTURE
Command12=ID_LINEAR_FISHER_DISCRIMINTIVE
Command13=ID_NONLINEAR
Command14=ID_CLUSTER_ANALYSIS
Command15=ID_FUZZY_CLUSTER_C_MEANS
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CTexture]
Type=0
HeaderFile=Texture.h
ImplementationFile=Texture.cpp
BaseClass=CDialog
Filter=D
LastObject=CTexture
VirtualFilter=dWC

[DLG:IDD_DIALOG_TEXTURE_GRAYSHOW]
Type=1
Class=CTexture
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_ENERGY,edit,1350631552
Control9=IDC_EDIT_ENTROPY,edit,1350631552
Control10=IDC_EDIT_INERTIA_QUADRATURE,edit,1350631552
Control11=IDC_EDIT_LOCAL_CALM,edit,1350631552
Control12=IDC_EDIT_CORRELATION,edit,1350631552

[DLG:IDD_DIALOG_LINEAR_FISHER]
Type=1
Class=CLinearFisher
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_PERCEPTRON,button,1342242816
Control4=IDC_BUTTON_FISHER,button,1342242816
Control5=IDC_COORD1,static,1342177287

[CLS:CLinearFisher]
Type=0
HeaderFile=LinearFisher.h
ImplementationFile=LinearFisher.cpp
BaseClass=CDialog
Filter=D
LastObject=CLinearFisher
VirtualFilter=dWC

[DLG:IDD_DIALOG_NONLINEAR]
Type=1
Class=CNonlinear
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_NEAREST,button,1342242816
Control4=IDC_BUTTON_K_NEAREST,button,1342242816
Control5=IDC_CORAD_NON,static,1342177287

[CLS:CNonlinear]
Type=0
HeaderFile=Nonlinear.h
ImplementationFile=Nonlinear.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNonlinear

[DLG:IDD_DIALOG_CLUSTER]
Type=1
Class=CClusterAnalysis
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_C_MEANS,button,1342242816
Control4=IDC_BUTTON_ISODATA,button,1342242816
Control5=IDC_DRAW_CLUSTER,static,1342177287
Control6=IDC_EDIT_I,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_ERRORX_ADD,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_k,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_thetaN,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_thetaS,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT_thetaD,edit,1350631552
Control18=IDC_EDIT_C,edit,1350631552
Control19=IDC_STATIC,static,1342308352

[CLS:CClusterAnalysis]
Type=0
HeaderFile=ClusterAnalysis.h
ImplementationFile=ClusterAnalysis.cpp
BaseClass=CDialog
Filter=D
LastObject=CClusterAnalysis
VirtualFilter=dWC

[DLG:IDD_DIALOG_FUZZY]
Type=1
Class=CFuzzy
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_Cval,edit,1350631552
Control5=IDC_DRAW_FUZZY,static,1342177287

[CLS:CFuzzy]
Type=0
HeaderFile=Fuzzy.h
ImplementationFile=Fuzzy.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

