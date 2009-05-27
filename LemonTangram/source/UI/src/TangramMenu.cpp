/*
 ============================================================================
 Name		: TangramMenu.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramMenu implementation
 ============================================================================
 */

#include "TangramMenu.h"

CTangramMenu::CTangramMenu()
	{
	// No implementation required
	}

CTangramMenu::~CTangramMenu()
	{
	}

CTangramMenu* CTangramMenu::NewLC()
	{
	CTangramMenu* self = new (ELeave)CTangramMenu();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangramMenu* CTangramMenu::NewL()
	{
	CTangramMenu* self=CTangramMenu::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangramMenu::ConstructL()
	{

	}
