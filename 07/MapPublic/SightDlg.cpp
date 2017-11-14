// SightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mappublic.h"
#include "SightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSightDlg property page

IMPLEMENT_DYNCREATE(CSightDlg, CPropertyPage)

CSightDlg::CSightDlg() : CPropertyPage(CSightDlg::IDD)
{
	//{{AFX_DATA_INIT(CSightDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSightDlg::~CSightDlg()
{
}

void CSightDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSightDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSightDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CSightDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSightDlg message handlers

void CSightDlg::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
    //-------------------------------------------------------------
	CPaintDC dc(GetDlgItem(IDC_STATIC1)); //�ô˾�,�õ�picture�ؼ���DC,ͼ�񽫱������ڿؼ���  
    CRect rcclient;
    GetDlgItem(IDC_STATIC1)->GetClientRect(&rcclient);
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);  
    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
    memdc.SelectObject( &bitmap );
    CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC , 0);
    CDC maskdc;
    maskdc.CreateCompatibleDC(&dc);
    CBitmap maskbitmap;
    maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL);
    maskdc.SelectObject( &maskbitmap );
    maskdc.BitBlt( 0, 0, rcclient.Width(), rcclient.Height(), &memdc, 
        rcclient.left, rcclient.top, SRCCOPY);
    CBrush brush;
    brush.CreatePatternBrush(&m_bmp);
    dc.FillRect(rcclient, &brush);  
    dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), 
             &memdc, rcclient.left, rcclient.top,SRCPAINT);
    brush.DeleteObject();



	//-----------------------------------------------------------------
/*	IPicture *pPic; 
	IStream *pStm; 
	
	CFileStatus fstatus; 
	CFile file; 
	LONG cb; 

	CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
	app->pitcure_name.TrimLeft();
	app->pitcure_name.TrimRight();
	CString RgbDir="res/"+app->pitcure_name+".jpg";
	AfxMessageBox(app->pitcure_name);
	if (file.Open(RgbDir,CFile::modeRead)&&file.GetStatus(RgbDir,fstatus)&& 
		((cb = fstatus.m_size) != -1)) 
	{ 
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb); 
		LPVOID pvData = NULL; 
		if (hGlobal != NULL) 
		{ 
			if ((pvData = GlobalLock(hGlobal)) != NULL) 
			{ 
				file.ReadHuge(pvData, cb); 
				GlobalUnlock(hGlobal); 
				CreateStreamOnHGlobal(hGlobal, TRUE, &pStm); 
				
				if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID* )&pPic))) 
				{ 
					OLE_XSIZE_HIMETRIC hmWidth; 
					OLE_YSIZE_HIMETRIC hmHeight; 
					
					pPic->get_Width(&hmWidth); 
					pPic->get_Height(&hmHeight); 
					
					double fX,fY; 
					fX = (double)dc.GetDeviceCaps(HORZRES)*(double)hmWidth/((double)dc.GetDeviceCaps(HORZSIZE)*100.0); 
					fY = (double)dc.GetDeviceCaps(VERTRES)*(double)hmHeight/((double)dc.GetDeviceCaps(VERTSIZE)*100.0); 
					if(FAILED(pPic->Render(dc,0,0,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL))) 
						AfxMessageBox("Failed To Render The picture!"); 
					pPic->Release(); 
				} 
				else 
					AfxMessageBox("Error Loading Picture From Stream!"); 
			} 
		} 
	}  	
*/

}
void CSightDlg::showpicture()
{	
   
	CMapPublicApp *app=(CMapPublicApp *)AfxGetApp();
//	 AfxMessageBox(app->pitcure_name);
	app->pitcure_name.TrimLeft();
	app->pitcure_name.TrimRight();
	CString str=sPath+app->pitcure_name+".bmp";
	if( m_bmp.m_hObject != NULL )//�ж�
        m_bmp.DeleteObject();
     /////////����ͼƬ
    HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), 

        str, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

     if( hbmp == NULL ) 

        return ;

    ///////////////////////�öϳ�������ȡ�ü��ص�BMP����Ϣ////////////////////////

    m_bmp.Attach( hbmp );

    DIBSECTION ds;

    BITMAPINFOHEADER &bminfo = ds.dsBmih; 

    m_bmp.GetObject( sizeof(ds), &ds );

    int cx=bminfo.biWidth;  //�õ�ͼ����

    int cy=bminfo.biHeight; //�õ�ͼ��߶�

    /////////////////// ////////////////////////////////

/////////////�õ���ͼ��Ŀ�Ⱥ͸߶Ⱥ�,���ǾͿ��Զ�ͼ���С������Ӧ,�������ؼ��Ĵ�С,����������ʾһ��ͼƬ///////////////////////////

    CRect rect;
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&rect);
    ScreenToClient(&rect);
    GetDlgItem(IDC_STATIC1)->MoveWindow(rect.left,rect.top,cx,cy,true);//������С
    InvalidateRect(rect,TRUE);
	
	return ;  
	              

}

BOOL CSightDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
 //AfxMessageBox("0000");  	
   GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);//ΪsPath����洢�ռ�
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ���·��
    nPos=sPath.ReverseFind('\\');
	sPath=sPath.Left(nPos);//��ȡ�ļ���·��
	sPath+="\\res";
	sPath+="\\";
	showpicture();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
