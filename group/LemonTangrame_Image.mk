#=====================================================================
# Name : lemontangram.mk
#
# Description:
#
#
#=====================================================================
#
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif
# -------------------------------------------------------------------
# TODO: Configure these.
# -------------------------------------------------------------------

# For the menu icon
TARGETDIR=$(ZDIR)\RESOURCE\APPS
ICONTARGETFILENAME=$(TARGETDIR)\lemontangram_aif.mif

# For the icons used by the application code (engine in this case)
TARGETDIR_PRIVATE=$(ZDIR)\private\EAE107BA
ICONTARGETFILENAME_PRIVATE=$(TARGETDIR_PRIVATE)\lemontangram.mbm

# Headers for both
HEADERDIR=$(EPOCROOT)epoc32\include
HEADERFILENAME_PRIVATE=$(HEADERDIR)\lemontangram.mbg

ICONDIR=..\aif

do_nothing : 
	@rem do_nothing
		
MAKMAKE : do_nothing

BLD : do_nothing
		
CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing

# -------------------------------------------------------------------
# TODO: Configure these.
#
# NOTE 1: DO NOT DEFINE MASK FILE NAMES! They are included
# automatically by MifConv if the mask depth is defined.
# -------------------------------------------------------------------

# The icons privately used by the application and the menu icon are built separately:
RESOURCE :
	mifconv $(ICONTARGETFILENAME_PRIVATE) /h$(HEADERFILENAME_PRIVATE) \
	/c16 ..\gfx\log.bmp \
	/c16 ..\gfx\bottomsvg.svg \

	mifconv $(ICONTARGETFILENAME) \
		/c32 ..\gfx\LTIcon.svg
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES : 
	@echo $(ICONTARGETFILENAME)
    
FINAL : do_nothing
