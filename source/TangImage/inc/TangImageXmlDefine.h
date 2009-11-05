#ifndef TANGIMAGEXMLDEFINE_H_
#define TANGIMAGEXMLDEFINE_H_

_LIT(KImageDataDomTagImage,"image");
_LIT(KImageDataDomTagImg,	"img");

_LIT(KImageDataAttrX,		"x");
_LIT(KImageDataAttrY,		"y");
_LIT(KImageDataAttrDegree,	"degree");
_LIT(KImageDataAttrIndex,	"index");
_LIT(KImageDataAttrFlip,	"flip");

enum TImageDataTag
	{
	EImageDataTagNone = 0,
	EImageDataTagImage,
	EImageDataTagImg,
	};

#endif /*TANGIMAGEXMLDEFINE_H_*/
