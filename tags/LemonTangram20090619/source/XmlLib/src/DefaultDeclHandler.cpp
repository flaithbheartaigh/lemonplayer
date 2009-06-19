/*
 ============================================================================
 Name		: DefaultDeclHandler.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDefaultDeclHandler implementation
 ============================================================================
 */

#include "DefaultDeclHandler.h"

CDefaultDeclHandler::CDefaultDeclHandler()
	{
	// No implementation required
	}

CDefaultDeclHandler::~CDefaultDeclHandler()
	{
	}

void CDefaultDeclHandler::ConstructL()
	{

	}

TSyExpatStatus CDefaultDeclHandler::NotStandalone()
	{
	return EStatusOk;
	}

void CDefaultDeclHandler::StartDocType(const TDesC& aDocType,
		const TDesC& aSystemId, const TDesC& aPublicId,
		const TBool aHasInternalSubset)
	{
	}

void CDefaultDeclHandler::EndDocType()
	{
	}

void CDefaultDeclHandler::StartNamespace(const TDesC& aPrefix, const TDesC& aURI)
	{
	}

void CDefaultDeclHandler::EndNamespace(const TDesC& aPrefix)
	{
	}

void CDefaultDeclHandler::Entity(const TDesC& aName, const TBool aIsParameter,
		const TDesC& aValue, const TDesC& aBase, const TDesC& aSystemId,
		const TDesC& aPublicId, const TDesC& aNotation)
	{
	}

void CDefaultDeclHandler::SkippedEntity(const TDesC& aEntity,
		const TBool aIsParameter)
	{
	}

void CDefaultDeclHandler::Notation(const TDesC& aNotationName,
		const TDesC& aBase, const TDesC& aSystemId, const TDesC& aPublicId)
	{
	}

void CDefaultDeclHandler::SetParser(CExpatParserBase* aParser)
	{
	}