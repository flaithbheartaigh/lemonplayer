#ifndef __MACROUTIL_H
#define __MACROUTIL_H

#define SAFE_DELETE( x ) \
{ \
	if (( x ) != NULL ) \
	{ \
		delete ( x ); \
		( x ) = NULL; \
	} \
}

#define SAFE_DELETE_RPONTERARRAY( x ) \
{ \
	if ((x)) \
	{ \
		(x)->ResetAndDestroy(); \
		delete (x); \
		(x) = NULL; \
	} \
}

#define SAFE_DELETE_ARRAY( x , y) \
{ \
	if ((x) != NULL) \
	{ \
		for(TInt i=0; i<y; i++) \
		{ \
			if (( x[i] ) != NULL ) \
			{ \
			delete ( x[i] ); \
			( x[i] ) = NULL; \
			} \
		} \
		delete ( x ); \
		( x ) = NULL; \
	} \
}

#define SAFE_RESET_DELETE_ARRAY( x ) \
{ \
	if ((x) != NULL) \
	{ \
		( x )->Reset();\
		delete ( x ); \
		( x ) = NULL; \
	} \
}

#define SAFE_DELETE_ACTIVE( x ) \
{ \
	if (( x ) != NULL) \
	{ \
		if (( x )->IsActive()) \
			( x )->Cancel(); \
		delete ( x ); \
		( x ) = NULL; \
	} \
}

#define SAFE_DELETE_R( x ) \
{ \
	if (( x ) != NULL) \
	{ \
		( x )->Close(); \
		delete ( x ); \
		( x ) = NULL; \
	} \
}

#define RETURN_ERROR(x) \
{ \
  if ( (x)!= KErrNone ) \
  	return (x); \
}

#endif /*MACROUTIL_*/
