/*
 ============================================================================
 Name		: UIOperateImplement.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIOperateImplement declaration
 ============================================================================
 */

#ifndef UIOPERATEIMPLEMENT_H
#define UIOPERATEIMPLEMENT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "UIOperateInterface.h"
// CLASS DECLARATION
class CSoundManager;
class CUIViewData;
/**
 *  CUIOperateImplement
 * 
 */
class CUIOperateImplement : public CBase, public MUIOperateInterface
	{
public:
	~CUIOperateImplement();
	static CUIOperateImplement* NewL(CUIViewData *aData);
	static CUIOperateImplement* NewLC(CUIViewData *aData);
private:
	CUIOperateImplement(CUIViewData *aData);
	void ConstructL();
public:
	//ÉùÒô²Ù×÷
	void PlayFile();
	void PlayFile(const TDesC& aFileName);

	void VolumeChange(TInt aVolume);
	void AddVolumeOneBlock();
	void DecVolumeOneBlock();

private:
	void StateChange();

private:
	CUIViewData *iData;
	CSoundManager *iSoundManager;

	};

#endif // UIOPERATEIMPLEMENT_H
