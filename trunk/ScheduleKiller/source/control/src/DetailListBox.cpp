/*
 ============================================================================
 Name		: DetailListBox.cpp
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDetailListBox implementation
 ============================================================================
 */

#include "DetailListBox.h"
#include "DetailListItemDrawer.h"
#include "UI_Layout.h"
#include "SHPlatform.h"

void CDetailListBox::CreateItemDrawerL()
	{
	iItemDrawer = new (ELeave) CDetailListItemDrawer(*this);
	iShowItems = 0;
	}

void CDetailListBox::OfferPointerEventL(const TPointerEvent& aPointerEvent)
	{
	HandlePointerEventL(aPointerEvent);
	
	TPoint point = aPointerEvent.iPosition;
	TInt type = aPointerEvent.iType;
	if (type == TPointerEvent::EButton1Up)
		{
		TInt index = this->CurrentItemIndex();
		if (index < 0)
			return;
		
		TRect rect(View()->ItemPos(index),LIST_DELETE_AREA_SIZE);
		if (rect.Contains(point))
			{
			if (iNotify)
				iNotify->HandleListEvent(MDetailListBoxNotify::EEventRemove);
			}
		}
	}

void CDetailListBox::SetListFocus(TBool aFocus)
	{
	SetFocus(aFocus);
	
	TInt count = SHModel()->GetTaskInfoManager()->GetTaskList().Count();
	if (count > iShowItems)
		if (aFocus)
			{
			ScrollBarFrame()->SetScrollBarVisibilityL(
					CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOn);
			}
		else
			{
			ScrollBarFrame()->SetScrollBarVisibilityL(
					CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff);
			}
	DrawNow();
	}

void CDetailListBox::UpdateScrollBar()
	{
	TInt count = SHModel()->GetTaskInfoManager()->GetTaskList().Count();
	if (count > iShowItems)
			{
			ScrollBarFrame()->SetScrollBarVisibilityL(
					CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOn);
			}
		else
			{
			ScrollBarFrame()->SetScrollBarVisibilityL(
					CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff);
			}
	}

