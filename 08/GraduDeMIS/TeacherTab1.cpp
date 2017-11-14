// TeacherTab1.cpp : implementation file
#include "stdafx.h"
#include "gradudemis.h"
#include "TeacherTab1.h"
#include "PreParent.h"		//��ӡԤ��������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTeacherTab1 dialog
CTeacherTab1::CTeacherTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CTeacherTab1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTeacherTab1)
	m_tecr_edit = _T("");
	//}}AFX_DATA_INIT
}
void CTeacherTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTeacherTab1)
	DDX_Control(pDX, IDC_TEACHER_EDIT, m_tecr_editctrl);
	DDX_Control(pDX, IDC_TEACHER_COMBO, m_tecr_combo);
	DDX_Control(pDX, IDC_TEACHER_LIST, m_tecr_listctrl);
	DDX_Text(pDX, IDC_TEACHER_EDIT, m_tecr_edit);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CTeacherTab1, CDialog)
	//{{AFX_MSG_MAP(CTeacherTab1)
	ON_BN_CLICKED(IDC_TEACHER_BTN, OnTeacherBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_TEACHER_LIST, OnItemchangedTeacherList)
	ON_BN_CLICKED(IDC_PRINTTEST, OnPrinttest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTeacherTab1 message handlers

BOOL CTeacherTab1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pSet1.Open();											//�򿪼�¼��
	m_tecr_listctrl.InsertColumn(0,"����",LVCFMT_LEFT,60,0);//�����б��⣬�趨��ȣ����뷽ʽ
	m_tecr_listctrl.InsertColumn(1,"�Ա�",LVCFMT_LEFT,40,0);
	m_tecr_listctrl.InsertColumn(2,"����",LVCFMT_LEFT,40,0);
	m_tecr_listctrl.InsertColumn(3,"������",LVCFMT_LEFT,80,0);
	m_tecr_listctrl.InsertColumn(4,"ְ��",LVCFMT_LEFT,60,0);
	m_tecr_listctrl.InsertColumn(5,"��ϵ��ʽ",LVCFMT_LEFT,100,0);

    m_tecr_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
															//�趨�������ѡ������
	int i=0;												//�������α���
	while(!pSet1.IsEOF())									//�����¼�������һ��
	{
		m_tecr_listctrl.InsertItem(i,pSet1.m_tecr_name);	//���б�ؼ��в�������
		m_tecr_listctrl.SetItemText(i,1,pSet1.m_tecr_sex);
		m_tecr_listctrl.SetItemText(i,2,pSet1.m_tecr_age);
		m_tecr_listctrl.SetItemText(i,3,pSet1.m_tecr_TRroom);
		m_tecr_listctrl.SetItemText(i,4,pSet1.m_tecr_level);		
		m_tecr_listctrl.SetItemText(i,5,pSet1.m_tecr_asoci);
        pSet1.MoveNext();									//�ƶ���������¼
        i++;
	}
	pSet1.Close();											//�رռ�¼��
//��Ͽ�
	CString str[6]={"����","�Ա�","����","������","ְ��"};	//�����ַ������鸳��ֵ
	for(int j=0;j<5;j++)
		m_tecr_combo.InsertString(j,str[j]);				//�������ݵ������б����
    m_tecr_combo.SetCurSel(0);								//Ĭ��ѡ�е�һ��
		UpdateData(false);									//��������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CTeacherTab1::OnTeacherBtn() 
{
	// TODO: Add your control notification handler code here
	int nIndex=m_tecr_combo.GetCurSel();					//��ȡ�û�ѡ����������
	switch(nIndex)
	{ 
	   case 0:
		   SelectItem(0);  break;							//�����Զ��庯��  
	   case 1:
		   SelectItem(1);  break; 
	   case 2:
		   SelectItem(2);  break;		   
	   case 3:
		   SelectItem(3);  break; 
	   case 4:
		   SelectItem(4);  break;		   
	   case 5:
		   SelectItem(5);  break; 
	};
}

//��ʦ��Ϣ��ѯ
void CTeacherTab1::SelectItem(int n)
{
	char filter[60];												//�����ַ�����
	CString str[5]={"tab_tecr.tecr_name='%s'","tab_tecr.tecr_sex='%s'",
		"tab_tecr.tecr_age='%s'","tab_tecr.tecr_TRroom='%s'","tab_tecr.tecr_level='%s'"};
	CString strEdit;												//�����ַ�������
    UpdateData();													//��������
	pSet1.Open();													//�򿪼�¼��
	wsprintf(filter,str[n],m_tecr_edit);							//��ʽ��
	pSet1.m_strFilter=filter;										//��¼��ֵ
	pSet1.Requery();												//ˢ�¼�¼��
    m_tecr_editctrl.GetWindowText(strEdit);							//��ȡ�ؼ����ı�
	if(strEdit=="")
	{
		MessageBox("��ѯ����Ϊ�գ�������ؼ��ʣ�");					//��Ϣ��ʾ
		pSet1.Close();												//�رռ�¼��
		return;
	}
	else 
	{	
		if(pSet1.IsEOF())											//��¼�Ѿ���ĩβ
			AfxMessageBox("Ҫ���ҵļ�¼�����ڣ�");
		else
		{
		  m_tecr_listctrl.DeleteAllItems();							//ɾ����������
		  int i=0;													//�������α���
		  while(!pSet1.IsEOF())										//�����¼û�е�ĩβ
		  {
			m_tecr_listctrl.InsertItem(i,pSet1.m_tecr_name);		//�������ݵ��б�ؼ���
			m_tecr_listctrl.SetItemText(i,1,pSet1.m_tecr_sex);
			m_tecr_listctrl.SetItemText(i,2,pSet1.m_tecr_age);
			m_tecr_listctrl.SetItemText(i,3,pSet1.m_tecr_TRroom);
			m_tecr_listctrl.SetItemText(i,4,pSet1.m_tecr_level);
			m_tecr_listctrl.SetItemText(i,5,pSet1.m_tecr_asoci);
			pSet1.MoveNext();										//�ƶ���������¼
			i++;
		  }
		 UpdateData(false);											//��������
		}
	   pSet1.Close();												//�رռ�¼��
	}
}

void CTeacherTab1::OnItemchangedTeacherList(NMHDR* pNMHDR, LRESULT* pResult) 
{

	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i=pNMListView->iItem;					//��ȡѡ�е��к�
	selectID=m_tecr_listctrl.GetItemText(i,0);	//��ȡѡ���еĵ�һ�е��ı�
	*pResult = 0;
}

//һ���Ǵ�ӡԤ��
void CTeacherTab1::OnPrinttest() 
{
    if(m_tecr_listctrl.GetItemCount()<= 0)
		return;
	PRNINFO PrnInfo = {0};
	PrnInfo.hListView = m_tecr_listctrl.m_hWnd;
	PrnInfo.hWnd = this->m_hWnd;
	PrnInfo.IsPrint = FALSE;
	PrnInfo.nCurPage = 1;
	PrnInfo.nMaxLine = m_tecr_listctrl.GetItemCount();
	
	CPreParent DlgPreView;
	DlgPreView.SetCallBackFun(DrawInfo, PrnInfo);
	DlgPreView.DoModal();

}
void CTeacherTab1::DrawInfo(CDC &memDC, PRNINFO PrnInfo)
{

	if(memDC.m_hDC == NULL)
		return;

	int nCurPage = PrnInfo.nCurPage;	//��ǰҳ
	BOOL IsPrint = PrnInfo.IsPrint;		//�Ƿ��ӡ
	int nMaxPage = PrnInfo.nCountPage;	//���ҳ��
	HWND hWnd = PrnInfo.hWnd;
	HWND hList = PrnInfo.hListView;
	CString csLFinality, csRFinality;
	CTime time;
	time=CTime::GetCurrentTime();
	csLFinality = time.Format("��������:%Y-%m-%d");
	csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);

	TCHAR szTitle[] = TEXT("��ʦ��Ϣ��");
	

	CRect rc, rt1, rt2, rt3, rt4, rt5, rt6;
	CPen *hPenOld;
	CPen		cPen;
	CFont TitleFont, DetailFont, *oldfont;
	//��������
	TitleFont.CreateFont(-MulDiv(14,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//ϸ������
	DetailFont.CreateFont(-MulDiv(10,memDC.GetDeviceCaps(LOGPIXELSY),72),
		0,0,0,FW_NORMAL,0,0,0,GB2312_CHARSET,
		OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,
		VARIABLE_PITCH|FF_SWISS,_T("����"));
	//�ֱ�
	cPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

 	int xP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSX);	//x����ÿӢ�����ص���
	int yP = GetDeviceCaps(memDC.m_hDC, LOGPIXELSY);	//y����ÿӢ�����ص���

	DOUBLE xPix = (DOUBLE)xP*10/254;	//ÿ mm ��ȵ�����
	DOUBLE yPix = (DOUBLE)yP*10/254;	//ÿ mm �߶ȵ�����
	DOUBLE fAdd = 7*yPix;		//ÿ�������
	DOUBLE nTop = 25*yPix;		//��һҳ������
	int	  iStart = 0;			//�ӵڼ��п�ʼ��ȡ
	DOUBLE nBottom = nTop+B5_ONELINE*fAdd;
	if(nCurPage != 1)
		nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
	if(nCurPage == 2)
		iStart = B5_ONELINE;
	if(nCurPage>2)
		iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;

	DOUBLE nLeft = 20*xPix;			//������
	DOUBLE nRight = xPix*(B5_W-20);	//������



	DOUBLE nTextAdd = 1.5*xPix;
	if(IsPrint)
	{
		//������ӡ����
		static DOCINFO di = {sizeof (DOCINFO),  szTitle} ;
		//��ʼ�ĵ���ӡ
		if(memDC.StartDoc(&di)<0)
		{
			::MessageBox(hWnd, "���ӵ���ӡ������!", "����", MB_ICONSTOP);
		}
		else
		{
			iStart = 0;
			nTop = 25*yPix;		//��һҳ������
			for(int iTotalPages = 1; iTotalPages<=nMaxPage; iTotalPages++)
			{
				int nCurPage = iTotalPages;
				csRFinality.Format("�� %i ҳ/�� %i ҳ", nCurPage, nMaxPage);
				time=CTime::GetCurrentTime();
				csLFinality = time.Format("��������:%Y-%m-%d");

				if(nCurPage != 1)
					nTop = 25*yPix-fAdd;	//�ǵ�һҳ������
				if(nCurPage == 2)
					iStart = B5_ONELINE;
				if(nCurPage>2)
					iStart = B5_ONELINE+(nCurPage - 2)*B5_OTHERLINE;
				//��ʼҳ
				if(memDC.StartPage() < 0)
				{
					::MessageBox(hWnd, _T("��ӡʧ��!"), "����", MB_ICONSTOP);
					memDC.AbortDoc();
					return;
				}
				else
				{
					//��ӡ
					//����
					/*
					oldfont = memDC.SelectObject(&TitleFont);
					int nItem = B5_OTHERLINE;
					if(nCurPage == 1)
					{
						nItem = B5_ONELINE;
						rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
						memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					//ϸ��
 					memDC.SelectObject(&DetailFont);
					rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
					//�Ϻ���
					memDC.MoveTo(rc.left, rc.top);
					memDC.LineTo(rc.right, rc.top);

					rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					//ѧ��
					rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	//����
					rt3.SetRect(rt2.right, rt1.top, rt2.right + 10*xPix, rt1.bottom);	//�Ա�
					rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	//רҵ
					rt5.SetRect(rt4.right, rt1.top, rt4.right + 25*xPix, rt1.bottom);	//�꼶
					rt6.SetRect(rt5.right, rt1.top, rc.right, rt1.bottom);				//�༶
					memDC.DrawText("ѧ ��", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("�� ��", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("�Ա�", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("ר ҵ", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("�� ��", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText("�� ��", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					memDC.MoveTo(rt1.right, rt1.top);
					memDC.LineTo(rt1.right, rt1.bottom);
					memDC.MoveTo(rt2.right, rt1.top);
					memDC.LineTo(rt2.right, rt1.bottom);
					memDC.MoveTo(rt3.right, rt1.top);
					memDC.LineTo(rt3.right, rt1.bottom);
					memDC.MoveTo(rt4.right, rt1.top);
					memDC.LineTo(rt4.right, rt1.bottom);
					memDC.MoveTo(rt5.right, rt1.top);
					memDC.LineTo(rt5.right, rt1.bottom);
//					memDC.MoveTo(rt6.right, rt1.top);
//					memDC.LineTo(rt6.right, rt1.bottom);
					memDC.MoveTo(rc.left, rt1.bottom);
					memDC.LineTo(rc.right, rt1.bottom);

					TCHAR szID[32]={0}, szName[16]={0}, szSex[8]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0};
					rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
					rt1.SetRect(nLeft+nTextAdd, rc.top, nLeft+20*xPix, rc.bottom);				//ѧ��
					rt2.SetRect(rt1.right+nTextAdd, rt1.top, rt1.right + 25*xPix, rt1.bottom);	//����
					rt3.SetRect(rt2.right+nTextAdd, rt1.top, rt2.right + 10*xPix, rt1.bottom);	//�Ա�
					rt4.SetRect(rt3.right+nTextAdd, rt1.top, rt3.right + 25*xPix, rt1.bottom);	//רҵ
					rt5.SetRect(rt4.right+nTextAdd, rt1.top, rt4.right + 25*xPix, rt1.bottom);	//�꼶
					rt6.SetRect(rt5.right+nTextAdd, rt1.top, rc.right, rt1.bottom);				//�༶

					int nCountItem = ListView_GetItemCount(hList);
					for(int i=0;i<nItem; i++)
					{
						ListView_GetItemText(hList, i+iStart, 0, szID, 32);
						ListView_GetItemText(hList, i+iStart, 1, szName, 16);
						ListView_GetItemText(hList, i+iStart, 2, szSex, 8);
						ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
						ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
						ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
						
						memDC.DrawText(szID, &rt1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szName, &rt2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szSex, &rt3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szZY, &rt4, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szNJ, &rt5, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						memDC.DrawText(szBJ, &rt6, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
						//�º���
						memDC.MoveTo(rc.left, rc.bottom);
						memDC.LineTo(rc.right, rc.bottom);
						memDC.MoveTo(rt1.right, rt1.top);
						memDC.LineTo(rt1.right, rt1.bottom);
						memDC.MoveTo(rt2.right, rt1.top);
						memDC.LineTo(rt2.right, rt1.bottom);
						memDC.MoveTo(rt3.right, rt1.top);
						memDC.LineTo(rt3.right, rt1.bottom);
						memDC.MoveTo(rt4.right, rt1.top);
						memDC.LineTo(rt4.right, rt1.bottom);
						memDC.MoveTo(rt5.right, rt1.top);
						memDC.LineTo(rt5.right, rt1.bottom);
//						memDC.MoveTo(rt6.right, rt1.top);
//						memDC.LineTo(rt6.right, rt1.bottom);
						memDC.MoveTo(rc.left, rt1.bottom);
						memDC.LineTo(rc.right, rt1.bottom);
						
						rc.top += fAdd;
						rc.bottom += fAdd;
						rt1.top = rc.top;
						rt1.bottom = rc.bottom;
						rt2.top = rt1.top;
						rt2.bottom = rt1.bottom;
						rt3.top = rt1.top;
						rt3.bottom = rt1.bottom;
						rt4.top = rt1.top;
						rt4.bottom = rt1.bottom;
						rt5.top = rt1.top;
						rt5.bottom = rt1.bottom;
						rt6.top = rt1.top;
						rt6.bottom = rt1.bottom;
						
						if((i+iStart+1)>=nCountItem)
							break;
 					}
					//��β
					memDC.MoveTo(rc.left, nTop);
					memDC.LineTo(rc.left, rc.top);
					memDC.MoveTo(rc.right, nTop);
					memDC.LineTo(rc.right, rc.top);
					memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
					memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);
					memDC.EndPage();
					memDC.SelectObject(oldfont);
				*/}
			}
			memDC.EndDoc();
		}
	}
	else
	{
		//��ӡԤ��
		
		//�߿���
		hPenOld = memDC.SelectObject(&cPen);
		rc.SetRect(0, 0, B5_W*xPix, B5_H*yPix);
		memDC.Rectangle(&rc);
		memDC.SelectObject(hPenOld);	
		//����
		oldfont = memDC.SelectObject(&TitleFont);
		int nItem = B5_OTHERLINE;
		if(nCurPage == 1)
		{
			nItem = B5_ONELINE;
			rc.SetRect(0, yPix*10, B5_W*xPix, yPix*20);
			memDC.DrawText(szTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		//ϸ��
 		memDC.SelectObject(&DetailFont);
		rc.SetRect(nLeft, nTop, nRight, nTop+fAdd);
		//�Ϻ���
		memDC.MoveTo(rc.left, rc.top);
		memDC.LineTo(rc.right, rc.top);

		rt1.SetRect(nLeft, nTop, nLeft+20*xPix, nTop+fAdd);					//ѧ��
		rt2.SetRect(rt1.right, rt1.top, rt1.right + 25*xPix, rt1.bottom);	//����
		rt3.SetRect(rt2.right, rt1.top, rt2.right + 10*xPix, rt1.bottom);	//�Ա�
		rt4.SetRect(rt3.right, rt1.top, rt3.right + 25*xPix, rt1.bottom);	//רҵ
		rt5.SetRect(rt4.right, rt1.top, rt4.right + 25*xPix, rt1.bottom);	//�꼶
		rt6.SetRect(rt5.right, rt1.top, rc.right, rt1.bottom);				//�༶
		memDC.DrawText("�� ��", &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�� ��", &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("�� ��", &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("������", &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("ְ ��", &rt5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText("��ϵ��ʽ", &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		memDC.MoveTo(rt1.right, rt1.top);
		memDC.LineTo(rt1.right, rt1.bottom);
		memDC.MoveTo(rt2.right, rt1.top);
		memDC.LineTo(rt2.right, rt1.bottom);
		memDC.MoveTo(rt3.right, rt1.top);
		memDC.LineTo(rt3.right, rt1.bottom);
		memDC.MoveTo(rt4.right, rt1.top);
		memDC.LineTo(rt4.right, rt1.bottom);
		memDC.MoveTo(rt5.right, rt1.top);
		memDC.LineTo(rt5.right, rt1.bottom);
//		memDC.MoveTo(rt6.right, rt1.top);
//		memDC.LineTo(rt6.right, rt1.bottom);
		memDC.MoveTo(rc.left, rt1.bottom);
		memDC.LineTo(rc.right, rt1.bottom);

		TCHAR szID[32]={0}, szName[16]={0}, szSex[8]={0}, szZY[32]={0}, szNJ[32]={0}, szBJ[32]={0};
		rc.SetRect(nLeft, nTop+fAdd, nRight, nTop+2*fAdd);
		rt1.SetRect(nLeft+nTextAdd, rc.top, nLeft+20*xPix, rc.bottom);				//ѧ��
		rt2.SetRect(rt1.right+nTextAdd, rt1.top, rt1.right + 25*xPix, rt1.bottom);	//����
		rt3.SetRect(rt2.right+nTextAdd, rt1.top, rt2.right + 10*xPix, rt1.bottom);	//�Ա�
		rt4.SetRect(rt3.right+nTextAdd, rt1.top, rt3.right + 25*xPix, rt1.bottom);	//רҵ
		rt5.SetRect(rt4.right+nTextAdd, rt1.top, rt4.right + 25*xPix, rt1.bottom);	//�꼶
		rt6.SetRect(rt5.right+nTextAdd, rt1.top, rc.right, rt1.bottom);				//�༶

		int nCountItem = ListView_GetItemCount(hList);
		for(int i=0;i<nItem; i++)
		{
			ListView_GetItemText(hList, i+iStart, 0, szID, 32);
			ListView_GetItemText(hList, i+iStart, 1, szName, 16);
			ListView_GetItemText(hList, i+iStart, 2, szSex, 8);
			ListView_GetItemText(hList, i+iStart, 3, szZY, 32);
			ListView_GetItemText(hList, i+iStart, 4, szNJ, 32);
			ListView_GetItemText(hList, i+iStart, 5, szBJ, 32);
			
			memDC.DrawText(szID, &rt1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szName, &rt2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szSex, &rt3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szZY, &rt4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szNJ, &rt5,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			memDC.DrawText(szBJ, &rt6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//�º���
			memDC.MoveTo(rc.left, rc.bottom);
			memDC.LineTo(rc.right, rc.bottom);
			memDC.MoveTo(rt1.right, rt1.top);
			memDC.LineTo(rt1.right, rt1.bottom);
			memDC.MoveTo(rt2.right, rt1.top);
			memDC.LineTo(rt2.right, rt1.bottom);
			memDC.MoveTo(rt3.right, rt1.top);
			memDC.LineTo(rt3.right, rt1.bottom);
			memDC.MoveTo(rt4.right, rt1.top);
			memDC.LineTo(rt4.right, rt1.bottom);
			memDC.MoveTo(rt5.right, rt1.top);
			memDC.LineTo(rt5.right, rt1.bottom);
//			memDC.MoveTo(rt6.right, rt1.top);
//			memDC.LineTo(rt6.right, rt1.bottom);
			memDC.MoveTo(rc.left, rt1.bottom);
			memDC.LineTo(rc.right, rt1.bottom);
			
			rc.top += fAdd;
			rc.bottom += fAdd;
			rt1.top = rc.top;
			rt1.bottom = rc.bottom;
			rt2.top = rt1.top;
			rt2.bottom = rt1.bottom;
			rt3.top = rt1.top;
			rt3.bottom = rt1.bottom;
			rt4.top = rt1.top;
			rt4.bottom = rt1.bottom;
			rt5.top = rt1.top;
			rt5.bottom = rt1.bottom;
			rt6.top = rt1.top;
			rt6.bottom = rt1.bottom;
			
			if((i+iStart+1)>=nCountItem)
				break;
 		}
		//��β
		memDC.MoveTo(rc.left, nTop);
		memDC.LineTo(rc.left, rc.top);
		memDC.MoveTo(rc.right, nTop);
		memDC.LineTo(rc.right, rc.top);
		memDC.DrawText(csLFinality, &rc, DT_LEFT| DT_VCENTER | DT_SINGLELINE);
		memDC.DrawText(csRFinality, &rc, DT_RIGHT| DT_VCENTER | DT_SINGLELINE);

		memDC.SelectObject(oldfont);
		memDC.SelectObject(hPenOld);
	}
	TitleFont.DeleteObject();
	DetailFont.DeleteObject();
	cPen.DeleteObject();
}
