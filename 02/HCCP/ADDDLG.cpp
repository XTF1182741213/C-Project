// ADDDLG.cpp : implementation file
//

#include "stdafx.h"
#include "HCCP.h"
#include "ADDDLG.h"
#include "ADOConn.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ADDDLG dialog


ADDDLG::ADDDLG(CWnd* pParent /*=NULL*/)
	: CDialog(ADDDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(ADDDLG)
	m_name = _T("");
	m_cno = _T("");
	m_cgrade = 0.0f;
	//}}AFX_DATA_INIT
}


void ADDDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADDDLG)
	DDX_Control(pDX, IDC_XHAO, m_xhao);
	DDX_Control(pDX, IDC_CHECK1, m_xuanze);
	DDX_Control(pDX, IDC_MZ, m_mz);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_CNO, m_cno);
	DDX_Text(pDX, IDC_CGRADE, m_cgrade);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADDDLG, CDialog)
	//{{AFX_MSG_MAP(ADDDLG)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_CBN_SELCHANGE(IDC_XHAO, OnSelchangeXhao)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ADDDLG message handlers

BOOL ADDDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	
	//ͨ��ѡ�����ڵ�Ĳ������ж���ӶԻ��������

	switch(nCount)
	{
	case 1:		
		str.Format("�����Ժϵ");  
		GetDlgItem(IDC_CHECK1)->ShowWindow(false);
		GetDlgItem(IDC_XHAO)->ShowWindow(false);
		GetDlgItem(IDC_KECHENGHAO)->ShowWindow(false);
		GetDlgItem(IDC_XXUEFEN)->ShowWindow(false);
		GetDlgItem(IDC_CNO)->ShowWindow(false);
		GetDlgItem(IDC_CGRADE)->ShowWindow(false);
		SetWindowText(str);
		m_mz.SetWindowText("��Ժϵ����");break;
	case 2:
		str.Format("����°༶");
		GetDlgItem(IDC_CHECK1)->ShowWindow(false);
		GetDlgItem(IDC_XHAO)->ShowWindow(false);
		GetDlgItem(IDC_KECHENGHAO)->ShowWindow(false);
		GetDlgItem(IDC_XXUEFEN)->ShowWindow(false);
		GetDlgItem(IDC_CNO)->ShowWindow(false);
		GetDlgItem(IDC_CGRADE)->ShowWindow(false);
		SetWindowText(str);
		m_mz.SetWindowText("�°༶����");break;
	case 3:
		str.Format("����¿γ�");
		GetDlgItem(IDC_XHAO)->ShowWindow(false);
		SetWindowText(str);
		m_mz.SetWindowText("�¿γ�����");break;
	case 4:		
		str.Format("����³ɼ�");
		GetDlgItem(IDC_CHECK1)->ShowWindow(false);
		GetDlgItem(IDC_KECHENGHAO)->SetWindowText("ѧ��ѧ�ţ�");
		GetDlgItem(IDC_XXUEFEN)->SetWindowText("�γ̳ɼ���");
		GetDlgItem(IDC_CNO)->ShowWindow(false);
		SetWindowText(str);
		XueSheng();
		m_mz.SetWindowText("ѧ������");break;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*---------------------------��ʼ����ӳɼ��Ի��������-----------------------------*/

void ADDDLG::XueSheng()
{
	k=0;
	str2=leaf11;  //ͨ��ȫ�ֱ�����ȡ�����ѡ��Ľڵ�ĸ��ڵ���Ϣ
	str2.TrimRight();
	str.Format("select * from student where sclass='%s'",str2);  //��ȡ��ѡȡ�ÿγ̵�ѧ����Ϣ
	sQL=(_bstr_t)str;
	m_pRc=myado.GetRecordSet(sQL);  //ִ��sql��䲢��ȡstudent��¼��
	leaf=m_pRc->GetCollect("sname");  //��ȡ��¼����ѧ������	
	str1=(LPCTSTR)(_bstr_t)leaf;  
	str1.TrimRight();
	m_name=str1;  //��ʼ����ʾ��һ��ѧ��������
	leaf=m_pRc->GetCollect("sno");  //��ȡ��¼����ѧ��ѧ�� 		
	str1=(LPCTSTR)(_bstr_t)leaf;
	str1.TrimRight();
	zhao=str1;
	do  //ͨ��whileѭ����ȡ��¼�����ݲ������������˵�����
	{
		leaf=m_pRc->GetCollect("sno");		
		str1=(LPCTSTR)(_bstr_t)leaf;
		str1.TrimRight();
		m_xhao.InsertString(k,str1);  //�����Ͽ���Ŀ
		m_pRc->MoveNext();  //ָ����һ����¼
		k++;
	}
	while(!m_pRc->adoEOF);

	m_xhao.SetCurSel(0);  //��ʼ��combo�ؼ�Ϊ��ʾ��һ����¼
	UpdateData(false);
}

/*---------------------------ͨ��check�ؼ��л�����³�Ա���¿γ�-----------------------------*/

void ADDDLG::OnCheck1() 
{
	CString str;
	if(m_xuanze.GetCheck())
	{
		str.Format("����³�Ա");
		GetDlgItem(IDC_KECHENGHAO)->SetWindowText("ѧ��ѧ�ţ�");
		GetDlgItem(IDC_XXUEFEN)->ShowWindow(false);
		GetDlgItem(IDC_XXUEFEN)->SetWindowText("�γ̳ɼ���");
		GetDlgItem(IDC_CGRADE)->ShowWindow(false);
		SetWindowText(str);
		m_mz.SetWindowText("��ѧ������");
		flag001=false;
	}
	else
	{
		str.Format("����¿γ�");
		GetDlgItem(IDC_KECHENGHAO)->SetWindowText("�γ̺ţ�");
		GetDlgItem(IDC_XXUEFEN)->ShowWindow(true);
		GetDlgItem(IDC_XXUEFEN)->SetWindowText("ѧ�֣�");
		GetDlgItem(IDC_CGRADE)->ShowWindow(true);
		SetWindowText(str);
		m_mz.SetWindowText("�¿γ�����");
		flag001=true;
	}
}

/*---------------------------Ϊcombo�ؼ������Ϣ-----------------------------*/

void ADDDLG::OnSelchangeXhao() 
{
	
	CString str;
	int n=m_xhao.GetCurSel();  //��ȡ��ѡ��combo�ؼ������ݵı��
	m_xhao.GetLBText(n,zhao);  //ͨ����Ż�ȡ��ѡ����Ŀ������
	str.Format("select sname from student where sno='%s'",zhao);  //��student���в��Ҷ�Ӧѧ�ŵļ�¼
	_bstr_t vSQL;
	vSQL=(_bstr_t)str;
	m_pRc=myado.GetRecordSet(vSQL);  //ִ��sql��䲢��ȡ��¼��
	
	leaf=m_pRc->GetCollect("sname");  //��ȡ��¼����sname������
	str1=(LPCTSTR)(_bstr_t)leaf;  
	str1.TrimRight();
	
	m_name=str1;  //��ʾѧ������
	UpdateData(false);
}
