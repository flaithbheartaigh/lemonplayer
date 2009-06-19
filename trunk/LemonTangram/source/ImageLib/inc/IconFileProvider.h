/*
 ============================================================================
 Name		: IconFileProvider.h
 Author	  : zhanghua
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CIconFileProvider declaration
 ============================================================================
 */

#ifndef ICONFILEPROVIDER_H
#define ICONFILEPROVIDER_H

// INCLUDES


#ifdef EKA2
#include <akniconutils.h> 

class MEikCommandObserver;

class CIconFileProvider : public CBase, public MAknIconFileProvider 
{	
public:
	CIconFileProvider(RFs aSession);
	static CIconFileProvider* NewL(RFs aSession, const TDesC& aFilename);
	void ConstructL( const TDesC& aFilename);
	~CIconFileProvider();
private:
	//from MAknIconFileProvider
	void RetrieveIconFileHandleL( RFile& aFile, const TIconFileType aType );
    void Finished();
    
    RFs iSession;
    HBufC* iFilename;
};
#endif//EKA2

#endif // ICONFILEPROVIDER_H
