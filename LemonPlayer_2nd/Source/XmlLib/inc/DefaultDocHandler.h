/*
 ============================================================================
 Name		: DefaultDocHandler.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDefaultDocHandler declaration
 ============================================================================
 */

#ifndef DEFAULTDOCHANDLER_H
#define DEFAULTDOCHANDLER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SyExpat.h"
// CLASS DECLARATION

/**
 *  CDefaultDocHandler
 * 
 */
class CDefaultDocHandler : 	public MSyDocHandler
	{
public:
	// Constructors and destructor
	~CDefaultDocHandler();
	CDefaultDocHandler();
	void ConstructL();
	
public: // From MSyDocHandler
	virtual void StartElement(const TQualified& aName, const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);
	virtual void CharacterData(const TDesC& aData);
	
	virtual void ProcessingInstruction(const TDesC& aTarget, const TDesC& aData);
	virtual void Comment(const TDesC& aData);
	virtual void StartCDataSection();
	virtual void EndCDataSection();
	virtual void Default(const TDesC& aData);
	virtual void SetParser(CExpatParserBase* aParser);

	};

#endif // DEFAULTDOCHANDLER_H
