// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B126AEC4_9365_4020_854C_7982C1F9B937__INCLUDED_)
#define AFX_STDAFX_H__B126AEC4_9365_4020_854C_7982C1F9B937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/////////////////////////////////////////////////////////////////////////
#include <WINSPOOL.H>


#define	 B5_W			182				//B5ֽ���mm
#define	 B5_H			257				//B5ֽ�߶�mm
#define	 B5_ONELINE		29				//B5ֽ��һҳ����
#define	 B5_OTHERLINE	30				//B5ֽ����ҳ����

//��ӡ�ṹ
typedef struct
{
	int 	nMaxLine;			//�������
	int		nCountPage;			//һ��ҳ��
	int		nCurPage;			//��ǰҳ��
	BOOL	IsPrint;			//�Ƿ��ӡ
	HWND	hWnd;				//���ھ��
	HWND	hListView;			//�б�ؼ����
	TCHAR	szTag[256];			//��������
	int		nTag;				//��������
	LPVOID	lpVoid;				//��������
}PRNINFO, *PPRNINFO;

typedef void(*PRINTPREVIEW) (CDC &MemDC, PRNINFO PrnInfo);
#include "Resource.h"
///////////////////////////////////////////////////////////////////////// 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B126AEC4_9365_4020_854C_7982C1F9B937__INCLUDED_)
