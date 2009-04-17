# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LemonMicro
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LemonMicro
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : LemonMicro_0xEFE1B7CE.hlp
LemonMicro_0xEFE1B7CE.hlp : LemonMicro.xml LemonMicro.cshlp Custom.xml
	cshlpcmp LemonMicro.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy LemonMicro_0xEFE1B7CE.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del LemonMicro_0xEFE1B7CE.hlp
	del LemonMicro_0xEFE1B7CE.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo LemonMicro_0xEFE1B7CE.hlp

FINAL : do_nothing
