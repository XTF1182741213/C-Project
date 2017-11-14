// AdoRecordset.cpp: implementation of the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoRecordset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoRecordset::CAdoRecordset()
{

}

CAdoRecordset::~CAdoRecordset()
{

}

void CAdoRecordset::SetDatabase(CAdoDatabase* pDB)
{
	m_pDB = pDB;
}

CString CAdoRecordset::VariantToCString(const _variant_t &var)
{
	CString strValue;	

	switch (var.vt)
	{
	case VT_BSTR://�ַ���
	case VT_LPSTR:
	case VT_LPWSTR:
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1://�޷����ַ�
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://������
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://�޷��Ŷ�����
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://����
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //����
	case VT_I8: //������
		 strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://�޷�������
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //�޷�������
	case VT_UI8: //�޷��ų�����
		 strValue.Format("%d", var.ulVal);
		 break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://������
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://˫������
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //С��
		strValue.Format("%.8f", (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = "[BLOB]";
		break;
	case VT_BOOL://������		
		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //������
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULLֵ
	case VT_EMPTY://��
		 strValue = "";
		 break;
	case VT_UNKNOWN://δ֪����
	default:
		strValue = "UN_KNOW";
		break;
	}

	return strValue;
}

BOOL CAdoRecordset::OpenRecordset(const CString &strSQL)
{
	if(!m_pDB) {
		AfxMessageBox(_T("CourseWare���ݼ�û�й������ݿ�!"));
		return FALSE;
	}

	//	create the Recordset object
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	try
	{
		//	open the table from the database
		m_pRecordset->CursorLocation = adUseClient;
		m_pRecordset->Open(strSQL.AllocSysString(), 
			m_pDB->m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch (_com_error e)
	{
		CString strError;
		strError.Format(_T("warning��exception in opening table, error info�� %s"),\
			e.ErrorMessage());
		AfxMessageBox(strError);
		return FALSE;
	}
	return TRUE;
}
