#ifndef MP3ENCODENOTIFIER_H_
#define MP3ENCODENOTIFIER_H_

class MMP3EncodeNotifier
{
public:
	virtual TInt Read(TDes8& aDes,TInt aLength) = 0;
	virtual void FrameDecoded() = 0; 
	virtual void ReportError(TInt aErrorCode) = 0;
};

#endif /*MP3ENCODENOTIFIER_H_*/
