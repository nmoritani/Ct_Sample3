#
#	Paprika ( Panasonic Application Platform and
#	                      Realtime-system Innovating Kernel Architecture )
#	Copyright (C) 2000-2000 by Matsushita Electric Industrial Co., Ltd.
#
#	GNU make only.
#
#-----------------------------------------------------------------------------

# "TOP_DIR" specifies relative path to Paprika root directory.
#
TOP_DIR		= $(ARCH_DIR)

## Block Common
include     $(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/Defs.mk

# "OBJ_DIR" specifies directory where object file is generated in.
#
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)

# "CSRC" and "ASRC" and "CPPSRC"specify C and Assembler source file name.
#
CPPSRC		= $(wildcard *.cpp)

SUBDIRS     = Window tk ws

ifeq ($(strip $(GUI_DBG_TSK)), YES)
SUBDIRS     += dbg
endif

## Common Rules
include     $(TOP_DIR)/mk/env.mk
