/*
 ============================================================================
 Name		: ViewMotify.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CViewMotify declaration
 ============================================================================
 */

#ifndef VIEWMOTIFY_H
#define VIEWMOTIFY_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CViewMotify
 * 
 */
class CViewMotify : public CBase
	{
public:
	// Constructors and destructor

	~CViewMotify();
	static CViewMotify* NewL();
	static CViewMotify* NewLC();

private:

	CViewMotify();
	void ConstructL();
	};

class MMainViewNotify
	{
public:
	virtual void OnMainViewNotify() = 0;
	};

class MListBoxViewNotify
	{
public:
	virtual void OnListBoxViewNotify() = 0;
	};

#endif // VIEWMOTIFY_H
