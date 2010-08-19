/*
 ============================================================================
 Name		: ListBoxPainter.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxPainter implementation
 ============================================================================
 */

#include "ListBoxPainter.h"
#include <eikenv.h>

const TInt KItemPadding = 4;

CListBoxPainter::CListBoxPainter()
:iItemPadding(KItemPadding),iItemHeight(0)
	{
	// No implementation required
	}

CListBoxPainter::~CListBoxPainter()
	{
	}

CListBoxPainter* CListBoxPainter::NewLC()
	{
	CListBoxPainter* self = new (ELeave) CListBoxPainter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CListBoxPainter* CListBoxPainter::NewL()
	{
	CListBoxPainter* self = CListBoxPainter::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CListBoxPainter::ConstructL()
	{

	}

const CFont* CListBoxPainter::GetFont()
	{
	return CEikonEnv::Static()->AnnotationFont();
	}

TInt CListBoxPainter::GetItemHeight()
	{
	if (!iItemHeight)
		{
		iItemHeight = GetFont()->HeightInPixels();
		iItemHeight += iItemPadding;
	
		TInt offset = iItemHeight % GetAnimationItemScrollFrame();
		if (offset)
			iItemHeight += GetAnimationItemScrollFrame()-offset;
		}
	return iItemHeight;
	}
