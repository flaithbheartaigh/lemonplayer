#
# ==============================================================================
#  Name        : bitmaps.mk
#  Part of     : Graphics
#  Interface   :
#  Description :
#  Version     :
#
#  Copyright (c) 2006 Nokia Corporation.
#  This material, including documentation and any related
#  computer programs, is protected by copyright controlled by
#  Nokia Corporation.
# ==============================================================================
#

ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

TARGETDIR=$(ZDIR)\private\A00001F8
ICONTARGETFILENAME=$(TARGETDIR)\GraphicsAppImages.mbm

HEADERDIR=$(EPOCROOT)epoc32\include
HEADERFILENAME=$(HEADERDIR)\GraphicsAppImages.mbg

do_nothing :
		@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE :
		mifconv $(ICONTARGETFILENAME) /h$(HEADERFILENAME) \
            /c12 ..\gfx\image1.bmp \
            /c12,1 ..\gfx\image2.bmp \
            /c16,8 ..\gfx\star.svg

FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
		@echo $(HEADERFILENAME)&& \
		@echo $(ICONTARGETFILENAME)

FINAL : do_nothing
