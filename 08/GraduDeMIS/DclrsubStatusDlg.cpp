// DclrsubStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "DclrsubStatusDlg.h"
#include "TecrDclrSubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString strStuName;
/////////////////////////////////////////////////////////////////////////////
// CDclrsubStatusDlg dialog

CString strTecrSub[10];					//�����ַ�������

CDclrsubStatusDlg::CDclrsubStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDclrsubStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDclrsubStatusDlg)
	m_strDclrmax = _T("");
	m_strDclrnum = _T("");
	m_strComlevel = _T("");
	m_strForlanlevel = _T("");
	m_strSchship = _T("");
	//}}AFX_DATA_INIT
}


void CDclrsubStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDclrsubStatusDlg)
	DDX_Control(pDX, IDC_ChoisubStu_LIST, m_ctrlStuName);
	DDX_Control(pDX, IDC_Ownsub_LIST, m_ctrlOwnsub);
	DDX_Text(pDX, IDC_DclrMaxNum_STATIC, m_strDclrmax);
	DDX_Text(pDX, IDC_DclrNum_STATIC, m_strDclrnum);
	DDX_Text(pDX, IDC_ComLevel_EDIT, m_strComlevel);
	DDX_Text(pDX, IDC_ForLanLevel_EDIT, m_strForlanlevel);
	DDX_Text(pDX, IDC_SchShip_EDIT, m_strSchship);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDclrsubStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CDclrsubStatusDlg)
	ON_BN_CLICKED(IDC_DclrSub_BTN, OnDclrSubBTN)
	ON_NOTIFY(NM_CLICK, IDC_Ownsub_LIST, OnClickOwnsubLIST)
	ON_LBN_SELCHANGE(IDC_ChoisubStu_LIST, OnSelchangeChoisubStuLIST)
	ON_BN_CLICKED(IDC_ChoiStu_BTN, OnChoiStuBTN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDclrsubStatusDlg message handlers

BOOL CDclrsubStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
    m_ctrlOwnsub.SetFocus();								//���ý���
	int i=0;												//�������α���
	m_ctrlOwnsub.InsertColumn(0,"����",LVCFMT_LEFT,350,0);	//�����б�ؼ����б�����Ϣ
    if(!pTecrsubSet.IsOpen())								//�򿪼�¼��
		pTecrsubSet.Open();
	pTecrsubSet.MoveFirst();								//�ƶ���������¼
	while(!pTecrsubSet.IsEOF())								//������¼��
	{
		if(pTecrsubSet.m_tecr_name==strExternUser)			//�ж�����
		{
			m_ctrlOwnsub.InsertItem(i,pTecrsubSet.m_sub_title);//�������ݵ��б���
			strTecrSub[i]=pTecrsubSet.m_sub_title;			//�ַ�����ĸ�ֵ
			i++;	
		}		
		pTecrsubSet.MoveNext();								//�ƶ���������¼
	}

	pTecrsubSet.Close();									//�رռ�¼��
	if(!pDclrsubSet.IsOpen())								//�򿪼�¼��
	   pDclrsubSet.Open();	
	pDclrsubSet.MoveFirst();								//�ƶ���������¼
	while(!pDclrsubSet.IsEOF())								//�����¼�������һ��
	{
		if(pDclrsubSet.m_tecr_name==strExternUser)			//�����ж�
		{
			m_strDclrmax=pDclrsubSet.m_tecr_MaxNum;			//������ֵ
			m_strDclrnum=pDclrsubSet.m_tecr_DclrNum;
			break; 
		}
		else
			pDclrsubSet.MoveNext();							//�ƶ���������¼
	}
	pDclrsubSet.Close();									//�رռ�¼��
    UpdateData(false);										//��������
	if(m_strDclrmax==m_strDclrnum)
	{
		CButton *pBtn=(CButton *)GetDlgItem(IDC_DclrSub_BTN);//��ȡ�ؼ���ָ��
		pBtn->ShowWindow(SW_HIDE);						   	//���ؿؼ�
	}
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDclrsubStatusDlg::OnDclrSubBTN() 
{
	// TODO: Add your control notification handler code here
	CTecrDclrSubDlg dlg;									//����Ի������
	dlg.DoModal();											//��ʾ�Ի���
}


void CDclrsubStatusDlg::OnClickOwnsubLIST(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=0;												//�������α���
	int nIndex=m_ctrlStuName.GetCount();					//��ȡ�ؼ������ݵ�����

    for(int j=0;j<nIndex;j++)								//ɾ������
	{
		m_ctrlStuName.DeleteString(j);
	}
	CString strSubTitle;									//�����ַ�������
	NMLISTVIEW *pLV=(NMLISTVIEW *)pNMHDR;    //  str.Format("%d",pLV->iItem);
    strSubTitle=m_ctrlOwnsub.GetItemText(pLV->iItem,0);     //��ȡѡ�е��б���ı�
    if(!pstusubSet.IsOpen())								//�򿪼�¼��
		pstusubSet.Open();
	pstusubSet.MoveFirst();								//�ƶ���������¼
    while(!pstusubSet.IsEOF())
	{
		if(pstusubSet.m_sub_Name==strSubTitle&&pstusubSet.m_stu_choisubStatus)//�����ж�
		{	
			m_ctrlStuName.InsertString(0,pstusubSet.m_stu_name);//�������ݵ��б����
			break;			
		}
		else if(pstusubSet.m_sub_Name==strSubTitle)
		{
			m_ctrlStuName.InsertString(i,pstusubSet.m_stu_name);
			i++;
		}

		pstusubSet.MoveNext();								//�ƶ���������¼	
	}		
	pstusubSet.Close();										//�رռ�¼��
	*pResult = 0;
}

void CDclrsubStatusDlg::OnSelchangeChoisubStuLIST() 
{
	// TODO: Add your control notification handler code here
   	int nIndex=m_ctrlStuName.GetCurSel();					//��ȡ�û�ѡ�е�λ��
   	m_ctrlStuName.GetText(nIndex,strStuName);				//�õ�ѡ�е��ı�
	if(!pstuAchvSet.IsOpen())								//�򿪼�¼��
	  pstuAchvSet.Open();
	pstuAchvSet.MoveFirst();								//�ƶ���������¼
	while(!pstuAchvSet.IsEOF())								//��¼û�е�ĩβ
	{
		if(pstuAchvSet.m_stu_name==strStuName)				//�����ж�
		{
			ACHIEVE stuAch;									//����ṹ����
			stuAch.comLevel=pstuAchvSet.m_comLevel;			//�ṹ�����ĸ�ֵ
			stuAch.forlanLevel=pstuAchvSet.m_forlanLevel;
			stuAch.schship=pstuAchvSet.m_schship;
			m_ctrlStuName.SetItemDataPtr(nIndex,new ACHIEVE(stuAch));//����ָ��
			break;
		}
		else
			pstuAchvSet.MoveNext();							//�ƶ���������¼
	}
	pstuAchvSet.Close();									//�رռ�¼��
	if(nIndex!=LB_ERR)
	{	
		ACHIEVE *stuAch=(ACHIEVE*)m_ctrlStuName.GetItemDataPtr(nIndex);//��ȡ��Ϣ
		m_strComlevel=stuAch->comLevel;						//���ṹ��Ϣ�����ڱ�����
		m_strForlanlevel=stuAch->forlanLevel;
		m_strSchship=stuAch->schship;
		UpdateData(false);									//��������
	}
}

void CDclrsubStatusDlg::OnChoiStuBTN() 
{
	// TODO: Add your control notification handler code here
     if(!pstusubSet.IsOpen())
		pstusubSet.Open();									//�򿪼�¼��		
	 pstusubSet.MoveFirst();								//�ƶ���������¼
     while(!pstusubSet.IsEOF())								//�����¼û�е�ĩβ
	 {
		 if(pstusubSet.m_stu_name==strStuName)				//�ж�����
		 {
			 if(MessageBox("�Ƿ�ѡ���ѧ����","��ʾ��Ϣ",MB_YESNO)==IDYES)//������ʾ
			 {
				 pstusubSet.Edit();							//�༭��¼
				 pstusubSet.m_stu_choisubStatus=true;		//��¼��ֵ
				 pstusubSet.Update();						//��������
				 pstusubSet.Requery();						//ˢ�¼�¼��
			 }
			 break;
		 }
		 else
		   pstusubSet.MoveNext();							//�ƶ���������¼
	 }
	 pstusubSet.Close();									//�رռ�¼��
}
