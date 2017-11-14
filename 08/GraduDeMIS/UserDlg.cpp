// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog
char Label;									//�����û�ѡ��Ĳ���

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_strPass = _T("");
	m_strRePass = _T("");
	m_user = _T("");
	m_IsAdmin = FALSE;
	//}}AFX_DATA_INIT
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_USER1, m_ctrlUser);
	DDX_Control(pDX, IDC_Passwd, m_ctrlPass);
	DDX_Control(pDX, IDC_User_LIST, m_ctrlUserList);
	DDX_Text(pDX, IDC_Passwd, m_strPass);
	DDX_Text(pDX, IDC_RePass, m_strRePass);
	DDX_Text(pDX, IDC_USER1, m_user);
	DDX_Check(pDX, IDC_IsAdmin_CHECK, m_IsAdmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_Exit_BTN, OnExitBTN)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_Cancel_BTN, OnCancelBTN)
	ON_BN_CLICKED(IDC_IsAdmin_CHECK, OnIsAdminCHECK)
	ON_BN_CLICKED(IDC_Save_BTN, OnSaveBTN)
	ON_LBN_SELCHANGE(IDC_User_LIST, OnSelchangeUserLIST)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//  m_ctrlUser.EnableWindow(false);
 
	if(!passwdSet.IsOpen())											//�򿪼�¼��
		passwdSet.Open();
	   passwdSet.MoveFirst();										//�ƶ�����һ����¼
	while(!passwdSet.IsEOF())										//������¼��
	{	
		int nIndex=m_ctrlUserList.AddString(passwdSet.m_lgn_user);	//���û�����ӵ��б���
		UserInfo structSet;											//�����û���Ϣ�ṹ����
		structSet.user=passwdSet.m_lgn_user;						//�����ĳ�ʼ��
		structSet.passwd=passwdSet.m_lgn_passwd;
		structSet.repasswd=passwdSet.m_lgn_passwd;
        structSet.bIsAdmin=passwdSet.m_lgn_isAdmin;
		m_ctrlUserList.SetItemDataPtr(nIndex,new UserInfo(structSet));//����һ��ָ������û���Ϣ
		passwdSet.MoveNext();										//�ƶ���������¼
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::OnExitBTN() 
{
	// TODO: Add your control notification handler code here
	OnCancel();														//�˳�
}

void CUserDlg::OnSelchangeUserLIST() 
{
	// TODO: Add your control notification handler code here

	int nIndex=m_ctrlUserList.GetCurSel();							//��ȡѡ���������
	if(nIndex!=LB_ERR)												//���û���׳��쳣
	{
		UserInfo *structSet=(UserInfo *)m_ctrlUserList.GetItemDataPtr(nIndex);//ȡ���û���Ϣ
		m_user=structSet->user;										//�û���Ϣ�����ĸ�ֵ
		m_strPass=structSet->passwd;
		m_strRePass=structSet->repasswd;
        m_IsAdmin=structSet->bIsAdmin;
		UpdateData(false);											//��������
	}
}

void CUserDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
   m_user="";														//��ձ༭��
   m_strPass="";
   m_strRePass="";
   m_IsAdmin=false;													//���ò�Ϊ����Ա
// m_ctrlUser.EnableWindow(true);
   m_ctrlUser.SetFocus();											//���ý���
   UpdateData(false);												//��������
   Label='A';														//�����û���ѡ�Ĳ���
}

void CUserDlg::OnEdit()									
{
	// TODO: Add your control notification handler code here
	//	UpdateData(false);
	Label='E';														//�����û���ѡ�Ĳ���
}

void CUserDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	
}

void CUserDlg::OnSaveBTN()											//���水ť
{
	// TODO: Add your control notification handler code here
	UpdateData();													//��������

	if(m_user.IsEmpty())											//�ж��Ƿ�Ϊ��
	{
		MessageBox("��������Ϊ��");									//������ʾ
		m_ctrlUser.SetFocus();										//���ý���
		return;														//����
	}
	if(m_strPass=="")												//�ж��Ƿ�Ϊ��
	{
    	MessageBox("���벻��Ϊ�գ����������룡");					//������ʾ
		m_ctrlPass.SetFocus();										//���ý���
		return;														//����
	}

	switch (Label)													//�û���ѡ�Ĳ���
	{
	case 'A':
		{	//������û�		
			m_user.TrimLeft();										//ȥ����ߵĿո�
			m_user.TrimRight();										//ȥ���ұߵĿո�
			if((m_ctrlUserList.FindString(-1,m_user))!=LB_ERR)		//�ж��Ƿ��Ѿ����
			{
				MessageBox("�б����������ͬ���������������");		//������ʾ
				m_user.Empty();										//��ձ༭��
                m_strPass.Empty();
                m_strRePass.Empty();
				UpdateData(false);									//��������
                m_ctrlUser.SetFocus();								//���ý���
				return;	
			}

			int nIndex=m_ctrlUserList.AddString(m_user);			//û����������
			UserInfo structSet;										//�����û���Ϣ�ṹ
			structSet.user=m_user;									//�ṹ�帳ֵ
			structSet.passwd=m_strPass;
			structSet.repasswd=m_strRePass;
			structSet.bIsAdmin=m_IsAdmin;			
			m_ctrlUserList.SetItemDataPtr(nIndex,new UserInfo(structSet));//����ָ��
            //д�����ݿ�
			if(!passwdSet.IsOpen())
				passwdSet.Open();									//�򿪼�¼��
		      passwdSet.MoveFirst();								//�ƶ�����һ����¼
			  passwdSet.AddNew();									//����¼�¼
			  passwdSet.m_lgn_user=structSet.user;					//���и��ֶεĸ�ֵ
			  passwdSet.m_lgn_passwd=structSet.passwd;
			  passwdSet.m_lgn_isAdmin=structSet.bIsAdmin;
			  passwdSet.Update();									//���¼�¼
			  passwdSet.Requery();									//ˢ�¼�¼��
			  passwdSet.Close();									//�رռ�¼��
              MessageBox("�û���ӳɹ������ס�û��������룡");		//������ʾ
		}
		break;
	case 'E':
		{//�޸��û�		 
			if(m_strPass!=m_strRePass)								//�ж��û����������Ƿ�һ��
			{
				MessageBox("������������벻һ�£��������������룡");//������ʾ
				m_ctrlPass.SetFocus();								//���ý���
				m_strPass="";										//��ձ༭��
				m_strRePass="";
				UpdateData(false);									//��������
				return;
			}
			CString strSQL;											//�����ַ�������
			strSQL.Format("select * from tab_password where lgn_user='%s'",m_user);
			//�����ѯ��ѯ���û���Ϣ��sql���
			MessageBox(m_user);
			if(passwdSet.IsOpen())
				passwdSet.Close();
			if(!passwdSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))///////???????????????
			{
				MessageBox("�����ݿ�ʧ�ܣ�");
				return;
			}	
			passwdSet.Edit();										//�༭��¼
			passwdSet.m_lgn_user=m_user;							//�����ֶεĸ�ֵ
			passwdSet.m_lgn_passwd=m_strPass;
			passwdSet.m_lgn_isAdmin=m_IsAdmin;
			passwdSet.Update();										//���¼�¼��
			MessageBox("�û��޸ĳɹ������ס�û��������룡");		//������ʾ
		}
		break;
      default:break;
	}
}

void CUserDlg::OnCancelBTN() 
{
	// TODO: Add your control notification handler code here
	
}

void CUserDlg::OnIsAdminCHECK() 
{
	// TODO: Add your control notification handler code here
	
}



void CUserDlg::OnDestroy() 
{
	CDialog::OnDestroy();											//���ٶԻ���
	
	// TODO: Add your message handler code here
}
