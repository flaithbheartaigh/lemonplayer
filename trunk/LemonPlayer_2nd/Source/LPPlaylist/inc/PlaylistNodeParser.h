/*
 ============================================================================
 Name		: PlaylistNodeParser.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistNodeParser declaration
 ============================================================================
 */

#ifndef PLAYLISTNODEPARSER_H
#define PLAYLISTNODEPARSER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SyExpat.h"
#include "PlaylistDefine.h"
// CLASS DECLARATION
class MPlaylistNodeNotify;
/**
 *  CPlaylistNodeParser
 * 
 */
_LIT(KPlaylistDomTagNode,"node");
_LIT(KPlaylistDomTagTree,"tree");
_LIT(KPlaylistDomTagParent,"parent");
_LIT(KPlaylistDomTagChildren,"children");

_LIT(KPlaylistAttrName,"name");
_LIT(KPlaylistAttrText,"text");
_LIT(KPlaylistAttrParent,"parent");
_LIT(KPlaylistAttrEvent,"event");

enum EPlaylistParser
	{
	KPlaylistParserNone = 0,
	KPlaylistParserNode,
	KPlaylistParserTree,
	KPlaylistParserParent,
	KPlaylistParserChildren
	};

class CPlaylistNodeParser : public CBase,
							public MSyDocHandler
	{
public:
	~CPlaylistNodeParser();
	static CPlaylistNodeParser* NewL();
	static CPlaylistNodeParser* NewLC();

private:
	CPlaylistNodeParser();
	void ConstructL();
	
public: // From MSyDocHandler
	virtual void StartElement(const TQualified& aName, const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);
	virtual void CharacterData(const TDesC& aData);
	
	virtual void ProcessingInstruction(const TDesC& aTarget, const TDesC& aData){};
	virtual void Comment(const TDesC& aData){};
	virtual void StartCDataSection(){};
	virtual void EndCDataSection(){};
	virtual void Default(const TDesC& aData){};
	virtual void SetParser(CExpatParserBase* aParser){};
	
private:
	TInt ConvertNameToNumber(const TDesC& aName);	
	
	void ParseNode(const RArray<TAttribute>& aAttributes);
	void ParseTree(const RArray<TAttribute>& aAttributes);
	void ParseParent(const RArray<TAttribute>& aAttributes);
	void ParseChildren(const RArray<TAttribute>& aAttributes);
	
	void EndParseNode();	
	
public:
	void SetNodeNotify(MPlaylistNodeNotify* aNotify);
	
private:
//	pPlaylistTreeNode iNode;
	MPlaylistNodeNotify* iNodeNotify;
	TInt iTreeIndex;
	};

class CPlaylistDecHandler : public CBase, 
							public MSyDeclHandler
{
public:
	// Constructors and destructor
	~CPlaylistDecHandler();
	static CPlaylistDecHandler* NewL();
	static CPlaylistDecHandler* NewLC();

private:
	CPlaylistDecHandler();
	void ConstructL();
	
public:	
	virtual TSyExpatStatus NotStandalone(){return EStatusOk;};
	virtual void StartDocType( const TDesC& aDocType, const TDesC& aSystemId, const TDesC& aPublicId, const TBool aHasInternalSubset){};
	virtual void EndDocType(){};
	virtual void StartNamespace(const TDesC& aPrefix, const TDesC& aURI){};
	virtual void EndNamespace(const TDesC& aPrefix){};
	virtual void Entity(const TDesC& aName, const TBool aIsParameter, const TDesC& aValue, const TDesC& aBase, const TDesC& aSystemId, const TDesC& aPublicId, const TDesC& aNotation){};
	virtual void SkippedEntity(const TDesC& aEntity, const TBool aIsParameter){};
	virtual void Notation(const TDesC& aNotationName, const TDesC& aBase, const TDesC& aSystemId, const TDesC& aPublicId){};
	virtual void SetParser(CExpatParserBase* aParser){};
};

#endif // PLAYLISTNODEPARSER_H
