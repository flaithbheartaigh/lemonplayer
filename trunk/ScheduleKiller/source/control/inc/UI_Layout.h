/*
 * UI_Layout.h
 *
 *  Created on: 2011-4-8
 *      Author: johnlzeng
 */

#ifndef UI_LAYOUT_H_
#define UI_LAYOUT_H_

#include <e32std.h>
#include <e32base.h>

const static TSize BOTTOM_BUTTON_SIZE = TSize(64,64);		//退出等按钮大小
const static TSize FUNCTION_BUTTON_SIZE = TSize(80,80);		//新建 按钮大小

const static TInt  LIST_CONTENT_WIDTH_RATE = 60;		//百分比
const static TInt  LIST_CONTENT_HEIGHT_RATE = 80;		//百分比

const static TSize LIST_DELETE_AREA_SIZE	= TSize(80,100);	//删除区域
const static TSize LIST_APP_ICON_AREA_SIZE	= TSize(60,50);		//程序icon区域
const static TSize LIST_APP_NAME_AREA_SIZE	= TSize(60,50);		//程序名字区域,宽度无效
const static TSize LIST_APP_TIME_AREA_SIZE	= TSize(60,48);		//倒计时时间区域,宽度无效

const static TSize LIST_DELETE_ICON_SIZE 	= TSize(64,64);		//删除按钮大小
const static TSize LIST_APP_ICON_SIZE		= TSize(48,48);		
const static TSize LIST_DIGITAL_SIZE		= TSize(32,48);
const static TSize LIST_COLON_SIZE			= TSize(8,48);		//冒号
#endif /* UI_LAYOUT_H_ */
