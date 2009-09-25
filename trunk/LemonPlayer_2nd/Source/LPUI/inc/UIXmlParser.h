/*
 ============================================================================
 Name		: UIXmlParser.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIXmlParser declaration 读取xml文件,搜集数据到数据结构里,属于MVC的MC
 ============================================================================
 */

#ifndef UIXMLPARSER_H
#define UIXMLPARSER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "SyExpat.h"

#include "UIData.h"
#include "ImageConvertorInterface.h"

typedef struct _ConvertFileStruct
	{
	TInt index;
	TBuf<256> filename;
	}ConvertFileStruct,*pConvertFileStruct;
// CLASS DECLARATION
class CUIViewData;
class CImageConvertor;
class CUIXmlDocHandler;
/**
 *  CUIXmlParser
 * 
 */
class CUIXmlParser : public CBase
	{
public:
	// Constructors and destructor

	~CUIXmlParser();
	static CUIXmlParser* NewL(CUIViewData *aData);
	static CUIXmlParser* NewLC(CUIViewData *aData);
	
public:
	TInt LoadFile(const TDesC& aFileName);

private:
	CUIXmlParser(CUIViewData *aData);
	void ConstructL();
	
private:
	CUIViewData *iData;
	CUIXmlDocHandler *iDocHandler;
	};

class CUIXmlDocHandler : public CBase,
						 public MSyDocHandler,
						 public MWImageConvertorListener
	{
public:
	// Constructors and destructor

	~CUIXmlDocHandler();
	static CUIXmlDocHandler* NewL(CUIViewData *aData);
	static CUIXmlDocHandler* NewLC(CUIViewData *aData);

private:

	CUIXmlDocHandler(CUIViewData *aData);
	void ConstructL();
	
public: // From MSyDocHandler
		virtual void StartElement(const TQualified& aName, const 
RArray<TAttribute>& aAttributes);
		virtual void EndElement(const TQualified& aName);
		virtual void CharacterData(const TDesC& aData);
		virtual void ProcessingInstruction(const TDesC& aTarget, const TDesC& 
aData){};
		virtual void Comment(const TDesC& aData){};
		virtual void StartCDataSection(){};
		virtual void EndCDataSection(){};
		virtual void Default(const TDesC& aData){};
		virtual void SetParser(CExpatParserBase* aParser){};
		
public:
		virtual void OnImageConvertedL(CFbsBitmap &aBitmap) ;
		virtual void OnImageConvertedL(const TDesC8 &aImgData) ;
		virtual	void OnConvertErrorL(TConvertResult aConvertResult) ;
		
public:
	void ConvertImage();
		
private:
	void FillControlData(const RArray<TAttribute>& aAttributes);
	void CopyBitmap(const CFbsBitmap &aBitmap,CFbsBitmap** destBitmap);
		
private:
	CUIViewData* 	iData;
	RPointerArray<ConvertFileStruct>  iArray; //把要转换的数据先放入到数组中.
	CImageConvertor* iConvertor;
	};

class CUIXmlDeclHandler : public CBase,
					 	  public MSyDeclHandler
	{
public:
	// Constructors and destructor
	~CUIXmlDeclHandler();
	static CUIXmlDeclHandler* NewL();
	static CUIXmlDeclHandler* NewLC();

private:
	CUIXmlDeclHandler();
	void ConstructL();
	
public: // From MSyDeclHandler
	virtual TSyExpatStatus NotStandalone(){return EStatusOk;};
	virtual void StartDocType( const TDesC& aDocType, const TDesC& aSystemId, const 
TDesC& aPublicId, const TBool aHasInternalSubset){};	
	virtual void EndDocType(){};
	virtual void StartNamespace(const TDesC& aPrefix, const TDesC& aURI){};
	virtual void EndNamespace(const TDesC& aPrefix){};
	virtual void Entity(const TDesC& aName, const TBool aIsParameter, const TDesC& 
aValue, const TDesC& aBase, const TDesC& aSystemId, const TDesC& aPublicId, const TDesC&
aNotation){};
	virtual void SkippedEntity(const TDesC& aEntity, const TBool aIsParameter){};
	virtual void Notation(const TDesC& aNotationName, const TDesC& aBase, const TDesC& 
aSystemId, const TDesC& aPublicId){};
	virtual void SetParser(CExpatParserBase* aParser){};
	};

#endif // UIXMLPARSER_H
