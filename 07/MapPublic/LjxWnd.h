#if !defined(AFX_LJXWND_H__1C1FDC6D_E55B_4578_BC35_8F9B4B93A879__INCLUDED_)
#define AFX_LJXWND_H__1C1FDC6D_E55B_4578_BC35_8F9B4B93A879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LjxWnd.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CLjxWnd window

class CLjxWnd : public CWnd
{
// Construction
public:
	CLjxWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLjxWnd)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CDC MemDC;  //�����ڴ�DC
	BITMAP bm;  //����λͼ�ṹ����
	CBitmap m_bitmap;  //����λͼ����
    CBitmap *old_bitmap;  //����λͼ����ָ��
	void CreatLjxWnd();
	virtual ~CLjxWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLjxWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LJXWND_H__1C1FDC6D_E55B_4578_BC35_8F9B4B93A879__INCLUDED_)
