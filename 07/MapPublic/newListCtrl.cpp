// newListCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "newListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CnewListCtrl

CnewListCtrl::CnewListCtrl()
{
	m_nitem=-1;
	m_nsubitem=-1;
	m_nitem1=-1;
	m_nsubitem1=-1;
}

CnewListCtrl::~CnewListCtrl()
{
}


BEGIN_MESSAGE_MAP(CnewListCtrl, CListCtrl)
//{{AFX_MSG_MAP(CnewListCtrl)
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CnewListCtrl message handlers
void CnewListCtrl::Edit()
{
	CRect rect;
	if(GetSubItemRect(m_nitem,m_nsubitem,LVIR_LABEL,rect)==FALSE)
		return;
	int sty=WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER;
	//���ñ༭����ʽ
	if(m_edit.Create(sty,rect,this,ID_MYEDIT)==FALSE)
		//�����༭��
		return;
	CString txt=GetItemText(m_nitem,m_nsubitem);
	m_edit.SetWindowText(txt);//���ñ༭�������
	m_edit.SetFocus();
	m_edit.SetSel(0,-1);
	m_edit.ShowWindow(SW_SHOW);//��ʾ�༭��
	m_nitem1=m_nitem;
	m_nsubitem1=m_nsubitem;

	
}
void CnewListCtrl::EndEdit()
{
	if(m_nitem1!=-1&&m_nsubitem1!=-1)//�ж��Ƿ�Ϊ��ʼʱ
	{
		CString txt;
		m_edit.GetWindowText(txt);
		SetItemText(m_nitem1,m_nsubitem1,txt);//����Ϊ�༭����ļ�����
		m_edit.DestroyWindow();
	}
}

void CnewListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LVHITTESTINFO testinfo;
	testinfo.pt.x=point.x;
	testinfo.pt.y=point.y;
	testinfo.flags=LVHT_ONITEMLABEL;//ǿ��������Ǳ���
	if(SubItemHitTest(&testinfo)<0)
		return;
	m_nitem=testinfo.iItem;//�õ��к�
	m_nsubitem=testinfo.iSubItem;//�õ��к�
	if(m_nitem==m_nitem1&&m_nsubitem==m_nsubitem1)//�ж��Ƿ���ǰһ���������
		return;
	else
	{
		EndEdit();//�����༭��
		Edit();//�����µı༭����б����б༭
		
		// TODO: Add your message handler code here and/or call default
	}
		CListCtrl::OnLButtonDown(nFlags, point);
	}
