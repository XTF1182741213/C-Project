#if !defined(AFX_VCWEIGHTING_H__5E31D391_B1CD_490A_B2B7_8FE56F072D89__INCLUDED_)
#define AFX_VCWEIGHTING_H__5E31D391_B1CD_490A_B2B7_8FE56F072D89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVcWeighting wrapper class

class CVcWeighting : public COleDispatchDriver
{
public:
	CVcWeighting() {}		// Calls COleDispatchDriver default constructor
	CVcWeighting(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcWeighting(const CVcWeighting& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetBasis();
	void SetBasis(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	void Set(long Basis, long Style);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCWEIGHTING_H__5E31D391_B1CD_490A_B2B7_8FE56F072D89__INCLUDED_)
