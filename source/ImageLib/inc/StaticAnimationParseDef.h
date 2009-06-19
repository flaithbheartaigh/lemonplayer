#ifndef STATICANIMATIONPARSEDEF_
#define STATICANIMATIONPARSEDEF_

_LIT(KStaticAniDomTagImage,	"image");
_LIT(KStaticAniDomTagImg,	"img");
_LIT(KStaticAniDomTagAnimation,	"animation");
_LIT(KStaticAniDomTagAction,"action");
_LIT(KStaticAniDomTagFrame,	"frame");
_LIT(KStaticAniDomTagSprite,"sprite");

_LIT(KStaticAniAttrNumber,	"number");
_LIT(KStaticAniAttrIndex,	"index");
_LIT(KStaticAniAttrDegree,	"degree");
_LIT(KStaticAniAttrX,		"x");
_LIT(KStaticAniAttrY,		"y");

enum TStaticAniTag
	{
	EStaticAniTagNone = 0,
	EStaticAniTagImage,
	EStaticAniTagImg,
	EStaticAniTagAnimation,
	EStaticAniTagAction,
	EStaticAniTagFrame,
	EStaticAniTagSprite
	};

#endif /*STATICANIMATIONPARSEDEF_*/
