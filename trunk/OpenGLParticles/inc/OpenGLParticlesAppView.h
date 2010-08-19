/*
 ============================================================================
 Name		: OpenGLParticlesAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __OPENGLPARTICLESAPPVIEW_h__
#define __OPENGLPARTICLESAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "OpenGLParticlesAppContainer.h"

// CLASS DECLARATION
class COpenGLParticlesAppView : public CAknView
	{
public:
	// Constructors and destructor
	~COpenGLParticlesAppView();
	static COpenGLParticlesAppView* NewL();
	static COpenGLParticlesAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	COpenGLParticlesAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	COpenGLParticlesAppContainer * iContainer;
	};

#endif // __OPENGLPARTICLESAPPVIEW_h__
// End of File
