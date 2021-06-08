#
#	Paprika ( Panasonic Application Platform and
#	                      Realtime-system Innovating Kernel Architecture )
#	Copyright (C) 2000-2000 by Matsushita Electric Industrial Co., Ltd.
#
#	$Id: makefile,v 1.17 2008/05/30 08:04:17 mi_tanaka Exp $
#
#	GNU make only.
#
#-----------------------------------------------------------------------------

# BLOCK_NAME	= Gui

# "TOP_DIR" specifies relative path to Paprika root directory.
#
TOP_DIR		= $(ARCH_DIR)

## Block Common
include     $(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/Defs.mk

# "OBJ_DIR" specifies directory where object file is generated in.
#
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)


# "RELEASE" specifies type of release object. You can choose either
# "lib" or "ex". If you specify "lib", it generates a TGT_NAME archive
# file in release/ directory that collects all object file in $(OBJ_DIR).
# Nothing is specified, no release objects are generated.
#
# RELEASE		= lib
# TGT_NAME	= ../../../../lib$(BLOCK_NAME)

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS		+= -I./includes -I../../include -I../../openvg/include
ifeq ($(strip $(TARGET_PF)),V8FHD)
LCFLAGS		+= -I../../openvg/GV210/GE-lib/include
else
LCFLAGS		+= -I../../openvg/PHLOX/include
endif

LASFLAGS	=

# "CSRC" and "ASRC" specify C and Assembler source file name.
CSRC		= DTmanager.c  DTversion.c BDF_Raster.c DcwHebrew.c DIF_Raster.c \
			   DCW_FdlGrade.c DCW_FdlRaster.c \
			   DcwBidiClassData.c DcwBidiMirroring.c \
			   DTdigitype.c DTplatform.c DcwLayout.c DTmemory.c DcwUnicodeRange.c DcwBiDi.c DcwCache.c \
			   Dcw.c Digitype_std.c Digitype_oul.c DcwLatin.c DcwVietnamese.c DcwThai.c DcwArabic.c \
			   DcwDevanagari.c Devanagari_render.c indic_common.c indic_find_syllable.c \
			   ovgDcw.c ovgDcwFdlRaster.c


# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC		=


# "SUBDIRS" specifies directory list that executes make command recursively.
#
SUBDIRS		= data chgdata


## Common Rules
include		$(TOP_DIR)/mk/env.mk
