#ifndef LEMONMENUDEF_H_
#define LEMONMENUDEF_H_

_LIT(KMenuDomTagMenu,	"menu");
_LIT(KMenuDomTagItem,	"item");

_LIT(KMenuAttrParent,	"parent");
_LIT(KMenuAttrText,		"text");
_LIT(KMenuAttrId,		"id");
_LIT(KMenuAttrCommand,	"command");


enum TMenuTag
	{
	EMenuTagNone = 0,
	EMenuTagMenu,
	EMenuTagItem,
	};

#endif /*LEMONMENUDEF_H_*/
