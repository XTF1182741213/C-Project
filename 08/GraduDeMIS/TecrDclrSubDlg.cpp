// TecrDclrSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "TecrDclrSubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTecrDclrSubDlg dialog


CTecrDclrSubDlg::CTecrDclrSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTecrDclrSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTecrDclrSubDlg)
	m_SubDemandVal = _T("");
	m_SubProVal = _T("");
	m_SubTitleVal = _T("");
	m_TecrAsociVal = _T("");
	m_strSubType = _T("");
	//}}AFX_DATA_INIT
}

void CTecrDclrSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTecrDclrSubDlg)
	DDX_Control(pDX, IDC_SubKind_COMBO, m_SubTypeCtrl);
	DDX_Text(pDX, IDC_SubDemand_EDIT, m_SubDemandVal);
	DDX_Text(pDX, IDC_SubProEDIT, m_SubProVal);
	DDX_Text(pDX, IDC_SubTitle_EDIT, m_SubTitleVal);
	DDX_Text(pDX, IDC_TecrAsoci_EDIT, m_TecrAsociVal);
	DDX_CBString(pDX, IDC_SubKind_COMBO, m_strSubType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTecrDclrSubDlg, CDialog)
	//{{AFX_MSG_MAP(CTecrDclrSubDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTecrDclrSubDlg message handlers

BOOL CTecrDclrSubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str[3]={"�о�","Ӧ���о�","������"};			//�����ַ������飬����ʼ��
	int nIndex;												//�������α���
	for(int i=0;i<3;i++)
	{
		nIndex=m_SubTypeCtrl.InsertString(i,str[i]);		//��������
	    m_SubTypeCtrl.SetItemData(nIndex,i);				
	}
	m_SubTypeCtrl.SetCurSel(0);								//����Ĭ��ѡ��
    CString strSubTitle;									//�����ַ�������
    if(!pchoisubSet.IsOpen())								//�򿪼�¼��
	  pchoisubSet.Open();
	pchoisubSet.MoveFirst();								//�ƶ���������¼ 
	while(!pchoisubSet.IsEOF())								//�����¼�������һ��
	{
		if(pchoisubSet.m_stu_name==strExternUser)
        {
			strSubTitle=pchoisubSet.m_sub_Name;				//������ֵ
			break;
		}
		else
			pchoisubSet.MoveNext();							//�ƶ�����һ����¼
	}
	pchoisubSet.Close();									//�رռ�¼��
	if(!psubSet.IsOpen())									//�򿪼�¼��
		psubSet.Open();
    psubSet.MoveFirst();									//�ƶ�����һ����¼
	while(!psubSet.IsEOF())									//�����¼�������һ��
	{
		if(psubSet.m_sub_title==strSubTitle)
		{
     		m_strSubType=psubSet.m_sub_type;				//�����ĸ�ֵ
			m_SubTitleVal=psubSet.m_sub_title;
			m_SubProVal=psubSet.m_sub_pro;
			m_SubDemandVal=psubSet.m_sub_demand;
			UpdateData(false);								//��������
			break;
		}
		else
			psubSet.MoveNext();								//�ƶ���������¼
	}
	psubSet.Close();										//�رվ�·��
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTecrDclrSubDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();											//��������
    psubSet.Open();											//�򿪼�¼��
 	int i=0;												//�������α���
	while(!psubSet.IsEOF())									//�����¼����ĩβ
	{
		psubSet.MoveNext();									//�����ƶ�
		i++;												//�õ����ݵ�����
	}
	CString strSubID,strSubType;							//�����ַ�������
	strSubID.Format("%d",i+1);								//����ת���ַ���
    strSubID="sub"+strSubID;					
  	psubSet.AddNew();										//����µļ�¼	 
    psubSet.m_sub_title=m_SubTitleVal;						//�¼�¼��ֵ
	m_SubTypeCtrl.GetWindowText(strSubType); 
    psubSet.m_sub_type=strSubType;
	if(strSubType=="��ѡ��")
	{
		MessageBox("��ѡ��������ͣ�","��ʾ��Ϣ",MB_OK);
		psubSet.Close();									//�رռ�¼��
		return;
	}
	psubSet.m_sub_demand=m_SubDemandVal;					//��¼��ֵ	
	psubSet.m_sub_pro=m_SubProVal;
	CGraduDeMISApp *point=(CGraduDeMISApp *)AfxGetApp();	//���Ӧ�����ָ��
    ptecrSet.Open();										//�򿪼�¼�� 
    ptecrSet.MoveFirst();									//�ƶ���������¼

	bool bDclrSubNumFlag=false;								//�ӱ��
	int  DclrSubNum=0;										//�������α���
	while(!ptecrSet.IsEOF())								//�����¼û�е�ĩβ
	{	
		if(ptecrSet.m_tecr_id==strExternUser)
		{		
			psubSet.m_tecr_name=ptecrSet.m_tecr_name;		//��ֵ
			break;
		}
		else
			ptecrSet.MoveNext();							//�����ƶ�
	}
	ptecrSet.Close();										//�رռ�¼��
 	if(!psubSet.Update()||!psubSet.Requery())				//������ˢ�¼�¼��
		MessageBox("��������ʧ��!");	
	else	
	{
		MessageBox("�걨����ɹ�!","",MB_OK);	
		bDclrSubNumFlag=true;								//���ı��
	}
    psubSet.Close();										//�رռ�¼��
	CDialog::OnOK();										//�رնԻ���
}
