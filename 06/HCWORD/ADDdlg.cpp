// ADDdlg.cpp : implementation file
//

#include "stdafx.h"
#include "HCWORD.h"
#include "ADDdlg.h"
#include "HCset.h"
#include "TIANJIADlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CString logFileName;
/////////////////////////////////////////////////////////////////////////////
// ADDdlg dialog


ADDdlg::ADDdlg(CWnd* pParent /*=NULL*/)
	: CDialog(ADDdlg::IDD, pParent)
{    //m_set=new HCset();
	//{{AFX_DATA_INIT(ADDdlg)
	//}}AFX_DATA_INIT
}


void ADDdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADDdlg)
	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADDdlg, CDialog)
	//{{AFX_MSG_MAP(ADDdlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, OnItemchangedList3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////



BOOL ADDdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    word="";
	columnname1="eg";                                                           //��ʼ��
	tablename="eh";
	selectrow=-1;
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); //�����б�ؼ��ķ��
    m_list.InsertColumn(0,"����",LVCFMT_CENTER,250);                //����б�ؼ�������
	m_list.InsertColumn(1,"����",LVCFMT_CENTER,250);
    pdb=new CDatabase;                                               //�������ݿ����ָ��
	pdb->OpenEx("DSN=�ʿ�;Trusted_Connection=Yes;");                                     //�����ݿ�
    m_combo.SetCurSel(0);                                            //��ʼ�������ؼ�                                 
	show();  
    return TRUE;  
}
void ADDdlg::show()                                                 //�Զ��庯��
{
	int i=0;
	CString temp1,temp2;
	strsql="select * from "+tablename;                          //��ȡ���ݱ���������Ϣ
	pdb->ExecuteSQL(strsql);
	CRecordset m_Set(pdb);
	m_Set.Open(CRecordset::dynaset,strsql);
	CODBCFieldInfo fieldinfo; 
    m_Set.GetODBCFieldInfo(short(0), fieldinfo);//ȡ��1���ֶε���Ϣ
	columnname1=fieldinfo.m_strName;
	m_Set.GetODBCFieldInfo(short(1), fieldinfo);//ȡ��2���ֶε���Ϣ
	columnname2=fieldinfo.m_strName;
	m_list.DeleteAllItems();                                          //�б�ؼ����
	while(!m_Set.IsEOF())                                             //�ж��Ƿ����ݱ��������ݿ������ݵ����
	{ 
		m_Set.GetFieldValue(short(0),temp1);
		m_Set.GetFieldValue(short(1),temp2);
		temp1.TrimRight();
		temp2.TrimRight();
		m_list.InsertItem(i,temp1);                               //�����ݿ��е����ݶ�Ӧ������ʾ     
		m_list.SetItemText(i,1,temp2);
		i++;                                                               
        m_Set.MoveNext();                                          //�ƶ�����һ����¼
	}
	UpdateData(false);                                         //ˢ������
	m_Set.Close();                                         //�ر����ݿ�
}  


void ADDdlg::OnSelchangeCombo1() 
{
	CString temp;
	m_combo.GetLBText(m_combo.GetCurSel(),temp);             //��ȡ�����ؼ���ֵ
	if(temp=="�ʿ��")                                      
	{
		tablename="eh";                                    
	}
	else if(temp=="���ʱ�")
	{
		tablename="ziliao";
	}
	else if(temp=="�ļ����Ե��ʱ�")
	{
		tablename="four";
	}
	show();                                       //���ú���
}

void ADDdlg::OnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	selectrow=pNMListView->iItem;
    word=m_list.GetItemText(selectrow,0);                     //��ȡ����������Ϣ
	mean=m_list.GetItemText(selectrow,1);                     //��ȡ����������Ϣ

	*pResult = 0;
}

void ADDdlg::OnButton1() 
{
	if(word!="")                                                  //�ж�������Ϣ�Ƿ�Ϊ��
	{
		CString str,temp,str2;                                        //�����ַ�������
		str.Format("select * from %s where %s='%s'",tablename,columnname1,word);    //�����������������ݱ�	
		pdb->ExecuteSQL(str);
		CRecordset m_Set(pdb);
		m_Set.Open(CRecordset::dynaset,str);
		m_Set.GetFieldValue(short(1),temp);	
		m_Set.Close();
		str2=temp;                                  //��ȡ����	
		CString sPath; 
		GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
		sPath.ReleaseBuffer();
		int nPos;
		nPos=sPath.ReverseFind('\\');
		sPath=sPath.Left(nPos);
		nPos=sPath.ReverseFind('\\');
		sPath=sPath.Left(nPos);
		logFileName = sPath + "\\log.txt";  
		CTime t=CTime::GetCurrentTime();//��ȡ���صĵ�ǰʱ��
        CString strtime=t.Format("%Y��%m��%d�� %Hʱ%M��%S��");
		CString   strTmp=strtime+"\r\n"+word+"\t\t"+str2+"\n\n\n";//��ȡ��ʾ��Ϣ
		CStdioFile file(logFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
		file.SeekToEnd();                                          //�ȶ�λ���ļ�β��
		file.WriteString(strTmp);                                  //д����ʾ��Ϣ
		file.Close();                                              //�ر��ļ�
	}
	REMDlg mydlg;                                             //�������
	mydlg.DoModal();                                          //��Ӧ��Ϣ����	
}

void ADDdlg::OnAdd() 
{
	
	TIANJIADlg mydlg;
	mydlg.addflag=true;
	if(mydlg.DoModal()==IDOK)
	{
		if(mydlg.m_1!=""&&mydlg.m_3!="")
		{
		CString str,temp,str2;                                        //�����ַ�������
		str.Format("insert into %s(%s,%s) values('%s','%s')",tablename,columnname1,columnname2,mydlg.m_1,mydlg.m_3);    //�����������������ݱ�	
		pdb->ExecuteSQL(str);
		show();
        AfxMessageBox("��ӳɹ���");
		}
		else
		{
			AfxMessageBox("�����뵥�ʺͽ���");
			return;
		}
	}
}

void ADDdlg::OnDelete() 
{
	 if(word=="")
	{
		AfxMessageBox("����ѡ��Ҫɾ���ļ�¼");
		return;
	}
	if(MessageBox("ע��","ȷ��Ҫɾ����",MB_OKCANCEL)==IDOK)
	{
		CString str,temp,str2;                                        //�����ַ�������
		str.Format("delete from %s where %s='%s'",tablename,columnname1,word);//�����������������ݱ�	
		pdb->ExecuteSQL(str);
		show();
        AfxMessageBox("ɾ���ɹ���");	
	}	
}

void ADDdlg::OnModify() 
{
	TIANJIADlg mydlg;
	mydlg.addflag=false;
	mydlg.m_1=word;
	mydlg.m_3=mean;
    if(word=="")
	{
		AfxMessageBox("����ѡ��Ҫ�޸ĵļ�¼");
		return;
	}
	if(mydlg.DoModal()==IDOK)
	{
		if(mydlg.m_1!=""&&mydlg.m_3!="")
		{
		CString str,temp,str2;                                        //�����ַ�������
		str.Format("update %s set %s='%s' where %s='%s'",tablename,columnname2,mydlg.m_3,columnname1,mydlg.m_1);//�����������������ݱ�	
		pdb->ExecuteSQL(str);
		show();
        AfxMessageBox("�޸ĳɹ���");
		}
		else
		{
			AfxMessageBox("�����뵥�ʺͽ���");
			return;
		}
	}
}
