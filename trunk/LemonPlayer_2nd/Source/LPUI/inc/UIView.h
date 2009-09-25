/*
 ============================================================================
 Name		: UIView.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIView declaration
 ============================================================================
 */

#ifndef UIVIEW_H
#define UIVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
// CLASS DECLARATION
class CUIViewData;
/**
 *  CUIView
 * 
 */
class CUIView : public CBase
	{
public:
	~CUIView();
	static CUIView* NewL();
	static CUIView* NewLC();

private:
	CUIView();
	void ConstructL();

	};

class CUIDisplay : public CBase
	{
public:
	~CUIDisplay();
	static CUIDisplay* NewL(CUIViewData *aData);
	static CUIDisplay* NewLC(CUIViewData *aData);

private:
	CUIDisplay(CUIViewData *aData);
	void ConstructL();
	
public:
	void Draw(CWindowGc& aGc);
	void Draw(CFbsBitGc& aBitGc);
	
private:
	void DrawControlViewData(CBitmapContext& aGc,TInt index);
	
private:
	CUIViewData *iData;

	};

#endif // UIVIEW_H
