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

# For the icons used by the application code (engine in this case)
TARGETDIR_PRIVATE=$(ZDIR)\private\2003717D
#TARGETDIR_PRIVATE=$(ZDIR)\resource\apps
ICONTARGETFILENAME_PRIVATE=$(TARGETDIR_PRIVATE)\ScheduleKiller.mbm
IMAGETARGETFILENAME_PRIVATE=$(TARGETDIR_PRIVATE)\ScheduleKiller.mif

# Headers for both
HEADERDIR=$(EPOCROOT)epoc32\include
HEADERFILENAME_PRIVATE=$(HEADERDIR)\ScheduleKiller.mbg

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
		
	mifconv $(IMAGETARGETFILENAME_PRIVATE)  \
		 /H$(HEADERFILENAME_PRIVATE)  \
		 /c24 ..\gfx\logo.bmp  \
		 /c32,8 ..\gfx\exit.svg  \
		 ..\gfx\remove.svg  \
		 ..\gfx\add.svg  \
		 ..\gfx\rules.svg  \
		 ..\gfx\about.svg  \
		 ..\gfx\fav.svg  \
		 ..\gfx\shutdown.svg
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES : 
	@echo $(ICONTARGETFILENAME)
    
FINAL : do_nothing
