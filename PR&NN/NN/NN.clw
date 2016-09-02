; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBP_match
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NN.h"
LastPage=0

ClassCount=9
Class1=CNNApp
Class2=CNNDoc
Class3=CNNView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_DIALOG_XOR
Resource2=IDR_NNTYPE
Resource3=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Class7=CPerceptron
Resource4=IDD_DIALOG_BPNN
Class8=CBP_match
Resource5=IDR_MAINFRAME
Class9=CHOPFIELD
Resource6=IDD_DIALOG_HOPFIELD

[CLS:CNNApp]
Type=0
HeaderFile=NN.h
ImplementationFile=NN.cpp
Filter=N

[CLS:CNNDoc]
Type=0
HeaderFile=NNDoc.h
ImplementationFile=NNDoc.cpp
Filter=N

[CLS:CNNView]
Type=0
HeaderFile=NNView.h
ImplementationFile=NNView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_ASSOCIATE_MEMORY


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=NN.cpp
ImplementationFile=NN.cpp
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

[MNU:IDR_NNTYPE]
Type=1
Class=CNNView
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
Command11=ID_XOR
Command12=ID_NONLINEAR
Command13=ID_AUTO_CLUSTER
Command14=ID_ASSOCIATE_MEMORY
CommandCount=14

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

[DLG:IDD_DIALOG_XOR]
Type=1
Class=CPerceptron
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_X,edit,1350631552
Control4=IDC_EDIT_Y,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_RESULT,edit,1350631552

[CLS:CPerceptron]
Type=0
HeaderFile=Perceptron.h
ImplementationFile=Perceptron.cpp
BaseClass=CDialog
Filter=D
LastObject=CPerceptron
VirtualFilter=dWC

[DLG:IDD_DIALOG_BPNN]
Type=1
Class=CBP_match
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DRAW,static,1342177287
Control4=IDC_BUTTON_INITIAL,button,1342242816
Control5=IDC_EDIT_ITER,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_ERROR,edit,1350631552

[CLS:CBP_match]
Type=0
HeaderFile=BP_match.h
ImplementationFile=BP_match.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_INITIAL
VirtualFilter=dWC

[DLG:IDD_DIALOG_HOPFIELD]
Type=1
Class=CHOPFIELD
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_TRAIN00,edit,1350631552
Control4=IDC_EDIT_TRAIN01,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_TEST0,edit,1350631552
Control7=IDC_EDIT_TEST1,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_MEMORY,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_EDIT_TRAIN02,edit,1350631552
Control14=IDC_EDIT_TRAIN10,edit,1350631552
Control15=IDC_EDIT_TRAIN11,edit,1350631552
Control16=IDC_EDIT_TRAIN12,edit,1350631552
Control17=IDC_EDIT_TRAIN20,edit,1350631552
Control18=IDC_EDIT_TRAIN21,edit,1350631552
Control19=IDC_EDIT_TRAIN22,edit,1350631552
Control20=IDC_EDIT_TEST2,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDIT_RESULT0,edit,1350631552
Control23=IDC_EDIT_RESULT1,edit,1350631552
Control24=IDC_EDIT_RESULT2,edit,1350631552

[CLS:CHOPFIELD]
Type=0
HeaderFile=HOPFIELD.h
ImplementationFile=HOPFIELD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHOPFIELD

