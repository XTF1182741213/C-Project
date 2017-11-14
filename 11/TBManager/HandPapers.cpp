// HandPapers.cpp : implementation file
//

#include "stdafx.h"
#include "TBManager.h"
#include "HandPapers.h"
#include "msword.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHandPapers dialog


CHandPapers::CHandPapers(CWnd* pParent /*=NULL*/)
	: CDialog(CHandPapers::IDD, pParent)
{
	listcount1=listcount2=listcount3=listcount4=0;
	//{{AFX_DATA_INIT(CHandPapers)
	m_num1 = 0;
	m_num2 = 0;
	m_num3 = 0;
	m_num4 = 0;
	m_score1 = 0;
	m_score2 = 0;
	m_score3 = 0;
	m_score4 = 0;
	m_fscore1 = _T("");
	m_fscore2 = _T("");
	m_fscore3 = _T("");
	m_fscore4 = _T("");
	m_fullscore = _T("");
	m_page = _T("");
	m_pagesname = _T("");
	m_subjectcontent = _T("");
	//}}AFX_DATA_INIT
}


void CHandPapers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHandPapers)
	DDX_Control(pDX, IDC_LIST4, m_listprocedure);
	DDX_Control(pDX, IDC_LIST3, m_listfilltext);
	DDX_Control(pDX, IDC_LIST2, m_listjudge);
	DDX_Control(pDX, IDC_LIST1, m_listchoose);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_NUM1, m_num1);
	DDX_Text(pDX, IDC_NUM2, m_num2);
	DDX_Text(pDX, IDC_NUM3, m_num3);
	DDX_Text(pDX, IDC_NUM4, m_num4);
	DDX_Text(pDX, IDC_SCORE1, m_score1);
	DDX_Text(pDX, IDC_SCORE2, m_score2);
	DDX_Text(pDX, IDC_SCORE3, m_score3);
	DDX_Text(pDX, IDC_SCORE4, m_score4);
	DDX_Text(pDX, IDC_FSCORE1, m_fscore1);
	DDX_Text(pDX, IDC_FSCORE2, m_fscore2);
	DDX_Text(pDX, IDC_FSCORE3, m_fscore3);
	DDX_Text(pDX, IDC_FSCORE4, m_fscore4);
	DDX_Text(pDX, IDC_FULLSCORE, m_fullscore);
	DDX_Text(pDX, IDC_PAGE, m_page);
	DDX_Text(pDX, IDC_PAPERSNMAE, m_pagesname);
	DDX_Text(pDX, IDC_SUBJECTCONTENT, m_subjectcontent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHandPapers, CDialog)
	//{{AFX_MSG_MAP(CHandPapers)
	ON_EN_CHANGE(IDC_NUM1, OnChangeNum1)
	ON_EN_CHANGE(IDC_NUM2, OnChangeNum2)
	ON_EN_CHANGE(IDC_NUM3, OnChangeNum3)
	ON_EN_CHANGE(IDC_NUM4, OnChangeNum4)
	ON_EN_CHANGE(IDC_SCORE1, OnChangeScore1)
	ON_EN_CHANGE(IDC_SCORE2, OnChangeScore2)
	ON_EN_CHANGE(IDC_SCORE3, OnChangeScore3)
	ON_EN_CHANGE(IDC_SCORE4, OnChangeScore4)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_TOP, OnTop)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_BN_CLICKED(IDC_FRONT, OnFront)
	ON_BN_CLICKED(IDC_ADDTHEME, OnAddtheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHandPapers message handlers

BOOL CHandPapers::OnInitDialog() 
{
	CDialog::OnInitDialog();
	pDB=new CADODatabase;
	pDB->Open("driver={SQL Server};Server=HC\\MSSQL2008;DATABASE=abao;");
	pRS=new CADORecordset(pDB);
	m_combo1.InsertString(0,"ѡ����");
	m_combo1.InsertString(1,"�ж���");
	m_combo1.InsertString(2,"�����");
	m_combo1.InsertString(3,"�ʴ���");
	m_combo1.SetCurSel(0);
	m_combo2.InsertString(0,"1");
	m_combo2.InsertString(1,"2");
	m_combo2.InsertString(2,"3");
	m_combo2.InsertString(3,"4");
	m_combo2.InsertString(4,"5");
	m_combo2.SetCurSel(0);
	strsql="delete from shijuan";
	pRS->Open(_bstr_t(strsql),CADORecordset.openQuery);
	ShowRecord();
	return TRUE;  
}

void CHandPapers::OnChangeNum1() 
{
	UpdateData();
	if(m_num1<10||m_num1>20)AfxMessageBox("�����10��20֮�����");
}

void CHandPapers::OnChangeNum2() 
{
	UpdateData();
	if(m_num2<10||m_num2>20)AfxMessageBox("�����10��20֮�����");
//	ShowScore2();
}

void CHandPapers::OnChangeNum3() 
{
	UpdateData();
	if(m_num3<3||m_num3>8)AfxMessageBox("�����3��8֮�����");
//	ShowScore3();
}

void CHandPapers::OnChangeNum4() 
{
	UpdateData();
	if(m_num4<2||m_num4>4)AfxMessageBox("�����2��4֮�����");
//	ShowScore4();
}

void CHandPapers::OnChangeScore1() 
{
	UpdateData();
	if(m_score1<2||m_score1>4)AfxMessageBox("�����2��4֮�����");
	ShowScore1();
	ShowFullScore();
	
}

void CHandPapers::OnChangeScore2() 
{
	UpdateData();
	if(m_score2<1||m_score2>2)AfxMessageBox("�����1��2֮�����");
	ShowScore2();
	ShowFullScore();
}

void CHandPapers::OnChangeScore3() 
{
	UpdateData();
	if(m_score3<3||m_score3>8)AfxMessageBox("�����3��8֮�����");
	ShowScore3();
	ShowFullScore();
}

void CHandPapers::OnChangeScore4() 
{
	UpdateData();
	if(m_score4<4||m_score4>8)AfxMessageBox("�����4��8֮�����");
	ShowScore4();
	ShowFullScore();
}

void CHandPapers::ShowScore1()
{
//	UpdateData();
	m_fscore1.Format("%d",m_num1*m_score1);
	UpdateData(false);
}

void CHandPapers::OnOK() //�ֹ�����
{
	UpdateData();
//	pRS->Close();
	if(m_pagesname=="")
	{
		AfxMessageBox("������������Ŀ");
		return;
	}
	if(m_num1==0||m_num2==0||m_num3==0||m_num4==0)
	{
		AfxMessageBox("Ԥ�����ⲻ�ܿ���");
		return;
	}
	if(m_num1!=m_listchoose.GetCount()||m_num2!=m_listjudge.GetCount()||
       m_num3!=m_listfilltext.GetCount()||m_num4!=m_listprocedure.GetCount())
	{
		AfxMessageBox("Ԥ������Ŀ�����Ծ����Ŀ����һ�������ʵ���ڵ�������Ծ�");
		return;
	}
	_Application WordApp;
	CoInitialize(NULL);
	if(!WordApp.CreateDispatch("Word.Application",NULL))
	{
		AfxMessageBox("����Word����ʧ��!");
		exit(1);
		return;
	}
	
	WordApp.SetVisible(TRUE);
	_Document doc;

	Documents docs=WordApp.GetDocuments();
	//׼������Documents::Add�����ˣ���Ҫ����4��������
	//��WORD����Կ�����3������������Ϊ��
	//Template�ַ���NewTemplate������DocumentType��ֵ
	//��Add��������Ҫһ��������Visible,ɵ��Ҳ�ܿ��������ֵ��ʾ�Ƿ���ʾ�����ĵ�
	//���ҿ��Ը�Ĭ��ֵ(VT_EMPTY)
	COleVariant covOptional((long) DISP_E_PARAMNOTFOUND,VT_ERROR);
	doc=docs.Add(covOptional,covOptional,covOptional,covOptional);
	//ͨ��WORD�����֪����ʹ��Selection,����һ������app��ȡ��
	//Selection��ʾ����㣬�������˸���Ǹ��ط�
	//Selection sel=WordApp.GetSelection();	
	//���ú���Selection::TypeText ��WORD�����ַ�
	COleVariant start_line,end_line;
	Range range;
	Table table;
	Tables tables;
	Cell cell;
	Paragraph paragraph;
	Paragraphs paragraphs;
	start_line=end_line=covOptional;
	range=doc.Range(start_line,end_line);
	tables=range.GetTables();
	table=tables.Add(range,11,1,covOptional,covOptional);
	cell=table.Cell(1,1);
	range=cell.GetRange();
	_Font ft=range.GetFont();
	ft.SetSize(20);
	ft.SetName("�����п�");
	ft.SetColor(RGB(255,55,66));
	range.SetBold(1);
	CString test;
	test="             "+m_pagesname;
	range.SetText(test);
	range.SetBold(1);
	cell=table.Cell(2,1);
	range=cell.GetRange();
	range.SetBold(1);
	test.Format("�����ܷ�:  %s   ������:_________",m_fullscore);
	test="                                              "+test;
	range.SetText(test);
	//		CString test;
	cell=table.Cell(3,1);
	range=cell.GetRange();
	range.SetBold(1);
	test.Format("һ��ѡ����(ÿ�� %d �֣��� %d ��)",m_score1,m_num1);
	range.SetText(test);
	cell=table.Cell(5,1);
	range=cell.GetRange();
	range.SetBold(1);
	test.Format("�����ж���(ÿ�� %d �֣��� %d ��)",m_score2,m_num2);
	range.SetText(test);
	cell=table.Cell(7,1);
	range=cell.GetRange();
	range.SetBold(1);
	test.Format("���������(ÿ�� %d �֣��� %d ��)",m_score3,m_num3);
	range.SetText(test);
	cell=table.Cell(9,1);
	range=cell.GetRange();
	range.SetBold(1);
	test.Format("�ģ��ʴ���(ÿ�� %d �֣��� %d ��)",m_score4,m_num4);
	range.SetText(test);
	ft.ReleaseDispatch();
	//Selection �����ˣ�һ��Ҫ�ͷ�
	docs.ReleaseDispatch();		
	//Documents Ҳ������
	WordApp.ReleaseDispatch();	
	CDialog::OnOK();
}

void CHandPapers::ShowScore2()
{
	m_fscore2.Format("%d",m_num2*m_score2);
	UpdateData(false);
}

void CHandPapers::ShowScore3()
{
	m_fscore3.Format("%d",m_num3*m_score3);
	UpdateData(false);
}

void CHandPapers::ShowScore4()
{
	m_fscore4.Format("%d",m_num4*m_score4);
	UpdateData(false);
}

void CHandPapers::ShowFullScore()
{
	m_fullscore.Format("%d",m_num1*m_score1+m_num2*m_score2+m_num3*m_score3+m_num4*m_score4);
	UpdateData(false);
}

void CHandPapers::ShowRecord()
{
	pRS->Close();
	UpdateData();
	m_subjectcontent="";
	int tixing=0,diff=0;
	CString tablename;
	tixing=m_combo1.GetCurSel();
	diff=m_combo2.GetCurSel();
	switch(tixing)
	{
	case 0:
		tablename="ti_choose";break;
	case 1:
		tablename="ti_judge";break;
	case 2:
		tablename="ti_filltext";break;
	case 3:
		tablename="ti_procedure";break;
	}
	strsql.Format("select * from %s where difficulty=%d",tablename,diff);
	pRS->Open(_bstr_t(strsql),CADORecordset.openQuery);
	if(!pRS->IsOpen())return;
	if(pRS->GetRecordCount()<=0)return;
	pRS->MoveFirst();
	switch(tixing)
	{
		case 0:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("xa",str2);
			pRS->GetFieldValue("xb",str3);
			pRS->GetFieldValue("xc",str4);
			pRS->GetFieldValue("xd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 1:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
		case 2:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("ka",str2);
			pRS->GetFieldValue("kb",str3);
			pRS->GetFieldValue("kc",str4);
			pRS->GetFieldValue("kd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 3:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
	}
	UpdateData(false);
		
}

void CHandPapers::OnSelchangeCombo1() 
{
	ShowRecord();
	
}

void CHandPapers::OnSelchangeCombo2() 
{
	ShowRecord();
	
}

void CHandPapers::OnTop() 
{
	pRS->MoveFirst();
	m_subjectcontent="";
	switch(m_combo1.GetCurSel())
	{
		case 0:
//			str1=str2=str3=str4=str5="";
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("xa",str2);
			pRS->GetFieldValue("xb",str3);
			pRS->GetFieldValue("xc",str4);
			pRS->GetFieldValue("xd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 1:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
		case 2:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("ka",str2);
			pRS->GetFieldValue("kb",str3);
			pRS->GetFieldValue("kc",str4);
			pRS->GetFieldValue("kd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 3:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
	}
//	if(pRS->MoveNext())
	UpdateData(false);
	
}

void CHandPapers::OnBack() 
{
	if(pRS->IsEOF())
	{
		AfxMessageBox("�ѵ����һ����¼");
		return;
	}
	pRS->MoveNext();
	if(pRS->IsEOF())
	{
		AfxMessageBox("�ѵ����һ����¼");
		return;
	}
	m_subjectcontent="";
	switch(m_combo1.GetCurSel())
	{
		case 0:
//			str1=str2=str3=str4=str5="";
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("xa",str2);
			pRS->GetFieldValue("xb",str3);
			pRS->GetFieldValue("xc",str4);
			pRS->GetFieldValue("xd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 1:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
		case 2:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("ka",str2);
			pRS->GetFieldValue("kb",str3);
			pRS->GetFieldValue("kc",str4);
			pRS->GetFieldValue("kd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 3:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
	}
//	if(pRS->MoveNext())
	UpdateData(false);
	
}

void CHandPapers::OnLast() 
{
	pRS->MoveLast();
	m_subjectcontent="";
	switch(m_combo1.GetCurSel())
	{
		case 0:
//			str1=str2=str3=str4=str5="";
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("xa",str2);
			pRS->GetFieldValue("xb",str3);
			pRS->GetFieldValue("xc",str4);
			pRS->GetFieldValue("xd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 1:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
		case 2:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("ka",str2);
			pRS->GetFieldValue("kb",str3);
			pRS->GetFieldValue("kc",str4);
			pRS->GetFieldValue("kd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 3:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
	}
//	if(pRS->MoveNext())
	UpdateData(false);
	
}

void CHandPapers::OnFront() 
{
	if(pRS->IsBOF())
	{
		AfxMessageBox("�ѵ���һ����¼");
		pRS->MoveFirst();
		return;
	}
	pRS->MovePrevious();
	if(pRS->IsBOF())
	{
		AfxMessageBox("�ѵ���һ����¼");
		pRS->MoveFirst();
		return;
	}
	
	m_subjectcontent="";
	switch(m_combo1.GetCurSel())
	{
		case 0:
//			str1=str2=str3=str4=str5="";
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("xa",str2);
			pRS->GetFieldValue("xb",str3);
			pRS->GetFieldValue("xc",str4);
			pRS->GetFieldValue("xd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 1:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
		case 2:
			pRS->GetFieldValue("tigan",str1);
			pRS->GetFieldValue("ka",str2);
			pRS->GetFieldValue("kb",str3);
			pRS->GetFieldValue("kc",str4);
			pRS->GetFieldValue("kd",str5);
			m_subjectcontent=str1+"\r\n"+str2+"\r\n"+str3+"\r\n"+str3+"\r\n"+str4+"\r\n"+str5;
			break;
		case 3:
			pRS->GetFieldValue("tigan",str1);
			m_subjectcontent=str1;
			break;
	}
//	if(pRS->MoveNext())
	UpdateData(false);
	
}

void CHandPapers::OnAddtheme() 
{
	pRS->Close();
	UpdateData();
//	AfxMessageBox(m_subjectcontent);
	strsql="select * from shijuan";
	pRS->Open(_bstr_t(strsql),CADORecordset.openQuery);
	if(!pRS->IsOpen())return;
//	if(pRS->GetRecordCount()<=0)return;
	pRS->AddNew();
	pRS->SetFieldValue("timu",m_subjectcontent);
	pRS->SetFieldValue("tixing",m_combo1.GetCurSel());
	pRS->Update();
	AfxMessageBox("��ӳɹ���");
//	pRS->Close();
	switch(m_combo1.GetCurSel())
	{
		case 0:
			m_listchoose.InsertString(listcount1,m_subjectcontent);
			listcount1++;
			break;
		case 1:
			m_listjudge.InsertString(listcount2,m_subjectcontent);
			listcount2++;
			break;
		case 2:
			m_listfilltext.InsertString(listcount3,m_subjectcontent);
			listcount3++;
			break;
		case 3:
			m_listprocedure.InsertString(listcount4,m_subjectcontent);
			listcount4++;
			break;
	}
	ShowRecord();
				
}
