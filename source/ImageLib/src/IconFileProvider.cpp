/*
 ============================================================================
 Name		: IconFileProvider.cpp
 Author	  : zhanghua
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CIconFileProvider implementation
 ============================================================================
 */

#include "IconFileProvider.h"

#ifdef EKA2
// Since the AknIconUtils cannot access the private directory of application,
// mix-in class MAknIconFileProvider is implemented to provide handle of the 
// icon files (ScalableScreenDrawingIcons.mbm in this case) to AknIconUtils.
CIconFileProvider::CIconFileProvider(RFs aSession) : iSession(aSession)
    {
    }

// Destructor
CIconFileProvider::	~CIconFileProvider()
{
	delete iFilename;
    iFilename = NULL;
}


CIconFileProvider* CIconFileProvider::NewL(RFs aSession, const TDesC& aFilename)
{
    CIconFileProvider* self = new (ELeave) CIconFileProvider(aSession);
    CleanupStack::PushL(self);
    self->ConstructL(aFilename);
    CleanupStack::Pop(); // self
    return self;
}

// Second-phase constructor
void CIconFileProvider::ConstructL(const TDesC& aFilename)
{
	  iFilename = aFilename.AllocL();
}

void CIconFileProvider::RetrieveIconFileHandleL( RFile& aFile, const TIconFileType aType )
{
	// MAknIconFileProvider will by default try to open files that
	// have .mif extension first. If in case of this application, only the
	// file handle of ScalableScreenDrawingIcons.mbm is passed to framework,
	// MAknIconFileProvider result will be KErrArgument. This is solved by
	// giving the correct file extension determined by function parameter
	// aType.
	// 
    TFileName filename;
    
    filename = iFilename->Left(iFilename->Length()-3);
    
    if (aType == EMifFile) 
        {
        filename.Append(_L("mif"));
        }
    else // mbm
        {
        filename.Append(_L("mbm"));
        }
    
	User::LeaveIfError(aFile.Open(iSession, filename, EFileShareAny));
}

void CIconFileProvider::Finished()
{
}
#endif //EKA2