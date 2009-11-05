/*
 ============================================================================
 Name		: TangImageDataWriter.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageDataWriter declaration
 ============================================================================
 */

#ifndef TANGIMAGEDATAWRITER_H
#define TANGIMAGEDATAWRITER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SyGen.h"
// CLASS DECLARATION
class CImageElement;

/**
 *  CTangImageDataWriter
 * 
 */
class CTangImageDataWriter : public CBase, public MSyOutputHandler
	{
public:
	// Constructors and destructor

	~CTangImageDataWriter();
	static CTangImageDataWriter* NewL(CImageElement** aElements);
	static CTangImageDataWriter* NewLC(CImageElement** aElements);

private:
	CTangImageDataWriter(CImageElement** aElements);
	void ConstructL();
	
protected:
	//MSyOutputHandler
	void WriteL(const TDesC& aString, const TBool aIsRawData);
	
public:
	void SaveDataToFile(const TDesC& aFileName);
	
private:
	void GenerateElementsData();

private:
	CImageElement** iElements;
	HBufC8 *iRequestXml;
	};

#endif // TANGIMAGEDATAWRITER_H
