# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Tangram3D
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Tangram3D
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : Tangram3D_0xE5FE764F.hlp
Tangram3D_0xE5FE764F.hlp : Tangram3D.xml Tangram3D.cshlp Custom.xml
	cshlpcmp Tangram3D.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy Tangram3D_0xE5FE764F.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del Tangram3D_0xE5FE764F.hlp
	del Tangram3D_0xE5FE764F.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo Tangram3D_0xE5FE764F.hlp

FINAL : do_nothing
