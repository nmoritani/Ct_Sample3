#
#	Paprika ( Panasonic Application Platform and
#	                      Realtime-system Innovating Kernel Architecture )
#	Copyright (C) 2000-2000 by Matsushita Electric Industrial Co., Ltd.
#
#	GNU make only.
#
#-----------------------------------------------------------------------------

BLOCK_NAME	= Gui

# "TOP_DIR" specifies relative path to Paprika root directory.
#
TOP_DIR		= $(ARCH_DIR)

include		$(TOP_DIR)/mk/cond.mk
-include	./Defs.mk

# "OBJ_DIR" specifies directory where object file is generated in.
#
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)


# "RELEASE" specifies type of release object. You can choose either
# "lib" or "ex". If you specify "lib", it generates a TGT_NAME archive
# file in release/ directory that collects all object file in $(OBJ_DIR).
# Nothing is specified, no release objects are generated.
#
RELEASE		= lib
TGT_NAME	= ../../lib$(BLOCK_NAME)

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS += -I./line
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Sys/Sys/PF/VENUS10/DD/Mdmac
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Sys/AsciiDebug

CSRC			= $(wildcard *.c)

# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC		= GUI.cfg


SUBDIRS     = Ct line gdi string dma TimeStamp

## Common Rules
include     $(TOP_DIR)/mk/env.mk
