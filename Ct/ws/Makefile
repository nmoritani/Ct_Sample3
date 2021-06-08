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

# BLOCK_NAME	= Ct

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
CSRC			=
ASRC			=
CPPSRC		= $(wildcard *.cpp)


# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC			= Ct.cfg

# "SUBDIRS" specifies directory list that executes make command recursively.
#
SUBDIRS			= 

# Don't modify. It includes common make file here.
#
include		$(TOP_DIR)/mk/env.mk

clean-subs:


