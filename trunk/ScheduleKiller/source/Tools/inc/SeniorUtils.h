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

	// ��Ӧ�ó������ǰ̨
	static void ShowApplication();
	// ����Ӧ�ó���
	static void HideApplication();

	//�������
	static TThreadId StartBroswerApp(const TDesC& aUrl);

	//��ȡ�Ѱ�װ����б�
	static void GetSofts(CDesCArray* aArray);

	//�����ǩ
	static void AddBookmark(const TDesC& aUrl, const TDesC& aName);

	};

#endif // SENIORUTILS_H
