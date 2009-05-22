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

MAKMAKE : LemonTangram_0xEAE107BA.hlp
LemonTangram_0xEAE107BA.hlp : LemonTangram.xml LemonTangram.cshlp Custom.xml
	cshlpcmp LemonTangram.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy LemonTangram_0xEAE107BA.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del LemonTangram_0xEAE107BA.hlp
	del LemonTangram_0xEAE107BA.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo LemonTangram_0xEAE107BA.hlp

FINAL : do_nothing
