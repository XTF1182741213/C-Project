// DabianfenzuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "DabianfenzuDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDabianfenzuDlg dialog


CDabianfenzuDlg::CDabianfenzuDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDabianfenzuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDabianfenzuDlg)
	m_strName = _T("");
	m_strClass = _T("");
	m_strDabianType = _T("");
	m_strSubType = _T("");
	m_strDate = _T("");
	m_strPosition = _T("");
	m_strDemand = _T("");
	m_strExpers = _T("");
	//}}AFX_DATA_INIT
}


void CDabianfenzuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDabianfenzuDlg)
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_SubType_COMBO, m_ctrlSubType);
	DDX_Control(pDX, IDC_DabianType_COMBO, m_ctrlDabianType);
	DDX_Control(pDX, IDC_Class_COMBO, m_ctrlClass);
	DDX_Control(pDX, IDC_Name_COMBO, m_ctrlName);
	DDX_CBString(pDX, IDC_Name_COMBO, m_strName);
	DDX_CBString(pDX, IDC_Class_COMBO, m_strClass);
	DDX_CBString(pDX, IDC_DabianType_COMBO, m_strDabianType);
	DDX_CBString(pDX, IDC_SubType_COMBO, m_strSubType);
	DDX_Text(pDX, IDC_STATIC_Date, m_strDate);
	DDX_Text(pDX, IDC_STATIC_Position, m_strPosition);
	DDX_Text(pDX, IDC_EDIT_Demand, m_strDemand);
	DDX_Text(pDX, IDC_STATIC_Expers, m_strExpers);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDabianfenzuDlg, CDialog)
//{{AFX_MSG_MAP(CDabianfenzuDlg)
ON_CBN_SELCHANGE(IDC_Class_COMBO, OnSelchangeClassCOMBO)
ON_CBN_SELCHANGE(IDC_Name_COMBO, OnSelchangeNameCOMBO)
ON_CBN_SELCHANGE(IDC_DabianType_COMBO, OnSelchangeDabianTypeCOMBO)
ON_CBN_SELCHANGE(IDC_SubType_COMBO, OnSelchangeSubTypeCOMBO)
ON_BN_CLICKED(IDC_Ok_BTN, OnOkBTN)
ON_BN_CLICKED(IDC_QUERY_BTN, OnQueryBtn)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDabianfenzuDlg message handlers

BOOL CDabianfenzuDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlList.InsertColumn(0,"����",LVCFMT_LEFT,60,0);					//���б�ؼ��в����һ�б��⣬���ö��뷽ʽ�����
	m_ctrlList.InsertColumn(1,"�������",LVCFMT_LEFT,80,0);				//���б�ؼ��в���ڶ��б��⣬���ö��뷽ʽ�����
	m_ctrlList.InsertColumn(2,"��������",LVCFMT_LEFT,80,0);				//���б�ؼ��в�������б��⣬���ö��뷽ʽ�����
    m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); //�����б�ؼ��������ѡ����ʾ����
	m_ctrlDabianType.InsertString(0,"Ժ����");						//������ݵ������б���
	m_ctrlDabianType.InsertString(1,"ϵ����");
	m_ctrlDabianType.InsertString(2,"С����");
	m_ctrlDabianType.SetCurSel(0);										//Ĭ��ѡ���һ��
	m_ctrlSubType.InsertString(0,"������");							//������ݵ������б���
	m_ctrlSubType.InsertString(1,"Ӧ���о�");
	m_ctrlSubType.InsertString(2,"�о�");
   	m_ctrlSubType.SetCurSel(0);											//Ĭ��ѡ���һ��
	m_ctrlClass.InsertString(0,"��Ϣ021");								//������ݵ������б���
    m_ctrlClass.InsertString(1,"��Ϣ022");
    m_ctrlClass.SetCurSel(0);											//Ĭ��ѡ���һ��
	CString strSQL;														//�����ַ�������
	int i=0;															//�������α���
    strSQL="select * from tab_stu where stu_class='��Ϣ021'";			//�����ѯstu_class�����������Ϣ��sql���
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))					//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");									//������ʾ
		return false;
	}
	while(!stuSet.IsEOF())												//������¼��
	{
		m_ctrlName.InsertString(i,stuSet.m_stu_name);					//�������ݵ������б����
		stuSet.MoveNext();												//�ƶ�����һ����¼
		i++;	
	}
	m_ctrlName.SetCurSel(0);											//����Ĭ��ѡ��
	stuSet.Close();														//�ر��ܼ�¼��
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDabianfenzuDlg::OnSelchangeClassCOMBO()
{
	// TODO: Add your control notification handler code here
	int m=0 ,k=0;														//�������α���
	m=m_ctrlName.GetCount();											//��ȡ�����б������ݵ�����
	for(int i=0;i<m;i++)												//ɾ������
		m_ctrlName.DeleteString(0);
	CString strSQL,strClass;											//�����ַ�������
	m_ctrlClass.GetWindowText(strClass);
	if(strClass=="��Ϣ021")												//�ж�
		strSQL="select * from tab_stu where stu_class='��Ϣ021'";		//�����ѯstu_class�����������Ϣ��sql���
	else
		strSQL="select * from tab_stu where stu_class='��Ϣ022'";		//�����ѯstu_class�����������Ϣ��sql���
	if(!stuSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))					//�򿪼�¼��
	{
		MessageBox("�����ݿ�ʧ�ܣ�");									//������ʾ
		return ;
	}
	while(!stuSet.IsEOF())												//������¼��
	{
		m_ctrlName.InsertString(k,stuSet.m_stu_name);					//�������ݵ������б���
		stuSet.MoveNext();												//�ƶ���������¼
		k++;
	}
	m_ctrlName.SetCurSel(0);											//Ĭ��ѡ��
	stuSet.Close();														//�رռ�¼��
}

void CDabianfenzuDlg::OnSelchangeSubTypeCOMBO() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();						//�������
}
void CDabianfenzuDlg::MyClearSubTypeCombo()
{
	int nCombo=0;										//�������α���
	nCombo=m_ctrlSubType.GetCount();					//��ȡ�����б������ݵ�����
	for(int i=0;i<nCombo;i++)							//ɾ������
		m_ctrlSubType.DeleteString(0);
}

void CDabianfenzuDlg::OnOkBTN()
{
	UpdateData();
	//m_ctrlList.DeleteAllItems();
    if(dabianfuzeSet.IsOpen())							    //�򿪼�¼��
		dabianfuzeSet.Close();
	CString strSQL;											//�����ַ�������
	strSQL.Format("select * from tab_DabianFenzu where stu_name='%s'",m_strName);
	//�����ѯ��ѯ���û���Ϣ��sql���
	dabianfuzeSet.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(dabianfuzeSet.GetRecordCount()==0)
	{
		dabianfuzeSet.Close();
		dabianfuzeSet.Open(AFX_DB_USE_DEFAULT_TYPE,"select * from tab_DabianFenzu ");
		dabianfuzeSet.AddNew();								//����¼�¼
		dabianfuzeSet.m_dabian_unit=m_strDabianType;		//�¼�¼�ĸ�ֵ
		dabianfuzeSet.m_stu_name=m_strName; 
		dabianfuzeSet.m_keti_type=m_strSubType;
		dabianfuzeSet.Update();								//���¼�¼��
		dabianfuzeSet.Requery();							//ˢ�¼�¼��
		dabianfuzeSet.Close();								//�رռ�¼��
		m_ctrlList.InsertItem(0,m_strName);					//�������ݵ��б�ؼ�
		m_ctrlList.SetItemText(0,1,m_strDabianType);
		m_ctrlList.SetItemText(0,2,m_strSubType);
		AfxMessageBox("����ɹ���");
		
	}
	else
	{
		AfxMessageBox(m_strName+"ͬѧ�Ѿ����飡");
		return;
	}	
}

void CDabianfenzuDlg::OnQueryBtn() 
{
	// TODO: Add your control notification handler code here
    m_ctrlList.DeleteAllItems();						//ɾ������
	int i=0;											//�������α���
	CString strDabianType,strSubType;					//�����ַ�����
	m_ctrlDabianType.GetWindowText(strDabianType);		//��ȡ�ı�����
	m_ctrlSubType.GetWindowText(strSubType);			//��ȡ�ı�����
	MyDate_Posi_Dem_Exp(strDabianType,strSubType);		//�����Զ��庯��
	if(!dabianfuzeSet.IsOpen())							//�򿪼�¼��
		dabianfuzeSet.Open();			
    dabianfuzeSet.MoveFirst();							//�ƶ���������¼
	while(!dabianfuzeSet.IsEOF())						//������¼��
	{
		if((strDabianType==dabianfuzeSet.m_dabian_unit)&&(strSubType==dabianfuzeSet.m_keti_type))//�ж�����
		{
			m_ctrlList.InsertItem(i,dabianfuzeSet.m_stu_name);		//�������ݵ��б�ؼ���
			m_ctrlList.SetItemText(i,1,strDabianType);
			m_ctrlList.SetItemText(i,2,strSubType);
			i++;
		}
		dabianfuzeSet.MoveNext();						//�ƶ���������¼
	}
	dabianfuzeSet.Close();								//�رռ�¼��
    UpdateData(false);									//��������
}

void CDabianfenzuDlg::MyDate_Posi_Dem_Exp(CString strDabianType,CString strSubType) 
{
	CString strDate,strPosition,strExpers,strDemand;	//�����ַ�������
	
	if(strDabianType=="Ժ����")						//�ж�����
	{
		strDate="2006��6��18������8��00~11��30";		//�����ĸ�ֵ
		strPosition="W1529";
		strExpers="����Ƽ ��� ʯ���� ������ ������";
		strDemand="       ��ÿ��ͬѧ׼���û㱨�Ļõ�Ƭ��ÿ��ͬѧ�Ĵ��ʱ���Լ30���ӣ����л㱨ʱ�������10~15�������ң��ش���С��ר�������ʱ����20�������ڡ�";
		
	}
	else if((strDabianType=="ϵ����")&&(strSubType=="������"))
	{	
		strDate="2006��6��18������13��30~17��00";
		strPosition="W1529";
		strExpers="����Ƽ ������ ������ �ź鲨 ��  ��";
		strDemand="       ��ͬѧ׼���û㱨�Ĳ��ϣ������ûõ�Ƭ����ÿ��ͬѧ�Ĵ��ʱ�䲻����25���ӣ����л㱨ʱ�������10~15�������ң��ش���С��ר�������ʱ����10�������ڡ�";	
	}
	else if((strDabianType=="ϵ����")&&(strSubType=="�о�"||strSubType=="Ӧ���о�"))
	{	
		strDate="2006��6��18������13��30~17��00";
		strPosition="W13��";
		strExpers="ʯ����  ���һ�  ������  ��־��  ���˳";
		strDemand="       ��ͬѧ׼���û㱨�Ĳ��ϣ������ûõ�Ƭ����ÿ��ͬѧ�Ĵ��ʱ�䲻����25���ӣ����л㱨ʱ�������10~15�������ң��ش���С��ר�������ʱ����10�������ڡ�";
	}
	else if((strDabianType=="С����")&&(strSubType=="������"))
	{
		strDate="2006��6��19������8��00~11��30";
		strPosition="W17��";
		strExpers="ʯ����  �ź鲨  ��  ��  ������";
		strDemand="       ��ÿ��ͬѧ׼���û㱨�Ĳ��ϣ����ʱ���Լ10���ӣ����л㱨ʱ�������6�������ң��ش���С��ר�������ʱ����4�������ڡ�";
	}
	else if((strDabianType=="С����")&&(strSubType=="Ӧ���о�"))
	{
		strDate="2006��6��19������8��00~11��30";
		strPosition="W2213";
		strExpers="���һ�  ���˳  ������ �����";
		strDemand="       ��ÿ��ͬѧ׼���û㱨�Ĳ��ϣ����ʱ���Լ10���ӣ����л㱨ʱ�������6�������ң��ش���С��ר�������ʱ����4�������ڡ�";
	}
	else if((strDabianType=="С����")&&(strSubType=="�о�"))
	{
		strDate="2006��6��19������8��00~11��30";
		strPosition="W2217";
		strExpers="������  ��־��  ������  �ⴺ��";
		strDemand="       ��ÿ��ͬѧ׼���û㱨�Ĳ��ϣ����ʱ���Լ10���ӣ����л㱨ʱ�������6�������ң��ش���С��ר�������ʱ����4�������ڡ�";
	}
	
	m_strDate=strDate;								//������ֵ���ؼ�
	m_strPosition=strPosition;
    m_strExpers=strExpers;
	m_strDemand=strDemand;
	
	UpdateData(false);								//��������
	
}
void CDabianfenzuDlg::OnSelchangeNameCOMBO() 
{
	// TODO: Add your control notification handler code here
	
}


void CDabianfenzuDlg::OnSelchangeDabianTypeCOMBO() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();										//�������
	
																		/*	CString strDabianType;
																		m_ctrlDabianType.GetWindowText(strDabianType);
																		if(strDabianType=="Ժ����")
																		{
																		MyClearSubTypeCombo();
																		m_ctrlSubType.InsertString(0,"");
																		m_ctrlSubType.InsertString(1,"");
																		m_ctrlSubType.InsertString(2,"");
																		}
																		else if(strDabianType=="ϵ����")
																		{
																		MyClearSubTypeCombo();
																		}
																		else if(strDabianType=="С����")
																		{		
																		MyClearSubTypeCombo();
																		}
	*/
}
