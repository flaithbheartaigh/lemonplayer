/*
 ============================================================================
 Name		: MusicDBMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicDBMgr implementation
 ============================================================================
 */

#include "MusicDBMgr.h"
#include "MacroUtil.h"
#include "coemain.h"
#include "bautils.h"
#include "MusicInfoBean.h"

const int KCustomSqlMaxLength = 256;

CMusicDBMgr::CMusicDBMgr()
	{
	// No implementation required
	}

CMusicDBMgr::~CMusicDBMgr()
	{
	Close();
	}

CMusicDBMgr* CMusicDBMgr::NewLC()
	{
	CMusicDBMgr* self = new (ELeave)CMusicDBMgr();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMusicDBMgr* CMusicDBMgr::NewL()
	{
	CMusicDBMgr* self=CMusicDBMgr::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMusicDBMgr::ConstructL()
	{

	}

TInt CMusicDBMgr::CreateDb(const TFileName& aNewBookFile)
	{
	Close();

	// Create empty database file.
	
	TRAPD(error,
//			iFileStore = CPermanentFileStore::ReplaceL(CCoeEnv::Static()->FsSession(),
//					aNewBookFile, EFileRead|EFileWrite);
//			iFileStore->SetTypeL(iFileStore->Layout());// Set file store type
//			TStreamId id = iBookDb.CreateL(iFileStore);// Create stream object
//			iFileStore->SetRootL(id);// Keep database id as root of store
//			iFileStore->CommitL();// Complete creation by commiting
			iBookDb.Create(CCoeEnv::Static()->FsSession(),aNewBookFile);
			// Create Book tables and indexes
			CreateBooksTableL();
//			CreateBooksIndexL();
	)
	;

	RETURN_ERROR(error);
	iOpen = ETrue;
	return KErrNone;
	}

TInt CMusicDBMgr::OpenDb(const TFileName& aExistingBookFile)
	{
	Close();

	if (!BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), aExistingBookFile))
		{
		return CreateDb(aExistingBookFile);
//		return KErrNotFound;
		}

	TRAPD(error,
//			iFileStore = CPermanentFileStore::OpenL(CCoeEnv::Static()->FsSession(),
//					aExistingBookFile, EFileRead|EFileWrite);
//			iFileStore->SetTypeL(iFileStore->Layout());/* Set file store type*/
//			iBookDb.OpenL(iFileStore,iFileStore->Root())
			iBookDb.Create(CCoeEnv::Static()->FsSession(),aExistingBookFile);
	)
	;

	RETURN_ERROR(error);

	iOpen = ETrue;
	return KErrNone;
	}

TInt CMusicDBMgr::RemoveDb(const TFileName& aExistingBookFile)
	{
	Close();

	if (!BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), aExistingBookFile))
		{
		return KErrNotFound;
		}

	// It is enough to delete the database file directly. Because this example
	// demonstrates DDL statements, it first opens and drops the Books table.

	TInt error = OpenDb(aExistingBookFile);

	RETURN_ERROR(error);

	DropBooksTable();
	Close();

	CCoeEnv::Static()->FsSession().Delete(aExistingBookFile);
	return KErrNone;
	}

TInt CMusicDBMgr::AddElementL(CMusicInfoBean* aBean)
	{
	TInt err = KErrNone;
	if (aBean->getId() == -1)
		{
		TInt id = 10;
		err = CreateId(id);
		
		RETURN_ERROR(err);

		aBean->setId(id);
		}

	RDbTable table;
	err = table.Open(iBookDb, KInfoTable, table.EUpdatable);

	RETURN_ERROR(err);

	CDbColSet* booksColSet = table.ColSetL();
	CleanupStack::PushL(booksColSet);

	table.Reset();

	TRAP(err,
			table.InsertL();
	
			table.SetColL(booksColSet->ColNo(KIdCol), aBean->getId());
			table.SetColL(booksColSet->ColNo(KArtistCol),aBean->getArtist());
			table.SetColL(booksColSet->ColNo(KTitleCol),aBean->getTitle());
			table.SetColL(booksColSet->ColNo(KAblumCol),aBean->getAblum());
			table.SetColL(booksColSet->ColNo(KGenreCol),aBean->getGenre());
			table.SetColL(booksColSet->ColNo(KFilenameCol),aBean->getFileName());
			table.SetColL(booksColSet->ColNo(KFilefolderCol),aBean->getFileFolder());
	)
	;

	RETURN_ERROR(err);

	TRAP(err, table.PutL()); // Complete changes (the insertion)

	RETURN_ERROR(err);

	CleanupStack::PopAndDestroy(booksColSet);
	table.Close();

	return KErrNone;
	}

TInt CMusicDBMgr::AddElementsL(RPointerArray<CMusicInfoBean>* aList)
	{
	TInt err;
	for (TInt i=0; i<aList->Count(); i++)
		{
		err = AddElementL((*aList)[i]);
		RETURN_ERROR(err);
		}
	return KErrNone;
	}

TInt CMusicDBMgr::RemoveAllElements(TInt& aResultCount)
	{
	_LIT(KDeleteFrom, "DELETE FROM ");

	// Sql: DELETE FROM Books
	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KDeleteFrom);
	sqlStr.Append(KInfoTable);

	RDbUpdate updOp;
	TRequestStatus incStat(1);
	TInt updStat = updOp.Execute(iBookDb, sqlStr, EDbCompareFolded);
	while (updStat==KErrNone && incStat ==1)
		{
		updOp.Next(incStat); // Start async operation. It returns
		// immediately.
		User::WaitForRequest(incStat); // For simplicity wait completion here.
		}

	aResultCount = updOp.RowCount();
	updOp.Close();

	if (updStat!=KErrNone)
		return updStat; // System wide error code
	else
		return incStat.Int(); // KErrNone or system wide error code
	}

TInt CMusicDBMgr::RemoveElementByIdL(TInt aId, TInt& aResultCount)
	{
	_LIT(KDeleteFrom, "DELETE FROM ");
	_LIT(KDeleteWhere, " WHRER ");
	_LIT(KDeleteEqual, "=");

	// Sql: DELETE FROM Books
	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KDeleteFrom);
	sqlStr.Append(KInfoTable);
	sqlStr.Append(KDeleteWhere);
	sqlStr.Append(KIdCol);
	sqlStr.Append(KDeleteEqual);
	sqlStr.AppendNum(aId);

	RDbUpdate updOp;
	TRequestStatus incStat(1);
	TInt updStat = updOp.Execute(iBookDb, sqlStr, EDbCompareFolded);
	while (updStat==KErrNone && incStat ==1)
		{
		updOp.Next(incStat); // Start async operation. It returns
		// immediately.
		User::WaitForRequest(incStat); // For simplicity wait completion here.
		}

	aResultCount = updOp.RowCount();
	updOp.Close();

	if (updStat!=KErrNone)
		return updStat; // System wide error code
	else
		return incStat.Int(); // KErrNone or system wide error code
	}

RPointerArray<CMusicInfoBean>* CMusicDBMgr::GetAllElementsL()
	{
	TPtrC author, title;
	TBuf<KDescriptionMaxLength> description;

	RDbTable table;
	TInt err = table.Open(iBookDb, KInfoTable, table.EReadOnly);
	User::LeaveIfError(err);

	RPointerArray<CMusicInfoBean>* resultArray = new (ELeave)RPointerArray<CMusicInfoBean>;
	CleanupStack::PushL(resultArray);

	table.Reset();
	CDbColSet* colSet = table.ColSetL();
	CleanupStack::PushL(colSet);

	for (table.FirstL(); table.AtRow(); table.NextL())
		{
		description.Zero();

		table.GetL();

		//		author.Set(table.ColDes(colSet->ColNo(KBooksAuthorCol)));
		//		title.Set(table.ColDes(colSet->ColNo(KBooksTitleCol)));
		//
		//		TDbColNo descrColNo = colSet->ColNo(KBooksDescriptionCol);
		//		RDbColReadStream readStream; // A stream object for long columns
		//		readStream.OpenLC(table, descrColNo);
		//		readStream.ReadL(description, table.ColLength(descrColNo));
		//		readStream.Close();
		//		CleanupStack::Pop(); //readStream

		}
	CleanupStack::PopAndDestroy(colSet);
	CleanupStack::Pop(resultArray);
	table.Close();

	return resultArray;
	}

CMusicInfoBean* CMusicDBMgr::GetElementByIdL(TInt aId)
	{
	TPtrC author, title;
	TBuf<KDescriptionMaxLength> description;

	_LIT(KSelect, "SELECT ");
	_LIT(KFrom, "FROM");
	_LIT(KWhere, " WHERE ");
	_LIT(KLike, " LIKE '");
	_LIT(KOrderBy, "' ORDER BY ");
	_LIT(KDot, ", ");

	// Sql: SELECT Author, Title, Description FROM Books
	//      WHERE "aColumnName LIKE aSearchString"
	//      ORDER BY Title, Author
	TBuf<KCustomSqlMaxLength> sqlStr;
	//	sqlStr.Append(KSelect);
	//	sqlStr.Append(KBooksAuthorCol);
	//	sqlStr.Append(KDot);
	//	sqlStr.Append(KBooksTitleCol);
	//	sqlStr.Append(KDot);
	//	sqlStr.Append(KBooksDescriptionCol);
	//	sqlStr.Append(KFrom);
	//	sqlStr.Append(KInfoTable);
	//	sqlStr.Append(KWhere);
	//	sqlStr.Append(KOrderBy);
	//	sqlStr.Append(KBooksTitleCol);
	//	sqlStr.Append(KDot);
	//	sqlStr.Append(KBooksAuthorCol);

	CMusicInfoBean* resultArray = CMusicInfoBean::NewL();
	CleanupStack::PushL(resultArray);

	// Create a view on the database
	RDbView view;
	User::LeaveIfError(view.Prepare(iBookDb, TDbQuery(sqlStr), view.EReadOnly));
	User::LeaveIfError(view.EvaluateAll());

	CDbColSet* colSet = view.ColSetL();
	CleanupStack::PushL(colSet);

	// Append each result row to array
	for (view.FirstL(); view.AtRow(); view.NextL())
		{

		description.Zero();

		view.GetL();

		//		author.Set(view.ColDes(colSet->ColNo(KBooksAuthorCol)));
		//		title.Set(view.ColDes(colSet->ColNo(KBooksTitleCol)));
		//
		//		TDbColNo descrColNo = colSet->ColNo(KBooksDescriptionCol);
		//		RDbColReadStream readStream; // A stream object for long columns
		//		readStream.OpenLC(view, descrColNo);
		//		readStream.ReadL(description, view.ColLength(descrColNo));
		//		readStream.Close();
		//		CleanupStack::Pop(); //readStream

		}
	CleanupStack::PopAndDestroy(colSet);
	view.Close();
	CleanupStack::Pop(resultArray);

	return resultArray;
	}

TInt CMusicDBMgr::GetAllElementsL(RPointerArray<CMusicInfoBean>** resultArray)
	{
	RDbTable table;
	TInt err = table.Open(iBookDb, KInfoTable, table.EReadOnly);
	RETURN_ERROR(err);

	SAFE_DELETE(*resultArray);
	*resultArray = new (ELeave)RPointerArray<CMusicInfoBean>;
	CleanupStack::PushL(*resultArray);

	table.Reset();
	CDbColSet* colSet = table.ColSetL();
	CleanupStack::PushL(colSet);

	for (table.FirstL(); table.AtRow(); table.NextL())
		{

		table.GetL();

		CMusicInfoBean *bean = CMusicInfoBean::NewL();
//		bean->setArtistL(table.ColDes8(colSet->ColNo(KBooksAuthorCol)));
//		bean->setTitleL(table.ColDes8(colSet->ColNo(KBooksTitleCol)));
		
		bean->setId(table.ColInt(colSet->ColNo(KIdCol)));
		bean->setArtistL(table.ColDes8(colSet->ColNo(KArtistCol)));
		bean->setTitleL(table.ColDes8(colSet->ColNo(KTitleCol)));
		bean->setAblumL(table.ColDes8(colSet->ColNo(KAblumCol)));
		bean->setGenre(table.ColInt(colSet->ColNo(KGenreCol)));
		bean->setFileNameL(table.ColDes8(colSet->ColNo(KFilenameCol)));
		bean->setFileFolderL(table.ColDes8(colSet->ColNo(KFilefolderCol)));

		(*resultArray)->Append(bean);

		}
	CleanupStack::PopAndDestroy(colSet);
	CleanupStack::Pop(*resultArray);
	table.Close();

	return KErrNone;
	}

TInt CMusicDBMgr::GetElementByIdL(TInt aId, CMusicInfoBean* resultArray)
	{
	_LIT(KSelect, "SELECT ");
	_LIT(KFrom, "FROM");
	_LIT(KWhere, " WHERE ");
	_LIT(KEqual, "=");
	_LIT(KDot, ", ");

	// Sql: SELECT Author, Title, Description FROM Books
	//      WHERE "aColumnName LIKE aSearchString"
	//      ORDER BY Title, Author
	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KSelect);
	sqlStr.Append(KIdCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KArtistCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KTitleCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KAblumCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KGenreCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KFilenameCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KFilefolderCol);
	sqlStr.Append(KFrom);
	sqlStr.Append(KInfoTable);
	sqlStr.Append(KWhere);
	sqlStr.Append(KIdCol);
	sqlStr.Append(KEqual);
	sqlStr.AppendNum(aId);

	SAFE_DELETE(resultArray);
	resultArray = CMusicInfoBean::NewL();
	CleanupStack::PushL(resultArray);

	// Create a view on the database
	RDbView view;
	TRAPD(err,
			view.Prepare(iBookDb, TDbQuery(sqlStr), view.EReadOnly);
			view.EvaluateAll();
	)
	;
	if (err != KErrNone)
		{
		CleanupStack::Pop(); // resultArray
		return err;
		}

	CDbColSet* colSet = view.ColSetL();
	CleanupStack::PushL(colSet);

	// Append each result row to array
	for (view.FirstL(); view.AtRow(); view.NextL())
		{

		view.GetL();

		resultArray->setId(view.ColInt(colSet->ColNo(KIdCol)));
		resultArray->setArtistL(view.ColDes8(colSet->ColNo(KArtistCol)));
		resultArray->setTitleL(view.ColDes8(colSet->ColNo(KTitleCol)));
		resultArray->setAblumL(view.ColDes8(colSet->ColNo(KAblumCol)));
		resultArray->setGenre(view.ColInt(colSet->ColNo(KGenreCol)));
		resultArray->setFileNameL(view.ColDes8(colSet->ColNo(KFilenameCol)));
		resultArray->setFileFolderL(view.ColDes8(colSet->ColNo(KFilefolderCol)));

		}
	CleanupStack::PopAndDestroy(colSet);
	view.Close();
	CleanupStack::Pop(resultArray);

	return KErrNone;
	}

TInt CMusicDBMgr::GetElementsByIdL(TInt aId,
		RPointerArray<CMusicInfoBean>* resultArray)
	{
	_LIT(KSelect, "SELECT ");
	_LIT(KFrom, "FROM");
	_LIT(KWhere, " WHERE ");
	_LIT(KEqual, "=");
	_LIT(KDot, ", ");

	// Sql: SELECT Author, Title, Description FROM Books
	//      WHERE "aColumnName LIKE aSearchString"
	//      ORDER BY Title, Author
	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KSelect);
	sqlStr.Append(KIdCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KArtistCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KTitleCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KAblumCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KGenreCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KFilenameCol);
	sqlStr.Append(KDot);
	sqlStr.Append(KFilefolderCol);
	sqlStr.Append(KFrom);
	sqlStr.Append(KInfoTable);
	sqlStr.Append(KWhere);
	sqlStr.Append(KIdCol);
	sqlStr.Append(KEqual);
	sqlStr.AppendNum(aId);

	SAFE_DELETE(resultArray);
	resultArray = new (ELeave)RPointerArray<CMusicInfoBean>;
	CleanupStack::PushL(resultArray);

	// Create a view on the database
	RDbView view;
	TRAPD(err,
			view.Prepare(iBookDb, TDbQuery(sqlStr), view.EReadOnly);
			view.EvaluateAll();
	)
	;
	if (err != KErrNone)
		{
		CleanupStack::Pop(); // resultArray
		return err;
		}

	CDbColSet* colSet = view.ColSetL();
	CleanupStack::PushL(colSet);

	// Append each result row to array
	for (view.FirstL(); view.AtRow(); view.NextL())
		{

		view.GetL();

		CMusicInfoBean *bean = CMusicInfoBean::NewL();
		bean->setId(view.ColInt(colSet->ColNo(KIdCol)));
		bean->setArtistL(view.ColDes8(colSet->ColNo(KArtistCol)));
		bean->setTitleL(view.ColDes8(colSet->ColNo(KTitleCol)));
		bean->setAblumL(view.ColDes8(colSet->ColNo(KAblumCol)));
		bean->setGenre(view.ColInt(colSet->ColNo(KGenreCol)));
		bean->setFileNameL(view.ColDes8(colSet->ColNo(KFilenameCol)));
		bean->setFileFolderL(view.ColDes8(colSet->ColNo(KFilefolderCol)));

		resultArray->Append(bean);

		}
	CleanupStack::PopAndDestroy(colSet);
	view.Close();
	CleanupStack::Pop(resultArray);

	return KErrNone;
	}

TInt CMusicDBMgr::ModifyElementByIdL(TInt aId, CMusicInfoBean* aBean)
	{
	_LIT(KUpdateSql, "update %s set %s=%d,%s=%s,%s=%s,%s=%s,%s=%d,%s=%s,%s=%s where %s=%d");
	
	TBuf<KCustomSqlMaxLength> sqlStr;

	sqlStr.Format(KUpdateSql, KInfoTable, KIdCol, aBean->getId(), KArtistCol,
			aBean->getArtist(), KTitleCol, aBean->getTitle(), KAblumCol,
			aBean->getAblum(), KGenreCol, aBean->getGenre(), KFilenameCol,
			aBean->getFileName(), KFilefolderCol, aBean->getFileFolder(),
			KIdCol, aId);

	return iBookDb.Execute(sqlStr);
	}

TInt CMusicDBMgr::Close()
	{
	iBookDb.Close();
	SAFE_DELETE(iFileStore);
	iOpen = EFalse;
	return KErrNone;
	}

void CMusicDBMgr::CreateBooksTableL()
	{
	// Specify columns for Books table
	TDbCol idCol(KIdCol, EDbColInt32);
	TDbCol artistCol(	KArtistCol, EDbColText8, KMaxName );
	TDbCol titleCol(	KTitleCol, 	EDbColText8,	KMaxName);
	TDbCol ablumCol(	KAblumCol, 	EDbColText8,	KMaxName);
	TDbCol genreCol(	KGenreCol, 	EDbColInt32);
	TDbCol filenameCol(	KFilenameCol, 	EDbColText8,KMaxName);
	TDbCol filefolderCol(KFilefolderCol,EDbColText8,KMaxName);
//	 TDbCol authorCol(KBooksAuthorCol, EDbColText);   // Using default length
//	 TDbCol titleCol(KBooksTitleCol, EDbColText, KTitleMaxLength);
//	 titleCol.iAttributes = TDbCol::ENotNull;
//	 TDbCol descriptionCol(KBooksDescriptionCol, EDbColLongText); // Stream Data
	 
	// Add the columns to column set
	CDbColSet* bookColSet = CDbColSet::NewLC();
	bookColSet->AddL(idCol);
	bookColSet->AddL(artistCol);
	bookColSet->AddL(titleCol);
	bookColSet->AddL(ablumCol);
	bookColSet->AddL(genreCol);
	bookColSet->AddL(filenameCol);
	bookColSet->AddL(filefolderCol);
//	bookColSet->AddL(authorCol);
//	bookColSet->AddL(titleCol);
//	bookColSet->AddL(descriptionCol);

	// Create the Books table
	User::LeaveIfError(iBookDb.CreateTable(KInfoTable, *bookColSet));
	CleanupStack::PopAndDestroy(bookColSet);
	}

void CMusicDBMgr::CreateBooksIndexL()
    {
    // Create index consisting of two columns
//    TDbKeyCol idCol(KIdCol);
//    
//    CDbKey* index = CDbKey::NewLC();   // create index key set
//    index->AddL(idCol);
//    User::LeaveIfError(iBookDb.CreateIndex(
//        KBooksIndexName, KInfoTable, *index));
//    CleanupStack::PopAndDestroy(index);
    TDbKeyCol authorCol(KBooksAuthorCol);
       TDbKeyCol titleCol(KBooksTitleCol);

       CDbKey* index = CDbKey::NewLC();   // create index key set
       index->AddL(titleCol);
       index->AddL(authorCol);
       User::LeaveIfError(iBookDb.CreateIndex(
           KBooksIndexName, KBooksTable, *index));
       CleanupStack::PopAndDestroy(index);
    }

void CMusicDBMgr::DropBooksTable()
	{
	_LIT(KDropTable, "DROP TABLE ");

	// Sql: DROP TABLE Books
	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KDropTable);
	sqlStr.Append(KInfoTable);

	RDbIncremental incOp;
	TInt incStep = 0xFFFF;
	// Initialise Execution
	TInt incStat = incOp.Execute(iBookDb, sqlStr, incStep);
	while (incStep>0 && incStat==KErrNone)
		{
		incStat = incOp.Next(incStep); // Do the work
		}
	incOp.Close();
	}

TInt CMusicDBMgr::CreateId(TInt& aId)
	{
//	_LIT(KSelectMaxId, "select max(id) id from ");
	_LIT(KSelectMaxId, "SELECT id FROM ");
	_LIT(KSelectGroup, " ORDER BY id DESC");

	TBuf<KCustomSqlMaxLength> sqlStr;
	sqlStr.Append(KSelectMaxId);
	sqlStr.Append(KInfoTable);
	sqlStr.Append(KSelectGroup);

	RDbView view;
	TRAPD(err,
			view.Prepare(iBookDb, TDbQuery(sqlStr), view.EReadOnly);
			view.EvaluateAll();
	)
	;
	if (err != KErrNone)
		{
		return err;
		}

	CDbColSet* colSet = view.ColSetL();
	CleanupStack::PushL(colSet);

	// Append each result row to array
//	view.FirstL(); 
	if (view.FirstL())
		{
		view.GetL();
		aId = view.ColInt(colSet->ColNo(KIdCol));
		aId++;
		}
	CleanupStack::PopAndDestroy(colSet);
	view.Close();

	return KErrNone;
	}