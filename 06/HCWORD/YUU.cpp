// YUU.cpp : implementation file
//

#include "stdafx.h"
#include "HCWORD.h"
#include "YUU.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// YUU dialog


YUU::YUU(CWnd* pParent /*=NULL*/)
	: CDialog(YUU::IDD, pParent)
{
	//{{AFX_DATA_INIT(YUU)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void YUU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(YUU)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(YUU, CDialog)
	//{{AFX_MSG_MAP(YUU)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// YUU message handlers


BOOL YUU::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CRect dlgRect;
	GetWindowRect(dlgRect);
	CRect desktopRect;
	//�����ڿ�ʼ��С��Ϊ0
	GetDesktopWindow()->GetWindowRect(desktopRect);
	MoveWindow((desktopRect.Width() - dlgRect.Width()) / 2,
	(desktopRect.Height() - dlgRect.Height()) / 2,0,0 );
	//��ʼ���仯��С
	m_nWidth=dlgRect.Width();
	m_nHeight=dlgRect.Height();
	m_nDx=6;
	m_nDy=6;
	m_nDx1=6;
	m_nDy1=6;                                                            //�趨��ʱ��1	
	SetTimer(1,10,NULL);
    m_theImageList.Create(IDB_BITMAP11,16,1,RGB(0,255,0));       //����ͼ���б�
	m_tree.SetImageList(&m_theImageList,TVSIL_NORMAL);          //���οؼ�����λͼ
	CString userTreeHeader[3]={"�﷨֪ʶ","�������","Ӣ��ɳ��"};
	HTREEITEM userItem[3];                                      //���οؼ��ĸ���
	for(int i=0;i<3;i++)
	{
		userItem[i]=m_tree.InsertItem(userTreeHeader[i],0,0,TVI_ROOT);//���븸��
		m_tree.SetItemData(userItem[i],(DWORD)(i+10));          //��������ֵ
	}
	HTREEITEM thePoint;
	HTREEITEM userSpecifics=m_tree.InsertItem("�����򶯴ʱ�",2,2,userItem[0]);//����1��������
	m_tree.SetItemData(userSpecifics,(DWORD)0);                //���ֵ0
	thePoint=userSpecifics;
	userSpecifics=m_tree.InsertItem("�����ܱ�",3,3,userItem[0]);//����1��������
	m_tree.SetItemData(userSpecifics,(DWORD)1);                //���ֵ1
	userSpecifics=m_tree.InsertItem("���ʵ�������",3,3,userItem[0]);//����1��������
	m_tree.SetItemData(userSpecifics,(DWORD)2);                //���ֵ2
	userSpecifics=m_tree.InsertItem("���Ϲ���Ҫ����",3,3,userItem[1]);//����2��������
	m_tree.SetItemData(userSpecifics,(DWORD)3);               //���ֵ3
	userSpecifics=m_tree.InsertItem("�й�����",3,3,userItem[1]);//����2��������
	m_tree.SetItemData(userSpecifics,(DWORD)4);                //���ֵ4
	userSpecifics=m_tree.InsertItem("�ճ�ϰ��",3,3,userItem[2]);//����3��������
	m_tree.SetItemData(userSpecifics,(DWORD)5);                 //���ֵ5
	userSpecifics=m_tree.InsertItem("����Ӣ��",3,3,userItem[2]);//����3��������
	return TRUE;

}
void YUU::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   	HTREEITEM SelItem;
	SelItem=m_tree.GetSelectedItem();                          //��ȡѡ�е�����
	DWORD m;
	m=m_tree.GetItemData(SelItem);                             //��ȡ�����ֵ
	switch (m)
	{	
	case 0:
		{	                                               //�б��ӵı�ͷ
			for(int i=0;i<3;i++)
			{
				m_list.DeleteColumn(i);                         //�����ͷ����
			}
			for(int j=0;j<3;j++)
			{
				m_list.InsertColumn(j,"",LVCFMT_LEFT,220);     //�����ͷ����
			}
			m_list.DeleteColumn(3);
			pdb=new CDatabase;
            pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
            m_pset=new ZLSet(pdb);
			m_pset->Open();	
			m_tree.SetItemImage(activeItem,3,3);               //��ǰ��������ͼ��
			m_tree.SetItemImage(activeparentItem,0,0);           //��ǰ��������ͼ��
			m_tree.SetItemImage(SelItem,2,2);                     //��ǰ��������ͼ��
			HTREEITEM Itemparent;
			Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
			m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
			activeItem=SelItem;
			activeparentItem=Itemparent;
            CString str;
			m_list.DeleteAllItems();
			str="�����򶯴ʱ�:";
			m_list.InsertItem(0,str);
			m_list.SetItemText(0,1,"");
			m_list.SetItemText(0,2,"");
			int k=1;
			while(!m_pset->IsEOF())
			{		  
				m_pset->m_piezi.TrimRight();
				m_pset->m_baozi.TrimRight();
				m_pset->m_guoqing.TrimRight();
				m_list.InsertItem(k,m_pset->m_piezi);
				m_list.SetItemText(k,1,m_pset->m_baozi);
				m_list.SetItemText(k,2,m_pset->m_guoqing);
				k++;
				m_pset->MoveNext();
			}
			m_pset->Close();
            break;
		}
	case 1:
		{	
			CString Field[3]={"","",""};                         //�б��ӵı�ͷ
			for(int i=0;i<3;i++)
			{
				m_list.DeleteColumn(i);                             //�����ͷ����
			}
			for(int j=0;j<3;j++)
			{
				m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,300);     //�����ͷ����
			}
			m_list.DeleteColumn(2);
			m_list.DeleteColumn(3);
			m_list.DeleteColumn(4);
			pdb=new CDatabase;
            pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
            m_pset=new ZLSet(pdb);
			m_pset->Open();	
			m_tree.SetItemImage(activeItem,3,3);                   //��ǰ��������ͼ��
			m_tree.SetItemImage(activeparentItem,0,0);            //��ǰ��������ͼ��
			m_tree.SetItemImage(SelItem,2,2);                     //��ǰ��������ͼ��
			HTREEITEM Itemparent;
			Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
			m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
			activeItem=SelItem;
			activeparentItem=Itemparent;
			CString str;
			m_list.DeleteAllItems();
			str="���ʵ�������:";
			m_list.InsertItem(0,str);
			m_list.SetItemText(0,1,"");
			m_list.SetItemText(0,2,"");
			m_list.SetItemText(0,3,"");
			int k=1;
			while(!m_pset->IsEOF())
			{		  
				m_pset->m_dian.TrimRight();
				m_pset->m_hua.TrimRight();
				m_list.InsertItem(k,m_pset->m_dian);
				m_list.SetItemText(k,1,m_pset->m_hua);
				k++;
				m_pset->MoveNext();
			}
			m_pset->Close();
			
			break;
		}
	case 2:
		{	
			CString Field[4]={"","","",""};                          //�б��ӵı�ͷ
			for(int i=0;i<4;i++)
			{
				m_list.DeleteColumn(i);                            //�����ͷ����
			}
			for(int j=0;j<4;j++)
			{
				m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,170);   //�����ͷ����
			}
			m_list.DeleteColumn(4);
            pdb=new CDatabase;
            pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
            m_pset=new ZLSet(pdb);
			m_pset->Open();	
			m_tree.SetItemImage(activeItem,3,3);                 //��ǰ��������ͼ��
			m_tree.SetItemImage(activeparentItem,0,0);            //��ǰ��������ͼ��
			m_tree.SetItemImage(SelItem,2,2);                     //��ǰ��������ͼ��
			HTREEITEM Itemparent;
			Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
			m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
			activeItem=SelItem;
			activeparentItem=Itemparent;
			CString str;
			m_list.DeleteAllItems();
			str="���ʵ�������:";
			m_list.InsertItem(0,str);
			m_list.SetItemText(0,1,"");
			m_list.SetItemText(0,2,"");
			m_list.SetItemText(0,3,"");
			int k=1;
			while(!m_pset->IsEOF())
			{		  
				m_pset->m_w1.TrimRight();
				m_pset->m_w2.TrimRight();
				m_pset->m_w3.TrimRight();
				m_pset->m_w4.TrimRight();
				m_list.InsertItem(k,m_pset->m_w1);
				m_list.SetItemText(k,1,m_pset->m_w2);
				m_list.SetItemText(k,2,m_pset->m_w3);
				m_list.SetItemText(k,3,m_pset->m_w4);
				k++;
				m_pset->MoveNext();
			}
			m_pset->Close();
			
			break;
		}
	case 3:
		{	
			CString Field[4]={"","","",""};                       //�б��ӵı�ͷ
			for(int i=0;i<4;i++)
			{
				m_list.DeleteColumn(i);                            //�����ͷ����
			}
			for(int j=0;j<4;j++)
			{
				m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,200);   //�����ͷ����
			}
			m_list.DeleteColumn(4);
			m_list.DeleteColumn(5);
			m_list.DeleteColumn(6);
			pdb=new CDatabase;
            pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
            m_pset=new ZLSet(pdb);
			m_pset->Open();	
			m_tree.SetItemImage(activeItem,3,3);                   //��ǰ��������ͼ��
			m_tree.SetItemImage(activeparentItem,0,0);            //��ǰ��������ͼ��
			m_tree.SetItemImage(SelItem,2,2);                     //��ǰ��������ͼ��
			HTREEITEM Itemparent;
			Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
			m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
			activeItem=SelItem;
			activeparentItem=Itemparent;
			CString str;
			m_list.DeleteAllItems();
			str="���Ϲ���Ҫ����:";
			m_list.InsertItem(0,str);
			m_list.SetItemText(0,1,"");
			m_list.SetItemText(0,2,"");
			m_list.SetItemText(0,3,"");
			int k=1;
			while(!m_pset->IsEOF())
			{		  
				m_pset->m_j3.TrimRight();
				m_pset->m_j4.TrimRight();
				m_pset->m_j5.TrimRight();
				m_pset->m_j6.TrimRight();
				
				m_list.InsertItem(k,m_pset->m_j3);
				m_list.SetItemText(k,1,m_pset->m_j4);
				m_list.SetItemText(k,2,m_pset->m_j5);
				m_list.SetItemText(k,3,m_pset->m_j6);
				
				
				k++;
				m_pset->MoveNext();
			}
			m_pset->Close();
			break;
		}
	case 4:
		{	CString Field[2]={"",""};                        //�б��ӵı�ͷ
		for(int i=0;i<2;i++)
		{
			m_list.DeleteColumn(i);                        //�����ͷ����
		}
		for(int j=0;j<2;j++)
		{
			m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,340);//�����ͷ����
		}
		m_list.DeleteColumn(2);
		m_list.DeleteColumn(3);
		m_list.DeleteColumn(4);
		pdb=new CDatabase;
		pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
		m_pset=new ZLSet(pdb);
		m_pset->Open();	
		m_tree.SetItemImage(activeItem,3,3);                //��ǰ��������ͼ��
		m_tree.SetItemImage(activeparentItem,0,0);          //��ǰ��������ͼ��
		m_tree.SetItemImage(SelItem,2,2);                   //��ǰ��������ͼ��
		HTREEITEM Itemparent;
		Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
		m_tree.SetItemImage(Itemparent,1,1);               //��ǰ��������ͼ��
		activeItem=SelItem;
		activeparentItem=Itemparent;
		CString str;
		m_list.DeleteAllItems();
		str="ȫ�����������:";
		m_list.InsertItem(0,str);
		m_list.SetItemText(0,1,"");
		int k=1;
		while(!m_pset->IsEOF())
		{		  
			m_pset->m_j1.TrimRight();
			m_pset->m_j2.TrimRight();
			m_list.InsertItem(k,m_pset->m_j1);
            m_list.SetItemText(k,1,m_pset->m_j2);
            
            k++;
            m_pset->MoveNext();
		}
		m_pset->Close();
		break;
		}
	case 5:
		
		{	CString Field[1]={""};                               //�б��ӵı�ͷ
		for(int i=0;i<1;i++)
		{
			m_list.DeleteColumn(i);                            //�����ͷ����
		}
		for(int j=0;j<1;j++)
		{
			m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,650);  //�����ͷ����
		}
		m_list.DeleteColumn(1);
		pdb=new CDatabase;
		pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
		m_pset=new ZLSet(pdb);
		m_pset->Open();	
		m_tree.SetItemImage(activeItem,3,3);                 //��ǰ��������ͼ��
		m_tree.SetItemImage(activeparentItem,0,0);           //��ǰ��������ͼ��
		m_tree.SetItemImage(SelItem,2,2);                    //��ǰ��������ͼ��
		HTREEITEM Itemparent;
		Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
		m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
		activeItem=SelItem;
		activeparentItem=Itemparent;
		CString str;
		m_list.DeleteAllItems();
		str="�ճ�ϰ��:";
		m_list.InsertItem(0,str);
		
		int k=1;
		while(!m_pset->IsEOF())
		{		  
			m_pset->m_j7.TrimRight();
			
			m_list.InsertItem(k,m_pset->m_j7);
			
            
            k++;
            m_pset->MoveNext();
		}
		m_pset->Close();
		break;
		}
	case 6:
		{	CString Field[2]={"",""};                          //�б��ӵı�ͷ
		for(int i=0;i<2;i++)
		{
			m_list.DeleteColumn(i);                         //�����ͷ����
		}
		for(int j=0;j<2;j++)
		{
			m_list.InsertColumn(j,Field[j],LVCFMT_LEFT,320);//�����ͷ����
		}
		pdb=new CDatabase;
		pdb->Open("ODBC;DSN=�ʿ�;Trusted_Connection=Yes");
		m_pset=new ZLSet(pdb);
		m_pset->Open();
		m_tree.SetItemImage(activeItem,3,3);               //��ǰ��������ͼ��
		m_tree.SetItemImage(activeparentItem,0,0);         //��ǰ��������ͼ��
		m_tree.SetItemImage(SelItem,2,2);                  //��ǰ��������ͼ��
		HTREEITEM Itemparent;
		Itemparent=m_tree.GetNextItem( SelItem, TVGN_PARENT);//��ȡ��ǰ����ĸ���
		m_tree.SetItemImage(Itemparent,1,1);                 //��ǰ��������ͼ��
		activeItem=SelItem;
		activeparentItem=Itemparent;
		CString str;
		m_list.DeleteAllItems();
		str="����Ӣ��:";
		m_list.InsertItem(0,str);
		m_list.SetItemText(0,1,"");
		int k=1;
		while(!m_pset->IsEOF())
		{		  
			m_pset->m_j8.TrimRight();
			m_pset->m_j9.TrimRight();
			m_list.InsertItem(k,m_pset->m_j8);
            m_list.SetItemText(k,1,m_pset->m_j9);
            
            k++;
            m_pset->MoveNext();
		}
		m_pset->Close();
		break;
		break;
		}
	}
	*pResult = 0;
}

void YUU::OnTimer(UINT nIDEvent) 
{                                                                      
	CRect dlgRect;
	GetWindowRect(dlgRect);//��ô�ʱ���ڵ�ʵ�ʴ�С
	CRect desktopRect;
	GetDesktopWindow()->GetWindowRect(desktopRect);//�������Ĵ�С
	if(nIDEvent == 1)//����Ǵ��ڵ������̣��������󴰿�
	{
		MoveWindow((-m_nDx+desktopRect.Width() - dlgRect.Width()) / 2,
			(-m_nDy+desktopRect.Height() - dlgRect.Height()) / 2, 
		+m_nDx+dlgRect.Width(),+m_nDy+dlgRect.Height() );
		if(dlgRect.Width() >=m_nWidth)//��Ҫ��������Ԥ��Ŀ�� 
			m_nDx=0; 
		if(dlgRect.Height() >=m_nHeight)//��Ҫ��������Ԥ��ĸ߶�
			m_nDy=0;
		if((dlgRect.Width() >=m_nWidth) && (dlgRect.Height() >=m_nHeight))
			KillTimer(1);//ֹͣ�仯���رն�ʱ��1 
	}
	if((dlgRect.Width() >=m_nWidth) && (dlgRect.Height() >=m_nHeight))
		KillTimer(1);//ֹͣ�仯���رն�ʱ��1 
	if(nIDEvent == 2)//����Ǵ��ڹرչ��̣�������С����
	{
		MoveWindow((+m_nDx+desktopRect.Width() - dlgRect.Width()) / 2,
                   (+m_nDy+desktopRect.Height() - dlgRect.Height()) / 2,
		        	-m_nDx1+dlgRect.Width(),-m_nDy1+dlgRect.Height() );
		if(dlgRect.Width() <= 0)//����ȵ�������ȾͲ��ڱ仯 
			m_nDx1=0;
		if(dlgRect.Height() <= 0 )//���߶ȵ������߶ȾͲ��ڱ仯
			m_nDy1=0; 
		if((dlgRect.Width() <= 0 ) && (dlgRect.Height() <=0))//ֹͣ�仯���رն�ʱ��2�����ҹرմ���
		{
			KillTimer(2);
			CDialog::OnOK();
		}	
	}	
	CDialog::OnTimer(nIDEvent);
}

void YUU::OnClose() 
{
	SetTimer(2,100,NULL);
	
	CDialog::OnClose();
}
