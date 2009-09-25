/*
 ============================================================================
 Name		: UIDataSerialize.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIDataSerialize declaration
 ============================================================================
 */

#ifndef UIDATASERIALIZE_H
#define UIDATASERIALIZE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "SyExpat.h"
#include "SyGen.h"
// CLASS DECLARATION
class CUIViewData;
/**
 *  CUIDataSerialize
 * 
 */
_LIT(KDataXmlTagFileList,	"filelist");
_LIT(KDataXmlTagPlayModel,	"playmodel");
_LIT(KDataXmlTagCurSelectFile,	"curselectfile");
_LIT(KDataXmlTagNextSelectFile,	"nextselectfile");
_LIT(KDataXmlTagVolume,		"volume");

_LIT(KDataXmlAtrValue,"value");

class CUIDataSerialize : public CBase,
						 public MSyDocHandler,
						 public MSyOutputHandler
	{
public:
	// Constructors and destructor
	~CUIDataSerialize();
	static CUIDataSerialize* NewL(CUIViewData *aData);
	static CUIDataSerialize* NewLC(CUIViewData *aData);
	
public:
	TInt LoadFile(const TDesC& aFileName);
	TInt WriteFile(const TDesC& aFileName);
	
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
		
public: //MSyOutputHandler
	virtual void WriteL(const TDesC& aString, const TBool aIsRawData);

private:
	CUIDataSerialize(CUIViewData *aData);
	void ConstructL();
	
private:
	void ParseFileList(const RArray<TAttribute>& aAttributes);
	void ParsePlayModel(const RArray<TAttribute>& aAttributes);
	void ParseCurSelectFile(const RArray<TAttribute>& aAttributes);
	void ParseNextSelectFile(const RArray<TAttribute>& aAttributes);
	void ParseVolume(const RArray<TAttribute>& aAttributes);
	
	void CheckData(); //读取xml文件后,对数据进行简单的校验
	
	void GenerateXml();
	void GenerateFileList(CSyGenerator *pXmlGenerator);
	void GeneratePlayModel(CSyGenerator *pXmlGenerator);
	void GenerateCurSelectFile(CSyGenerator *pXmlGenerator);
	void GenerateNextSelectFile(CSyGenerator *pXmlGenerator);
	void GenerateVolume(CSyGenerator *pXmlGenerator);
	
	void ClearBuffer();
	void WriteDesToFile(const TDesC& aFileName);
	
private:
	CUIViewData *iData;
	HBufC8 *iXmlBuffer;
	};

#endif // UIDATASERIALIZE_H
