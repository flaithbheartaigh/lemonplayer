/*
 ============================================================================
 Name		: ListBoxHighLightControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxHighLightControl implementation
 ============================================================================
 */

#include "ListBoxHighLightControl.h"

CListBoxHighLightControl::CListBoxHighLightControl()
	{
	// No implementation required
	}

CListBoxHighLightControl::~CListBoxHighLightControl()
	{
	}

CListBoxHighLightControl* CListBoxHighLightControl::NewLC()
	{
	CListBoxHighLightControl* self = new (ELeave) CListBoxHighLightControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CListBoxHighLightControl* CListBoxHighLightControl::NewL()
	{
	CListBoxHighLightControl* self = CListBoxHighLightControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CListBoxHighLightControl::ConstructL()
	{

	}

void CListBoxHighLightControl::Draw(CBitmapContext& gc) const
	{
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	if (iPainter)
		gc.SetBrushColor( iPainter->GetHightLightClock() );
	
	gc.Clear(Rect());
	}
