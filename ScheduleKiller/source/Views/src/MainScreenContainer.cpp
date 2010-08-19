/*
 ============================================================================
 Name		: MainScreenContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include "MainScreenContainer.h"

#include <akniconutils.h> 	//AknIconUtils
#include <aknsutils.h> 		//AknsUtils 
#include "SHPlatform.h"
#include "MacroUtil.h"

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer* CMainScreenContainer::NewL(const TRect& aRect)
	{
	CMainScreenContainer* self = CMainScreenContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer* CMainScreenContainer::NewLC(const TRect& aRect)
	{
	CMainScreenContainer* self = new (ELeave) CMainScreenContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// C$(baseName)AppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	//InitTest();
	InitClockDigital();
	InitIcon();

	iBgContext = CAknsBasicBackgroundControlContext::NewL(
			KAknsIIDQsnBgAreaMain, aRect, ETrue);

	SetRect(aRect);
	ActivateL();

	//add your code here ...
	//if (SHModel()->IsEmputy() == EFalse)
	Start();
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::C$(baseName)AppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CMainScreenContainer::CMainScreenContainer() :
	iInitIcon(EFalse), iIcon(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::~C$(baseName)AppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer::~CMainScreenContainer()
	{
		// No implementation required

		SAFE_DELETE(iBgContext)

		SAFE_DELETE(iIcon)

	iClock->ResetAndDestroy();
	delete iClock;

		SAFE_DELETE_ACTIVE(iPeriodicTimer)
	}

// ---------------------------------------------------------
// CMainScreenContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CMainScreenContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CMainScreenContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CMainScreenContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// -----------------------------------------------------------------------------
// CMainScreenContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
	AknsDrawUtils::Background(skin, cc, this, gc, drawRect);

	if (SHModel()->IsEmputy() == EFalse)
		{
		DrawClock();
		DrawApp();
		}
	}

// -----------------------------------------------------------------------------
// CMainScreenContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::SizeChanged()
	{
	if (iBgContext)
		{
		iBgContext->SetRect(Rect());
		if (&Window())
			{
			iBgContext->SetParentPos(PositionRelativeToScreen());
			}
		}

	DrawNow();
	}

// ---------------------------------------------------------
// CMainScreenContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CMainScreenContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}
TKeyResponse CMainScreenContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode /*aType*/)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		default:
			// Let Listbox take care of its key handling           
			break;
		}
	return EKeyWasNotConsumed;
	}

void CMainScreenContainer::DrawClock() const
	{
	RArray<TInt> array;
	TTime time = SHModel()->GetTime();
	TTime now;
	now.HomeTime();

	if (time > now)
		ParseLeftTime((TInt) (time.MicroSecondsFrom(now).Int64() / 1000000ll),
				array);

	TInt x, y;
	TInt count = array.Count();
	x = (Rect().Width() - (count - 1) * SHUI()->GetClockSingleDigitalWidth()
			- SHUI()->GetClockColonWidth()) / 2;
	y = (Rect().Height() - SHUI()->GetContentHeight()) / 2;
	for (TInt i = 0; i < count; i++)
		{
		TInt index = array[i];
		DrawClockDigital(index, TPoint(x, y));
		if (index < 10)
			x += SHUI()->GetClockSingleDigitalWidth();
		else
			x += SHUI()->GetClockColonWidth();
		}

	array.Close();
	}

void CMainScreenContainer::DrawApp() const
	{
	const TDesC& name = SHModel()->GetName();
	const CFont* font = SHUI()->GetFont();

	TInt padding = 4;
	TInt fontWidth = font->MeasureText(name);
	TInt x = (Rect().Width() - SHUI()->GetIconSize().iWidth - fontWidth
			- padding) / 2;
	TInt y = (Rect().Height() - SHUI()->GetContentHeight()) / 2
			+ SHUI()->GetClockHeight() + SHUI()->GetPadding();
	TSize size = SHUI()->GetIconSize();

	CFbsBitmap* b1 = iIcon->Bitmap();
	CFbsBitmap* b2 = iIcon->Mask();
	AknIconUtils::SetSize(b1, size, EAspectRatioNotPreserved);
	AknIconUtils::SetSize(b2, size, EAspectRatioNotPreserved);

	CWindowGc& gc = SystemGc();
	TPoint point = TPoint(x, y);

	gc.BitBltMasked(point, b1, size, b2, EFalse);
	//gc.BitBlt(point, b1);

	x += size.iWidth + padding;
	size.iWidth = fontWidth;
	TRect rect = TRect(TPoint(x, y), size);

	TRgb color;
	AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), color,
			KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG1/*EAknsCIQsnLineColorsCG1 */);	
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(color);
	gc.UseFont(font);
	gc.DrawText(name, rect, rect.Height() / 2 + font->AscentInPixels() / 2,
			CGraphicsContext::ELeft, 0);
	gc.DiscardFont();
	}

void CMainScreenContainer::DrawClockDigital(TInt& aNumber, const TPoint& aPoint) const
	{
	CWindowGc& gc = SystemGc();
	if (aNumber >= 0)
		{
		TInt index = aNumber;
		if (aNumber > 9)
			index = 10;
		CGulIcon* icon = (*iClock)[index];

		TSize size;
		if (aNumber < 10)
			size = SHUI()->GetClockSingleDigtalSize();
		else
			size = SHUI()->GetClockColonSize();
		CFbsBitmap* b1 = icon->Bitmap();
		CFbsBitmap* b2 = icon->Mask();

		AknIconUtils::SetSize(b1, size, EAspectRatioNotPreserved);
		AknIconUtils::SetSize(b2, size, EAspectRatioNotPreserved);

		//		TRect rect = TRect(aPoint, size);
		gc.BitBltMasked(aPoint, b1, size, b2, EFalse);
		//		gc.BitBlt(aPoint, b1);
		}
	}

TInt CMainScreenContainer::ParseLeftTime(TInt aSecend, RArray<TInt>& aArray) const
	{
	TInt minute, secend;
	minute = aSecend / 60;
	secend = aSecend % 60;

	if (minute >= 10)
		{
		ParseNumber(minute, aArray);
		}
	else if (minute > 0)
		{
		aArray.Append(0);
		aArray.Append(minute);
		}
	else
		{
		aArray.Append(0);
		aArray.Append(0);
		}

	aArray.Append(10); //:

	aArray.Append(secend / 10);
	aArray.Append(secend % 10);

	return KErrNone;
	}

TInt CMainScreenContainer::ParseNumber(TInt aNumber, RArray<TInt>& aArray) const
	{
	TInt high = aNumber / 10;
	TInt low = aNumber % 10;

	while (high)
		{
		aArray.Insert(low, 0);

		low = high % 10;
		high = high / 10;
		}
	aArray.Insert(low, 0);

	return KErrNone;
	}

void CMainScreenContainer::InitClockDigital()
	{
	iClock = new RPointerArray<CGulIcon> (4);

	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewZero, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewOne, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewTwo, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewThree, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewFour, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewFive, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewSix, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewSeven, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewEight, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewNine, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewColon, ETrue));
	}

void CMainScreenContainer::InitIcon()
	{
	CFbsBitmap* AppIcon(NULL);
	CFbsBitmap* AppIconMsk(NULL);
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	TSize size = SHUI()->GetIconSize();
	TRAPD(err, AknsUtils::CreateAppIconLC(skin, SHModel()->GetUid(), EAknsAppIconTypeList, AppIcon, AppIconMsk);CleanupStack::Pop(2));
		//	AknIconUtils::SetSize(AppIcon, size, EAspectRatioNotPreserved);
		//	AknIconUtils::SetSize(AppIconMsk, size, EAspectRatioNotPreserved);
		SAFE_DELETE(iIcon);
	if (err == KErrNone)
		{
		iIcon = CGulIcon::NewL(AppIcon, AppIconMsk);
		}
	else
		{
		iIcon = AknsUtils::CreateGulIconL(skin, KAknsIIDQgnMenuUnknownLst,
				ETrue);
		}
	}

void CMainScreenContainer::InitTest()
	{
	TTime time;
	time.HomeTime();
	//	time += TTimeIntervalSeconds(10);
	time += TTimeIntervalMinutes(30);
	SHModel()->SetName(_L("Radio"));
	SHModel()->SetTime(time);
	SHModel()->SetUid(TUid::Uid(0x101FF976));
	}

void CMainScreenContainer::Start()
	{
	if (iPeriodicTimer && !iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Start(1, 1000000, TCallBack(
				CMainScreenContainer::Period, this));
		}
	}
void CMainScreenContainer::Stop()
	{
	if (iPeriodicTimer && iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Cancel();
		}
	}

TInt CMainScreenContainer::Period(TAny* aPtr)
	{
	(static_cast<CMainScreenContainer*> (aPtr))->DoPeriodTask();
	// Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

void CMainScreenContainer::DoPeriodTask()
	{
	Update();

	DrawNow();
	}

void CMainScreenContainer::Update()
	{
	if (!iInitIcon)
		{
		if (!SHModel()->IsEmputy())
			{
			iInitIcon = ETrue;
			InitIcon(); //ÖØÐÂ³õÊ¼icon
			}
		}
	}

void CMainScreenContainer::KillProcess()
	{
	TUid uid = SHModel()->GetUid();

	TApaTaskList taskList(CEikonEnv::Static()->WsSession());
	TApaTask task = taskList.FindApp(uid);
	if (task.Exists())
		{
		task.EndTask();
		task.KillTask();
		}
	}

TTypeUid::Ptr CMainScreenContainer::MopSupplyObject(TTypeUid aId)
	{
	if (iBgContext)
		{
		return MAknsControlContext::SupplyMopObject(aId, iBgContext);
		}
	return CCoeControl::MopSupplyObject(aId);
	}
// End of File

