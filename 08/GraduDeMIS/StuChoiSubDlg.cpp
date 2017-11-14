// StuChoiSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gradudemis.h"
#include "StuChoiSubDlg.h"
#include "ChoiSubDlg.h"
#include "TecrDclrSubDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStuChoiSubDlg dialog

CStuChoiSubDlg::CStuChoiSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStuChoiSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStuChoiSubDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CStuChoiSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStuChoiSubDlg)
	DDX_Control(pDX, IDC_ChoiSub_LIST, m_ChoiSubList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStuChoiSubDlg, CDialog)
	//{{AFX_MSG_MAP(CStuChoiSubDlg)
	ON_BN_CLICKED(IDC_DclrSub_BTN, OnDclrSubBTN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStuChoiSubDlg message handlers

BOOL CStuChoiSubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	int i=0;									//�������α���
	m_ChoiSubList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
												//�б�ؼ������趨����ѡ������
	m_ChoiSubList.InsertColumn(0,"����",LVCFMT_LEFT,270,0);//�����б��⣬��ȣ����뷽ʽ
    m_ChoiSubList.InsertColumn(1,"����",LVCFMT_LEFT,70,0);
	m_ChoiSubList.InsertColumn(2,"��ʦ",LVCFMT_LEFT,60,0);
	m_ChoiSubList.InsertColumn(3,"ѧ��",LVCFMT_LEFT,60,0);
    if(!pchoisubSet.IsOpen())
		pchoisubSet.Open();						//�򿪼�¼��
	pchoisubSet.MoveFirst();					//�ƶ�������
	if(!psubSet.IsOpen())						//�򿪼�¼��
		psubSet.Open();
	psubSet.MoveFirst();						//�ƶ�������
    while(!pchoisubSet.IsEOF())					//�����¼����ĩβ
	{
//		if(pchoisubSet.m_stu_choisubStatus)
		{
			m_ChoiSubList.InsertItem(i,pchoisubSet.m_sub_Name);	//�����һ�����ݵ��б�ؼ���
            m_ChoiSubList.SetItemText(i,3,pchoisubSet.m_stu_name); //�������ݵ��б�ؼ���
            
			while(!psubSet.IsEOF())				//�����¼û�е�ĩβ
			{
				if(psubSet.m_sub_title==pchoisubSet.m_sub_Name)		//�ж�����
				{
					m_ChoiSubList.SetItemText(i,1,psubSet.m_sub_type);//�������ݵ��б�ؼ���
					m_ChoiSubList.SetItemText(i,2,psubSet.m_tecr_name);
					break;
				}
				else
					psubSet.MoveNext();			//�ƶ���������¼
			}
			psubSet.MoveFirst();				//�ƶ���¼����һ��
		}
		pchoisubSet.MoveNext();					//�ƶ���������¼
	}
	pchoisubSet.Close();						//�رռ�¼��
	psubSet.Close();							//�رռ�¼��
    return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CStuChoiSubDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class	
	return CDialog::DestroyWindow();		//���ٴ���
}

void CStuChoiSubDlg::OnDclrSubBTN() 
{
	// TODO: Add your control notification handler code here
	OnCancel();								//�˳�
	CTecrDclrSubDlg dlg;					//����Ի������
	dlg.DoModal();							//��ʾ�Ի���
}
