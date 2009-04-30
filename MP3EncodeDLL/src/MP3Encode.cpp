/*
 ============================================================================
 Name		: MP3Encode.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMP3Encode implementation
 ============================================================================
 */

#include "MP3Encode.h"
#include <utf.h>

extern "C"
{
#include "shine.h"
}

CMP3Encode::CMP3Encode()
	{
	// No implementation required
	}

CMP3Encode::~CMP3Encode()
	{
	delete iCharFileWav;
	delete iCharFileMp3;
	}

CMP3Encode* CMP3Encode::NewLC()
	{
	CMP3Encode* self = new (ELeave)CMP3Encode();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMP3Encode* CMP3Encode::NewL()
	{
	CMP3Encode* self=CMP3Encode::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMP3Encode::ConstructL()
	{

	}

TInt CMP3Encode::Open(const TDesC &aFileWav, const TDesC& aFileMp3) 
{
	iFileNameWav.Copy(aFileWav);
	iFileNameMp3.Copy(aFileMp3);
	iUseFile = ETrue;

	TInt iErr = InitMP3();

	if(iErr)
		bFileOpened = EFalse;
	else
		{
		bFileOpened = ETrue;
		
		HBufC8* infile = HBufC8::NewLC(iFileNameWav.Length()*3);	
		TPtr8 inptr = infile->Des();
		inptr.Zero();
		CnvUtfConverter::ConvertFromUnicodeToUtf8(inptr,iFileNameWav);
		
		HBufC8* outfile = HBufC8::NewLC(iFileNameMp3.Length()*3);	
		TPtr8 outptr = outfile->Des();
		outptr.Zero();
		CnvUtfConverter::ConvertFromUnicodeToUtf8(outptr,iFileNameMp3);		
			
		iCharFileWav = descriptorToStringL(inptr);
		iCharFileMp3 = descriptorToStringL(outptr);
		
		init_encode_file(iCharFileWav,iCharFileMp3);
		
		CleanupStack::PopAndDestroy(2);
		}

	return iErr;
}

TInt CMP3Encode::Open(MMP3EncodeNotifier* aNotifier,const TDesC& aFileMp3)
	{
	iNotifier = aNotifier;
	iFileNameMp3.Copy(aFileMp3);
	iUseFile = EFalse;
	
	TInt iErr = InitMP3();

	if(iErr)
		bFileOpened = EFalse;
	else
		{
		bFileOpened = ETrue;
		
		HBufC8* outfile = HBufC8::NewLC(iFileNameMp3.Length()*3);	
		TPtr8 outptr = outfile->Des();
		outptr.Zero();
		CnvUtfConverter::ConvertFromUnicodeToUtf8(outptr,iFileNameMp3);	
		
		iCharFileMp3 = descriptorToStringL(outptr);
		
		init_encode_stream(iCharFileMp3);
		
		CleanupStack::PopAndDestroy(outfile);
		}

	return iErr;
}

TInt CMP3Encode::Close()
{
	if(bFileOpened)
	{
		CloseMP3();
	}
	close_encode_file(iUseFile);
	return 0;
}

TInt CMP3Encode::GetFileLength()
{
	TInt iLength=0;
	
	if(iFile.Size(iLength)==KErrNone)
	{
		return iLength;
	}
	else
	{
		return 0;
	}
}

TInt CMP3Encode::GetFilePosition()
{
	TInt iPos=0;
	if(iFile.Seek(ESeekCurrent, iPos)==KErrNone)
	{
		return iPos;
	}
	else
	{
		return 0;
	}
}

TInt CMP3Encode::InitMP3()
{
	TInt iErr=0;
//	if (iUseFile)
//		iErr = iFile.Open(*iFileSession,iFileNameWav,EFileRead|EFileShareReadersOnly);

	/* First the structures used by libmad must be initialized. */

	return iErr;
}

TInt CMP3Encode::CloseMP3()
{
//	if (iUseFile)
//		iFile.Close();

	return 0;
}

TInt CMP3Encode::EncodeOneFrame()
{
	int iErr;
	
	if (iUseFile)
		iErr = DecodeOneFrameFile();
	else
		iErr = DecodeOneFrameStream();
	
	return iErr;
}

TInt CMP3Encode::EncodeOneFrame(TDes& /*aBuffer*/)
{
	int iErr = DecodeOneFrameFile();
	return iErr;
}

int CMP3Encode::DecodeOneFrameFile()
{
	int err = decode_one_frame(NULL,0);

//	if (iUseFile)
//		iFile.Read(*iInputBuf,ReadSize);
//	else
//		iNotifier->Read(*iInputBuf,ReadSize);
	
	return err;
}

int CMP3Encode::DecodeOneFrameStream()
	{
	int length,err;
	TBuf8<4609> pcm;
	char* ptr;
	
	length = get_encode_frame_length();
	pcm.Zero();
	err = iNotifier->Read(pcm,length);
	if (err != KErrNone)
		return 0;
	
	ptr = (char*)pcm.Ptr();
	
	err = decode_one_frame(ptr,length);
	return err;
	}

char* CMP3Encode::descriptorToStringL(const TDesC8& aDescriptor)
	{
    TInt length = aDescriptor.Length();
 
    char* str = new(ELeave) char[length + 1];
    Mem::Copy(str, aDescriptor.Ptr(), length);
    str[length] = '\0';
 
    return str;
	}