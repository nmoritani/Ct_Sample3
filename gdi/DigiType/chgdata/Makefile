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

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS		= 
LASFLAGS	=

# "CSRC" and "ASRC" specify C and Assembler source file name.
CSRC		+= UCS-CNS-ARABIC.c UCS-CNS-THAI.c Ucs-GB-Hei-W4-Part.c Ucs-Big5-Hei-W4-Part.c Ucs-Hangul-Hei-W4-Part.c \
			   UCS-CNS-HINDI.c \
			   UCS-JIS-HEI-W4.c

# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC		=

# "SUBDIRS" specifies directory list that executes make command recursively.
#
SUBDIRS		=

include		$(TOP_DIR)/mk/env.mk
