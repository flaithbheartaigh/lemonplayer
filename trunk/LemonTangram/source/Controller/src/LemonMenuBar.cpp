/*
 ============================================================================
 Name		: LemonMenuBar.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuBar implementation
 ============================================================================
 */

#include "LemonMenuBar.h"

CLemonMenuBar::CLemonMenuBar()
	{
	// No implementation required
	}

CLemonMenuBar::~CLemonMenuBar()
	{
	}

CLemonMenuBar* CLemonMenuBar::NewLC()
	{
	CLemonMenuBar* self = new (ELeave)CLemonMenuBar();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuBar* CLemonMenuBar::NewL()
	{
	CLemonMenuBar* self=CLemonMenuBar::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonMenuBar::ConstructL()
	{

	}
