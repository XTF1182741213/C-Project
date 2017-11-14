// MADDSONG.cpp : implementation file
//

#include "stdafx.h"
#include "HCOK.h"
#include "MADDSONG.h"
#include "ADOConn.h"
#include "ADDSGEDLG.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString desongname1,desingername1,deformat1;
bool mp3filebroken;
/////////////////////////////////////////////////////////////////////////////
// MADDSONG dialog


MADDSONG::MADDSONG(CWnd* pParent /*=NULL*/)
	: CDialog(MADDSONG::IDD, pParent)
{
	//{{AFX_DATA_INIT(MADDSONG)
	m_filename = _T("");
	m_format = _T("");
	m_singer = _T("");
	m_songname = _T("");
	//}}AFX_DATA_INIT
}


void MADDSONG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MADDSONG)
	DDX_Control(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO2, m_comb2);
	DDX_Control(pDX, IDC_COMBO1, m_comb1);
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	DDX_Text(pDX, IDC_FORMAT, m_format);
	DDX_Text(pDX, IDC_SINGER, m_singer);
	DDX_Text(pDX, IDC_SONGNAME, m_songname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MADDSONG, CDialog)
	//{{AFX_MSG_MAP(MADDSONG)
	ON_BN_CLICKED(IDC_CHOOSE, OnChoose)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MADDSONG message handlers

BOOL MADDSONG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//*********************��ʼ������������ѡ��*********************///
    m_comb1.InsertString(0,"1");
	m_comb1.InsertString(1,"2");
	m_comb1.InsertString(2,"3");
	m_comb1.InsertString(3,"4");
	m_comb1.InsertString(4,"5");
	m_comb1.InsertString(5,"6");
    m_comb1.InsertString(6,"7");
	m_comb1.InsertString(7,"8");
	m_comb1.InsertString(8,"9");
	m_comb1.InsertString(9,"10");
	m_comb1.InsertString(10,"11");
	m_comb1.InsertString(11,"12");
    m_comb1.SetCurSel(0);
	//*********************��ʼ����������ѡ��*********************///
	m_comb2.InsertString(0,"����");
	m_comb2.InsertString(1,"����");
	m_comb2.InsertString(2,"ͨ��");
	m_comb2.InsertString(3,"�ŵ�");
	m_comb2.InsertString(4,"��ʿ");
	m_comb2.InsertString(5,"ҡ��");
    m_comb2.InsertString(6,"������");
	   m_comb2.SetCurSel(0);
		//*********************��ʼ��list�ؼ�********************///
	   
	   m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	   m_list.InsertColumn(0,"����",LVCFMT_CENTER,150);
	   m_list.InsertColumn(1,"������",LVCFMT_CENTER,100);
	   m_list.InsertColumn(2,"�������",LVCFMT_CENTER,80);
	   m_list.InsertColumn(3,"��ʽ",LVCFMT_CENTER,80);

	   m_radio.SetCheck(1);  //Ĭ��ѡ���������
/////////////////////////////////////////////
	   mp3filebroken=false;
	   ShowData() ;
	   return TRUE;  // return TRUE unless you set the focus to a control
//		
}

void MADDSONG::OnChoose() 
{
	//���ÿ���ѡ����ļ�����
	char szFilter[] =" ý���ļ� (��������)|*.mp3;*.wma;*.wmv;*.wav;*.avi;*.rm;*.rmvb\
		|��Ƶ�ļ� |*.wmv;*.avi;*.rm;*.rmvb|��Ƶ�ļ�|*.mp3;*.wma;*.wav|�����ļ� (*.*)|*.*||";
		CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter); 	
	if(filedlg.DoModal()==IDOK)
	{
		CString  strname,strname1;
		strname=filedlg.GetFileName();////////////////////////�ĵ��ļ���
		strname1=filedlg.GetFileTitle();////////////////////////�ļ���
		Qfilename1=filedlg.GetPathName();/////////////////////////��ֵ
		Qfilename2=strname;//////////////////��ֵ
		GetDlgItem(IDC_FILENAME)->SetWindowText(strname);//��ʾ���༭��
		CString strname2,strname3,strname4;
		GetDlgItem(IDC_SONGNAME)->GetWindowText(strname2);//�õ��༭���ֵ
		GetDlgItem(IDC_FILENAME)->GetWindowText(strname3);//�õ��༭���ֵ
		strname4=strname3.Right(strname3.GetLength()-strname1.GetLength()-1);//�õ��ļ��ĸ�ʽ ,��'mp3,wma'
		if( strname4=="mp3")//�����MP3��ʽ�ľ��÷����Զ���ȡ�ļ�����	
		{
			CFile file;
			file.Open(strname,CFile::modeRead);
			//���ļ������128�ֽ���Ϣ����pbuf����
			long seekPos = 128;
			file.Seek(-seekPos,CFile::end);
			BYTE pbuf[128];
			memset(pbuf,0,sizeof(pbuf));
			file.Read(pbuf,128);
			//���tag,�������tag����ô�ͷ���
			if(!((pbuf[0] == 'T'|| pbuf[0] == 't')
				&&(pbuf[1] == 'A'|| pbuf[1] == 'a')
				&&(pbuf[2] == 'G'|| pbuf[0] == 'g')))
			{
				file.Close();
				mp3filebroken=true;
				return ;
			}
			mp3=(MP3INFO *) new BYTE[sizeof(MP3INFO)];
			ZeroMemory(mp3,sizeof(MP3INFO));	
			memcpy(mp3->Identify,pbuf,3); //���tag
			memcpy(mp3->Title,pbuf+3,30); //��ø���
			memcpy(mp3->Artist,pbuf+33,30); //�������
			memcpy(mp3->Album,pbuf+63,30); //��ó�Ƭ��
			memcpy(mp3->Year,pbuf+93,4); //�����
			memcpy(mp3->Comment,pbuf+97,28); //���ע��
			memcpy(&mp3->reserved,pbuf+125,1); //��ñ���
			memcpy(&mp3->reserved2,pbuf+126,1);
			memcpy(&mp3->reserved3,pbuf+127,1);
			GetDlgItem(IDC_SONGNAME)->SetWindowText(mp3->Title);//���������ر༭��
			GetDlgItem(IDC_SINGER)->SetWindowText(mp3->Artist);//�����������ر༭��
			GetDlgItem(IDC_FORMAT)->SetWindowText(strname4);//����ʽ���ر༭��
			file.Close();
			delete mp3;	
		}
		else{
			GetDlgItem(IDC_FORMAT)->SetWindowText(strname4);//���ý�ȡ�õ���ֵ
			GetDlgItem(IDC_SONGNAME)->SetWindowText(  strname1); //��ʾ����
			GetDlgItem(IDC_FILENAME)->SetWindowText(strname);//�ļ���
		}
		mp3filebroken=false;
	}		 
}


void MADDSONG::OnAdd() 
{	 
	tempshow++;
	CString songname,format,strname4,singer,addpath,newfilename,strtemp;
	GetDlgItem(IDC_SONGNAME)->GetWindowText(  songname);  
	GetDlgItem(IDC_FORMAT)->GetWindowText(  format);
	GetDlgItem(IDC_SINGER)->GetWindowText(  singer);///////////////////��ȡ������
	if(Qfilename1==""||songname=="")  //·���͸���Ϊ��ʱ
		GetDlgItem(IDC_INFOR)->SetWindowText("����ѡ�����!");
	else
	{
		if( singer=="")//���������Ϊ��
		{	GetDlgItem(IDC_INFOR)->SetWindowText("�������!");
		if( mp3filebroken==true)
			GetDlgItem(IDC_INFOR)->SetWindowText("������������͸�ʽ��ʽ!");
		}
		else
		{
			ADOConn m_AdoConn;/////////////////////////////��ADO�������ݿ�	
			m_AdoConn.OnInitADOConn();  //�������ݿ�
			_RecordsetPtr m_pRecordset;  //�����¼��
			_bstr_t sql;
			sql ="select*from musiclist where muname ='"+songname+"'and singernam='"+singer+"'";//��ѯ����
			m_pRecordset=m_AdoConn.GetRecordSet(sql);
			if(!(m_pRecordset->adoEOF))////////////////////////�ж��и�����¼
				GetDlgItem(IDC_INFOR)->SetWindowText("���Ѿ���ӹ����׸���!");	
			else//�ж���û����
			{  
				_bstr_t findsin;
				findsin = "select* from singer where sinnam='"+ singer+"'";////////////////////
				m_pRecordset=m_AdoConn.GetRecordSet(findsin);
				if(m_pRecordset->adoEOF)  //û�е�ǰ������ĸ��ֵ�����,�ᵯ���Ի����������
				{
					GetDlgItem(IDC_INFOR)->SetWindowText("�����û�иø������ֵ���Ϣ,�벹��!");
					ADDSGEDLG addsinger;
					addsinger.m_singer=singer;
					addsinger.DoModal();
				}
				//�������,���ļ���ӵ������ļ�����,�˷�������,����ֱ�ӵ��ļ����ƺ���
				if(!m_radio.GetCheck() )//����ļ��������ļ���/////////////////
				{
					CString sPath ,fullname;
					int nPos;
					CFile* writefile;//////////////////////д�ļ�
					CFile* readfile;////////////////////////���ļ�
					long readlen,poslen,filelen;
					LPVOID pvData;
					HGLOBAL hGlobal;
					GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//�õ�Ҫ����ļ���·��
					nPos=sPath.ReverseFind('\\');
					sPath=sPath.Left(nPos);
					nPos=sPath.ReverseFind('\\');
				    sPath=sPath.Left(nPos);
					sPath=sPath+"\\����ļ���";
					CString  strname,strname1,filename1;
					filename1=  Qfilename1; ////////////////�õ�·�� ,��ѡ���ļ��Ǳߵõ���
					strname=   Qfilename2;////////////////////////�ĵ��ļ���,��ѡ���ļ��Ǳߵõ���
					fullname.Format("%s\\%s",sPath,strname);
					readfile=new CFile(filename1,CFile::modeRead);
					HANDLE hfile=::CreateFile(	fullname,GENERIC_WRITE|GENERIC_WRITE,0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
					CloseHandle(hfile);
					writefile=new CFile(fullname,CFile::modeWrite);
					filelen=readfile->GetLength();
					hGlobal = GlobalAlloc(GMEM_MOVEABLE,512);
					pvData = GlobalLock(hGlobal);
					while(1)
					{
						ZeroMemory(pvData,512);
						readlen=readfile->ReadHuge(pvData,512);
						poslen=readfile->GetPosition();//��ȡ�ļ�ָ���λ��
						writefile->WriteHuge(pvData,readlen);
						if(poslen==filelen)//���ָ���Ƶ�ĩβ,���˳�ѭ��
							break;
					}
					GlobalUnlock(hGlobal);
					readfile->Close();  //���ر�
					writefile->Close();
					//�������ļ�
					songname.TrimRight();  //ȥ�ո�
					CString	stredfilename=songname+'.'+format;//�õ��ļ���+��ʽ
					CString temp,strtemp;strtemp=temp=	fullname;
					int pos1=temp.Find("\\");
					while(pos1>0)
					{
						temp=temp.Right(temp.GetLength()-1-pos1);
						pos1=temp.Find("\\");
					}
					strtemp=strtemp.Left(strtemp.GetLength()-temp.GetLength());
					strtemp+=stredfilename; 
					CFile::Rename(fullname,strtemp);
					addpath="ϵͳ�ļ�����";
					newfilename=stredfilename;
				}    
				else//*************����ֻ���ַ�Ĳ������ļ���
				{
					addpath=Qfilename1;
					songname.TrimRight();
					newfilename=songname+'.'+format;
				}
				CString strname5, format;
				GetDlgItem(IDC_SINGER)->GetWindowText(  strname5);///////////////////��ȡ������
				CString munum;
				int k=m_comb1.GetCurSel();
				m_comb1.GetLBText(k,munum);///////////////////�õ�������
				CString mutype;
				int k2=m_comb2.GetCurSel();
				m_comb2.GetLBText(k2,mutype);////////////////////�õ���������
				GetDlgItem(IDC_FORMAT)->GetWindowText( format);//�õ���ʽ��
				m_AdoConn.ExitConnect();	
				m_AdoConn.OnInitADOConn();
				_RecordsetPtr m_pRecordset;
				_bstr_t sql;
				sql = "select*from musiclist";
				m_pRecordset=m_AdoConn.GetRecordSet(sql);
				m_pRecordset->AddNew();//�������
				m_pRecordset->GetFields()->GetItem("singernam")->Value=(_bstr_t) strname5 ;///д�������
				m_pRecordset->GetFields()->GetItem("muname")->Value=(_bstr_t) songname;////д�����
				m_pRecordset->GetFields()->GetItem("mnum")->Value=(_bstr_t)  munum;////д�������
				m_pRecordset->GetFields()->GetItem("mtpye")->Value=(_bstr_t)  mutype ;////д��������
				m_pRecordset->GetFields()->GetItem("fname")->Value=(_bstr_t) newfilename;////д���ļ���
				m_pRecordset->GetFields()->GetItem("format")->Value=(_bstr_t)  format ;////д���ʽ
				m_pRecordset->GetFields()->GetItem("path")->Value=(_bstr_t)  addpath ;////д��·��
				m_pRecordset->Update();
				m_AdoConn.ExitConnect();//�ͷ����ݿ���Դ
				GetDlgItem(IDC_INFOR)->SetWindowText("���"+songname+"�ɹ������!");
				GetDlgItem(IDC_SONGNAME)->SetWindowText("");  //��������
				GetDlgItem(IDC_SINGER)->SetWindowText(""); //��������
				GetDlgItem(IDC_FILENAME)->SetWindowText(""); //��������
				GetDlgItem(IDC_FORMAT)->SetWindowText("");//��������
				m_comb1.SetCurSel(0);//������ʾ��һ��
				m_comb2.SetCurSel(0);//������ʾ��һ��
				}
				}
		}
		
		ShowData() ;			
}
void MADDSONG::ShowData() //��ʾ��Ϣ
{
	CString  muname, singername, mtype,format;
	m_list.DeleteAllItems();  //ɾ�����е�
	int k=0;
	ADOConn m_AdoConn;//�������ݿ��������
			
	m_AdoConn.OnInitADOConn();//�������ݿ�
   _RecordsetPtr m_pRecordset; //�����¼��
	_bstr_t sql;
				
	sql = "select*from musiclist";
		
		m_pRecordset=m_AdoConn.GetRecordSet(sql);//�õ���¼��
	if(m_pRecordset->adoEOF)  //���û�о��˳�����
	{
			m_AdoConn.ExitConnect(); //�ͷ����ݿ���Դ
					return;
	}
	m_pRecordset->MoveFirst();
			

while(!m_pRecordset->adoEOF)  //������¼����ʾ��list��
	{   		

	muname=m_pRecordset->GetFields()->GetItem("muname")->Value.bstrVal;/////////////////ȡ������
	   singername=m_pRecordset->GetFields()->GetItem("singernam")->Value.bstrVal;/////////////////ȡ������
	   
	   mtype=m_pRecordset->GetFields()->GetItem("mtpye")->Value.bstrVal;/////////////////ȡ�������
	   format=m_pRecordset->GetFields()->GetItem("format")->Value.bstrVal;/////////////////ȡ��ʽ
	   m_list.InsertItem(k, muname);  //��ʾ������list��
	   m_list.SetItemText(k,1,singername);//��ʾ���ֵ�list��
	   m_list.SetItemText(k,2, mtype);
	   m_list.SetItemText(k,3,format);
	   m_pRecordset->MoveNext();
	   k++;
	}
	m_AdoConn.ExitConnect();
}

void MADDSONG::OnDel() 
{
	delsongfresh++;
	ADOConn m_AdoConn;//�������ݿ����Ӷ���
			
	m_AdoConn.OnInitADOConn();  //��������
	_RecordsetPtr m_pRecordset; //�����¼��
     _bstr_t sql;
		
	sql = "delete from musiclist where singernam='"+desingername1+"'and muname='"+desongname1+"'";
    m_pRecordset=m_AdoConn.GetRecordSet(sql);//ɾ�����ݿ���
	//�õ�ϵͳ�ļ�·��\Debug\����ļ���
    CString sPath ;
	int nPos;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);

	sPath=sPath+"\\����ļ���";
	desongname1.TrimRight();//ȥ�ұߵĿո�
	
	CString	defilename1=desongname1+'.'+deformat1; //�õ��ļ��Ӹ�ʽ��

     CString	filename=sPath+"\\"+defilename1;//�õ�����·��
	DeleteFile(filename);
	ShowData() ;
		GetDlgItem(IDC_INFOR)->SetWindowText("ɾ��"+desongname1+"�ɹ�!");
	
}

void MADDSONG::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int selectrow=pNMListView->iItem;
   desongname1=m_list.GetItemText(selectrow,0);//�õ�����
    desingername1=m_list.GetItemText(selectrow,1); //�õ�������
    deformat1=m_list.GetItemText(selectrow,3);//�õ���ʽ
   UpdateData(false);
	
	
	*pResult = 0;
}
