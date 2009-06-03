# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LemonTangram
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LemonTangram
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : LemonTangram.hlp
LemonTangram.hlp : LemonTangram.xml LemonTangram.cshlp Custom.xml
	cshlpcmp LemonTangram.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy LemonTangram.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del LemonTangram.hlp

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo LemonTangram.hlp

FINAL : do_nothing
