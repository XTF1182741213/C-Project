// SysLgnDlg.cpp : implementation file
//ϵͳ��½�Ի���

#include "stdafx.h"
#include "gradudemis.h"
#include "SysLgnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysLgnDlg dialog


CSysLgnDlg::CSysLgnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysLgnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysLgnDlg)
	m_strUser = _T("");
	m_strPasswd = _T("");
	//}}AFX_DATA_INIT
}


void CSysLgnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysLgnDlg)
	DDX_Control(pDX, IDC_UserUnit_COMBO, m_ctrlUserUnit);
	DDX_Control(pDX, IDC_UserType_COMBO, m_ctrlUserType);
	DDX_Control(pDX, IDC_PASSWORD, m_ctrlPasswd);
	DDX_Control(pDX, IDC_User_COMBO, m_ctrlUser);
	DDX_CBString(pDX, IDC_User_COMBO, m_strUser);
	DDX_Text(pDX, IDC_PASSWORD, m_strPasswd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysLgnDlg, CDialog)
	//{{AFX_MSG_MAP(CSysLgnDlg)
	ON_BN_CLICKED(IDC_LoginBtn, OnLoginBtn)
	ON_CBN_SELCHANGE(IDC_UserType_COMBO, OnSelchangeUserTypeCOMBO)
	ON_CBN_SELCHANGE(IDC_UserUnit_COMBO, OnSelchangeUserUnitCOMBO)
	ON_BN_CLICKED(IDC_ExitBtn, OnExitBtn)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysLgnDlg message handlers

BOOL CSysLgnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//�������ݵ��û����е������б�򣬲�Ĭ�ϵ�ǰѡ�е�һ�
	m_ctrlUserType.InsertString(0," ѧ   ��");
	m_ctrlUserType.InsertString(1," ��   ʦ");
    m_ctrlUserType.InsertString(2,"�� �� Ա");
    m_ctrlUserType.SetCurSel(0);
	//�������ݵ����ڵ�λ�������б�򣬲�Ĭ�ϵ�ǰѡ�е�һ�
	m_ctrlUserUnit.InsertString(0,"��Ϣ021");
    m_ctrlUserUnit.InsertString(1,"��Ϣ022");
	m_ctrlUserUnit.SetCurSel(0);
//*************************************
	CString strSQL;													//�����ַ����洢sql��䡣
	int i=0;														//���������������
	UpdateData();													//��������
    strSQL="select * from tab_password where user_unit='��Ϣ021'";	//sql���ѡ�����ڵ�λΪ����Ϣ021������������
	if(!passwdSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))				//��sql���򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");								//�쳣����
	    return false;
	}
	while(!passwdSet.IsEOF())										//�����¼�������һ���������ȡ
	{
		m_ctrlUser.InsertString(i,passwdSet.m_lgn_user);			//�����ݲ��뵽�û����������б����
		passwdSet.MoveNext();										//�ƶ�����һ����¼
		i++;														//������һ
	}
    m_ctrlUser.SetCurSel(0);										//��ʼ��ѡ�е�һ��

    passwdSet.Close();												//�رռ�¼��
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//��½��ť����Ϣ��Ӧ����
void CSysLgnDlg::OnLoginBtn()						
{
	// TODO: Add your control notification handler code here
	CString strSQL;											//�����ַ����洢sql���
	UpdateData();											//��������
	if(m_strUser.IsEmpty())									//�ж�m_strUser�е������Ƿ�Ϊ��						
	{		
		MessageBox("�������û�����");
		m_ctrlUser.SetFocus();								//����m_strUse�����뽹��
		return;
	}
	if(m_strPasswd.IsEmpty())								//�ж�m_strPasswd�е������Ƿ�Ϊ��
	{
		MessageBox("���������룡");
		m_ctrlPasswd.SetFocus();							//����m_strPasswd�����뽹��
		return;	
	}
    strSQL.Format("select * from tab_password where lgn_user='%s' AND lgn_passwd='%s'",m_strUser,m_strPasswd);
	//����sql��� ��tab_password����ѡ���뵱ǰ�����û���������ƥ�������
	if(!passwdSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))		//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	if(passwdSet.GetRecordCount()==0)						//�����¼Ϊ0���ʾû��ƥ�������
	{
		//���������
		passwdSet.Close();									//�رռ�¼����
		MessageBox("����������������룡");
		m_strPasswd="";										//��������
		m_ctrlPasswd.SetFocus();							//���ý���
		UpdateData(false);									//��������
	}
	else
	{
		//������ȷ����������̨���������û�Ȩ��
//	    m_bIsAdmin=passwdSet.m_lgn_isAdmin;
		passwdSet.Close();									//�رռ�¼��
//		MessageBox("���Խ���������̨");						
		strExternUser=m_strUser;							//���浱ǰ��½���û���
		OnCancel();											//�رյ�ǰ�Ի���										
	}
}

//�û����͵������б��ѡ�е���Ϣ��Ӧ����
void CSysLgnDlg::OnSelchangeUserTypeCOMBO() 
{
	// TODO: Add your control notification handler code here
	CString strUserType;									//�����ַ������浱ǰѡ�е�����
	m_ctrlUserType.GetWindowText(strUserType);				//��ȡm_ctrlUserType�е��ı�
	if(strUserType==" ѧ   ��")								//�ж��û�����
	{
		bstuExternFlag=true;								//ȫ�ֱ����ӱ��
		MessageBox("DDDDD");
		int num1=0;											//�������α���
    	num1=m_ctrlUserUnit.GetCount();						//��ȡm_ctrlUserUnit�����������б�������ݵ�����
    	for(int i=0;i<num1;i++)								//ɾ������
		  m_ctrlUserUnit.DeleteString(0);

		m_ctrlUserUnit.InsertString(0,"��Ϣ021");			//�������б���в�������
		m_ctrlUserUnit.InsertString(1,"��Ϣ022");
        m_ctrlUserUnit.SetCurSel(0);						//Ĭ��ѡ�е�һ��
	}
	else if(strUserType==" ��   ʦ")						//ͬ��	
	{	
		btecrExternFlag=true;							
		int num2=0;
     	num2=m_ctrlUserUnit.GetCount();
    	for(int i=0;i<num2;i++)
		  m_ctrlUserUnit.DeleteString(0);

		m_ctrlUserUnit.InsertString(0,"��Ϣ������");
		m_ctrlUserUnit.InsertString(1,"���������");
		m_ctrlUserUnit.InsertString(2,"��ѧ������");
        m_ctrlUserUnit.SetCurSel(0);
	}
	else													//ͬ��
	{
		badminExternFlag=true;
		int num3=0;
     	num3=m_ctrlUserUnit.GetCount();
    	for(int i=0;i<num3;i++)
		  m_ctrlUserUnit.DeleteString(0);

		m_ctrlUserUnit.InsertString(0,"��Ϣ��ѧϵ");
        m_ctrlUserUnit.SetCurSel(0);
	}
	m_ctrlUserUnit.SetCurSel(0);
}

//�û���λ����Ϣ��Ӧ����
void CSysLgnDlg::OnSelchangeUserUnitCOMBO() 
{
	// TODO: Add your control notification handler code here
    CString strUserUnit,strSQL;							//����sql���
    m_ctrlUserUnit.GetWindowText(strUserUnit);			//��ȡ�û���λ���ı�

	if(strUserUnit=="��Ϣ021")
	{	
		MyAddComboBoxItem(strUserUnit);        
	}
	else if(strUserUnit=="��Ϣ022")
	{
		MyAddComboBoxItem(strUserUnit);
	}
	else if(strUserUnit=="��Ϣ������")
	{
		MyAddComboBoxItem(strUserUnit);
	}
	else if(strUserUnit=="���������")
	{		
		MyAddComboBoxItem(strUserUnit);
	}
	else if(strUserUnit=="��ѧ������")
	{	
		MyAddComboBoxItem(strUserUnit);
	}
	else if(strUserUnit=="��Ϣ��ѧϵ")
	{
		MyAddComboBoxItem(strUserUnit);
	}
}

//�û��Զ��庯������û�������Ӧ�������б���в���Ϊ�û���λ
void CSysLgnDlg::MyAddComboBoxItem(CString str)
{
	//���Combo�ؼ�����
	int numUser=0;
	numUser=m_ctrlUser.GetCount();
	for(int i=0;i<numUser;i++)											//ɾ���û��������е���Ϣ
		m_ctrlUser.DeleteString(0);
	//���Combo�ؼ�����
	CString strSQL;														//��������洢sql���
	strSQL.Format("select * from tab_password where user_unit='%s'",str);//��tab_password����ѡ���û�����Ϊ���ݱ���ֵ����������
	if(!passwdSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))					//�Ե�ǰsql���򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");
		return;
	}
	while(!passwdSet.IsEOF())											//�������е�����
	{
		m_ctrlUser.AddString(passwdSet.m_lgn_user);						//���û�����ӵ��б����
		passwdSet.MoveNext();											//�ƶ�����������¼
	}
	passwdSet.Close();													//�رռ�¼��
}

//�Ƴ���ť����Ϣ��Ӧ����
void CSysLgnDlg::OnExitBtn()						
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

//���ON_PAINT��Ϣ��ӱ�������Ϣ
void CSysLgnDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CPaintDC dc1(this); // device context for painting
	//**********************************************
	CRect rect;		
	GetClientRect(&rect);												//��ȡ�ͻ�����С
	HBITMAP hbitmap;													//������
	hbitmap=::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP5)); //��ȡbmpͼƬ
	HDC hMenDC=::CreateCompatibleDC(NULL);								//�����Ը����ݵ�DC
	SelectObject(hMenDC,hbitmap);										//ѡ���豸����������
	::StretchBlt(dc.m_hDC,0,0,1024,768,hMenDC,0,0,1024,768,SRCCOPY);	//����ͼƬ
	::DeleteDC(hMenDC);													//�ͷž��
	::DeleteObject(hbitmap);
	// Do not call CDialog::OnPaint() for painting messages
}

