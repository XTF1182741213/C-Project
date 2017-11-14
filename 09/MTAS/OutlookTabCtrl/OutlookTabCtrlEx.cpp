//==========================================================
// Author: Borodenko Oleg
// 08/10/2007 <oktamail@gmail.com>
//==========================================================
// 
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "../resource.h"
#include "OutlookTabCtrlEx.h"
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(OutlookTabCtrlEx,OutlookTabCtrl)
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// OutlookTabCtrlEx.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(OutlookTabCtrlEx, OutlookTabCtrl)
	ON_COMMAND(ID_POPUP_OUTLOOKTABCTRL_POP, OnPop)
	ON_COMMAND(ID_POPUP_OUTLOOKTABCTRL_PUSH, OnPush)
	ON_COMMAND(ID_POPUP_OUTLOOKTABCTRL_MANAGE, OnManage)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlEx::ShowMenu(CRect const *prcButtonMenu)
{	CPoint pt(prcButtonMenu->right,prcButtonMenu->top);
	ClientToScreen(&pt);
		// 
	CNewMenu menu;
	menu.LoadMenu(IDR_POPUP_OUTLOOKTABCTRL);
	CNewMenu* pPopup = (CNewMenu*)menu.GetSubMenu(0);
		// 
	if(CanPopItem()==false)
		pPopup->EnableMenuItem(ID_POPUP_OUTLOOKTABCTRL_POP,MF_BYCOMMAND | MF_GRAYED);
	if(CanPushItem()==false)
		pPopup->EnableMenuItem(ID_POPUP_OUTLOOKTABCTRL_PUSH,MF_BYCOMMAND | MF_GRAYED);
		// 
	pPopup->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlEx::OnPop()
{	PopItem();
	Update();
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlEx::OnPush()
{	PushItem();
	Update();
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlEx::OnManage()
{	OutlookTabCtrlCmdDialog dlg(this,(vector<HTAB> *)&m_vtritems);
		// 
	if(dlg.DoModal()==IDOK)
	{	if(m_hCurItem!=NULL) ::ShowWindow(HNDLtoPTR(m_hCurItem)->hwnd,SW_HIDE);
		Update();
	}
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// OutlookTabCtrlCmdDialog.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(OutlookTabCtrlCmdDialog, CNewDialog)
	ON_BN_CLICKED(IDD_OUTLOOK_CMD_BUTTON_UP, OnBnClickedUp)
	ON_BN_CLICKED(IDD_OUTLOOK_CMD_BUTTON_DOWN, OnBnClickedDown)
	ON_BN_CLICKED(IDD_OUTLOOK_CMD_BUTTON_RESET, OnBnClickedReset)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// 
OutlookTabCtrlCmdDialog::OutlookTabCtrlCmdDialog(OutlookTabCtrlEx *pTabCtrl, vector<HTAB> *pvtrtabs) : 
	CNewDialog(IDD_OUTLOOK_CMD)
{
	m_pTabCtrl = pTabCtrl;
	m_pvtritems = pvtrtabs;
		// 
	CImageList *pImageListBig, *pImageListSmall;
	m_pTabCtrl->GetImageLists(&pImageListBig,&pImageListSmall,NULL,NULL);
	CSize szImageBig, szImageSmall;
	m_pTabCtrl->GetImageSizes(&szImageBig,&szImageSmall,NULL,NULL);
	m_ImageList.Create(szImageSmall.cy<=szImageBig.cy ? pImageListSmall : pImageListBig);
}
/////////////////////////////////////////////////////////////////////////////
// 
BOOL OutlookTabCtrlCmdDialog::OnInitDialog()
{	
	CNewDialog::OnInitDialog();

	short	shBtnColor = 30;
	m_btnUp.SetIcon(IDI_UP);
	m_btnUp.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnUp.SetRounded(TRUE);
	m_btnDown.SetIcon(IDI_DOWN);
	m_btnDown.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnDown.SetRounded(TRUE);
	m_btnReset.SetIcon(IDI_RESET);
	m_btnReset.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnReset.SetRounded(TRUE);
	m_btnOk.SetIcon(IDI_OK);
	m_btnOk.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnOk.SetRounded(TRUE);
	m_btnCancel.SetIcon(IDI_CANCEL, 15, 15);
	m_btnCancel.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnCancel.SetRounded(TRUE);
		// 
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
		// 
	CRect rc;
	pListCtrl->GetClientRect(&rc);
	pListCtrl->InsertColumn(0,"",LVCFMT_LEFT,rc.Width());
	pListCtrl->GetHeaderCtrl()->ModifyStyle(0,HDS_HIDDEN);
	pListCtrl->SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListCtrl->SetImageList(&m_ImageList,LVSIL_SMALL);
	FillList();
		// 
	return TRUE;
}


void OutlookTabCtrlCmdDialog::DoDataExchange(CDataExchange* pDX)
{
	CNewDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProperties)
	DDX_Control(pDX, IDD_OUTLOOK_CMD_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, IDD_OUTLOOK_CMD_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, IDD_OUTLOOK_CMD_BUTTON_RESET, m_btnReset);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlCmdDialog::FillList()
{	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
	pListCtrl->DeleteAllItems();
		// 
	CString text;
	int idx, imageSmall;
		// 
	for(m_i_vtritems i=m_pvtritems->begin(); i!=m_pvtritems->end(); ++i)
	{	m_pTabCtrl->GetItemText(*i,&text);
		m_pTabCtrl->GetItemImage(*i,NULL,&imageSmall);
		idx = i-m_pvtritems->begin();
		pListCtrl->InsertItem(idx,text,imageSmall);
		pListCtrl->SetItemData(idx,(DWORD)*i);
		pListCtrl->SetCheck(idx,m_pTabCtrl->IsVisible(*i)==true ? 1 : 0);
	}
	if(m_pvtritems->empty()==false)
	{	idx = m_pTabCtrl->GetIdxByHandle( m_pTabCtrl->GetSel() );
		SelectListItem(idx);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Up.
// 
void OutlookTabCtrlCmdDialog::OnBnClickedUp()
{	int src = GetSelectListItem();
	if(src==-1) return;
	int dst = src-1;
		// 
	if(dst>=0)
	{	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
			// 
		CString text;
		int imageSmall;
		HTAB hSrc = (HTAB)pListCtrl->GetItemData(src);
		m_pTabCtrl->GetItemText(hSrc,&text);
		m_pTabCtrl->GetItemImage(hSrc,NULL,&imageSmall);
		bool srcCheck = pListCtrl->GetCheck(src)!=0;
			// 
		pListCtrl->DeleteItem(src);
		pListCtrl->InsertItem(dst,text,imageSmall);
		pListCtrl->SetCheck(dst,srcCheck==true ? 1 : 0);
		pListCtrl->SetItemData(dst,(DWORD)hSrc);
		SelectListItem(dst);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Down.
// 
void OutlookTabCtrlCmdDialog::OnBnClickedDown()
{	int src = GetSelectListItem();
	if(src==-1) return;
	int dst = src+1;
		// 
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
		// 
	if(dst < pListCtrl->GetItemCount())
	{	CString text;
		int imageSmall;
		HTAB hSrc = (HTAB)pListCtrl->GetItemData(src);
		m_pTabCtrl->GetItemText(hSrc,&text);
		m_pTabCtrl->GetItemImage(hSrc,NULL,&imageSmall);
		bool srcCheck = pListCtrl->GetCheck(src)!=0;
			// 
		pListCtrl->DeleteItem(src);
		pListCtrl->InsertItem(dst,text,imageSmall);
		pListCtrl->SetCheck(dst,srcCheck==true ? 1 : 0);
		pListCtrl->SetItemData(dst,(DWORD)hSrc);
		SelectListItem(dst);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Reset.
// 
void OutlookTabCtrlCmdDialog::OnBnClickedReset()
{	FillList();
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlCmdDialog::GetSelectListItem()
{	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
		// 
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if(pos==NULL) return -1;	// there are not select items.
	return pListCtrl->GetNextSelectedItem(pos);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlCmdDialog::SelectListItem(int idx)
{	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
	pListCtrl->SetItemState(idx,LVIS_SELECTED,LVIS_SELECTED);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlCmdDialog::OnOK()
{	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDD_OUTLOOK_CMD_LIST1);
		// 
	m_pvtritems->clear();
		// 
	for(int i=0; i<pListCtrl->GetItemCount(); ++i)
	{	HTAB hItem = (HTAB)pListCtrl->GetItemData(i);
		m_pvtritems->push_back(hItem);
		m_pTabCtrl->ShowItem(hItem,pListCtrl->GetCheck(i)!=0);
	}
		// 
	CNewDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////





























