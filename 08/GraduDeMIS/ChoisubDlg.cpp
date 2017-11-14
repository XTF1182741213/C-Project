// ChoisubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "ChoisubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoisubDlg dialog


CChoisubDlg::CChoisubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoisubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoisubDlg)
	m_QueSubVal = _T("");
	//}}AFX_DATA_INIT
}


void CChoisubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoisubDlg)
	DDX_Control(pDX, IDC_QuerySubEDIT, m_QueSubCtrl);
	DDX_Control(pDX, IDC_SubQuery_LIST, m_SubQueryList);
	DDX_Control(pDX, IDC_SubQuery_COMBO, m_SubQueryCombo);
	DDX_Text(pDX, IDC_QuerySubEDIT, m_QueSubVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoisubDlg, CDialog)
	//{{AFX_MSG_MAP(CChoisubDlg)
	ON_BN_CLICKED(IDC_QUERY_BTN, OnQueryBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_SubQuery_LIST, OnDblclkSubQueryLIST)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoisubDlg message handlers


BOOL CChoisubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here      
	m_SubQueryList.InsertColumn(0,"������",LVCFMT_LEFT,300,0);
	m_SubQueryList.InsertColumn(1,"��ʦ",LVCFMT_LEFT,60,0);
	m_SubQueryList.InsertColumn(2,"��������",LVCFMT_LEFT,70,0);
	m_SubQueryList.InsertColumn(3,"������",LVCFMT_LEFT,250,0);
	m_SubQueryList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//�б�ؼ������趨����ѡ������
    int i=0;												//�������α���
	if(!psubSet.IsOpen())
    psubSet.Open();											//�򿪼�¼��
	psubSet.MoveFirst();									//�ƶ���������¼
	while(!psubSet.IsEOF())									//�����¼����ĩβ
	{  
		m_SubQueryList.InsertItem(i,psubSet.m_sub_title);	//���б�ؼ��в�������
		m_SubQueryList.SetItemText(i,1,psubSet.m_tecr_name);
		m_SubQueryList.SetItemText(i,2,psubSet.m_sub_type);
		m_SubQueryList.SetItemText(i,3,psubSet.m_sub_pro);
        psubSet.MoveNext();									//�ƶ���������¼
        i++;
	}	
	psubSet.Close();										//�رռ�¼��
    CString str[3]={"������","��ʦ","��������"};			//�����ַ������鸳��ֵ
	for(int j=0;j<3;j++)
		m_SubQueryCombo.InsertString(j,str[j]);				//���������ݲ��뵽�����б����
	m_SubQueryCombo.SetCurSel(0);							//�趨Ĭ��ѡ���һ��
	UpdateData(false);										//��������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CChoisubDlg::OnQueryBtn() 
{
	// TODO: Add your control notification handler code here
	int nIndex=m_SubQueryCombo.GetCurSel();					//�õ������б��ѡ�е�����
	switch(nIndex)	
	{
	   case 0:
		   SelectItem(0);  break;							//�����û��Զ��庯��	   
	   case 1:
		   SelectItem(1);  break; 
	   case 2:
		   SelectItem(2); break;
	   default:break;
	}    
}

void CChoisubDlg::SelectItem(int n)	
{  
	char filter[60];                                            //�����ַ�����
	CString str[3]={"tab_sub.sub_title='%s'","tab_sub.tecr_name='%s'","tab_sub.sub_type='%s'"};		
	CString strEdit;                                            //�����ַ���
    UpdateData();												//��������
	psubSet.Open();												//�򿪼�¼��
	wsprintf(filter,str[n],m_QueSubVal);						//��ʽ���ַ�
	psubSet.m_strFilter=filter;									//��¼����ֵ
	psubSet.Requery();											//ˢ�¼�¼��
    m_QueSubCtrl.GetWindowText(strEdit);						//��ȡ�ؼ����ı�
	if(strEdit=="")												//�ж�����
	{
		MessageBox("��ѯ����Ϊ�գ�������ؼ��ʣ�");
		m_QueSubCtrl.SetFocus();								//���ý���
		psubSet.Close();										//�رռ�¼��
		return;
	}
	else 
	{	
		if(psubSet.IsEOF())										//�����¼����ĩβ
			AfxMessageBox("Ҫ���ҵĿ��ⲻ���ڣ�");
		else
		{
		  m_SubQueryList.DeleteAllItems();						//ɾ�����пؼ��е�����
		  int i=0;												//�������α���
		  while(!psubSet.IsEOF())								//�����¼����ĩβ
		  {	
			m_SubQueryList.InsertItem(i,psubSet.m_sub_title);	//�������ݵ��б�ؼ���
			m_SubQueryList.SetItemText(i,1,psubSet.m_tecr_name);
			m_SubQueryList.SetItemText(i,2,psubSet.m_sub_type);
			m_SubQueryList.SetItemText(i,3,psubSet.m_sub_pro);
			psubSet.MoveNext();									//�ƶ���������¼
			i++;
		  }
		 UpdateData(false);										//��������
		}	
	   psubSet.Close();											//�رռ�¼��
	}
}

void CChoisubDlg::OnDblclkSubQueryLIST(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   NMLISTVIEW *pLV=(NMLISTVIEW *)pNMHDR;
   CString strSubTitle;											//�����ַ���
   strSubTitle=m_SubQueryList.GetItemText(pLV->iItem,0);		//��ȡ�û�ѡ�����
   if(MessageBox("ÿ��ֻ��ѡ��һ�⣬�Ƿ�ѡ����⣿","��ʾ��Ϣ",MB_YESNO)==IDYES)
   {
	   pchoisubSet.Open();
	   pchoisubSet.AddNew();  									//����µļ�¼
	   pchoisubSet.m_stu_name=strExternUser;					//�¼�¼��ֵ
	   pchoisubSet.m_stu_choisubStatus=false;
	   pchoisubSet.m_sub_Name=strSubTitle;
	   pchoisubSet.Update();									//��������
	   pchoisubSet.Requery();									//ˢ�¼�¼��
	   pchoisubSet.MoveLast();									//�ƶ���ĩβ
	   pchoisubSet.Close();										//�رռ�¼��
       MessageBox("ѡ��ɹ���","��ʾ��Ϣ",MB_OK);				//��Ϣ��ʾ
   }
   else
       return;
	*pResult = 0;
}

void CChoisubDlg::OnClose() 
{
	CDialog::OnClose();				//�رնԻ���
}
