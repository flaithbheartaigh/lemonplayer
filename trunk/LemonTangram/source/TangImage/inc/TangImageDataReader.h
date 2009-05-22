/*
 ============================================================================
 Name		: TangImageDataReader.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageDataReader declaration
 ============================================================================
 */

#ifndef TANGIMAGEDATAREADER_H
#define TANGIMAGEDATAREADER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "DefaultDocHandler.h"
#include "TangImageXmlDefine.h"
// CLASS DECLARATION
class CImageElement;
class CImageRotator;
/**
 *  CTangImageDataReader
 * 
 */
class CTangImageDataReader : public CBase, public CDefaultDocHandler
	{
public:
	// Constructors and destructor
	~CTangImageDataReader();
	static CTangImageDataReader* NewL(CImageElement** aElements);
	static CTangImageDataReader* NewLC(CImageElement** aElements);

	//CDefaultDocHandler
	virtual void StartElement(const TQualified& aName,
			const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);
	
	void LoadImageDataFileL(const TDesC& aFileName);
private:
	CTangImageDataReader(CImageElement** aElements);
	void ConstructL();
	
	TInt ConvertNameToNumber(const TDesC& aName);	
	void ParseImg(const RArray<TAttribute>& aAttributes);

private:
	CImageElement** iElements;
//	CImageRotator** iRotator;
	};

#endif // TANGIMAGEDATAREADER_H
