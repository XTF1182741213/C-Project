// GUANLI.cpp : implementation file
//

#include "stdafx.h"
#include "licai.h"
#include "GUANLI.h"
#include "XGQX.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GUANLI dialog


GUANLI::GUANLI(CWnd* pParent /*=NULL*/)
	: CDialog(GUANLI::IDD, pParent)
{
	//{{AFX_DATA_INIT(GUANLI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GUANLI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GUANLI)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GUANLI, CDialog)
	//{{AFX_MSG_MAP(GUANLI)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnModify)
	ON_BN_CLICKED(IDC_BUTTON2, OnDele)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GUANLI message handlers

BOOL GUANLI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	pdb=new CDatabase;
	mySet=new PWSet(pdb);
	mySet->Open();	
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    m_list.InsertColumn(0,"�û���",LVCFMT_CENTER,150);
    m_list.InsertColumn(1,"�û�Ȩ��",LVCFMT_CENTER,150);
	LOADDATA();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GUANLI::LOADDATA()
{
	mySet->Requery();
	m_list.DeleteAllItems();
	int i=0;
	while(!mySet->IsEOF())
	{
		m_list.InsertItem(i,mySet->m_ID);
		m_list.SetItemText(i,1,mySet->m_AUTHOR);
		i++;
		mySet->MoveNext();
	}
}

void GUANLI::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) //��ö�Ӧ�б����Ϣ
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int selectrow=pNMListView->iItem;	
	m_id=m_list.GetItemText(selectrow,0);
	*pResult = 0;
}

void GUANLI::OnModify() 
{
	if(m_id=="")
	{
		MessageBox("��ѡ�������޸ĵļ�¼","��ʾ",MB_OK|MB_ICONINFORMATION);
		return;
	}
	if(ID==m_id)
	{
		MessageBox("��ǰ�û��޷��޸�Ȩ��","��ʾ",MB_OK|MB_ICONINFORMATION);
		return;
	}
	else
	{
		mySet->MoveFirst();
		while(!mySet->IsEOF())
		{   
			if(mySet->m_ID==m_id)
				break;
			else
				mySet->MoveNext();		
		}
		XGQX mydlg;
		mydlg.m_id=mySet->m_ID;
		if(mySet->m_AUTHOR=="����Ա")
			glflag=true;
		else
			glflag=false;
		UpdateData(false);
		if(mydlg.DoModal()==IDOK)
		{ 	
			mySet->Edit();
			mySet->m_AUTHOR=mydlg.author;
			mySet->Update();
			UpdateData(false);
			LOADDATA();
			MessageBox("�û�Ȩ���޸ĳɹ�","��ʾ",MB_OK|MB_ICONINFORMATION);
			COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
			CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��"); 
			CString strTmp=strFileName+"\r\n����Ա "+ID+" �޸��û���"+m_id+" ��Ȩ��Ϊ"+mydlg.author+"\r\n";
			CStdioFile file(logFileName,CFile::modeNoTruncate|CFile::modeWrite);
			file.SeekToEnd();//�ȶ�λ���ļ�β��
			file.WriteString(strTmp);
			file.Close();
			m_id="";
		}		
	}			
}

void GUANLI::OnDele() 
{
	CString str;
    int i=0;
    if(mySet->IsOpen())       //�ж��û����ݱ��Ƿ�Ϊ��
		mySet->Close();
	mySet->Open();
    while(!mySet->IsEOF())
	{
		mySet->MoveNext();
		i++;
	}
	if(i==0)
	{
		MessageBox("       ����������û���Ϣ          ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
	} 
	else
    {   
		mySet->MoveFirst();
		if(m_id=="")
			MessageBox("          ��ѡ����Ҫɾ�����û�                ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
		else if(MessageBox("          ȷ��ɾ�����û���?                 ","�Ƿ�ɾ��",MB_YESNO|MB_ICONINFORMATION)==IDYES)
		{	
			while(!mySet->IsEOF())
		{  
				if(ID==m_id)
				{
					MessageBox("  ��ǰ����Ա��½�ʺ��޷�ɾ��,��ʹ����������ԱȨ�޽���ɾ��   ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
					LOADDATA();
					break;
				}
				if(mySet->m_ID!=m_id)
					mySet->MoveNext();
				else
				{
					str.Format("delete from password where ID='%s'",mySet->m_ID);     //SQL����IDΪ��ǰѡ�е��û���Ϣɾ��
		            pdb->ExecuteSQL(str);
		            mySet->Requery();
	              	LOADDATA();
			    	MessageBox("          ���û����ɹ�ɾ��                 ","��ͥ�������ϵͳ",MB_OK|MB_ICONINFORMATION);
			        COleDateTime oleDt=COleDateTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
		         	CString strFileName=oleDt.Format("%Y��%m��%d�� %Hʱ%M��%S��");
          			CString strTmp=strFileName+"\r\n\n����Ա "+ID+" ɾ���û���Ϊ "+m_id+" ���û�   ɾ���ɹ�\r\n\n\n\n\n";
	           		CStdioFile file(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
        			file.SeekToEnd();//�ȶ�λ���ļ�β��
	        		file.WriteString(strTmp);
        			file.Close();
	         		m_id="";
			    	break;				
				}
			}
		}	
	}	
}
