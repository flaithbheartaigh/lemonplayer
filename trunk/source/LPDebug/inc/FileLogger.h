#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <e32base.h>
#include <f32file.h>

_LIT( KDefaultLogFile, "c:\\res.txt" );
class CFileLogger : public CBase
{
public:
	enum EWriteFileMode
		{
		KModeAlwayOpen = 0,
		KModeOpenAndClose 
		};
	/**
	* Factory method for construction. See ConstructL(const TDesC&) for
	* detailed documentation.
	*/
	static CFileLogger* CFileLogger::NewL( const TDesC &logFileName = KDefaultLogFile,
			EWriteFileMode aMode = KModeAlwayOpen);

	/**
	* Construct an instance of the MResultViewer that writes contents to
	* the file specified by logFileName parameter. The file is opened at
	* the construction time and kept open until object is destroyed.
	*
	* @param logFileName file name where contents are written.
	*/
	void ConstructL( const TDesC &logFileName,EWriteFileMode aMode);

	/**
	* Destroys the object and closes the file opened at construction time.
	*/
	virtual ~CFileLogger();

	/**
	* write the aDes to the logFile.
	* 
	*/   

	void WriteStream(const TDesC8 &aDes);
	void WriteStream(const TDesC &aDes);
	void ReadStream(TDes &aDes);
	void  SetSize(TInt aSize);

	
	/**
	*write the aVal to the logFile that specifid in the NewL();
	*/
	void WriteInt(const TInt aVal);
	
private:
	HBufC8* From16To8(const TDesC& aDes);
	void OpenFile();
	void WriteDate();

public:
	// TBuf<1024> iBuf;
	

private:
	RFs        iFsSession;
	RFile      iFile;
	
	TFileName iFileName;
	EWriteFileMode iMode;
};

#endif
