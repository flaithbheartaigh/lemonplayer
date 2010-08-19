/*
 ============================================================================
 Name		: SeniorUtils.h
 Author	  : SeniorUtils
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSeniorUtils declaration
 ============================================================================
 */

#ifndef SENIORUTILS_H
#define SENIORUTILS_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <badesca.h> 
// CLASS DECLARATION

/**
 *  CSeniorUtils
 * 
 */
class CSeniorUtils
	{
public:
	// Constructors and destructor
	~CSeniorUtils();
	CSeniorUtils();

	// 将应用程序带到前台
	static void ShowApplication();
	// 隐藏应用程序
	static void HideApplication();

	//打开浏览器
	static TThreadId StartBroswerApp(const TDesC& aUrl);

	//获取已安装软件列表
	static void GetSofts(CDesCArray* aArray);

	//添加书签
	static void AddBookmark(const TDesC& aUrl, const TDesC& aName);

	};

#endif // SENIORUTILS_H
