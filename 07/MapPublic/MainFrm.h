// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CB16C593_E78F_4832_994E_586352FCE74C__INCLUDED_)
#define AFX_MAINFRM_H__CB16C593_E78F_4832_994E_586352FCE74C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HawkSightView.h"
#include "MapControlView.h"
#include "Attribute.h"
#include "MapPublicView.h"
#include ".\\clock\\EDCLOCK.H"//�������ϵ�ʱ��
#include "CoolMenu.h"

#include "ShowEndDlg.h"
class CMyToolBar : public CToolBar
{
public:
	CEdit m_EditBox;
	CStatic m_staticlock;
	
};  


	
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;

	CMyToolBar m_wndToolBar;

// Operations
public:
    CStatusBar  m_wndStatusBar;
    CReBar		m_wndReBar;      //Rebar��
	CLEDClock   m_clock;         //ʱ�Ӷ���
	void AddMenu();
	CCoolMenu       m_CoolMenu;//�˵�
	COLORREF m_color;//���ĸ��Ĳ˵���ɫ
	BOOL PlayResource(WORD wResourceID);//�������
	CShowEndDlg m_dlg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMainFrame();
	virtual ~CMainFrame();
		int CreateMyEditBox();//�����༭��
 
//	CEdit m_EditBox;
//	CToolBar    m_wndToolBar;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	
	
    CToolBar    m_featureToolBar; // ���ڿ�����ʾ�������͵Ĺ�����

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSkin();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CB16C593_E78F_4832_994E_586352FCE74C__INCLUDED_)
