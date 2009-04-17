/*
 ============================================================================
 Name		: InformationContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CInformationContainer declaration
 ============================================================================
 */

#ifndef INFORMATIONCONTAINER_H
#define INFORMATIONCONTAINER_H
#include <aknapp.h>
#include <eikenv.h>			// for CEikonEnv
#include <eikmenub.h>		// for CEikMenuBar
#include <eiksbfrm.h>		// for CEikScrollBarFrame
class CInformationContainer : public CCoeControl, MCoeControlObserver,
		MEikScrollBarObserver
	{
public:
	void ConstructL(const TRect& aRect);
	~CInformationContainer();
	void setInformationL(const TDesC& info);
private:
	TInt calcLineChar(const TDesC& info, TInt& thisEnd, TInt& nextStart);

	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleScrollEventL(CEikScrollBar* aScrollBar,
			TEikScrollEvent aEventType);

	const CFont* iFont;
	CDesCArray* iInfoArray;
	CEikScrollBarFrame *iScrollBar;

	TBool iWordWrap;
	TUint iBorderWidth;
	TUint iBorderHeight;
	TUint iLeftMargin;
	TUint iRightMargin;
	TUint iTopMargin;
	TUint iLineSpace;
	TInt iDispLines;
	TUint iTopLine;
	};

#endif // INFORMATIONCONTAINER_H
