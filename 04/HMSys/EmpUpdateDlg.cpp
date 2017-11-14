// EmpUpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hmsys.h"
#include "EmpUpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmpUpdateDlg dialog

extern CHMSysApp theApp;
CEmpUpdateDlg::CEmpUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmpUpdateDlg)
	m_strAddr = _T("");
	m_nAge = 0;
	m_strMore = _T("");
	m_strName = _T("");
	m_strPhone = _T("");
	m_Birth = 0;
	//}}AFX_DATA_INIT
	m_hPhotoBitmap = NULL;
	m_pBMPBuffer = NULL;
}


void CEmpUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmpUpdateDlg)
	DDX_Control(pDX, IDC_COMBO2, m_DepartCrtl);
	DDX_Control(pDX, IDC_COMBO1, m_SexCrtl);
	DDX_Text(pDX, IDC_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_AGE, m_nAge);
	DDX_Text(pDX, IDC_MORE, m_strMore);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Birth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmpUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CEmpUpdateDlg)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpUpdateDlg message handlers
void CEmpUpdateDlg::OnUpdate() 
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
	CString strSex, strDepart, strBirth, strAge;	//�����ַ�������

	SYSTEMTIME   time;   
	CDateTimeCtrl*m_TimeCtrl=(CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);   
	DateTime_GetSystemtime(m_TimeCtrl->m_hWnd,&time);   
	strBirth.Format("%d-%d-%d",time.wYear,time.wMonth,time.wDay);
	GetDlgItem(IDC_COMBO1)->GetWindowText(strSex);//���ÿؼ����ı�
	GetDlgItem(IDC_COMBO2)->GetWindowText(strDepart);
	strAge.Format("%d", m_nAge);
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
	MessageBox("�޸ĳɹ���");
}

void CEmpUpdateDlg::OnExit() 
{
	OnOK();	
}

void CEmpUpdateDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect Rect;							//����һ������
	GetDlgItem(IDC_PHOTO)->GetWindowRect(&Rect);//��ȡ����
	ScreenToClient(&Rect);		//����Ļ����ת��Ϊ�ͻ�����		
	if(Rect.PtInRect(point))		//��������������
	{
		Selectphoto();
	}
}

BOOL CEmpUpdateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pRecordset.CreateInstance("ADODB.Recordset");	
	CString strSQL;
	strSQL.Format("select name from dep");
	try
	{
		m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)strSQL, NULL, adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			m_DepartCrtl.AddString((char*)_bstr_t(m_pRecordset->GetCollect(_variant_t((long)0))));
			m_pRecordset->MoveNext();
		}
	}
	CATCH_ERROR;
	m_pRecordset->Close();
	ReadData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmpUpdateDlg::ReadData()
{
	DestroyPhoto();						///���ԭͼ��
	CString strSQL;
	strSQL.Format("select * from emp where id = %s", theApp.m_strEmpID);
	m_pRecordset->Open((_bstr_t)strSQL,_variant_t((IDispatch *)theApp.m_pConnection,true),
		adOpenDynamic,adLockPessimistic,adCmdText);
	long lDataSize = m_pRecordset->GetFields()->GetItem("photo")->ActualSize;
	if(lDataSize > 0)
	{
		_variant_t			varBLOB;
		varBLOB = m_pRecordset->GetFields()->
			GetItem("photo")->GetChunk(lDataSize);
		if(varBLOB.vt == (VT_ARRAY | VT_UI1))
		{
			///���·����Ҫ�Ĵ洢�ռ�
			if(m_pBMPBuffer = new char[lDataSize+1]) 
			{	
				char *pBuf = NULL;
				SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
				//�������ݵ�������m_pBMPBuffer
				memcpy(m_pBMPBuffer,pBuf,lDataSize);			
				SafeArrayUnaccessData (varBLOB.parray);
				m_nFileLen = lDataSize;
				///����BITMAP����
				m_hPhotoBitmap = BufferToHBITMAP();					
			}
		}
	}
		
	m_strName = m_pRecordset->GetCollect("name").bstrVal;
	m_nAge = m_pRecordset->GetCollect("age").lVal;
	GetDlgItem(IDC_COMBO1)->SetWindowText((char*)_bstr_t(m_pRecordset->GetCollect("sex").bstrVal));
	GetDlgItem(IDC_COMBO2)->SetWindowText((char*)_bstr_t(m_pRecordset->GetCollect("depart").bstrVal));
	m_strAddr = m_pRecordset->GetCollect("addr").bstrVal;
	m_strPhone = m_pRecordset->GetCollect("phone").bstrVal;
	m_strMore = m_pRecordset->GetCollect("more").bstrVal;
	CString strBirth = (char*)_bstr_t(m_pRecordset->GetCollect("birth").bstrVal);//��������
	COleVariant vtime(strBirth);
	vtime.ChangeType(VT_DATE);
	COleDateTime time1=vtime;
//	SYSTEMTIME systime;
//	VariantTimeToSystemTime(time1, &systime);
	CTime tm(time1);
	m_Birth=tm;
	UpdateData(FALSE);
}

///////////ѡ��BMP�ļ������ص��ڴ�/////////////
void CEmpUpdateDlg::Selectphoto() 
{
	CFileDialog dlg(TRUE,"BMP",NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"BMP Files (*.bmp)|*.bmp||");
	if(dlg.DoModal() == IDOK)
	{
		CString pathname = dlg.GetPathName();
		DestroyPhoto();
		LoadBMPFile(pathname);
		m_hPhotoBitmap = BufferToHBITMAP();
		Invalidate();
	}
}

/////////////�������Ķ���/////////////
void CEmpUpdateDlg::DestroyPhoto()
{
	if(m_hPhotoBitmap)
	{
		DeleteObject(m_hPhotoBitmap);
		m_hPhotoBitmap = NULL;
	}
	if(m_pBMPBuffer)
	{
		delete m_pBMPBuffer;
		m_pBMPBuffer = NULL;
	}
}

/////////////����BMP�ļ����ڴ�//////////////
BOOL CEmpUpdateDlg::LoadBMPFile(const char *pBMPPathname)
{
	CFile file;
	if( !file.Open( pBMPPathname, CFile::modeRead) )
		return FALSE;
	m_nFileLen = file.GetLength();
	m_pBMPBuffer = new char[m_nFileLen + 1];
	if(!m_pBMPBuffer)
		return FALSE;
	if(file.ReadHuge(m_pBMPBuffer,m_nFileLen) != m_nFileLen)
		return FALSE;
	return TRUE;
}

///////////���ڴ��е�BMP�ļ�����ת����HBITMAP//////
HBITMAP CEmpUpdateDlg::BufferToHBITMAP()
{
	HBITMAP				hBmp;
	LPSTR				hDIB,lpBuffer = m_pBMPBuffer;
	LPVOID				lpDIBBits;
	BITMAPFILEHEADER	bmfHeader;
	DWORD				bmfHeaderLen;

	//���λͼ��ͷ��Ϣ
	bmfHeaderLen = sizeof(bmfHeader);
	strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);

	//���ݻ�õ���Ϣͷ�ж��Ƿ���λͼ
	if (bmfHeader.bfType != (*(WORD*)"BM")) return NULL;

	//��ȡλͼ����
	hDIB = lpBuffer + bmfHeaderLen;
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	lpDIBBits=(lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;  //ƫ���ֽ���

	//����λͼ
	CClientDC dc(this);
	hBmp = CreateDIBitmap(dc.m_hDC,&bmiHeader,
		CBM_INIT,lpDIBBits,&bmInfo,DIB_RGB_COLORS);
	return hBmp;
}

void CEmpUpdateDlg::OnPaint() 
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

void CEmpUpdateDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect Rect;							//����һ������
	GetDlgItem(IDC_PHOTO)->GetWindowRect(&Rect);//��ȡ����
	ScreenToClient(&Rect);			//����Ļ����ת��Ϊ�ͻ�����		
	if(Rect.PtInRect(point))		//��������������
	{
		HCURSOR hCursor; 
		hCursor = AfxGetApp() ->LoadCursor(IDC_HAND); 
		SetCursor(hCursor); 	
	}	
	CDialog::OnMouseMove(nFlags, point);
}

