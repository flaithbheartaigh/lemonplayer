#include <aknutils.h>
#include <COEMAIN.H>
#include <eikapp.h>
#include <eikenv.h>
#include <GULICON.H>

#include "LMSvgUtil.h"
#include "Utils.h"

#ifdef EKA2
#include "IconFileProvider.h"
#include "ScheduleKillerDocument.h"
#endif

_LIT(KIconBasename, "ScheduleKiller.mbm");
_LIT(KIconPath, "\\resource\\apps\\");
		
LMSvgUtil::~LMSvgUtil()
	{
	}

LMSvgUtil::LMSvgUtil()
	{
	}

TInt LMSvgUtil::SetIconSize(CFbsBitmap* aBitmap, const TSize& aSize)
	{
#ifdef EKA2
	return AknIconUtils::SetSize(aBitmap, aSize, EAspectRatioNotPreserved);
#else
	//aBitmap->Resize(aSize);
	return 0;
#endif
	}

CFbsBitmap* LMSvgUtil::GetImageFromResourceL(TInt aId)
	{
	TFileName filename;
	CFbsBitmap* image= NULL;

	GetAppPath(filename);
#ifdef __WINS__
	filename[0] = 'z';
#endif	

#ifdef EKA2
	CScheduleKillerDocument* document = (CScheduleKillerDocument*)((CEikAppUi*)(CEikonEnv::Static()->AppUi()))->Document();
	CIconFileProvider* iconProvider = document->GetIconFileProvider();
	if (iconProvider == NULL)
		{
		filename.Append(KIconBasename);
		iconProvider = CIconFileProvider::NewL(CEikonEnv::Static()->FsSession(), filename);
		CleanupStack::PushL(iconProvider);
		document->SetIconFileProvider(iconProvider);
		CleanupStack::Pop();
		}
	image = AknIconUtils::CreateIconL(*iconProvider, aId);
	image->SetDisplayMode(EColor64K);
#else
	filename.Append( KIconBasename );
	image = CEikonEnv::Static()->CreateBitmapL( filename, aId );
#endif
	return image;
	}

void LMSvgUtil::GetImageAndMaskFormResourceL(CFbsBitmap*& aBitmap,
		CFbsBitmap*& aBitmapMask, TInt aBitmapId, TInt aMaskId)
	{
	TFileName filename;
	GetAppPath(filename);
#ifdef __WINS__
	filename[0] = 'z';
#endif	

#ifdef EKA2
	CScheduleKillerDocument* document = (CScheduleKillerDocument*)((CEikAppUi*)(CEikonEnv::Static()->AppUi()))->Document();
	CIconFileProvider* iconProvider = document->GetIconFileProvider();
	if (iconProvider == NULL)
		{
		filename.Append(KIconBasename);
		iconProvider = CIconFileProvider::NewL(CEikonEnv::Static()->FsSession(), filename);
		CleanupStack::PushL(iconProvider);
		document->SetIconFileProvider(iconProvider);
		CleanupStack::Pop();
		}
	AknIconUtils::CreateIconL(aBitmap, aBitmapMask, *iconProvider,
			aBitmapId, aMaskId);
	aBitmap->SetDisplayMode(EColor64K);
	//aBitmapMask->SetDisplayMode(EColor64K);
#else
	filename.Append( KIconBasename );
#endif
	
	}

CGulIcon* LMSvgUtil::GetIconFormResourceL(TInt aBitmapId, TInt aMaskId)
	{
	CGulIcon* icon = CGulIcon::NewL();
	CFbsBitmap* bitmap;
	CFbsBitmap* mask;
	GetImageAndMaskFormResourceL(bitmap,mask,aBitmapId,aMaskId);
	icon->SetBitmap(bitmap);
	icon->SetMask(mask);
	return icon;
	}

void LMSvgUtil::GetImageAndMaskFormResourcePathL(CFbsBitmap*& aBitmap,
		CFbsBitmap*& aBitmapMask, TInt aBitmapId, TInt aMaskId)
	{
	TFileName filename;
	
    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->AppFullName());
    filename.Append(parse.Drive());
    filename.Append(KIconPath);
	
#ifdef __WINS__
	filename[0] = 'z';
#endif	

#ifdef EKA2
	CScheduleKillerDocument* document = (CScheduleKillerDocument*)((CEikAppUi*)(CEikonEnv::Static()->AppUi()))->Document();
	CIconFileProvider* iconProvider = document->GetIconFileProvider();
	if (iconProvider == NULL)
		{
		filename.Append(KIconBasename);
		iconProvider = CIconFileProvider::NewL(CEikonEnv::Static()->FsSession(), filename);
		CleanupStack::PushL(iconProvider);
		document->SetIconFileProvider(iconProvider);
		CleanupStack::Pop();
		}
	AknIconUtils::CreateIconL(aBitmap, aBitmapMask, *iconProvider,
			aBitmapId, aMaskId);
	aBitmap->SetDisplayMode(EColor64K);
	//aBitmapMask->SetDisplayMode(EColor64K);
#else
	filename.Append( KIconBasename );
#endif
	
	}
