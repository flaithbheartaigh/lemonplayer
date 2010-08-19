/*
 ============================================================================
 Name		: LemonMenuBar.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuBar declaration
 ============================================================================
 */

#ifndef LEMONMENUBAR_H
#define LEMONMENUBAR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <COEDEF.H>
#include <BITSTD.H>
#include <W32STD.H>

// CLASS DECLARATION

/**
 *  CLemonMenuBar
 * 
 */
class CLemonMenuBar : public CBase
	{
public:
	// Constructors and destructor
	~CLemonMenuBar();
	static CLemonMenuBar* NewL();
	static CLemonMenuBar* NewLC();

	void Draw(CBitmapContext& gc,TBool aActive);
private:
	CLemonMenuBar();
	void ConstructL();
	
	enum TOptionState
		{
		EOptionLeftHide = 0,
		EOptionRightHide,
		EOptionLeftActive,
		EOptionRightActive,
		EOptionTotal
		};

private:
	CFbsBitmap* iFrame;
	TRgb iTextColor;
	TBuf<10> iOptionText[EOptionTotal];
	
	
	};

#endif // LEMONMENUBAR_H
