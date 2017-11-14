// DocChekDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "DocChekDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocChekDlg dialog


CDocChekDlg::CDocChekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDocChekDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDocChekDlg)
	m_strFanyi = _T("");
	m_strKaiti = _T("");
	m_strShixi = _T("");
	m_bFYnum = FALSE;
	m_bFYrelate = FALSE;
	m_bFYsubmit = FALSE;
	m_bKTbasecndi = FALSE;
	m_bKTplan = FALSE;
	m_bKTsubmit = FALSE;
	m_bSXrelate = FALSE;
	m_bSXsubmit = FALSE;
	m_strFYQuality = _T("");
	m_strKTunderstand = _T("");
	m_strSXbehave = _T("");
	m_strStuName = _T("");
	//}}AFX_DATA_INIT
}

void CDocChekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocChekDlg)
	DDX_Control(pDX, IDC_COMBO_Kaiti, m_ctrlKTunderstand);
	DDX_Control(pDX, IDC_COMBO_Shixi, m_ctrlShixi);
	DDX_Control(pDX, IDC_COMBO_Fanyi, m_ctrlFanyi);
	DDX_Control(pDX, IDC_StuName_COMBO, m_ctrlStuName);
	DDX_Control(pDX, IDC_Class_COMBO, m_ctrlClass);
	DDX_Text(pDX, IDC_EDIT_Fanyi, m_strFanyi);
	DDX_Text(pDX, IDC_EDIT_Kaiti, m_strKaiti);
	DDX_Text(pDX, IDC_EDIT_Shixi, m_strShixi);
	DDX_Check(pDX, IDC_FY_bNum_CHECK, m_bFYnum);
	DDX_Check(pDX, IDC_FY_bRelate_CHECK, m_bFYrelate);
	DDX_Check(pDX, IDC_FY_bSubmit_CHECK, m_bFYsubmit);
	DDX_Check(pDX, IDC_KT_bBaseCndi_CHECK, m_bKTbasecndi);
	DDX_Check(pDX, IDC_KT_bPlan_CHECK, m_bKTplan);
	DDX_Check(pDX, IDC_KT_bSubmit_CHECK, m_bKTsubmit);
	DDX_Check(pDX, IDC_SX_bRelate_CHECK, m_bSXrelate);
	DDX_Check(pDX, IDC_SX_bSubmit_CHECK, m_bSXsubmit);
	DDX_CBString(pDX, IDC_COMBO_Fanyi, m_strFYQuality);
	DDX_CBString(pDX, IDC_COMBO_Kaiti, m_strKTunderstand);
	DDX_CBString(pDX, IDC_COMBO_Shixi, m_strSXbehave);
	DDX_CBString(pDX, IDC_StuName_COMBO, m_strStuName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDocChekDlg, CDialog)
	//{{AFX_MSG_MAP(CDocChekDlg)
	ON_BN_CLICKED(IDC_OkBTN, OnOkBTN)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_StuName_COMBO, OnSelchangeStuNameCOMBO)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocChekDlg message handlers

BOOL CDocChekDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ctrlFanyi.InsertString(0,"����");					//�������б���в�������
	m_ctrlFanyi.InsertString(1,"����");
	m_ctrlFanyi.InsertString(2,"һ��");
	m_ctrlFanyi.InsertString(3,"�ϲ�");
	m_ctrlKTunderstand.InsertString(0,"����");			//�������б���в�������
	m_ctrlKTunderstand.InsertString(1,"����");
	m_ctrlKTunderstand.InsertString(2,"һ��");
	m_ctrlKTunderstand.InsertString(3,"�ϲ�");
	m_ctrlShixi.InsertString(0,"����");					//�������б���в�������
	m_ctrlShixi.InsertString(1,"����");    
	m_ctrlShixi.InsertString(2,"һ��");    
	m_ctrlShixi.InsertString(3,"�ϲ�");    
	m_ctrlClass.InsertString(0,"��Ϣ021");				//�������б���в�������
    m_ctrlClass.InsertString(1,"��Ϣ022");
    m_ctrlClass.SetCurSel(0);							//Ĭ��ѡ���һ��
	CString strSQL;										//�����ַ�������
	int i=0;
    strSQL="select * from tab_stu where stu_class='��Ϣ021'";//�����ѯ��Ӧ�༶��������Ϣ��sql���
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))	//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
	    return false;
	}
	while(!stuSet.IsEOF())								//�����¼û�е�ĩβ
	{
		m_ctrlStuName.InsertString(i,stuSet.m_stu_name);//�������ݵ������б����
		stuSet.MoveNext();								//�ƶ���������¼
		i++;
	}
	m_ctrlStuName.SetCurSel(0);							//Ĭ��ѡ��������¼
	stuSet.Close();										//�رռ�¼��
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDocChekDlg::OnOkBTN() 
{
	// TODO: Add your control notification handler code here
	UpdateData();										//��������
	if(!pkaitiSet.IsOpen())								//�򿪼�¼��
		pkaitiSet.Open();	
	pkaitiSet.MoveFirst();								//�ƶ���������¼
	pkaitiSet.AddNew();									//�����µļ�¼
    pkaitiSet.m_stu_name=m_strStuName;					//��¼�ĸ�ֵ
	pkaitiSet.m_kaiti_bBaseCndi=m_bKTbasecndi;
	pkaitiSet.m_kaiti_bPlan=m_bKTplan;
	pkaitiSet.m_kaiti_bSubmit=m_bKTsubmit;
	pkaitiSet.m_kaiti_ColiResult=m_strKaiti;
	pkaitiSet.m_kaiti_Understand=m_strKTunderstand;
	pkaitiSet.Update();									//��������
	pkaitiSet.Requery();								//ˢ�¼�¼��
	pkaitiSet.Close();									//�رռ�¼��
	if(!pShixiSet.IsOpen())								//�򿪼�¼��
		pShixiSet.Open();
	pShixiSet.MoveFirst();								//�ƶ���������¼
	pShixiSet.AddNew();									//�����µļ�¼
    pShixiSet.m_stu_name=m_strStuName;
	pShixiSet.m_shixi_Behave=m_strSXbehave;				//��¼��ֵ
	pShixiSet.m_shixi_bRelate=m_bSXrelate;
	pShixiSet.m_shixi_bSubmit=m_bSXsubmit;
	pShixiSet.m_shixi_Result=m_strShixi;
	pShixiSet.Update();									//���¼�¼
	pShixiSet.Requery();								//ˢ�¼�¼��
	pShixiSet.Close();									//�رռ�¼��
	if(!pFanyiSet.IsOpen())								//�򿪼�¼��
		pFanyiSet.Open();
	pFanyiSet.MoveFirst();								//�ƶ���������¼
	pFanyiSet.AddNew();									//����µļ�¼
    pFanyiSet.m_stu_name=m_strStuName;					//��¼�ĸ�ֵ
	pFanyiSet.m_fanyi_bNum=m_bFYnum;
	pFanyiSet.m_fanyi_bRelate=m_bFYrelate;
	pFanyiSet.m_fanyi_bSubmit=m_bFYsubmit;
	pFanyiSet.m_fanyi_Quality=m_strFanyi;
	pFanyiSet.m_fanyi_Result=m_strKTunderstand;
	pFanyiSet.Update();									//���¼�¼
	pFanyiSet.Requery();								//ˢ�¼�¼��
	pFanyiSet.Close();									//�رռ�¼��
}

void CDocChekDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDD_DocChek_DLG);	
//	CDialog::OnClose();
}

void CDocChekDlg::OnSelchangeStuNameCOMBO() 
{
	// TODO: Add your control notification handler code here
	
}