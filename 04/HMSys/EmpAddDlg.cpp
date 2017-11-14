// EmpAddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMSys.h"
#include "EmpAddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmpAddDlg dialog

extern CHMSysApp theApp;
CEmpAddDlg::CEmpAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmpAddDlg)
	m_strName = _T("");
	m_nAge = 0;
	m_strAddr = _T("");
	m_strPhone = _T("");
	m_strMore = _T("");
	m_Birth = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CEmpAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmpAddDlg)
	DDX_Control(pDX, IDC_COMBO2, m_DepartCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_SexCtrl);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_AGE, m_nAge);
	DDX_Text(pDX, IDC_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_MORE, m_strMore);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Birth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmpAddDlg, CDialog)
	//{{AFX_MSG_MAP(CEmpAddDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpAddDlg message handlers

void CEmpAddDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect Rect;							//����һ������
	GetDlgItem(IDC_PHOTO)->GetWindowRect(&Rect);//��ȡ����
	ScreenToClient(&Rect);		//����Ļ����ת��Ϊ�ͻ�����		
	if(Rect.PtInRect(point))		//��������������
	{
		CFileDialog FileDlg(TRUE, "BMP", NULL,		//�����ļ��Ի���
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "λͼ�ļ�(*.BMP)|*.BMP||");
		if(FileDlg.DoModal() != IDOK)			//���ļ��Ի���
			return ;
		CString pathname = FileDlg.GetPathName();//��ȡѡ���ļ���·��
		CFile file;						//����һ���ļ�����
		if(!file.Open(pathname, CFile::modeRead) )//���ƶȵķ�ʽ���ļ�
			return ;
		m_nFileLen = file.GetLength();//��ȡ�ļ��ĳ���
		m_pBMPBuffer = new char[m_nFileLen + 1];//���ٷ�����
		if(!m_pBMPBuffer)			//����ؼ�������
			return ;
		if(file.ReadHuge(m_pBMPBuffer,m_nFileLen) != m_nFileLen)//��ȡ�ļ��������ַ�������
			return ;
		LPSTR				hDIB,lpBuffer = m_pBMPBuffer;
		LPVOID				lpDIBBits;
		BITMAPFILEHEADER	bmfHeader;//����bmp�ļ�ͷ����Ϣ
		DWORD				bmfHeaderLen;//�����ļ�ͷ�ĳ���

		bmfHeaderLen = sizeof(bmfHeader);//��ȡ�ļ�ͷ�ĳ���
		strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);//�ļ��ĸ�ֵ
		if (bmfHeader.bfType != (*(WORD*)"BM"))//����ļ����Ͳ���
			return ;
		hDIB = lpBuffer + bmfHeaderLen;	//��ָ���ƶ����ļ�ͷ�ĺ���
		BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;//��ȡbmp�ļ�������
		BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
		lpDIBBits=(lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;

		CClientDC dc(this);
		m_hPhotoBitmap = CreateDIBitmap(dc.m_hDC,&bmiHeader,CBM_INIT,lpDIBBits,&bmInfo,DIB_RGB_COLORS);
		Invalidate();
	}	
	CDialog::OnLButtonDown(nFlags, point);
}


void CEmpAddDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CStatic *pStaic = (CStatic*)GetDlgItem(IDC_PHOTO);//��ȡIDΪIDC_PHOTO�ؼ���ָ��
	CBitmap bmp;							//����λͼ����
	bmp.Attach(m_hPhotoBitmap);	
	BITMAP bm;								//����һ��λͼ�ṹ
	bmp.GetBitmap(&bm);						
	CDC dcMem; 
	dcMem.CreateCompatibleDC(GetDC());		//����һ�����ݵ�DC
	CBitmap *poldBitmap=(CBitmap*)dcMem.SelectObject(bmp); //��λͼѡ���豸������
	CRect lRect;					    	//����һ������
	pStaic->GetClientRect(&lRect);			//��ȡ�ؼ��Ŀͻ�����
	lRect.NormalizeRect(); 
	pStaic->GetDC()->StretchBlt(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(), 
		&dcMem,0 ,0,bm.bmWidth,bm.bmHeight,SRCCOPY); //��ʾλͼ 
	dcMem.SelectObject(&poldBitmap); //��ԭ�еľ��ѡ���豸����
}
BOOL CEmpAddDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSQL;							//�����ַ�������
	strSQL.Format("select * from dep");	//��ʽ��SQL���
	try
	{
		m_pRecordset1 = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);//ִ��SQL��䲢��������ظ���¼��
		while(!m_pRecordset1->adoEOF)		//�����¼û�е�ĩβ
		{
			m_DepartCtrl.AddString((char*)_bstr_t(m_pRecordset1->GetCollect(_variant_t((long)1))));//����¼����ѯ�Ľ����ӵ������б����
			m_pRecordset1->MoveNext();//�ƶ�����һ����¼
		}
	}
	CATCH_ERROR;

	m_pRecordset.CreateInstance("ADODB.Recordset");
	HRESULT hr = m_pRecordset->Open("SELECT * FROM emp",
		_variant_t((IDispatch *)theApp.m_pConnection,true),
		adOpenDynamic,adLockPessimistic,adCmdText);
	m_SexCtrl.SetCurSel(0);//�����б��Ĭ��ѡ���һ��
	m_DepartCtrl.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmpAddDlg::OnBtnAdd() 
{
	UpdateData();						//��������
	if(m_strName == "")					//�����ж�
	{
		MessageBox("��������Ϊ�գ�");
		return ;
	}
	if(m_nAge == 0)
	{
		MessageBox("���������䣡");
		return ;
	}
	CString strSex, strDepart, strBirth, strAge;//�����ַ�������
	strBirth.Format("%d-%d-%d", m_Birth.GetYear(), m_Birth.GetMonth(), m_Birth.GetDay());
	int nIndex = m_SexCtrl.GetCurSel();//��ȡ�����б��ѡ�е�����
	m_SexCtrl.GetLBText(nIndex, strSex);//��ȡ�����б����ı�
	nIndex = m_DepartCtrl.GetCurSel();
	m_DepartCtrl.GetLBText(nIndex, strDepart);
	strAge.Format("%d", m_nAge);
	m_pRecordset->AddNew;
	m_pRecordset->PutCollect("name",_variant_t(m_strName));
	m_pRecordset->PutCollect("age",_variant_t((long)m_nAge));
	m_pRecordset->PutCollect("sex",_variant_t(strSex));
	m_pRecordset->PutCollect("addr",_variant_t(m_strAddr));
	m_pRecordset->PutCollect("depart",_variant_t(strDepart));
	m_pRecordset->PutCollect("birth",_variant_t(strBirth));
	m_pRecordset->PutCollect("phone",_variant_t(m_strPhone));
	m_pRecordset->PutCollect("more",_variant_t(m_strMore));
	char			*pBuf = m_pBMPBuffer;
	VARIANT			varBLOB;
	SAFEARRAY		*psa;
    SAFEARRAYBOUND	rgsabound[1];
	if(pBuf)
	{    
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = m_nFileLen;
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for (long i = 0; i < (long)m_nFileLen; i++)
			SafeArrayPutElement (psa, &i, pBuf++);
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		m_pRecordset->GetFields()->GetItem("photo")->AppendChunk(varBLOB);
	}
	m_pRecordset->Update();
	MessageBox("����ɹ���");
}


void CEmpAddDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect Rect;							//����һ������
	GetDlgItem(IDC_PHOTO)->GetWindowRect(&Rect);//��ȡ����
	ScreenToClient(&Rect);		//����Ļ����ת��Ϊ�ͻ�����		
	if(Rect.PtInRect(point))		//��������������
	{
		HCURSOR hCursor; 
		hCursor = AfxGetApp() -> LoadCursor(IDC_HAND); 
		SetCursor(hCursor); 	
	}
	CDialog::OnMouseMove(nFlags, point);
}
