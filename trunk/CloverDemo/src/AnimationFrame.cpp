/*
 ============================================================================
 Name		: AnimationFrame.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationFrame implementation
 ============================================================================
 */

#include "AnimationFrame.h"
#include "MacroUtil.h"

CAnimationFrame::CAnimationFrame(MAnimationNofity& aNotify)
:iNotify(aNotify)
	{
	// No implementation required
	}

CAnimationFrame::~CAnimationFrame()
	{
	SAFE_DELETE_ACTIVE(iAnimer)
	
	SAFE_DELETE_RPONTERARRAY(iFuncs)
//	if (iFuncs)
//		{
//		iFuncs->Reset();
//		iFuncs->Close();
//		delete iFuncs;
//		iFuncs = NULL;
//		}
	}

TInt CAnimationFrame::AppendAnimation(TCallBack* aFunc)
	{
	TInt index = KErrNotFound;
	if (iFuncs)
		{
		index = iFuncs->Count();
		iFuncs->Append(aFunc);
		}
	
	if (iAnimer && !iAnimer->IsActive())
		iAnimer->Start(1, 1, TCallBack(CAnimationFrame::Callback, this));
	
	return index;
	}
void CAnimationFrame::RemoveAnimation(const TInt& aIndex)
	{
	if (iFuncs)
		{
		if (aIndex >=0 && aIndex < iFuncs->Count())
			{
			TCallBack* func = (*iFuncs)[aIndex];
			iFuncs->Remove(aIndex);
			delete func;
			}
		}
	}

void CAnimationFrame::RemoveAnimation(TCallBack* aFunc)
	{
	if (iFuncs)
		{
		TInt index = iFuncs->Find(aFunc);
		if (index != KErrNotFound)
			{
			RemoveAnimation(index);
			}
		}
	}

void CAnimationFrame::StartTimer()
	{
	iAnimer->Cancel();
	iAnimer->Start(1, 1, TCallBack(CAnimationFrame::Callback, this));
	}	

TInt CAnimationFrame::Callback(TAny* aThis)
	{
	return static_cast<CAnimationFrame*> (aThis)->Animation();
	}

TInt CAnimationFrame::Animation()
	{
	if (iFuncs)
		{
		TInt count = iFuncs->Count();
	
		if (count)
			{
			for(TInt i=0; i<iFuncs->Count(); i++)
				{
				TCallBack* func = (*iFuncs)[i];
				if (func)
					func->CallBack();
				}
			iNotify.AnimationCallback();
			}
		else
			iAnimer->Cancel();
		}
	}
