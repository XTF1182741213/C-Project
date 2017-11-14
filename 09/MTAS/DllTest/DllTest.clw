; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=OutlookCtrl
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DllTest.h"
LastPage=0

ClassCount=10
Class1=CDllTestApp
Class2=CDllTestDoc
Class3=CDllTestView
Class4=CMainFrame
Class9=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class10=OutlookCtrl

[CLS:CDllTestApp]
Type=0
HeaderFile=DllTest.h
ImplementationFile=DllTest.cpp
Filter=N

[CLS:CDllTestDoc]
Type=0
HeaderFile=DllTestDoc.h
ImplementationFile=DllTestDoc.cpp
Filter=N

[CLS:CDllTestView]
Type=0
HeaderFile=DllTestView.h
ImplementationFile=DllTestView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DllTest.cpp
ImplementationFile=DllTest.cpp
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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:OutlookCtrl]
Type=0
HeaderFile=OutlookCtrl.h
ImplementationFile=OutlookCtrl.cpp
BaseClass=generic CWnd
Filter=W
