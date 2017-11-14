// StudentTab1.cpp : implementation file
#include "stdafx.h"
#include "gradudemis.h"
#include "StudentTab1.h"
#include "StudentTab2.h"
#include"StudentSet.h"
#include "StudentTab2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentTab1 dialog


CStudentTab1::CStudentTab1(CWnd* pParent /*=NULL*/)
: CDialog(CStudentTab1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStudentTab1)
	m_strcombo1 = _T("");
	m_strCombo2 = _T("");
	//}}AFX_DATA_INIT
}


void CStudentTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentTab1)
	DDX_Control(pDX, IDC_STUTAB1_COMBO2, m_ctrlCombo2);
	DDX_Control(pDX, IDC_COMBO1, m_StuTab1Combo);
	DDX_Control(pDX, IDC_LIST1, m_StuTab1listctl);

	DDX_CBString(pDX, IDC_COMBO1, m_strcombo1);
	DDX_CBString(pDX, IDC_STUTAB1_COMBO2, m_strCombo2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStudentTab1, CDialog)
//{{AFX_MSG_MAP(CStudentTab1)
    ON_BN_CLICKED(IDC_STUTAB1_BUTTON, OnStutab1Button)
//	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentTab1 message handlers

BOOL CStudentTab1::OnInitDialog() 
{	
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
    pSet.Open();												//�򿪼�¼��
	m_StuTab1listctl.InsertColumn(0,"ѧ��",LVCFMT_LEFT,70,0);	//���б�ؼ������б����趨��ȶ��뷽ʽ
	m_StuTab1listctl.InsertColumn(1,"����",LVCFMT_LEFT,60,0);
	m_StuTab1listctl.InsertColumn(2,"�Ա�",LVCFMT_LEFT,50,0);
	m_StuTab1listctl.InsertColumn(3,"����",LVCFMT_LEFT,50,0);
    m_StuTab1listctl.InsertColumn(4,"�༶",LVCFMT_LEFT,80,0);
	m_StuTab1listctl.InsertColumn(5,"רҵ",LVCFMT_LEFT,110,0);
	m_StuTab1listctl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//�����趨����ѡ������
    int i=0;													//�������α���
	pSet.MoveFirst();											//��¼���ƶ���������¼
	while(!pSet.IsEOF())										//�����¼����ĩβ
	{   
		m_StuTab1listctl.InsertItem(i,pSet.m_stu_id);			//���б�ؼ��в�������
		m_StuTab1listctl.SetItemText(i,1,pSet.m_stu_name);
		m_StuTab1listctl.SetItemText(i,2,pSet.m_stu_sex);
		m_StuTab1listctl.SetItemText(i,3,pSet.m_stu_age);
		m_StuTab1listctl.SetItemText(i,4,pSet.m_stu_class);
		m_StuTab1listctl.SetItemText(i,5,pSet.m_stu_depart);
        pSet.MoveNext();										//�ƶ���������¼
        i++;	
	}
	pSet.Close();												//�رռ�¼��
    CString str[6]={"ѧ��","����","�Ա�","����","�༶","רҵ"};	//�����ַ������鲢��ʼ��
	for(int j=0;j<6;j++)										//���ַ�����������ݲ��뵽�����б����
	{
		m_StuTab1Combo.InsertString(j,str[j]);
	}
	m_StuTab1Combo.SetCurSel(0);								//����Ĭ��ѡ�е�һ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStudentTab1::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();											//��������
	int nIndex=m_StuTab1Combo.GetCurSel();					//��ȡ�����б����ѡ�е�������
	switch(nIndex)					
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		{
			MyClearCombo2();								//���ú�����������б���е�����
			m_ctrlCombo2.InsertString(0,"��");				//��������
		    m_ctrlCombo2.InsertString(1,"Ů");
		    m_ctrlCombo2.SetCurSel(0);						//����Ĭ��ѡ��
		}
		break;
	case 3:
		{
			CString strI;									//�����ַ�������
			MyClearCombo2();								//���ú�������б���е�����
			for(int i=0;i<30;i++)
			{
				strI.Format("%d",i+10);						//����ת���ַ���
				m_ctrlCombo2.InsertString(i,strI);			//��������
			}
		    m_ctrlCombo2.SetCurSel(0);						//Ĭ�ϵ�һ��ѡ��
		}
		break;
	case 4:
		{	
			MyClearCombo2();								//���ú�������б���е�����
			m_ctrlCombo2.InsertString(0,"��Ϣ021");			//��������
		    m_ctrlCombo2.InsertString(1,"��Ϣ022");
		    m_ctrlCombo2.SetCurSel(0);						//Ĭ�ϵ�һ��ѡ��
		}
		break;
	case 5:
		{
			MyClearCombo2();								//���ú�������б���е�����
			m_ctrlCombo2.InsertString(0,"��Ϣ������ѧ");	//��������
		    m_ctrlCombo2.InsertString(1,"Ӧ����ѧ");	
			m_ctrlCombo2.InsertString(2,"Ӧ������");
		    m_ctrlCombo2.SetCurSel(0);						//Ĭ�ϵ�һ��ѡ��
		}
		break;
	default:break;
	}
}

void CStudentTab1::MyClearCombo2()
{
	int nIndex=m_StuTab1Combo.GetCount();		//�õ��б���е����ݵ�����
	for(int i=0;i<nIndex;i++)
	{
		m_ctrlCombo2.DeleteString(0);			//ɾ������
	}
}

void CStudentTab1::OnStutab1Button() 
{
	// TODO: Add your control notification handler code here
	int nIndex=m_StuTab1Combo.GetCurSel();		//�õ������б��ѡ�е�����
	switch(nIndex) 
	{
	   case 0:
		   SelectItem(0);  break;				//���ú���	   
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
	}    
}

void CStudentTab1::SelectItem(int n)
{
	char filter[60];							//�����ַ�����
	CString str[6]={"tab_stu.stu_id='%s'","tab_stu.stu_name='%s'","tab_stu.stu_sex='%s'",
		"tab_stu.stu_age='%s'","tab_stu.stu_class='%s'","tab_stu.stu_depart='%s'"};
												//�����ַ������鲢��ֵ��ֵ
	CString strEdit;							//�����ַ�������
    UpdateData();								//��������
	pSet.Open();								//�򿪼�¼��
	wsprintf(filter,str[n],m_strCombo2);		//��ʽ���ַ���
	pSet.m_strFilter=filter;					//��¼��ֵ
	pSet.Requery();								//ˢ�¼�¼��
	if(m_strCombo2=="")							//�ж�
	{
		MessageBox("��ѯ����Ϊ�գ�������ؼ��ʣ�");//��Ϣ��ʾ
		pSet.Close();							//�رռ�¼��
		return;
	}
	else 
	{	
		if(pSet.IsEOF())						//�����¼ָ��ĩβ
			AfxMessageBox("Ҫ���ҵļ�¼�����ڣ�");
		else
		{
			m_StuTab1listctl.DeleteAllItems();	//ɾ������
			int i=0;
			while(!pSet.IsEOF())				//��¼���û��ָ�����
			{
				m_StuTab1listctl.InsertItem(i,pSet.m_stu_id);		//�������ݵ��б���
				m_StuTab1listctl.SetItemText(i,1,pSet.m_stu_name);
				m_StuTab1listctl.SetItemText(i,2,pSet.m_stu_sex);
				m_StuTab1listctl.SetItemText(i,3,pSet.m_stu_age);
				m_StuTab1listctl.SetItemText(i,4,pSet.m_stu_class);		
				m_StuTab1listctl.SetItemText(i,5,pSet.m_stu_depart);
				pSet.MoveNext();				//�ƶ���������¼
				i++;
			}
			UpdateData(false);					//��������
		}
		pSet.Close();							//�رռ�¼��
	}
}

void CStudentTab1::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i=pNMListView->iItem;					//��ȡѡ�е���
	selectID=m_StuTab1listctl.GetItemText(i,0); //��ȡѡ���е�һ����ı�
	*pResult = 0;
}
