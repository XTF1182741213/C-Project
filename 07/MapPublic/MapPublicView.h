// MapPublicView.h : interface of the CMapPublicView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "map.h"
//}}AFX_INCLUDES
#include "SpeciesSet.h"
#include "MapPublic.h"
#include "modataconnection.h"
#include "mopoint.h"
#include "morectangle.h"
#include "molayers.h"
#include "momaplayer.h"
#include "mogeodataset.h"
#include "mogeodatasets.h"
#include "mosymbol.h"
#include "mogrouprenderer.h"
#include "movaluemaprenderer.h"
#include "MapObjects2.h"
#include "MapHelper.h"
#include "FindDlg.h"
#include "MainFrm.h"

#include "MyNewThread.h"
#include "MusicThread.h"
#include "Led.h"
#if !defined(AFX_MAPPUBLICVIEW_H__F17ACC6C_67EF_4EAB_9567_827159CBCC7C__INCLUDED_)
#define AFX_MAPPUBLICVIEW_H__F17ACC6C_67EF_4EAB_9567_827159CBCC7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapPublicDoc.h"

#include "InfoMation.h"

#include "Led.h"

struct drawtext//��¼���ع���վ����Ϣ
{
	CMoPoint station_pt;
	CString strName;
	
};


class CMapPublicView : public CFormView
{
protected: // create from serialization only
	CMapPublicView();
	DECLARE_DYNCREATE(CMapPublicView)
		
public:
	//{{AFX_DATA(CMapPublicView)
	enum { IDD = IDD_MAPPUBLIC_FORM };
	CMap1	m_Map;
	CString m_editbox;
	CLed	m_Led23;
	CLed	m_Led22;
	CLed	m_Led21;
	CLed	m_Led20;
	CLed	m_Led19;
	CLed	m_Led18;
	CLed	m_Led17;
	CLed	m_Led16;
	CLed	m_Led15;
	CLed	m_Led14;
	CLed	m_Led13;
	CLed	m_Led12;
	CLed	m_Led11;
	CLed	m_Led10;
	CLed	m_Led9;
	CLed	m_Led8;
	CLed	m_Led7;
	CLed	m_Led6;
	CLed	m_Led5;
	CLed	m_Led4;
	CLed	m_Led3;
	CLed	m_Led2;
	CLed	m_Led1;
																//}}AFX_DATA
																
																// Attributes
public:
	CMapPublicDoc* GetDocument();
    CMoLayers m_layers;
    CMoMapLayer m_maplayer;
    CString sPath;//����·��
	CMoMapLayer m_mapLayer[28];//ÿһ��ҽӵ�ʸ������
   	//***********************************
	CString GetFileName(const CString &path);
	CString GetFileTitle(const CString &path);
	CString GetFileDirectory(const CString &path);
	/*layers ��ӵ�ͼ��
	
	*/
	CString AddShpLayer(CMoMapLayer mapLayer,const CString &VectorFileName,COLORREF color,short symbolSize,short symbolStyle,BOOL VisibleFlag,int index);
    //******************************************
	void OnSetLabelParameter(int index,COLORREF color,int FontSize);
	void AddLayer();
    void AddLabel(int index,COLORREF color,int FontSize);//��ӱ�ע
	CMoLayers m_players;//ȫ�ֱ���
	CMoMapLayer m_pmaplayer;//ȫ�ֱ���
	int Number;//���Ƶ�ͼ����ʾ
	
	bool bControlFlag;//���ƽ���ʾһ������ʱ��
	LayerInfo m_mapInfo[28];
	int m_nindex;//�ؼ��еĸ���ͼ��
	
	void ShowLayer();//ͼ����ʾ����
	void HideLayer();//ͼ�������
	
	//--------------------------------------
	//��������
	CMoPoint m_startPoint,m_endPoint;
	int m_mouseDownNum;
	CInfoMation Info;//ͼ����Ϣ
	CFindDlg finddlg;
	void FindArea(CString searchText);
	//----------------------------------------
	//����ѡ��
	CMoRecordset m_SelectRecSet;//���ڴ������õ��ļ�¼��,�Ա����������ʾ
	bool showflag;//���ڿ����Ƿ������ʾ
	bool showpointflag;//���ڿ����Ƿ������ʾ
	void GetSelectAttribute(long x,long y);//��ȡ��·����
	void GetPointAttribute(CString strName,long X,long Y);//��õ�������
	
	//------------------------------------------
	//���������ʽ
	UINT m_cur;
	HCURSOR m_Cursor;
	//-------------------------------------------
	//ˢ���Ա�ȥ�����
	//void flash();
	void require_attribute(CString string);
	//-----------------------------------------------
	// Operations
public:
	DWORD m_CurrentOperation;//��굱ǰ����
    bool pointflag;// ���ڿ��Ƶ���ѡ�񣬵��û�ѡ��һ����ʱ��
	CString strName;//���ڴ��ݵ���ͼ����
	bool bCheckMenu;//���Ʋ˵��Ƿ�ѡ��
	//�ſ���ʹ�õ���ѡ��Ŧ
	//----------------------------------------------------
	//�Զ���������վ��ͼ��
public:
	
	bool CreateNewLayer();//����һ���µ�ͼ��
	bool CreateTable(CMoRecordset m_RecSet);/////////nameΪ������
	bool Draw_TEXT(CMoFields ShapeFields,CString strName);//������վ����
	bool flashflag;//����ͼ���ˢ��
	drawtext m_Struct[200];
	
	//-------------------------------------------------------------
	CMyNewThread *p_thread;
	CMusicThread *p_music;
	//-----------------------------------------------------
	//��������
	BOOL PlayResource(WORD wResourceID);//�������
	void showlight();
	bool musicflag;//���ر�������
    CLed m_ledstatic;
	void  createled(int X,int Y);
	//--------------------------------------------------------------
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapPublicView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMapPublicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMapPublicView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMapZoomin();
	afx_msg void OnMapZoomout();
	afx_msg void OnMapPan();
	afx_msg void OnMouseDownMap1(short Button, short Shift, long X, long Y);
	afx_msg void OnMapFullshow();
	afx_msg void OnCommunity();
	afx_msg void OnBank();
	afx_msg void OnEducation();
	afx_msg void OnRestaurant();
	afx_msg void OnShop();
	afx_msg void OnTour();
	afx_msg void OnHospital();
	afx_msg void OnTraffic();
	afx_msg void OnEnterprise();
	afx_msg void OnGoverment();
	afx_msg void OnAll();
	afx_msg void OnSavebmp();
	afx_msg void OnMeasure();
	afx_msg void OnDblClickMap1();
	afx_msg void OnFind();
	afx_msg void OnDelStation();
	afx_msg void OnAddRoadway();
	afx_msg void OnDelRoadway();
	afx_msg void OnChangeStation();
	afx_msg void OnSelect();
	afx_msg void OnSelectAttribute();
	afx_msg void OnAfterLayerDrawMap1(short index, BOOL canceled, long hDC);
	afx_msg void OnSelectPoint();
	afx_msg void OnFresh();
	afx_msg void OnUpdateSelectPoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelStation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChangeStation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddRoadway(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelRoadway(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectAttribute(CCmdUI* pCmdUI);
	afx_msg void OnUserLogin();
	afx_msg void OnUpdateUserLogin(CCmdUI* pCmdUI);
	afx_msg void OnQuit();
	afx_msg void OnUpdateQuit(CCmdUI* pCmdUI);
	afx_msg void OnPublicBus();
	afx_msg void OnHelp();
	afx_msg void OnSysLog();
	afx_msg void OnUpdateSysLog(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMusic();
	afx_msg void OnUpdateMusic(CCmdUI* pCmdUI);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapPublicView.cpp
inline CMapPublicDoc* CMapPublicView::GetDocument()
{ return (CMapPublicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPUBLICVIEW_H__F17ACC6C_67EF_4EAB_9567_827159CBCC7C__INCLUDED_)
