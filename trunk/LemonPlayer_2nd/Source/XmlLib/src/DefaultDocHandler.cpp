/*
 ============================================================================
 Name		: DefaultDocHandler.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDefaultDocHandler implementation
 ============================================================================
 */

#include "DefaultDocHandler.h"

CDefaultDocHandler::CDefaultDocHandler()
	{
	// No implementation required
	}

CDefaultDocHandler::~CDefaultDocHandler()
	{
	}

void CDefaultDocHandler::ConstructL()
	{

	}

void CDefaultDocHandler::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	}
void CDefaultDocHandler::EndElement(const TQualified& aName)
	{
	}
void CDefaultDocHandler::CharacterData(const TDesC& aData)
	{
	}

void CDefaultDocHandler::ProcessingInstruction(const TDesC& aTarget,
		const TDesC& aData)
	{
	}

void CDefaultDocHandler::Comment(const TDesC& aData)
	{
	}

void CDefaultDocHandler::StartCDataSection()
	{
	}

void CDefaultDocHandler::EndCDataSection()
	{
	}

void CDefaultDocHandler::Default(const TDesC& aData)
	{
	}

void CDefaultDocHandler::SetParser(CExpatParserBase* aParser)
	{
	}
