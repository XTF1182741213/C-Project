// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitDBConnect()
{
	
	::CoInitialize(NULL);  //��ʼ��OLE/COM�⻷��
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");  //����connection����		
		m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;Database=HCCP;","","",adModeUnknown);
	  //m_pConnection->Open("driver={SQL Server};Server=HC\\MSSQL2008;Database=HCCP;UID=sa;PWD=","","",adModeUnknown);  //���������ַ���,������BSTR�ͻ���_bstr_t����
	}
	catch(_com_error e)  //��׽�쳣
	{
		AfxMessageBox(e.Description());//��ʾ������Ϣ
	}
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{		
		if(m_pConnection==NULL)  //�������ݿ�,���connection����Ϊ��,�������������ݿ�8
			OnInitDBConnect();
		
		m_pRecordset.CreateInstance(__uuidof(Recordset));  //������¼������		
		m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);  //ȡ�ü��еļ�¼
	}
	
	catch(_com_error e)  //��׽�쳣
	{
		AfxMessageBox(e.Description());  //��ʾ������Ϣ
	}
	return m_pRecordset;  //���ؼ�¼��
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{		
		if(m_pConnection==NULL)  //�Ƿ��Ѿ����ӵ����ݿ�
			OnInitDBConnect();
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	
	catch(_com_error e)  //��׽�쳣
	{
		AfxMessageBox(e.Description());  //��ʾ������Ϣ
		return false;
	}
}

void ADOConn::ExitConnect()
{	
	if(m_pRecordset!=NULL)  //�رռ�¼��������
	{
		m_pRecordset->Close();
		m_pConnection->Close();
	}
	
	::CoUninitialize();  //�ͷŻ���
}