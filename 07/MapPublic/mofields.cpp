// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "mofields.h"

// Dispatch interfaces referenced by this interface
#include "mofield.h"


/////////////////////////////////////////////////////////////////////////////
// CMoFields properties

short CMoFields::GetCount()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void CMoFields::SetCount(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMoFields operations

CMoField CMoFields::Item(const VARIANT& Item)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		&Item);
	return CMoField(pDispatch);
}
