/*
============================================================================
 Name		: Configuration.cpp
 Author	  : yaoyang
 Version	 :
 Copyright   : 
 Description : CConfiguration implementation
============================================================================
*/

#include "Configuration.h"
#include "Utils.h"

#include <eikenv.h>
#include <f32file.h>
#include <utf.h>


CConfiguration::CConfiguration()
{
	// No implementation required
	//iFsSessionPtr = NULL;
}


CConfiguration::~CConfiguration()
{
	if(!iHasSave){
		SaveL();
	}
	if ( iConfigItemArray ) {
		delete iConfigItemArray;
		iConfigItemArray=NULL;
	}
}

CConfiguration* CConfiguration::NewLC(const TDesC& aConfigFilePath)
{
	CConfiguration* self = new (ELeave)CConfiguration();
	CleanupStack::PushL(self);
	self->ConstructL(aConfigFilePath);
	return self;
}

CConfiguration* CConfiguration::NewL(const TDesC& aConfigFilePath)
{
	CConfiguration* self=CConfiguration::NewLC(aConfigFilePath);
	CleanupStack::Pop(); // self;
	return self;
}

void CConfiguration::ConstructL(const TDesC& aConfigFilePath)
{
	iFilePath = aConfigFilePath;
	iHasSave = true;
}

TBool CConfiguration::Get(const TDesC& aKey, TDes& aValue)
{
	TBool loadResult = LoadL();
	if(!loadResult)
		return false;

	for(TInt i = 0; i < iConfigItemArray->Count(); i ++){
		if(iConfigItemArray->At(i).iKey == aKey){
			aValue.Copy(iConfigItemArray->At(i).iValue);
			return true;
		}
	}
	return false;
}

TBool CConfiguration::Set(const TDesC& aKey, const TDesC& aValue)
{
	if(aKey.Length() > 32 || aValue.Length() > 128)
		return false;

	TBuf<128> value;
	TBool hasKey = Get(aKey, value);
	if(hasKey){
		for(TInt i = 0; i < iConfigItemArray->Count(); i ++){
			if(iConfigItemArray->At(i).iKey == aKey){
				iConfigItemArray->At(i).iValue.Copy(aValue);
			}
		}
	}
	else{
		TConfigItem configItem;
		configItem.iKey.Copy(aKey);
		configItem.iValue.Copy(aValue);
		iConfigItemArray->AppendL(configItem);
	}
	iHasSave = SaveL();
	return true;
}

void CConfiguration::ParseLine(TDesC& aLine, TDes& akey, TDes& aValue)
{
	TBuf<1> tag(_L("="));
	TInt pos = aLine.Find(tag);
	if(pos == KErrNotFound){
		akey = _L("");
		aValue = _L("");
	}
	else{
		akey = aLine.Mid(0, pos);
		aValue = aLine.Mid(pos + 1);
	}
}

TBool CConfiguration::SaveL()
{
	return SaveInternalL(CEikonEnv::Static()->FsSession());
}

TBool CConfiguration::SaveInternalL(RFs& aFs)
{
	RFs& fsSession = aFs;//CEikonEnv::Static()->FsSession();
	RFile file;
	TInt errCode = file.Replace(fsSession, iFilePath, EFileWrite);
	if(errCode != KErrNone)
		return false;
	
	TBuf8<2> header;
	TChar c;
	c = 0xff;
	header.Append(c);
	c = 0xfe;
	header.Append(c);
	file.Write(header);

	for(TInt i = 0; i < iConfigItemArray->Count(); i ++){
		TBuf<512> line;
		line.Append(iConfigItemArray->At(i).iKey);
		line.Append(_L("="));
		
		line.Append(iConfigItemArray->At(i).iValue);
		line.Append(_L("\r\n"));
		TPtr8 ptr((TUint8*)line.Ptr(), line.Length()*2, line.Length()*2) ;
		file.Write(ptr);
	}
	file.Close();
	return true;
}

TBool CConfiguration::LoadL()
{
	TBool val = EFalse;
	RFs fs;
	if ( fs.Connect() )
		return val;
	val = LoadInternalL(fs);
	fs.Close();
	return val;
}

TBool CConfiguration::LoadInternalL(RFs& aFs)
{
	delete iConfigItemArray;
	iConfigItemArray = new(ELeave)CArrayFixFlat<TConfigItem>(3);
	
	RFs& fsSession = aFs;//CEikonEnv::Static()->FsSession();
	RFile file;
	TInt nErr = file.Open(fsSession, iFilePath, EFileRead|EFileShareAny);
	if (nErr)
	{
		return EFalse;
	}

	TFileText fileText;
	fileText.Set(file);
	HBufC* line = HBufC::NewLC(160);
	TPtr linePtr = line->Des();
	
	while (fileText.Read(linePtr) == KErrNone){
		TBuf<32> key;
		TBuf<128> value;
		TConfigItem item;
		ParseLine(linePtr, key, value);
		if(key.Length() != 0){
			item.iKey.Append(key);
			item.iValue.Append(value);
			iConfigItemArray->AppendL(item);
		}
	}
	CleanupStack::PopAndDestroy(); //line
	file.Close();

	return ETrue;
}
