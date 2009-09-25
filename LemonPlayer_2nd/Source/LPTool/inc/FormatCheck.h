#ifndef FORMATCHECK_H_
#define FORMATCHECK_H_

#include <e32std.h>
#include <e32base.h>
#include <badesca.h>

class FormatCheck
	{
public:
	FormatCheck();
	~FormatCheck();
	static FormatCheck* GetInstance();
	
	TBool IsAllowedFormat(const TDesC& aExt);
	
private:
	void ConstructL();
	
private:
	static FormatCheck* iInstance;
	CDesCArray* iFormatArray;
	};
#endif /*FORMATCHECK_H_*/
