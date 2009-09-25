/*
 ============================================================================
 Name		: UIInterface.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIInterface declaration
 ============================================================================
 */

#ifndef UIOPERATEINTERFACE_H
#define UIOPERATEINTERFACE_H

class MUIOperateInterface
	{
public:
	//ÉùÒô²Ù×÷
	virtual void PlayFile() = 0;
	virtual void PlayFile(const TDesC& aFileName) = 0;
	
	virtual void VolumeChange(TInt aVolume) = 0;
	virtual void AddVolumeOneBlock() = 0;
	virtual void DecVolumeOneBlock() = 0;
	};
#endif 