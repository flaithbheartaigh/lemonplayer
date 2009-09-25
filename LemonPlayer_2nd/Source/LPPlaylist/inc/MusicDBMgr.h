/*
 ============================================================================
 Name		: MusicDBMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicDBMgr declaration
 ============================================================================
 */

#ifndef MUSICDBMGR_H
#define MUSICDBMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <d32dbms.h>
#include <s32file.h>

// CLASS DECLARATION
class CMusicInfoBean;
/**
 *  CMusicDBMgr
 * 
 */
_LIT(KInfoTable, "Books");                /* Name of the one table       */
//_LIT(KInfoTable, "musicinfo");                /* Name of the one table       */

_LIT(KBooksTable, "Books");                /* Name of the one table       */
_LIT(KBooksAuthorCol, "Author");           /* First column                */
_LIT(KBooksTitleCol, "Title");             /* Second column               */
_LIT(KBooksDescriptionCol, "Description"); /* Third column                */

_LIT(KIdCol, 		"id");           	
_LIT(KArtistCol, 	"artist");           
_LIT(KTitleCol, 	"title");          
_LIT(KAblumCol, 	"ablum");           
_LIT(KGenreCol, 	"genre");    
_LIT(KFilenameCol, 	"filename");             /* Second column               */
_LIT(KFilefolderCol, "filefolder"); 		/* Third column                */

_LIT(KBooksIndexName,"BooksIndex");        /* Name of the one index       */

const int KTitleMaxLength = 60;            /* Max length of title column  */
const int KDescriptionMaxLength = 128;     /* Max length of descr. column */

class CMusicDBMgr : public CBase
	{
public:
	~CMusicDBMgr();
	static CMusicDBMgr* NewL();
	static CMusicDBMgr* NewLC();

private:

	CMusicDBMgr();
	void ConstructL();
	
public:
	TInt CreateDb(const TFileName& aNewBookFile);
	TInt OpenDb(const TFileName& aExistingBookFile);

	TInt RemoveDb(const TFileName& aExistingBookFile);

	TInt AddElementL(CMusicInfoBean* aBean);
	TInt AddElementsL(RPointerArray<CMusicInfoBean>* aList);

	TInt RemoveAllElements(TInt& aResultCount);
	TInt RemoveElementByIdL(TInt aId,TInt& aResultCount);
//	void RemoveElementsByIdL(TInt aId);

	RPointerArray<CMusicInfoBean>* GetAllElementsL();
	CMusicInfoBean* GetElementByIdL(TInt aId);
	RPointerArray<CMusicInfoBean>* GetElementsByIdL(TInt aId);
	
	TInt GetAllElementsL(RPointerArray<CMusicInfoBean>** aArray);
	TInt GetElementByIdL(TInt aId,CMusicInfoBean* aBean);
	TInt GetElementsByIdL(TInt aId,RPointerArray<CMusicInfoBean>* aArray);

	TInt ModifyElementByIdL(TInt aId,CMusicInfoBean* aBean);
	TInt ModifyElementsByIdL(TInt aId,RPointerArray<CMusicInfoBean>* aList);
	
private:
	TInt Close();
	void CreateBooksTableL();
	void CreateBooksIndexL();
	void DropBooksTable();
	
	TInt CreateId(TInt& aId);
	
private:
	RDbNamedDatabase iBookDb;
	RDbStoreDatabase iBookDb2;	/* For database operations                 */
	CFileStore*      iFileStore;  /* For creating and opening database files */
	TBool            iOpen;       /* Flag indicating iBookDb open status*/
	
	};

#endif // MUSICDBMGR_H
