/*
 ============================================================================
 Name		: TangramAnimation.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramAnimation declaration
 ============================================================================
 */

#ifndef TANGRAMANIMATION_H
#define TANGRAMANIMATION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bitstd.h>

#include "ImageArrayReader.h"

// CLASS DECLARATION
class CImageArrayReader;
class CStaticAnimation;

/**
 *  CTangramAnimation
 * 
 */
class CTangramAnimation : 	public CBase,
							public MImageArrayNotify
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CTangramAnimation();

	/**
	 * Two-phased constructor.
	 */
	static CTangramAnimation* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CTangramAnimation* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CTangramAnimation();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	virtual void ConvertComplete();
	
public:
	void Init();	
	TBool Update();
	void UpdateDisplay(CFbsBitGc& gc);	
	
private:
	CImageArrayReader* iBitmapArray;
	CStaticAnimation*  iAnimation;

	};

#endif // TANGRAMANIMATION_H
