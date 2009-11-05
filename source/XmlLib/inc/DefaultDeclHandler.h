/*
 ============================================================================
 Name		: DefaultDeclHandler.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDefaultDeclHandler declaration
 ============================================================================
 */

#ifndef DEFAULTDECLHANDLER_H
#define DEFAULTDECLHANDLER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SyExpat.h"
// CLASS DECLARATION

/**
 *  CDefaultDeclHandler
 * 
 */
class CDefaultDeclHandler : public MSyDeclHandler
	{
public:
	// Constructors and destructor
	~CDefaultDeclHandler();
	CDefaultDeclHandler();
	void ConstructL();

public:
	virtual TSyExpatStatus NotStandalone();
	virtual void StartDocType(const TDesC& aDocType, const TDesC& aSystemId,
			const TDesC& aPublicId, const TBool aHasInternalSubset);
	virtual void EndDocType();
	virtual void StartNamespace(const TDesC& aPrefix, const TDesC& aURI);
	virtual void EndNamespace(const TDesC& aPrefix);
	virtual void Entity(const TDesC& aName, const TBool aIsParameter,
			const TDesC& aValue, const TDesC& aBase, const TDesC& aSystemId,
			const TDesC& aPublicId, const TDesC& aNotation);
	virtual void SkippedEntity(const TDesC& aEntity, const TBool aIsParameter);
	virtual void Notation(const TDesC& aNotationName, const TDesC& aBase,
			const TDesC& aSystemId, const TDesC& aPublicId);
	virtual void SetParser(CExpatParserBase* aParser);
	};

#endif // DEFAULTDECLHANDLER_H
