#if !defined(AFX_NEWLISTCTRL_H__B5AA6D6D_9AA5_4CAF_BA54_3DF8275128B1__INCLUDED_)
#define AFX_NEWLISTCTRL_H__B5AA6D6D_9AA5_4CAF_BA54_3DF8275128B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// newListCtrl.h : header file
//
#include "MapPublic.h"
/////////////////////////////////////////////////////////////////////////////
// CnewListCtrl window

class CnewListCtrl : public CListCtrl
{
// Construction
public:
	CnewListCtrl();

// Attributes
public:

	CEdit m_edit;//�༭��ؼ�
   int m_nitem,m_nsubitem,m_nitem1,m_nsubitem1;
//m_nitem,m_nsubitemΪ������к����к�,m_nitem1,m_nsubitem1Ϊǰһ�����к����к�
    void Edit();//�Զ���ı༭����
    void EndEdit();//�Զ���Ľ����༭����

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CnewListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CnewListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CnewListCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWLISTCTRL_H__B5AA6D6D_9AA5_4CAF_BA54_3DF8275128B1__INCLUDED_)
