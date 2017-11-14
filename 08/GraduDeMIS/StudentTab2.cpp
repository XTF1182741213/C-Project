// StudentTab2.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "StudentTab2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentTab2 dialog

CStudentTab2::CStudentTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CStudentTab2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStudentTab2)
	m_StuTab2_ID = _T("");
	m_StuTab2_NAME = _T("");
//	m_StuTab2_DEPART = _T("");
//	m_StuTab2_AGE = _T("");
	m_strSex = _T("");
	m_strClass = _T("");
	m_strAge = _T("");
	m_strDepart = _T("");
	//}}AFX_DATA_INIT
    bAddBtnFlag=bEditBtnFlag=false;

}
void CStudentTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentTab2)
	DDX_Control(pDX, IDC_Depart_COMBO, m_ctrlDepart);
	DDX_Control(pDX, IDC_Age_COMBO, m_ctrlAge);
	DDX_Control(pDX, IDC_Class_COMBO, m_ctrlClass);
	DDX_Control(pDX, IDC_Sex_COMBO, m_ctrlSex);
	DDX_Control(pDX, IDC_EDIT_ID, m_StuTab2EditCtl);
	DDX_Text(pDX, IDC_EDIT_ID, m_StuTab2_ID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_StuTab2_NAME);
//	DDX_Text(pDX, IDC_EDIT_DEPART, m_StuTab2_DEPART);
//	DDX_Text(pDX, IDC_EDIT_AGE, m_StuTab2_AGE);
	DDX_CBString(pDX, IDC_Sex_COMBO, m_strSex);
	DDX_CBString(pDX, IDC_Class_COMBO, m_strClass);
	DDX_CBString(pDX, IDC_Age_COMBO, m_strAge);
	DDX_CBString(pDX, IDC_Depart_COMBO, m_strDepart);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CStudentTab2, CDialog)
	//{{AFX_MSG_MAP(CStudentTab2)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, OnButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentTab2 message handlers

BOOL CStudentTab2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
    MyBtnHide(1,1,1,0,0);						//�û��Զ��庯�����ư�ť����������ʾ				
    m_ctrlSex.AddString("��");					//�������
    m_ctrlSex.AddString("Ů");					//�������
    m_ctrlSex.SetCurSel(0);						//����Ĭ��ѡ��
    m_ctrlClass.AddString("��Ϣ021");			//�������
    m_ctrlClass.AddString("��Ϣ022");
    m_ctrlClass.SetCurSel(0);					//����Ĭ��ѡ��
	CString strI;								//�����ַ�������
	for(int i=0;i<30;i++)
	{
		strI.Format("%d",i+10);
		m_ctrlAge.InsertString(i,strI);			//������ݵ��ؼ���
	}
    m_ctrlAge.SetCurSel(0);						//����Ĭ��ѡ��
	m_ctrlDepart.InsertString(0,"��Ϣ������ѧ");//��������
	m_ctrlDepart.InsertString(1,"Ӧ������");
	m_ctrlDepart.InsertString(2,"Ӧ����ѧ");
    m_ctrlDepart.SetCurSel(0);					//����Ĭ��ѡ��

	if(!pSet2.IsOpen())							//�򿪼�¼��
		pSet2.Open();	
	pSet2.MoveFirst();							//�ƶ��������¼
	m_StuTab2_ID=pSet2.m_stu_id;				//�����ĸ�ֵ
	m_StuTab2_NAME=pSet2.m_stu_name;	
	m_strSex=pSet2.m_stu_sex;
    m_strAge=pSet2.m_stu_age;
	m_strDepart=pSet2.m_stu_depart;    
	m_strClass=pSet2.m_stu_class;
	pSet2.Close();								//�رռ�¼��
	UpdateData(false);							//��������
	return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX Property Pages should return FALSE
}

void CStudentTab2::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here

   MyBtnHide(0,0,0,1,1);						//��ť����������ʾ
   bAddBtnFlag=true;							//���ı��
   MyClearItem();								//������пؼ��е�����

}

void CStudentTab2::OnButtonEdit() 
{

	// TODO: Add your control notification handler code here
	MyBtnHide(0,0,0,1,1);						//��ť����������ʾ
	bEditBtnFlag=true;							//���ı��

}

void CStudentTab2::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	MyBtnHide(0,0,0,1,1);						//��ť����������ʾ
	pSet2.Open();								//�򿪼�¼��
	if(!pSet2.CanUpdate())						//�ж�
	{
		AfxMessageBox("ɾ��ʧ�ܣ���ѡ��ĳ����¼");
		pSet2.Close();
		return;
	}
	if(MessageBox("ȷ��Ҫɾ����ɾ���󲻿ɻָ���������صĿ����ϢҲ����ɾ����",
		          "ע�⣡",MB_YESNO)!=IDYES)
	{  	
		pSet2.Close();							//�رռ�¼��
		MyBtnHide(1,1,1,0,0);					//��ť����������ʾ
		return;	
	};
	while(!pSet2.IsEOF())						//�����¼û�е�ĩβ
	{
		if(pSet2.m_stu_id==selectID)		
		{
			pSet2.Delete();						//ɾ������
			MyClearItem();						//���
		}
		else
			pSet2.MoveNext();					//�ƶ�������
	}
	pSet2.Close();								//�رռ�¼��
	MyBtnHide(1,1,1,0,0);						//��ť����������ʾ
}

void CStudentTab2::OnButtonSave() 
{
	if(bEditBtnFlag)							//�жϱ��
	{	
		UpdateData();							//��������
		bEditBtnFlag=false;						//���ı��
	    if(!pSet2.IsOpen())						//�򿪼�¼��
		   pSet2.Open();
        pSet2.MoveFirst();						//�ƶ�����һ��
		pSet2.Edit();							//�༭��¼
		while(!pSet2.IsEOF())					//�����¼û�е�ĩβ
		{
			if(pSet2.m_stu_id==selectID)	
			{	
				pSet2.m_stu_id=m_StuTab2_ID;	//��¼��ֵ
				pSet2.m_stu_name=m_StuTab2_NAME;
				pSet2.m_stu_sex=m_strSex;
				pSet2.m_stu_age=m_strAge;
				pSet2.m_stu_class=m_strClass;
				pSet2.m_stu_depart=m_strDepart;	
				pSet2.Update();					//��ϸ����
				pSet2.Requery();				//ˢ�¼�¼��
				break;
			}
			else
				pSet2.MoveNext();				//�����ƶ�
				AfxMessageBox(selectID);
		}
		pSet2.Close();							//�رռ�¼��
		MessageBox("�޸ĳɹ���","��ʾ��Ϣ",MB_OK);//��Ϣ��ʾ
	}
	MyBtnHide(1,1,1,0,0);						//��ť����������ʾ
}

void CStudentTab2::OnButtonCancle() 
{

	MyBtnHide(1,1,1,0,0);						//��ť����������ʾ
}

CStudentTab2::MyClearItem()
{
	UpdateData();								//��������
	m_StuTab2_ID="";            //�Զ���ǰ������ѧ��???	
    m_StuTab2_NAME="";							//�����Ϣ
    m_strSex="";
    m_strAge="";
    m_strClass="";
    m_strDepart="";   
	UpdateData(false);							//��������
}

void CStudentTab2::OnShow()
{
	if(!pSet2.IsOpen())							//�򿪼�¼��
	pSet2.Open();
	while(!pSet2.IsEOF())						//��¼����ĩβ
	{
		if(pSet2.m_stu_id==selectID)
		{
			m_StuTab2_ID=pSet2.m_stu_id;		///������ֵ
			m_StuTab2_NAME=pSet2.m_stu_name;
			m_strSex=pSet2.m_stu_sex;
			m_strAge=pSet2.m_stu_age;
			m_strDepart=pSet2.m_stu_depart;    
			m_strClass=pSet2.m_stu_class;
			break;
		}
		else
			pSet2.MoveNext();					//�����ƶ�
	}
	pSet2.Close();								//�رռ�¼��
	UpdateData(FALSE);							//��������
}

CStudentTab2::MyBtnHide(bool bBtnAdd,bool bBtnEdit,bool bBtnDel,bool bBtnSave,bool bBtnCancel)
{
	CButton *pBtnAdd=(CButton *)GetDlgItem(IDC_BUTTON_ADD);			//��ȡ��ť��ָ��
	CButton *pBtnDel=(CButton *)GetDlgItem(IDC_BUTTON_DEL);
	CButton *pBtnEdit=(CButton *)GetDlgItem(IDC_BUTTON_EDIT);
	CButton *pBtnSave=(CButton *)GetDlgItem(IDC_BUTTON_SAVE);
	CButton *pBtnCancel=(CButton *)GetDlgItem(IDC_BUTTON_CANCLE);
	
	if(bBtnAdd)  
		pBtnAdd->ShowWindow(SW_SHOW);						//��ʾ��ť
	else
		pBtnAdd->ShowWindow(SW_HIDE);						//���ذ�ť

	if(bBtnEdit)  
		pBtnEdit->ShowWindow(SW_SHOW);						//��ʾ��ť
	else
		pBtnEdit->ShowWindow(SW_HIDE);						//���ذ�ť

	if(bBtnDel)  
		pBtnDel->ShowWindow(SW_SHOW);						//��ʾ��ť
	else
		pBtnDel->ShowWindow(SW_HIDE);						//���ذ�ť

	if(bBtnSave)  
		pBtnSave->ShowWindow(SW_SHOW);						//��ʾ��ť
	else
		pBtnSave->ShowWindow(SW_HIDE);						//���ذ�ť

	if(bBtnCancel)  
		pBtnCancel->ShowWindow(SW_SHOW);					//��ʾ��ť
	else
		pBtnCancel->ShowWindow(SW_HIDE);						//���ذ�ť
}
