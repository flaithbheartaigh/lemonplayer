# ============================================================================
#  Name	 : build_help_2x.mk
#  Part of  : LemonTangram
# ============================================================================
#  Name	 : build_help_2x.mk
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

makmake :
	cshlpcmp LemonTangram.cshlp

ifeq (WINS, $(findstring WINS, $(PLATFORM)))
	copy LemonTangram.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\system\help
endif

CLEAN :
	del LemonTangram.hlp
	
BLD : 
	cshlpcmp LemonTangram.cshlp
	
ifeq (WINS, $(findstring WINS, $(PLATFORM)))
	copy ..\help\HelpExample.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\system\help
endif

freeze lib cleanlib final resource savespace releasables :
