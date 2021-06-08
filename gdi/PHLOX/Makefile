#
#	Paprika ( Panasonic Application Platform and
#	                      Realtime-system Innovating Kernel Architecture )
#	Copyright (C) 2000-2000 by Matsushita Electric Industrial Co., Ltd.
#
#	$Id: Makefile,v 1.6 2005/03/25 11:32:22 chikaishi Exp $
#
#	GNU make only.
#
#-----------------------------------------------------------------------------

PHLOX_LIB	= *.a

#MD			= $(DOSTOOL_DIR)\mkdir.bat
#CP			= $(DOSTOOL_DIR)\cp.bat
#RMDIR		= $(DOSTOOL_DIR)\rmdir.bat
#RM			= $(DOSTOOL_DIR)\rm.bat
MD			= mkdir -p
CP			= cp -u
RMDIR		= rm -f -r
RM			= rm -f

$(BUILD_DIR)/libOpenVG.a : Lib/$(PHLOX_LIB)
	$(CP) Lib/$(PHLOX_LIB) $(BUILD_DIR)

clean:
	$(RM) $(OBJ_DIR)/../libDMPallocator.a
	$(RM) $(OBJ_DIR)/../libDMPdmpNative.a
	$(RM) $(OBJ_DIR)/../libDMPeglNative.a
	$(RM) $(OBJ_DIR)/../libDMPOsWrapper.a
	$(RM) $(OBJ_DIR)/../libDMPrenderman.a
	$(RM) $(OBJ_DIR)/../libEGL.a
	$(RM) $(OBJ_DIR)/../libGLESv1_CM.a
	$(RM) $(OBJ_DIR)/../libOpenVG.a

clean-subs:

