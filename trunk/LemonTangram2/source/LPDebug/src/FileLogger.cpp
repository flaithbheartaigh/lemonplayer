/*
 * ==============================================================================
 *  Name     : CFileLogger
 *  Part of  : AOExample
 *  Created  : 3.5.2004 by Markus Pelkonen
 *  Implementation notes: See detailed documentation from the file
 *                        "FileLogger.h"
 *  Version  :
 *  Copyright: Nokia
 * ==============================================================================
 */

#include <e32base.h>
#include <e32cons.h>
#include <e32std.h>
#include <f32file.h>
#include "FileLogger.h"
#include <sysutil.h>
#include <utf.h> 

// -----------------------------------------------------------------------------
CFileLogger* CFileLogger::NewL(const TDesC &logFileName, EWriteFileMode aMode)
	{
	CFileLogger* result = new (ELeave) CFileLogger();
	CleanupStack::PushL(result);
	result->ConstructL(logFileName, aMode);
	CleanupStack::Pop();
	return result;
	}

// -----------------------------------------------------------------------------
void CFileLogger::ConstructL(const TDesC &logFileName, EWriteFileMode aMode)
	{
	iFileName.Copy(logFileName);
	iMode = aMode;

	int pos = logFileName.LocateReverse( '\\');
	TPtrC dirName = logFileName.Left(pos+1);

	User::LeaveIfError(iFsSession.Connect());
	iFsSession.MkDirAll(dirName);

	if (iMode == KModeAlwayOpen)
		{
		OpenFile();
		}

	}

void CFileLogger::OpenFile()
	{
	if (iFile.Open(iFsSession, iFileName, EFileWrite|EFileStreamText)
			== KErrNone)
		{
		// go to the end of the file
		TInt tmp = 0;
		iFile.Seek(ESeekEnd, tmp);
		}
	else
		{
		// file doesn't exist, create a new
		User::LeaveIfError(iFile.Replace(iFsSession, iFileName, EFileWrite
				|EFileStreamText));
		}
	}

void CFileLogger::WriteStream(const TDesC8 &aDes)
	{
	//TPtrC8 representation( aDes, aDes.Size() );
	if (iMode == KModeOpenAndClose)
		{
		OpenFile();
		}
	
	TInt end = 0;
	iFile.Seek(ESeekEnd, end);

	WriteDate();
	
	iFile.Write(aDes);
	iFile.Write(_L8("\r\n"));
	iFile.Flush();
	if (iMode == KModeOpenAndClose)
		{
		iFile.Close();
		}

	}
void CFileLogger::WriteStream(const TDesC &aDes)
	{
	if (iMode == KModeOpenAndClose)
		{
		OpenFile();
		}
	
	TInt end = 0;
	iFile.Seek(ESeekEnd, end);
	
	WriteDate();

	HBufC8* text = From16To8(aDes);
	iFile.Write( *text);
	iFile.Write(_L8("\r\n"));
	iFile.Flush();
	delete text;
	if (iMode == KModeOpenAndClose)
		{
		iFile.Close();
		}
	}

void CFileLogger::ReadStream(TDes &aDes)
	{
	TBuf8<50> buf;
	TInt pos = 0;
	User::LeaveIfError(iFile.Seek(ESeekStart, pos));
	iFile.Read(buf);
	aDes.Copy((TUint16* )buf.Ptr(), buf.Size()/2);
	}

void CFileLogger::SetSize(TInt aSize)
	{
	iFile.SetSize(aSize);
	iFile.Flush();
	}

void CFileLogger::WriteInt(const TInt aVal)
	{
	TBuf<16> buf;
	buf.AppendNum(aVal);
	WriteStream(buf);
	}

void CFileLogger::WriteDate()
	{
	_LIT(KTimeFormat,"%H:%T:%S");
	TBuf<10> current;
	TTime Now;
	Now.HomeTime();
	TDateTime Dtime=Now.DateTime();

	Now.FormatL(current, KTimeFormat);

	TBuf8<10> text;
	text.Copy(current);
	iFile.Write(text);
	iFile.Write(_L8("\t"));
	}
// -----------------------------------------------------------------------------
CFileLogger::~CFileLogger()
	{
	iFile.Close();
	iFsSession.Close();
	}

HBufC8* CFileLogger::From16To8(const TDesC& aStr)
	{
	HBufC8* ret = HBufC8::NewLC(aStr.Length()*3);
	TPtr8 ptr = ret->Des();
	CnvUtfConverter::ConvertFromUnicodeToUtf8(ptr, aStr);

	CleanupStack::Pop(ret);
	return ret;
	}

