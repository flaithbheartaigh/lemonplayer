/*
 ============================================================================
 Name		: PlaylistNodeParser.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistNodeParser implementation
 ============================================================================
 */

#include "PlaylistNodeParser.h"
#include "PlaylistDataMgr.h"

CPlaylistNodeParser::CPlaylistNodeParser() :
	iTreeIndex(KErrNotFound)
	{
	// No implementation required
	}

CPlaylistNodeParser::~CPlaylistNodeParser()
	{
	}

CPlaylistNodeParser* CPlaylistNodeParser::NewLC()
	{
	CPlaylistNodeParser* self = new (ELeave)CPlaylistNodeParser();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistNodeParser* CPlaylistNodeParser::NewL()
	{
	CPlaylistNodeParser* self=CPlaylistNodeParser::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistNodeParser::ConstructL()
	{

	}

TInt CPlaylistNodeParser::ConvertNameToNumber(const TDesC& aName)
	{
	HBufC* text = aName.AllocL();
	text->Des().LowerCase();
	TInt re = KPlaylistParserNone;

	if (text->Compare(KPlaylistDomTagNode) == 0)
		{
		re = KPlaylistParserNode;
		}
	else
		if (text->Compare(KPlaylistDomTagTree) == 0)
			{
			re = KPlaylistParserTree;
			}
		else
			if (text->Compare(KPlaylistDomTagParent) == 0)
				{
				re = KPlaylistParserParent;
				}
			else
				if (text->Compare(KPlaylistDomTagChildren) == 0)
					{
					re = KPlaylistParserChildren;
					}
	delete text;
	return re;
	}

void CPlaylistNodeParser::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	TInt type = ConvertNameToNumber(aName.iLocalName);
	switch (type)
		{
		case KPlaylistParserNode:
			ParseNode(aAttributes);
			break;
		case KPlaylistParserTree:
			ParseTree(aAttributes);
			break;
		case KPlaylistParserParent:
			ParseParent(aAttributes);
			break;
		case KPlaylistParserChildren:
			ParseChildren(aAttributes);
			break;
		default:
			break;
		}
	}
void CPlaylistNodeParser::EndElement(const TQualified& aName)
	{
	TInt type = ConvertNameToNumber(aName.iLocalName);
	switch (type)
		{
		case KPlaylistParserNode:
			break;
		case KPlaylistParserChildren:
			break;
		default:
			break;
		}
	}
void CPlaylistNodeParser::CharacterData(const TDesC& aData)
	{
	}

void CPlaylistNodeParser::ParseNode(const RArray<TAttribute>& aAttributes)
	{
	pPlaylistTreeNode node = new (ELeave)PlaylistTreeNode;
	//	iNode = node;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();
		attrName->Des().LowerCase();
		attrValue->Des().Trim();
		if (attrName->Compare(KPlaylistAttrName) == 0)
			{
			TInt index = KErrNotFound;
			if (iNodeNotify)
				{
				index = iNodeNotify->ConvertNameToIndex(*attrValue);
				}
			node->iIndex = index;
			}
		else
			if (attrName->Compare(KPlaylistAttrText) == 0)
				{
				node->iName = attrValue->AllocL();
				}
			else
				if (attrName->Compare(KPlaylistAttrEvent) == 0)
					{
					EPlaylistNodeEvent index = KPlaylistEventNone;
					if (iNodeNotify)
						{
						index = iNodeNotify->ConvertEventToIndex(*attrValue);
						}
					node->iEvent = index;
					}
		CleanupStack::PopAndDestroy(2);
		}
	if (iNodeNotify)
		{
		iNodeNotify->AddPlaylistNode(node);
		}
	}

void CPlaylistNodeParser::ParseTree(const RArray<TAttribute>& aAttributes)
	{
	iTreeIndex = KErrNotFound;

	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();
		attrName->Des().LowerCase();
		attrValue->Des().Trim();

		if (attrName->Compare(KPlaylistAttrName) == 0)
			{
			if (iNodeNotify)
				{
				iTreeIndex = iNodeNotify->ConvertNameToIndex(*attrValue);
				}
			}

		CleanupStack::PopAndDestroy(2);
		}
	}

void CPlaylistNodeParser::ParseParent(const RArray<TAttribute>& aAttributes)
	{
	if (iTreeIndex == KErrNotFound)
		return;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();
		attrName->Des().LowerCase();
		attrValue->Des().Trim();

		if (attrName->Compare(KPlaylistAttrName) == 0)
			{
			TInt index = KErrNotFound;
			if (iNodeNotify)
				{
				index = iNodeNotify->ConvertNameToIndex(*attrValue);

				pPlaylistTreeNode node =
						iNodeNotify->GetPlaylistNodeByIndex(iTreeIndex);
				if (node)
					{
					node->iParent = index;
					}
				}
			}

		CleanupStack::PopAndDestroy(2);
		}
	}

void CPlaylistNodeParser::ParseChildren(const RArray<TAttribute>& aAttributes)
	{
	if (iTreeIndex == KErrNotFound)
		return;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();
		attrName->Des().LowerCase();
		attrValue->Des().Trim();
		if (attrName->Compare(KPlaylistAttrName) == 0)
			{
			TInt index = KErrNotFound;
			if (iNodeNotify)
				{
				index = iNodeNotify->ConvertNameToIndex(*attrValue);

				pPlaylistTreeNode node =
						iNodeNotify->GetPlaylistNodeByIndex(iTreeIndex);
				if (node)
					{
					node->iChildren.AppendL(index);
					}
				}
			}
		CleanupStack::PopAndDestroy(2);
		}
	}

void CPlaylistNodeParser::EndParseNode()
	{
	}

void CPlaylistNodeParser::SetNodeNotify(MPlaylistNodeNotify* aNotify)
	{
	iNodeNotify = aNotify;
	}

/**************************************************/

CPlaylistDecHandler::CPlaylistDecHandler()
	{
	// No implementation required
	}

CPlaylistDecHandler::~CPlaylistDecHandler()
	{
	}

CPlaylistDecHandler* CPlaylistDecHandler::NewLC()
	{
	CPlaylistDecHandler* self = new (ELeave)CPlaylistDecHandler();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistDecHandler* CPlaylistDecHandler::NewL()
	{
	CPlaylistDecHandler* self=CPlaylistDecHandler::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistDecHandler::ConstructL()
	{
	}