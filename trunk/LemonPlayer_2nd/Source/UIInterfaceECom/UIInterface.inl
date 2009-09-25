/**
*
* @brief Inline Definition of CShape
*
* Copyright (c) EMCC Software Ltd 2003
* @version 1.0
*/

inline CUIInterface* CUIInterface::NewL()
	{
	const TUid KCCircleInterfaceUid = {0x0116C9D8};

	TAny* interface = REComSession::CreateImplementationL (
		KCCircleInterfaceUid, _FOFF (CUIInterface, iDestructorIDKey));

	return reinterpret_cast <CUIInterface*> (interface);
	}




inline CUIInterface* CUIInterface::NewL (const TDesC8& aMatch,CUIViewData *aData,
		MUIOperateInterface *aOperate)
	{
//	iData = aData;
//	iOperate = aOperate;
	
	const TUid KCShapeInterfaceUid = {0x0116C9D4};
	const TUid KCShapeResolverUid =  {0x0116C9D6};

	TEComResolverParams resolverParams;
	resolverParams.SetDataType (aMatch);
	resolverParams.SetWildcardMatch (ETrue);

	TAny* interface = REComSession::CreateImplementationL (KCShapeInterfaceUid,
		_FOFF (CUIInterface, iDestructorIDKey), resolverParams, KCShapeResolverUid);

	return reinterpret_cast <CUIInterface*> (interface);
	}



inline CUIInterface::~CUIInterface()
	{
	REComSession::DestroyedImplementation (iDestructorIDKey);
	}


