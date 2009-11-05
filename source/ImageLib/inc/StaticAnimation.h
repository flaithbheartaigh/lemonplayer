/*
 ============================================================================
 Name		: TangramImageManager.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramImageManager declaration
 ============================================================================
 */

#ifndef STATICANIMATION_H
#define STATICANIMATION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "ImageLibDefine.h"
#include "ImageRotator.h"
#include "DefaultDocHandler.h"
// CLASS DECLARATION

/**
 *  CTangramImageManager
 * 
 */
class CStaticAnimation : 	public CBase,
							public CDefaultDocHandler
	{
public:
	// Constructors and destructor

	~CStaticAnimation();
	static CStaticAnimation* NewL();
	static CStaticAnimation* NewLC();
	
public:
	//CDefaultDocHandler
	virtual void StartElement(const TQualified& aName, const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);
	
public:	
	void LoadDataFromXml(const TDesC& aFileName);
	void Draw(CFbsBitGc& gc,TInt aX, TInt aY);
	void ChangeAction();
	void UpdataData();

private:
	CStaticAnimation();
	void ConstructL();
	
//	void GetFileNameByIndex(TInt index, TDes &aFile);
	
	TInt ConvertNameToNumber(const TDesC& aName);	
	
	void ParseImage(const RArray<TAttribute>& aAttributes);
	void ParseImg(const RArray<TAttribute>& aAttributes);
	void ParseAnimation(const RArray<TAttribute>& aAttributes);
	void ParseAction(const RArray<TAttribute>& aAttributes);
	void ParseFrame(const RArray<TAttribute>& aAttributes);
	void ParseSprite(const RArray<TAttribute>& aAttributes);
	
	void EndParseAction();
	void EndParseFrame();
	void EndParseSprite();
	
	void ConstructImageL(TInt aNumber);
	void InitImageL(TInt aIndex,TInt aDegree,TInt aX,TInt aY);
	
	void ConstructAnimationL(TInt aNumber);
	void ConstructAction(TInt aNumber);
	void ConstructFrame(TInt aNumber);
	void ConstructSprite(TInt aIndex,TInt aX,TInt aY);
//	void LoadImageFromXml(RPointerArray<CSenElement>& aArray,CXmlParser *aParser);
//	void LoadActionFromXml(RPointerArray<CSenElement>& aArray,CXmlParser *aParser);
	
public:
	void ClearData();
	
private:
	void ClearAction();
	void ClearFrame();
	void ClearSprite();
	
	void IncreaseAction();
	void IncreaseFrame();
	void IncreaseSprite();
	
public:
	void SetSrcBitmap(CFbsBitmap** aBitmap,const TInt aCount);
	
private:
	TangramImageStruct** iStruct;
	TangramImageStruct** iOffset;
	CImageRotator** iRotator;	
	TInt iImageCount;
	
	UiImageStruct*** iAnimation;
	TInt iActionCount;
	TInt* iFrameCount;
	TInt** iSpriteCount; 
	
	TInt iCurAction;
	TInt iCurFrame;
	
	CFbsBitmap** iSrcBitmap;   //ÒýÓÃ
	TInt iSrcBitmapCount;
	
	TInt iParseAction;
	TInt iParseFrame;
	TInt iParseSprite;
	
	TBool iInitComplete;
	};

#endif // STATICANIMATION_H
