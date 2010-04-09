/*
 ============================================================================
 Name		: UIManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIManager implementation
 ============================================================================
 */

#include "UIManager.h"
#include <eikenv.h>

CUIManager::CUIManager()
	{
	// No implementation required
	}

CUIManager::~CUIManager()
	{
	}

CUIManager* CUIManager::NewLC()
	{
	CUIManager* self = new (ELeave) CUIManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIManager* CUIManager::NewL()
	{
	CUIManager* self = CUIManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIManager::ConstructL()
	{

	}

const CFont* CUIManager::GetFont()
	{
	return CEikonEnv::Static()->AnnotationFont();
	}

TBool CUIManager::CheckPenEnabled()
	{
	TBool penEnabled = EFalse;

	RLibrary avkonDll;
	if (avkonDll.Load(_L( "avkon.dll" )) == KErrNone)
		{
#ifdef __WINS__
		TLibraryFunction PenEnabled = avkonDll.Lookup(3184);
#else
		TLibraryFunction PenEnabled = avkonDll.Lookup( 4251 );
#endif

		if (PenEnabled != NULL)
			{
			penEnabled = PenEnabled();
			}

		avkonDll.Close();
		}
	return penEnabled;

	}
